#include "gpio.h"
#define LAMPADA_1_OUT 0
#define LAMPADA_2_OUT 1
#define LAMPADA_3_OUT 2
#define LAMPADA_4_OUT 3
#define AR_COND_1_OUT 23
#define AR_COND_2_OUT 24
#define SENSOR_PRESENCA_1_IN 6
#define SENSOR_PRESENCA_2_IN 25
#define SENSOR_ABERTURA_1_IN 21
#define SENSOR_ABERTURA_2_IN 22
#define SENSOR_ABERTURA_3_IN 26
#define SENSOR_ABERTURA_4_IN 27
#define SENSOR_ABERTURA_5_IN 28
#define SENSOR_ABERTURA_6_IN 29

int HANDLER_PTHREAD_ID;

struct sensor sensores[8];
void GPIO(){
    wiringPiSetup ();
    create_handlers();
}
void turn_on(int gpio_port){
    pinMode(gpio_port, OUTPUT);
    digitalWrite(gpio_port, HIGH); 
}
void turn_off(int gpio_port){
    pinMode(gpio_port, OUTPUT);
    digitalWrite(gpio_port, LOW);
}
int read_gpio(int gpio_port){
    pinMode(gpio_port, INPUT);
    int value = digitalRead(gpio_port);
    return value;
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
void handle_sensor_0() {
    sensores[0].value = read_gpio(sensores[0].port);
    printf("porta: %d valor: %d\n", sensores[0].port, sensores[0].value);
}
void handle_sensor_1() {
    sensores[1].value = read_gpio(sensores[1].port);
    printf("porta: %d valor: %d\n", sensores[1].port, sensores[1].value);
}
void handle_sensor_2() {
    sensores[2].value = read_gpio(sensores[2].port);
    printf("porta: %d valor: %d\n", sensores[2].port, sensores[2].value);
}
void handle_sensor_3() {
    sensores[3].value = read_gpio(sensores[3].port);
    printf("porta: %d valor: %d\n", sensores[3].port, sensores[3].value);
}
void handle_sensor_4() {
    sensores[4].value = read_gpio(sensores[4].port);
    printf("porta: %d valor: %d\n", sensores[4].port, sensores[4].value);
}
void handle_sensor_5() {
    sensores[5].value = read_gpio(sensores[5].port);
    printf("porta: %d valor: %d\n", sensores[5].port, sensores[5].value);
}
void handle_sensor_6() {
    sensores[6].value = read_gpio(sensores[6].port);
    printf("porta: %d valor: %d\n", sensores[6].port, sensores[6].value);
}
void handle_sensor_7() {
    sensores[7].value = read_gpio(sensores[7].port);
    printf("porta: %d valor: %d\n", sensores[7].port, sensores[7].value);
}
void create_handlers () {
    int ports[] = {SENSOR_PRESENCA_1_IN, SENSOR_PRESENCA_2_IN, SENSOR_ABERTURA_1_IN, SENSOR_ABERTURA_2_IN, SENSOR_ABERTURA_3_IN, SENSOR_ABERTURA_4_IN, SENSOR_ABERTURA_5_IN, SENSOR_ABERTURA_6_IN};
    int functions[] = {handle_sensor_0, handle_sensor_1, handle_sensor_2, handle_sensor_3, handle_sensor_4, handle_sensor_5, handle_sensor_6, handle_sensor_7};
    int length = sizeof(ports)/sizeof(ports[0]);
    for(int i = 0; i < length; i++){
        sensores[i].port = ports[i];
        sensores[i].value = read_gpio(ports[i]);
        wiringPiISR(ports[i], INT_EDGE_BOTH, functions[i]);
    }
    while(1){
        sleep(1);
    } 
}