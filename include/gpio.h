#ifndef __GPIO_H__
#define __GPIO_H__

#define GPIO_FOLDER "/sys/class/gpio"
#define GPIO_EXPORT_BINARY "export"
#define GPIO_UNEXPORT_BINARY "unexport"

typedef enum{
	E_GPIO_DIRECTION_OUT = 0,
	E_GPIO_DIRECTION_IN,
}E_gpio_direction;

typedef enum{
	E_GPIO_EDGE_RISING = 0,
	E_GPIO_EDGE_FALLING,
	E_GPIO_EDGE_BOTH,
}E_gpio_edge;

typedef struct{
	bool is_initialized;         /* is gpio struct initialized */
	int fd;                      /* open file descriptor on the gpio at export */
	uint16_t number;             /* gpio number */
	E_gpio_direction direction;  /* gpio direction */
	//T_gpio_handler handler;
}T_gpio;

//Callback gpio handler for the gpio_export_select()
typedef int (*T_gpio_handler)(T_gpio * gpio, bool value);

int gpio_init(T_gpio * gpio, uint16_t number, E_gpio_direction direction, uint8_t value);
int gpio_release(T_gpio * gpio);

//int gpio_export_select(T_gpio * gpio, uint16_t number, E_gpio_edge edge, T_gpio_handler handler);

int gpio_get_value(T_gpio * gpio);
int gpio_set_value(T_gpio * gpio, uint8_t value);


#endif
