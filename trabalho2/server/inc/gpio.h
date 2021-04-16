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
typedef struct gpio_component {
    int port;
    int value;
} gpio_component;
struct gpio_component presence_sensors[2];
struct gpio_component open_sensors[6];
struct gpio_component light_outs[4];
struct gpio_component air_outs[2];
int get_presence_sensors_lenght();
int get_open_sensors_lenght();
int get_light_outs_lenght();
int get_air_outs_lenght();
#endif