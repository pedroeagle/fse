#include "i2c.h"
#define I2C_ADDR 0x76


void I2C(){
    bme280Init(1, I2C_ADDR);
}
float get_external_temperature_i2c(){
    int T, P, H;
    bme280ReadValues(&T, &P, &H);
    return T/100.0;
}