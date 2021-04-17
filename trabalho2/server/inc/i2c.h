#ifndef I2C_H_
#define I2C_H_

#include "bme280.h"
#include "json.h"
#include "client.h"
void * I2C(void *vargp);
float read_temperature();
float read_humidity();
void get_i2c_values();
int T, P, H;
#endif