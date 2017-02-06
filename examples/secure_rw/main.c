#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "secure_rw.h"
#include "log.h"

int main( void){
	int ret;
	int fd;
	uint8_t data[256];
	uint8_t data_read[256];

	//Set data tab
	memset( data, 0x20, sizeof(data));

	//Set some different value
	data[42]= 75;
	data[68]= 25;
	data[123]= 95;

	printf( "Start Test secure_rw\n");
	ret = libcommon_init_log();
	if( ret  < 0){
		printf("[%s line:%d]Error libcommon_init_log fail, return: %d\n", __FILE__, __LINE__,ret);
		return -1;
	}

	fd = open( "/tmp/test_file_secure_rw", O_RDWR | O_CREAT, 0644);
	common_die_negative( fd, -2, "Error: open file fail, return: %d, errno: %d (%s)", fd, errno, strerror(errno));

	ret = secure_write( fd, data, sizeof(data));
	if( ret < 0){
		//close file
		close(fd);
	}
	common_die_negative(ret, -3, "Error: secure_write fail, return: %d", ret);

	//Move the file offset to the start of the file
	ret = lseek( fd, 0, SEEK_SET);
	common_die_negative( ret, -4, "Error: lseek fail, return: %d, errno: %d (%s)", ret, errno, strerror(errno));

	ret = secure_read( fd, data_read, sizeof(data_read));
	if( ret < 0){
		//close file
		close(fd);
	}
	common_die_negative(ret, -5, "Error: secure_read fail, return: %d", ret);

	if( memcmp( data, data_read, sizeof(data)) == 0){
		printf( "data[] and data_read[] are the same: SUCCESS\n");
	}else{
		printf( "data[] and data_read[] are NOT the same: FAIL\n");
	}

	close(fd);
	return 0;
}
