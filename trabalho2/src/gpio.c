#include "gpio.h"
#define LAMPADA_1_OUT 17
#define LAMPADA_2_OUT 18
#define LAMPADA_3_OUT 27
#define LAMPADA_4_OUT 22
#define AR_COND_1_OUT 13
#define AR_COND_2_OUT 19
#define SENSOR_PRESENCA_1_IN 25
#define SENSOR_PRESENCA_2_IN 26
#define SENSOR_ABERTURA_1_IN 5
#define SENSOR_ABERTURA_2_IN 6
#define SENSOR_ABERTURA_3_IN 12
#define SENSOR_ABERTURA_4_IN 16
#define SENSOR_ABERTURA_5_IN 20
#define SENSOR_ABERTURA_6_IN 21

int GPIO(){
    return wiringPiSetup ();
}
void turn_on(int gpio_port){
    pinMode(gpio_port, OUTPUT);
    digitalWrite(gpio_port, HIGH); 
}
void turn_off(int gpio_port){
    pinMode(gpio_port, OUTPUT);
    digitalWrite(gpio_port, LOW);
}
void read_gpio(int gpio_port){
    pinMode(gpio_port, INPUT);
    printf("%d\n", digitalRead(gpio_port));
}
void TURN_OFF_GPIO(){
    int ports[] = {LAMPADA_1_OUT, LAMPADA_2_OUT, LAMPADA_3_OUT, LAMPADA_4_OUT, AR_COND_1_OUT, AR_COND_2_OUT};
    int length = sizeof(ports)/sizeof(ports[0]);
    for(int i = 0; i < length; i++){
        pinMode(ports[i], OUTPUT);
        softPwmCreate(ports[i], 0,100);
        softPwmWrite (ports[i], 0);
    }
}