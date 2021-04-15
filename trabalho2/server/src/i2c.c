#include "i2c.h"
#define I2C_ADDR 0x76


void I2C(){
    bme280Init(1, I2C_ADDR);
}
void * get_i2c_values(void * argp){
    I2C();
    while(1){
        bme280ReadValues(&T, &P, &H);
        sleep(1);
    }
}
float read_temperature(){
    return T/100.0;
}
float read_humidity(){
    return H/1000.0;
}