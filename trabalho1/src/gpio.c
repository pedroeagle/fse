#include "gpio.h"
#define RESISTOR_GPIO_PIN 4
#define FAN_GPIO_PIN 5
#define FAN_MIN_INTENSITY 40

pthread_t TURN_ON_FAN_PTHREAD_ID, TURN_OFF_FAN_PTHREAD_ID;

int GPIO(){
    return wiringPiSetup ();
}
void turn_off_resistor(){
    pinMode(RESISTOR_GPIO_PIN, OUTPUT);
    softPwmCreate(RESISTOR_GPIO_PIN, 0,100);
    softPwmWrite (RESISTOR_GPIO_PIN, 0);
}
void turn_off_fan(){
    pinMode(FAN_GPIO_PIN, OUTPUT);
    softPwmCreate(FAN_GPIO_PIN, 0,100);
    softPwmWrite (FAN_GPIO_PIN, 0);
}
void turn_on_fan(int intensity){
    turn_off_resistor();
    if(abs(intensity) > FAN_MIN_INTENSITY){
        pinMode(FAN_GPIO_PIN, OUTPUT);
        softPwmCreate(FAN_GPIO_PIN, 0,100);
        softPwmWrite (FAN_GPIO_PIN, abs(intensity));
    }
}
void turn_on_resistor(int intensity){
    turn_off_fan();
    pinMode(RESISTOR_GPIO_PIN, OUTPUT);
    softPwmCreate(RESISTOR_GPIO_PIN, 0,100);
    softPwmWrite (RESISTOR_GPIO_PIN, abs(intensity));
}
void turn_off(){
    turn_off_fan();
    turn_off_resistor();
}