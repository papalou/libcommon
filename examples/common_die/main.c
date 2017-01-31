#include <stdint.h>
#include <stdio.h>

#include "log.h"

static int _test_common_die_zero( int value){
	common_die_negative( value, -1, "Value: %d trigger common die zero", value);
	return 0;
}

int main( void){
	int ret;
	printf( "Start Test common_die\n");

	ret = _test_common_die_zero(-1);
	printf( "Test common die zero return: %d\n", ret);
	return 0;
}
