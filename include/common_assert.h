#ifndef __COMMON_ASSERT_H__
#define __COMMON_ASSERT_H__

#include "log.h"

/*
 * DIE IF THE VALUE IS 'NOT' EXPECTED
 */

//Die if value_to_check is NOT 'Negative' OR 'Zero'
#define common_assert_negative_or_zero(value_to_check, size, return_value, ...) \
	if(value_to_check >= 0){                                                    \
		write_log(__VA_ARGS__);                                                 \
		return return_value;                                                    \
	}

//Die if value_to_check is NOT 'Negative'
#define common_assert_negative(value_to_check, size, return_value, ...)         \
	if(value_to_check > 0){                                                     \
		write_log(__VA_ARGS__);                                                 \
		return return_value;                                                    \
	}

//Die if value_to_check is NOT 'Zero'
#define common_assert_zero(value_to_check, size, return_value, ...)             \
	if(value_to_check != 0){                                                    \
		write_log(__VA_ARGS__);                                                 \
		return return_value;                                                    \
	}

//Die if value_to_check is NOT 'Positive'
#define common_assert_positive(value_to_check, size, return_value, ...)         \
	if(value_to_check < 0){                                                     \
		write_log(__VA_ARGS__);                                                 \
		return return_value;                                                    \
	}

//Die if value_to_check is NOT 'Positive' OR 'Zero'
#define common_assert_positive_or_zero(value_to_check, size, return_value, ...) \
	if(value_to_check <= 0){                                                    \
		write_log(__VA_ARGS__);                                                 \
		return return_value;                                                    \
	}

//TODO
// common_assert_equal( value_to_check, reference_value, return_value, ...)
// common_assert_inferior( value_to_check, reference_value, return_value, ...)
// common_assert_superior( value_to_check, reference_value, return_value, ...)

// common_assert_true( value_to_check, return_value, ...)
// common_assert_false( value_to_check, return_value, ...)

// common_assert_null( value_to_check, return_value, ...)
// common_assert_not_null( value_to_check, return_value, ...)

#endif
