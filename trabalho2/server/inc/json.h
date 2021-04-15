#ifndef JSON_H_
#define JSON_H_
#include "gpio.h"
#include "i2c.h"
char * presence_sensors_to_json_string();
char * open_sensors_to_json_string();
char * i2c_values_to_json_string();
char * get_json();
#endif