#include "gpio.h"
#include "json.h"
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
    presence_sensors[0].value = read_gpio(presence_sensors[0].port);
    printf("porta: %d valor: %d\n", presence_sensors[0].port, presence_sensors[0].value);
}
void handle_sensor_1() {
    presence_sensors[1].value = read_gpio(presence_sensors[1].port);
    printf("porta: %d valor: %d\n", presence_sensors[1].port, presence_sensors[1].value);
}
void handle_sensor_2() {
    open_sensors[0].value = read_gpio(open_sensors[0].port);
    printf("porta: %d valor: %d\n", open_sensors[0].port, open_sensors[0].value);
}
void handle_sensor_3() {
    open_sensors[1].value = read_gpio(open_sensors[1].port);
    printf("porta: %d valor: %d\n", open_sensors[1].port, open_sensors[1].value);
}
void handle_sensor_4() {
    open_sensors[2].value = read_gpio(open_sensors[2].port);
    printf("porta: %d valor: %d\n", open_sensors[2].port, open_sensors[2].value);
}
void handle_sensor_5() {
    open_sensors[3].value = read_gpio(open_sensors[3].port);
    printf("porta: %d valor: %d\n", open_sensors[3].port, open_sensors[3].value);
}
void handle_sensor_6() {
    open_sensors[4].value = read_gpio(open_sensors[4].port);
    printf("porta: %d valor: %d\n", open_sensors[4].port, open_sensors[4].value);
}
void handle_sensor_7() {
    open_sensors[5].value = read_gpio(open_sensors[5].port);
    printf("porta: %d valor: %d\n", open_sensors[5].port, open_sensors[5].value);
}
void create_handlers () {
    int presence_ports[] = {SENSOR_PRESENCA_1_IN, SENSOR_PRESENCA_2_IN};
    int open_ports[] = {SENSOR_ABERTURA_1_IN, SENSOR_ABERTURA_2_IN, SENSOR_ABERTURA_3_IN, SENSOR_ABERTURA_4_IN, SENSOR_ABERTURA_5_IN, SENSOR_ABERTURA_6_IN};
    int functions[] = {handle_sensor_0, handle_sensor_1, handle_sensor_2, handle_sensor_3, handle_sensor_4, handle_sensor_5, handle_sensor_6, handle_sensor_7};
    int length_presence = sizeof(presence_ports)/sizeof(presence_ports[0]);
    int length_open = sizeof(open_ports)/sizeof(open_ports[0]);
    for(int i = 0; i < length_presence; i++){
        presence_sensors[i].port = presence_ports[i];
        presence_sensors[i].value = read_gpio(presence_ports[i]);
        wiringPiISR(presence_ports[i], INT_EDGE_BOTH, functions[i]);
    }
    for(int i = 0; i <length_open; i++){
        open_sensors[i].port = open_ports[i];
        open_sensors[i].value = read_gpio(open_ports[i]);
        wiringPiISR(open_ports[i], INT_EDGE_BOTH, functions[i+2]);
    }
    while(1){
        sleep(1);
    } 
}