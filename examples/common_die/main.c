#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "log.h"

int main( void){
	int ret;
	int test_value = -1;
	printf( "Start Test common_die\n");
	ret = libcommon_init_log();
	if( ret  < 0){
		printf("[%s line:%d]Error libcommon_init_log fail, return: %d\n", __FILE__, __LINE__,ret);
		return -1;
	}

	write_log("This is a simple log without color :) ");

	//Set color log
	ret = libcommon_set_color_log( true);
	common_die_negative( ret, -2, "Error: libcommon_set_color_log fail, return: %d", ret);

	write_log("This is a simple log with color _0/ ");

	common_die_negative( test_value, -3, "Test common_die_negative with test_value=%d", test_value);

	return 0;
}
