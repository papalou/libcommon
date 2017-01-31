#ifndef __COMMON_DIE_H__
#define __COMMON_DIE_H__

#include "log.h"

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

//DEPRECATED
#define common_die_snprintf(value_to_check, size, return_value, ...)          \
	if(value_to_check > (size -1)){                                           \
		write_log(__VA_ARGS__);                                               \
		return return_value;                                                  \
	}

#endif
