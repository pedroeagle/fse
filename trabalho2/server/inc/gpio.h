#ifndef GPIO_H_
#define GPIO_H_

#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>

void GPIO();
void TURN_OFF_GPIO();
void turn_on(int gpio_port);
void turn_off(int gpio_port);
int read_gpio(int gpio_port);
void create_handlers();
typedef struct sensor {
    int port;
    int value;
} sensor;
#endif