#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "log.h"
#include "gpio.h"

#include "gpio.private.h"

#define PATH_LENGTH 128
#define DATA_LENGTH 16

static int _open_and_write( char * path, char * data){
	int ret;
	int fd;

	common_die_null( path, -1, "Error path is null");
	common_die_null( data, -2, "Error data is null");

	fd = open( path, O_WRONLY);
	common_die_negative( fd, -3, "Error: open %s fail, return: %d, errno: %d (%s)", path, fd, errno, strerror(errno));

	ret = write( fd, data, sizeof(data));
	if(ret < 0){
		close(fd);
		common_die_negative(ret, -4, "Error: write fail, return: %d, errno: %d (%s)", path, ret, errno, strerror(errno));
	}
	close(fd);

	return 0;
}

static int _export_gpio( uint16_t number){
	int ret;
	char path[PATH_LENGTH];
	char data[DATA_LENGTH];

	ret = snprintf(path, PATH_LENGTH, "%s/%s", GPIO_FOLDER, GPIO_EXPORT_BINARY);
	common_die_superior_or_equal(ret, PATH_LENGTH, -2, "Error: snprintf fail, can be trancated");

	ret = snprintf(data, DATA_LENGTH, "%d", number);
	common_die_superior_or_equal(ret, PATH_LENGTH, -3, "Error: snprintf fail, can be trancated");

	ret = _open_and_write( path, data);
	common_die_negative(ret, -4, "Error: _open_and_write fail, return: %d");

	return 0;
}

static int _unexport_gpio( uint16_t number){
	int ret;
	char path[PATH_LENGTH];
	char data[DATA_LENGTH];

	ret = snprintf(path, PATH_LENGTH, "%s/%s", GPIO_FOLDER, GPIO_UNEXPORT_BINARY);
	common_die_superior_or_equal(ret, PATH_LENGTH, -3, "Error: snprintf fail, can be trancated");

	ret = snprintf(data, DATA_LENGTH, "%d", number);
	common_die_superior_or_equal(ret, PATH_LENGTH, -4, "Error: snprintf fail, can be trancated");

	ret = _open_and_write( path, data);
	common_die_negative(ret, -5, "Error: _open_and_write fail, return: %d");

	return 0;
}

static int _set_direction( uint16_t number, E_gpio_direction direction){
	int ret;
	char path[PATH_LENGTH];
	char data[DATA_LENGTH];

	ret = snprintf(path, PATH_LENGTH, "%s/GPIO%d/direction", GPIO_FOLDER, number);
	common_die_superior_or_equal(ret, PATH_LENGTH, -5, "Error: snprintf fail, can be trancated");

	switch( direction){
		case E_GPIO_DIRECTION_IN:
			ret = snprintf( data, DATA_LENGTH, "%s", "in");
			common_die_superior_or_equal(ret, 8, -6, "Error strncpy may have fail, output can be truncated");
			break;
		case E_GPIO_DIRECTION_OUT:
			ret = snprintf( data, DATA_LENGTH, "%s", "out");
			common_die_superior_or_equal(ret, 8, -7, "Error strncpy may have fail, output can be truncated");
			break;
		default:
			common_die( -8, "Error direction may be wrong, direction -> %d", direction);
			break;
	}

	ret = _open_and_write( path, data);
	common_die_negative(ret, -9, "Error: _open_and_write fail, return: %d");
	return 0;
}

int gpio_init(T_gpio * gpio, uint16_t number, E_gpio_direction direction, uint8_t value){
	int ret;
	char path[PATH_LENGTH];

	common_die_null( gpio, -1, "Error: gpio in null");

	//Export GPIO
	ret = _export_gpio(number);
	common_die_negative(ret, -2, "Error: export gpio fail, return: %d", ret);
	gpio->number = number;

	//Set Direction
	ret = _set_direction(number, direction);
	common_die_negative(ret, -3, "Error: set gpio direction fail, return: %d", ret);
	gpio->direction = direction;

	//Set Value
	ret = snprintf(path, PATH_LENGTH, "%s/GPIO%d/value", GPIO_FOLDER, number);
	common_die_superior_or_equal(ret, PATH_LENGTH, -4, "Error: snprintf fail, can be trancated");

	gpio->fd = open( path, O_WRONLY);
	common_die_negative( gpio->fd, -5, "Error: open %s fail, return: %d, errno: %d (%s)", path, gpio->fd, errno, strerror(errno));

	if(value == 0){
		ret = write( gpio->fd, "0", 1);
		common_die_negative( ret, -5, "Error: write gpio%d value fail, return: %d", number, ret);
	}else{
		ret = write( gpio->fd, "1", 1);
		common_die_negative( ret, -6, "Error: write gpio%d value fail, return: %d", number, ret);
	}

	lseek(gpio->fd, 0, SEEK_SET);

	gpio->is_initialized = true;

	return 0;
}

int gpio_release(T_gpio * gpio){
	int ret;

	common_die_null( gpio, -1, "Error: gpio in null");

	if(gpio->is_initialized != true){
		common_die( -2, "Error gpio is not initialized");
	}

	ret = _unexport_gpio(gpio->number);
	common_die_negative( ret, -3, "Error: unexport gpio%d fail, return: %d", gpio->number, ret);

	//Close file descriptor on gpio value
	close( gpio->fd);

	gpio->is_initialized = false;

	return 0;
}

int gpio_get_value(T_gpio * gpio){
	int ret;
	char path[PATH_LENGTH];
	char value;

	common_die_null( gpio, -1, "Error: gpio in null");

	if(gpio->is_initialized != true){
		common_die( -2, "Error gpio is not initialized");
	}

	//Get Value
	ret = read( gpio->fd, &value, sizeof(value));
	common_die_negative(ret, -4, "Error: read fail, return: %d, errno: %d (%s)", path, ret, errno, strerror(errno));

	lseek(gpio->fd, 0, SEEK_SET);

	//Interpret value and return it
	if(value == '0'){
		return 0;
	}else{
		return 1;
	}
}

int gpio_set_value(T_gpio * gpio, uint8_t value){
	int ret;

	common_die_null( gpio, -1, "Error: gpio in null");

	if(gpio->is_initialized != true){
		common_die( -2, "Error gpio is not initialized");
	}

	//Set Value
	if(value == 0){
		ret = write( gpio->fd, "0", 1);
		common_die_negative( ret, -5, "Error: write gpio%d value fail, return: %d", gpio->number, ret);
	}else{
		ret = write( gpio->fd, "1", 1);
		common_die_negative( ret, -6, "Error: write gpio%d value fail, return: %d", gpio->number, ret);
	}

	lseek(gpio->fd, 0, SEEK_SET);

	return 0;
}

//int gpio_export_select(T_gpio * gpio, uint16_t number, E_gpio_edge edge, T_gpio_handler handler){
//	int ret;
//	char path[PATH_LENGTH];
//	char data[DATA_LENGTH];
//
//	common_die_null( gpio, -1, "Error: gpio in null");
//
//	if(gpio->is_initialized != true){
//		common_die( -2, "Error gpio is not initialized");
//	}
//
//	return 0;
//}
