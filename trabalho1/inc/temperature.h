#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include <unistd.h>
#include "uart.h"
#include "i2c.h"
#include "display.h"
#include "csv.h"
#include "pid.h"
#include "gpio.h"
#include "menu.h"

void * update_temperatures(void * vargp);
float get_potentiometer_temperature();
float get_internal_temperature();
float get_external_temperature();
float get_terminal_temperature();
void set_terminal_temperature(float temperature);
int potentiometer_as_reference;
#endif