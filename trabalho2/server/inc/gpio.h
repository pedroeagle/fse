#ifndef GPIO_H_
#define GPIO_H_

#include <wiringPi.h>

int GPIO();
void TURN_OFF_GPIO();
void turn_on(int gpio_port);
void turn_off(int gpio_port);
void read_gpio(int gpio_port);
#endif