#ifndef JSON_H_
#define JSON_H_
#include "gpio.h"
#include "i2c.h"
char * gpio_component_to_json_string(gpio_component * gpio_comps, int length);
char * i2c_values_to_json_string();
char * get_json();
void parse_json(char * json);
#endif