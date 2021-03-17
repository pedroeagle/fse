#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "uart.h"
#include "i2c.h"
#include "display.h"
#include "csv.h"

void * update_temperatures(void * vargp);
float get_potentiometer_temperature();
float get_internal_temperature();
float get_external_temperature();
#endif