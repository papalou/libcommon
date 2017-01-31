#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "log.h"
#include "log.private.h"

#define _GNU_SOURCE
#include <errno.h>
extern char * program_invocation_short_name;

struct{
	bool is_initialized;
	char log_path[LOG_FILE_PATH_MAX_LENGTH];
	pthread_mutex_t mutex;
	bool use_color;
} g_libcommon_log = {
	.is_initialized = false,
	.mutex = PTHREAD_MUTEX_INITIALIZER,
	.use_color = false,
};

void _write_log(const char * filename, const char * function, int line, const char * format, ...){
	int ret;
	struct timeval tv;
	struct tm * ptm;
	char tmp_time_string[64];
	char time_string[64];
	va_list args;
	FILE * log_file_fd;
	char log_va_list_buffer[MAX_LOG_LENGTH];

	char full_log_message[MAX_LOG_LENGTH];

	if(g_libcommon_log.is_initialized == false){
		printf("%s: %s():l%d: WARNING, try to use log uninitialized, initialized with default value...\n",__FILE__,__FUNCTION__,__LINE__);
		ret = libcommon_init_log();
		if(ret < 0){
			printf("%s: %s():l%d: ERROR: Log initialiation fail, return: %d\n",__FILE__,__FUNCTION__,__LINE__, ret);
			return;
		}
	}

	/*
	 * Get va_args into log_va_list_buffer
	 */
	va_start( args,format);
	vsnprintf( log_va_list_buffer, sizeof(log_va_list_buffer), format, args);
	va_end( args);

	/*
	 * make string from time
	 */
	ret = gettimeofday( &tv, NULL);
	if( ret < 0) {
		printf( "Error gettimeofday return %d\n", ret);
	}

	ptm = localtime( &tv.tv_sec);
	ret = strftime( tmp_time_string, sizeof(tmp_time_string), "%Y-%m-%d %H:%M:%S", ptm);
	if( ret == 0) {
		printf( "Error strftime return %d\n", (int) ret);
	}

	ret = snprintf( time_string, sizeof( time_string), "%s.%03ld", tmp_time_string, (tv.tv_usec/1000));
	if( ret < 0) {
		printf( "Error snprintf return %d\n", ret);
	}

	if( g_libcommon_log.use_color == true ){
		ret = snprintf( full_log_message, MAX_LOG_LENGTH, " %s "GREEN" %-13s [%d:%d]"NORMAL" ["BLACKBOLD"%s:%d:%s"NORMAL"] "REDBOLD"%s"NORMAL"\n", time_string, program_invocation_short_name, getpid(),(int)syscall( SYS_gettid), filename, line, function, log_va_list_buffer);
	}else{
		ret = snprintf( full_log_message, MAX_LOG_LENGTH, "%s %-13s [%d:%d] [%s:%d:%s] %s\n", time_string, program_invocation_short_name,getpid(),(int)syscall( SYS_gettid), filename, line, function, log_va_list_buffer);
	}
	if(ret >= MAX_LOG_LENGTH){
		printf("WARNING: Log message is to long for the buffer, size: %d >= MAX_LOG_LENGTH: %d", ret, MAX_LOG_LENGTH);
	}
	/*
	 * Print log on console
	 */
	printf("%s", full_log_message);

	/*
	 * Write log in file
	 */
	pthread_mutex_lock(&g_libcommon_log.mutex);

	log_file_fd = fopen( g_libcommon_log.log_path, "a");
	if(log_file_fd == NULL){
		printf("Error: fopen log file '%s' fail, error: %s ", g_libcommon_log.log_path, strerror(errno));
		pthread_mutex_unlock(&g_libcommon_log.mutex);
		return;
	}

	ret = fwrite(full_log_message, sizeof(char), sizeof(full_log_message), log_file_fd);

	fclose(log_file_fd);

	pthread_mutex_unlock(&g_libcommon_log.mutex);

	return;
}

int libcommon_init_log(void){
	int ret;

	ret = snprintf(g_libcommon_log.log_path, sizeof(g_libcommon_log.log_path), "%s%s_%s", DEFAULT_LOG_FOLDER, program_invocation_short_name, DEFAULT_LOG_FILE_NAME);
	if((unsigned)ret >= sizeof(g_libcommon_log.log_path)){
		printf("%s: %s():l%d: WARNING: log file path might be truncated, please check!!!\n",__FILE__,__FUNCTION__,__LINE__);
	}

	g_libcommon_log.is_initialized = true;

	write_log("Init log, log file -> %s", g_libcommon_log.log_path);
	return 0;
}

int libcommon_change_log_path( char * full_path){
	int ret;

	if(g_libcommon_log.is_initialized == false){
		printf("%s: %s():l%d: WARNING, try to use log uninitialized, initialized with default value...\n",__FILE__,__FUNCTION__,__LINE__);
		ret = libcommon_init_log();
		if(ret < 0){
			printf("%s: %s():l%d: ERROR: Log initialiation fail, return: %d\n",__FILE__,__FUNCTION__,__LINE__, ret);
			return -1;
		}
	}

	common_die_null( full_path, -2, "Error full_path is null");

	ret = snprintf(g_libcommon_log.log_path, sizeof(g_libcommon_log.log_path), "%s",  full_path);
	if((unsigned)ret >= sizeof(g_libcommon_log.log_path)){
		printf("%s: %s():l%d: WARNING: log file path might be truncated, please check!!!\n",__FILE__,__FUNCTION__,__LINE__);
	}

	write_log("Change log path, new path -> %s\n", g_libcommon_log.log_path);
	return 0;
}

int libcommon_set_color_log( bool value){
	int ret;

	if(g_libcommon_log.is_initialized == false){
		printf("%s: %s():l%d: WARNING, try to use log uninitialized, initialized with default value...\n",__FILE__,__FUNCTION__,__LINE__);
		ret = libcommon_init_log();
		if(ret < 0){
			printf("%s: %s():l%d: ERROR: Log initialiation fail, return: %d\n",__FILE__,__FUNCTION__,__LINE__, ret);
			return -1;
		}
	}

	g_libcommon_log.use_color = value;

	write_log("Set log color: %s", value ? "ON" : "OFF");
	return 0;
}
