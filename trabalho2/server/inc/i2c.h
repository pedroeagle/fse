#ifndef I2C_H_
#define I2C_H_

#include "bme280.h"
void I2C();
float read_temperature();
float read_humidity();
void * get_i2c_values(void * argp);
int T, P, H;
#endif