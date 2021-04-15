#include "i2c.h"
#define I2C_ADDR 0x76


void I2C(){
    bme280Init(1, I2C_ADDR);
}
float get_values(){
    bme280ReadValues(&T, &P, &H);
}
float read_temperature(){
    get_values();
    return T/100.0;
}
float read_humidity(){
    get_values();
    return H/1000.0;
}