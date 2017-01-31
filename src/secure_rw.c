#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "log.h"
#include "secure_rw.h"

int secure_read(int fd, void * buf, size_t count){
	int ret;
	int index = 0;
	int nb_left = count;
	uint8_t * buffer = buf;

	common_die_zero(fd, -1, "Error, bad fd: %d", fd);
	common_die_null(buf, -2, "Error buf is null");

	while(nb_left > 0){
		ret = read(fd,  &buffer[index], nb_left);
		common_die_zero(ret, -3, "Error: read fail, %s", strerror(errno));
		if(ret == 0){
			common_die(-4, "Error: read return: 0, %s", strerror(errno));
		}
		index += ret;
		nb_left -= ret;
	}

	return 0;
}

int secure_write(int fd, void * buf, size_t count){
	int ret;
	int index = 0;
	int nb_left = count;
	uint8_t * buffer = buf;

	common_die_zero(fd, -1, "Error, bad fd: %d", fd);
	common_die_null(buf, -2, "Error buf is null");

	while(nb_left > 0){
		ret = write(fd,  &buffer[index], nb_left);
		common_die_zero(ret, -3, "Error: write fail, %s", strerror(errno));
		if(ret == 0){
			common_die(-4, "Error: read return: 0, %s", strerror(errno));
		}
		index += ret;
		nb_left -= ret;
	}

	return 0;
}
