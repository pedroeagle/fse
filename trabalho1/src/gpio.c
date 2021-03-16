#include "gpio.h"
#define RESISTOR_GPIO_PIN 4
#define FAN_GPIO_PIN 5

#define FAN_INTENSITY 80
#define RESISTOR_INTENSITY 20

pthread_t TURN_ON_FAN_PTHREAD_ID, TURN_OFF_FAN_PTHREAD_ID;

int GPIO(){
    return wiringPiSetup ();
}
void * turn_on_fan_thread(void *vargp){
    while(1){
        softPwmWrite (FAN_GPIO_PIN, FAN_INTENSITY);
        printf("Girando o FAN\n");
        delay(100);
    }
}
void * turn_off_fan_thread(void *vargp){
    printf("Desligando FAN\n");
    pthread_cancel(TURN_ON_FAN_PTHREAD_ID);
    printf("Desligado!\n");
}
void turn_on_fan(){
    pthread_create(&TURN_ON_FAN_PTHREAD_ID, NULL, turn_on_fan_thread, NULL);
    pthread_join(turn_on_fan_thread, NULL);
    //colocar aqui a função que de verificação se o fan deve permanecer ligado
    delay(5000);
    pthread_create(&TURN_OFF_FAN_PTHREAD_ID, NULL, turn_off_fan_thread, NULL);
    pthread_join(turn_off_fan_thread, NULL);
}