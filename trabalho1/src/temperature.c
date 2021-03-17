#include "temperature.h"
float potentiometer = 0.0, internal = 0.0, external = 0.0;
void * update_temperatures(void * vargp){
    DISPLAY();
    CSV();
    while(1){
        int uart = UART();
        I2C();
        potentiometer = get_potentiometer_temperature_uart(uart);
        internal = get_internal_temperature_uart(uart);
        external = get_external_temperature_i2c();
        char first[15], second[15];
        sprintf(first, "TI:%.2fTE:%.2f", get_internal_temperature(), get_external_temperature());
        sprintf(second, "TR:%.2f", get_potentiometer_temperature());
        write_first(first);
        write_second(second);
        float temperatures[5] = {internal, external, potentiometer, 0, -1};
        insert_line(temperatures, 5);
        delay(1000);
    }
}
float get_potentiometer_temperature(){
    return potentiometer;
}
float get_internal_temperature(){
    return internal;
}
float get_external_temperature(){
    return external;
}