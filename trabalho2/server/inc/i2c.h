#ifndef I2C_H_
#define I2C_H_

#include "bme280.h"
void I2C();
float read_temperature();
float read_humidity();
int T, P, H;
#endif