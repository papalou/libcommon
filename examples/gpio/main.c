#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "gpio.h"
#include "log.h"

int main( void){
	int ret;
	T_gpio my_gpio;

	printf( "Start Test gpio\n");
	ret = libcommon_init_log();
	if( ret  < 0){
		printf("[%s line:%d]Error libcommon_init_log fail, return: %d\n", __FILE__, __LINE__,ret);
		return -1;
	}

	ret = gpio_init( &my_gpio, 54, E_GPIO_DIRECTION_OUT, 0);
	common_die_negative(ret, -2, "Error: gpio_init fail, return: %d", ret);

	ret = gpio_get_value( &my_gpio); 
	common_die_negative(ret, -4, "Error: get gpio value fail, return: %d", ret);

	printf("Gpio value: %d (expect 0)\n", ret);

	ret = gpio_set_value( &my_gpio, 1);
	common_die_negative(ret, -3, "Error: gpio_set_value fail, return: %d", ret);

	ret = gpio_get_value( &my_gpio); 
	common_die_negative(ret, -4, "Error: get gpio value fail, return: %d", ret);

	printf("Gpio value: %d (expect 1)\n", ret);

	return 0;
}
