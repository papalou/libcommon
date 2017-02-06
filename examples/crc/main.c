#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "crc.h"
#include "log.h"

int main( void){
	int ret;
	uint8_t data[5] = {5,2,4,6,54};
	uint8_t crc;

	printf( "Start Test secure_rw\n");
	ret = libcommon_init_log();
	if( ret  < 0){
		printf("[%s line:%d]Error libcommon_init_log fail, return: %d\n", __FILE__, __LINE__,ret);
		return -1;
	}

	crc = crc_compute_crc8( data, sizeof(data));

	printf("CRC8 of data[] = %d\n", crc);

	return 0;
}
