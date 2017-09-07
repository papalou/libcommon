#ifndef __LOG__H__
#define __LOG__H__

//Needed to use this header file with C++ source code
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

int libcommon_init_log(void);
int libcommon_change_log_path( char * full_path);
int libcommon_set_color_log( bool value);

// --- LOG ---
//#define write_log(...)
//#define write_log_negative_or_zero(value_to_check, ...)
//#define write_log_negative(value_to_check, ...)
//#define write_log_zero(value_to_check, ...)
//#define write_log_not_zero(value_to_check, ...)
//#define write_log_positive(value_to_check, ...)
//#define write_log_positive_or_zero(value_to_check, ...)
//#define write_log_null(value_to_check, ...)
//#define write_log_not_null(value_to_check, ...)
//#define write_log_true(value_to_check, ...)
//#define write_log_false(value_to_check, ...)
//#define write_log_equal(value_to_check_1, value_to_check_2, ...)
//#define write_log_not_equal(value_to_check_1, value_to_check_2, ...)
//#define write_log_superior(value_to_check_1, value_to_check_2, ...)
//#define write_log_inferior(value_to_check_1, value_to_check_2, ...)
//#define write_log_superior_or_equal(value_to_check_1, value_to_check_2, ...)
//#define write_log_inferior_or_equal(value_to_check_1, value_to_check_2, ...)

// --- Common die ---
//#define common_die(return_value, ...)
//#define common_die_negative_or_zero(value_to_check, return_value, ...)
//#define common_die_negative(value_to_check, return_value, ...)
//#define common_die_zero(value_to_check, return_value, ...)
//#define common_die_not_zero(value_to_check, return_value, ...)
//#define common_die_positive(value_to_check, return_value, ...)
//#define common_die_positive_or_zero(value_to_check, return_value, ...)
//#define common_die_null(value_to_check, return_value, ...)
//#define common_die_not_null(value_to_check, return_value, ...)
//#define common_die_true(value_to_check, return_value, ...)
//#define common_die_false(value_to_check, return_value, ...)
//#define common_die_equal(value_to_check_1, value_to_check_2, return_value, ...)
//#define common_die_not_equal(value_to_check_1, value_to_check_2, return_value, ...)
//#define common_die_superior(value_to_check_1, value_to_check_2, return_value, ...)
//#define common_die_inferior(value_to_check_1, value_to_check_2, return_value, ...)
//#define common_die_superior_or_equal(value_to_check_1, value_to_check_2, return_value, ...)
//#define common_die_inferior_or_equal(value_to_check_1, value_to_check_2, return_value, ...)

//_write_log() function don't use it directy, use write_log() macro instead
void _write_log(const char * filename, const char * function, int line, const char * format, ...);

//#########################################
//#                                       #
//#               Log section             #
//#                                       #
//#########################################

// Write simple log
#define write_log(...)                                                        \
	do {                                                                      \
		_write_log(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);            \
	} while(0)

/*
 * WRITE LOG IF THE VALUE IS EXPECTED
 */

