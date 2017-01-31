#ifndef __LOG__H__
#define __LOG__H__

int libcommon_init_log(void);
int libcommon_change_log_path( char * full_path);
void _write_log(const char * filename, const char * function, int line, const char * format, ...);

#define write_log(...)                                                        \
	do {                                                                      \
		_write_log(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);            \
	} while(0)

/*
 *
 * Write simple log
 *
 */

#define write_log_zero(value_to_check, ...)                                   \
	if(value_to_check < 0){                                                   \
		write_log(__VA_ARGS__);                                               \
	}

#define write_log_null(value_to_check, ...)                                   \
	if(value_to_check == NULL){                                               \
		write_log(__VA_ARGS__);                                               \
	}

#define write_log_snprintf(value_to_check, text_length, ...)                  \
	if(value_to_check > (size -1)){                                           \
		write_log(__VA_ARGS__);                                               \
	}

#define write_log_pthread(value_to_check, ...)                                \
	if(value_to_check != 0){                                                  \
		write_log(__VA_ARGS__);                                               \
	}

#endif
