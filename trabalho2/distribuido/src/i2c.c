#include "i2c.h"
#define I2C_ADDR 0x76

void * I2C(void *vargp){
    printf("I2C\n");
    bme280Init(1, I2C_ADDR);
    get_i2c_values();
}
void get_i2c_values(){
    while(1){
        bme280ReadValues(&T, &P, &H);
        send_message(get_json());
        sleep(1);
    }
}
void CLOSE_I2C(){
    int fd = open("/dev/i2c-1", O_RDWR);
    close(fd);
}
float read_temperature(){
    return T/100.0;
}
float read_humidity(){
    return H/1000.0;
}