//Write log if value_to_check is 'Negative' OR 'zero'
#define write_log_negative_or_zero(value_to_check, ...)                       \
	if(value_to_check <= 0){                                                  \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is stricly 'Negative'
#define write_log_negative(value_to_check, ...)                               \
	if(value_to_check < 0){                                                   \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is stricly 'Zero'
#define write_log_zero(value_to_check, ...)                                   \
	if(value_to_check == 0){                                                  \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is different from 'Zero'
#define write_log_not_zero(value_to_check, ...)                               \
	if(value_to_check != 0){                                                  \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is stricly 'Positive'
#define write_log_positive(value_to_check, ...)                               \
	if(value_to_check > 0){                                                   \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is 'Positive' OR 'Zero'
#define write_log_positive_or_zero(value_to_check, ...)                       \
	if(value_to_check >= 0){                                                  \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is 'NULL'
#define write_log_null(value_to_check, ...)                                   \
	if(value_to_check == NULL){                                               \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is 'NOT NULL'
#define write_log_not_null(value_to_check, ...)                               \
	if(value_to_check != NULL){                                               \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is 'TRUE'
#define write_log_true(value_to_check, ...)                                   \
	if(value_to_check == true){                                               \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check is 'FALSE'
#define write_log_false(value_to_check, ...)                                  \
	if(value_to_check == false){                                              \
		write_log(__VA_ARGS__);                                               \
	}

//Write log if value_to_check_1 and value_to_check_2 are 'EQUAL'
#define write_log_equal(value_to_check_1, value_to_check_2, ...)                   \
	if(value_to_check_1 == value_to_check_2){                                      \
		write_log(__VA_ARGS__);                                                    \
	}

//Write log if value_to_check_1 and value_to_check_2 are 'NOT EQUAL'
#define write_log_not_equal(value_to_check_1, value_to_check_2, ...)               \
	if(value_to_check_1 != value_to_check_2){                                      \
		write_log(__VA_ARGS__);                                                    \
	}

//Write log if value_to_check_1 is 'SUPERIOR TO' value_to_check_2
#define write_log_superior(value_to_check_1, value_to_check_2, ...)                \
	if(value_to_check_1 > value_to_check_2){                                       \
		write_log(__VA_ARGS__);                                                    \
	}

//Write log if value_to_check_1 is 'INFERIOR TO' value_to_check_2
#define write_log_inferior(value_to_check_1, value_to_check_2, ...)                \
	if(value_to_check_1 < value_to_check_2){                                       \
		write_log(__VA_ARGS__);                                                    \
	}

//Write log if value_to_check_1 is 'SUPERIOR OR EQUAL TO' value_to_check_2
#define write_log_superior_or_equal(value_to_check_1, value_to_check_2, ...)               \
	if(value_to_check_1 >= value_to_check_2){                                              \
		write_log(__VA_ARGS__);                                                            \
	}

//Write log if value_to_check_1 is 'INFERIOR OR EQUAL TO' value_to_check_2
#define write_log_inferior_or_equal(value_to_check_1, value_to_check_2, ...)               \
	if(value_to_check_1 <= value_to_check_2){                                              \
		write_log(__VA_ARGS__);                                                            \
	}


//#########################################
//#                                       #
//#           Common die section          #
//#                                       #
//#########################################

/*
 * DIE IF THE VALUE IS EXPECTED
 */

//Just DIE...
#define common_die(return_value, ...){                                        \
	write_log(__VA_ARGS__);                                                   \
	return return_value;                                                      \
}

//Die if value_to_check is 'Negative' OR 'zero'
#define common_die_negative_or_zero(value_to_check, return_value, ...)        \
	if(value_to_check <= 0){                                                  \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is stricly 'Negative'
#define common_die_negative(value_to_check, return_value, ...)                \
	if(value_to_check < 0){                                                   \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is stricly 'Zero'
#define common_die_zero(value_to_check, return_value, ...)                    \
	if(value_to_check == 0){                                                  \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is stricly different from 'Zero'
#define common_die_not_zero(value_to_check, return_value, ...)                \
	if(value_to_check != 0){                                                  \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is stricly 'Positive'
#define common_die_positive(value_to_check, return_value, ...)                \
	if(value_to_check > 0){                                                   \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is 'Positive' OR 'Zero'
#define common_die_positive_or_zero(value_to_check, return_value, ...)        \
	if(value_to_check >= 0){                                                  \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is 'NULL'
#define common_die_null(value_to_check, return_value, ...)                    \
	if(value_to_check == NULL){                                               \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is 'NOT NULL'
#define common_die_not_null(value_to_check, return_value, ...)                \
	if(value_to_check != NULL){                                               \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is 'TRUE'
#define common_die_true(value_to_check, return_value, ...)                    \
	if(value_to_check == true){                                               \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check is 'FALSE'
#define common_die_false(value_to_check, return_value, ...)                   \
	if(value_to_check == false){                                              \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

//Die if value_to_check_1 and value_to_check_2 are 'EQUAL'
#define common_die_equal(value_to_check_1, value_to_check_2, return_value, ...)    \
	if(value_to_check_1 == value_to_check_2){                                      \
		write_log(__VA_ARGS__);                                                    \
		return return_value;                                                       \
	}

//Die if value_to_check_1 and value_to_check_2 are 'NOT EQUAL'
#define common_die_not_equal(value_to_check_1, value_to_check_2, return_value, ...)\
	if(value_to_check_1 != value_to_check_2){                                      \
		write_log(__VA_ARGS__);                                                    \
		return return_value;                                                       \
	}

//Die if value_to_check_1 is 'SUPERIOR TO' value_to_check_2
#define common_die_superior(value_to_check_1, value_to_check_2, return_value, ...) \
	if(value_to_check_1 > value_to_check_2){                                       \
		write_log(__VA_ARGS__);                                                    \
		return return_value;                                                       \
	}

//Die if value_to_check_1 is 'INFERIOR TO' value_to_check_2
#define common_die_inferior(value_to_check_1, value_to_check_2, return_value, ...) \
	if(value_to_check_1 < value_to_check_2){                                       \
		write_log(__VA_ARGS__);                                                    \
		return return_value;                                                       \
	}

//Die if value_to_check_1 is 'SUPERIOR OR EQUAL TO' value_to_check_2
#define common_die_superior_or_equal(value_to_check_1, value_to_check_2, return_value, ...)\
	if(value_to_check_1 >= value_to_check_2){                                              \
		write_log(__VA_ARGS__);                                                            \
		return return_value;                                                               \
	}

//Die if value_to_check_1 is 'INFERIOR OR EQUAL TO' value_to_check_2
#define common_die_inferior_or_equal(value_to_check_1, value_to_check_2, return_value, ...)\
	if(value_to_check_1 <= value_to_check_2){                                              \
		write_log(__VA_ARGS__);                                                            \
		return return_value;                                                               \
	}


#ifdef __cplusplus
}
#endif
