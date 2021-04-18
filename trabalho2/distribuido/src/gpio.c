#include "gpio.h"
#include "json.h"
#include "client.h"
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
void * GPIO(void *vargp){
    printf("GPIO\n");
    wiringPiSetup ();
    int ports[] = {LAMPADA_1_OUT, LAMPADA_2_OUT, LAMPADA_3_OUT, LAMPADA_4_OUT, AR_COND_1_OUT, AR_COND_2_OUT};
    int length = sizeof(ports)/sizeof(ports[0]);
    for(int i = 0; i < length; i++){
        digitalWrite(ports[i], LOW);
    }
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
void toggle(int gpio_port){
    int read = read_gpio(gpio_port);
    read?turn_off(gpio_port):turn_on(gpio_port);
}
int read_gpio(int gpio_port){
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
void handle_gpio_component_0() {
    presence_sensors[0].value = read_gpio(presence_sensors[0].port);
    printf("porta: %d valor: %d\n", presence_sensors[0].port, presence_sensors[0].value);
    send_message(get_json());
}
void handle_gpio_component_1() {
    presence_sensors[1].value = read_gpio(presence_sensors[1].port);
    printf("porta: %d valor: %d\n", presence_sensors[1].port, presence_sensors[1].value);
    send_message(get_json());
}
void handle_gpio_component_2() {
    open_sensors[0].value = read_gpio(open_sensors[0].port);
    printf("porta: %d valor: %d\n", open_sensors[0].port, open_sensors[0].value);
    send_message(get_json());
}
void handle_gpio_component_3() {
    open_sensors[1].value = read_gpio(open_sensors[1].port);
    printf("porta: %d valor: %d\n", open_sensors[1].port, open_sensors[1].value);
    send_message(get_json());
}
void handle_gpio_component_4() {
    open_sensors[2].value = read_gpio(open_sensors[2].port);
    printf("porta: %d valor: %d\n", open_sensors[2].port, open_sensors[2].value);
    send_message(get_json());
}
void handle_gpio_component_5() {
    open_sensors[3].value = read_gpio(open_sensors[3].port);
    printf("porta: %d valor: %d\n", open_sensors[3].port, open_sensors[3].value);
    send_message(get_json());
}
void handle_gpio_component_6() {
    open_sensors[4].value = read_gpio(open_sensors[4].port);
    printf("porta: %d valor: %d\n", open_sensors[4].port, open_sensors[4].value);
    send_message(get_json());
}
void handle_gpio_component_7() {
    open_sensors[5].value = read_gpio(open_sensors[5].port);
    printf("porta: %d valor: %d\n", open_sensors[5].port, open_sensors[5].value);
    send_message(get_json());
}
void handle_gpio_component_8() {
    light_outs[0].value = read_gpio(light_outs[0].port);
    printf("porta: %d valor: %d\n", light_outs[0].port, light_outs[0].value);
    send_message(get_json());
}
void handle_gpio_component_9() {
    light_outs[1].value = read_gpio(light_outs[1].port);
    printf("porta: %d valor: %d\n", light_outs[1].port, light_outs[1].value);
    send_message(get_json());
}
void handle_gpio_component_10() {
    light_outs[2].value = read_gpio(light_outs[2].port);
    printf("porta: %d valor: %d\n", light_outs[2].port, light_outs[2].value);
    send_message(get_json());
}
void handle_gpio_component_11() {
    light_outs[3].value = read_gpio(light_outs[3].port);
    printf("porta: %d valor: %d\n", light_outs[3].port, light_outs[3].value);
    send_message(get_json());
}
void handle_gpio_component_12() {
    air_outs[0].value = read_gpio(air_outs[0].port);
    printf("porta: %d valor: %d\n", air_outs[0].port, air_outs[0].value);
    send_message(get_json());
}
void handle_gpio_component_13() {
    air_outs[1].value = read_gpio(air_outs[1].port);
    printf("porta: %d valor: %d\n", air_outs[1].port, air_outs[1].value);
    send_message(get_json());
}
void create_handlers () {
    int presence_ports[] = {SENSOR_PRESENCA_1_IN, SENSOR_PRESENCA_2_IN};
    int open_ports[] = {SENSOR_ABERTURA_1_IN, SENSOR_ABERTURA_2_IN, SENSOR_ABERTURA_3_IN, SENSOR_ABERTURA_4_IN, SENSOR_ABERTURA_5_IN, SENSOR_ABERTURA_6_IN};
    int light_ports[] = {LAMPADA_1_OUT, LAMPADA_2_OUT, LAMPADA_3_OUT, LAMPADA_4_OUT};
    int air_ports[] = {AR_COND_1_OUT, AR_COND_2_OUT};
    int functions[] = {handle_gpio_component_0, handle_gpio_component_1, handle_gpio_component_2, handle_gpio_component_3, handle_gpio_component_4, handle_gpio_component_5, handle_gpio_component_6, handle_gpio_component_7, handle_gpio_component_8, handle_gpio_component_9, handle_gpio_component_10, handle_gpio_component_11, handle_gpio_component_12, handle_gpio_component_13};
    int length_presence = sizeof(presence_ports)/sizeof(presence_ports[0]);
    int length_open = sizeof(open_ports)/sizeof(open_ports[0]);
    int length_light = sizeof(light_ports)/sizeof(light_ports[0]);
    int length_air = sizeof(air_ports)/sizeof(air_ports[0]);
    for(int i = 0; i < length_presence; i++){
        pinMode(presence_ports[i], INPUT);
        presence_sensors[i].port = presence_ports[i];
        presence_sensors[i].value = read_gpio(presence_ports[i]);
        wiringPiISR(presence_ports[i], INT_EDGE_BOTH, functions[i]);
    }
    for(int i = 0; i <length_open; i++){
        pinMode(open_ports[i], INPUT);
        open_sensors[i].port = open_ports[i];
        open_sensors[i].value = read_gpio(open_ports[i]);
        wiringPiISR(open_ports[i], INT_EDGE_BOTH, functions[i+length_presence]);
    }
    for(int i = 0; i <length_light; i++){
        pinMode(light_ports[i], INPUT);
        light_outs[i].port = light_ports[i];
        light_outs[i].value = read_gpio(light_ports[i]);
        wiringPiISR(light_ports[i], INT_EDGE_BOTH, functions[i+length_presence+length_open]);
    }
    for(int i = 0; i <length_air; i++){
        pinMode(air_ports[i], INPUT);
        air_outs[i].port = air_ports[i];
        air_outs[i].value = read_gpio(air_ports[i]);
        wiringPiISR(air_ports[i], INT_EDGE_BOTH, functions[i+length_presence+length_open+length_light]);
    }
    while(1){
        sleep(1);
    } 
}
int get_presence_sensors_lenght(){
    int length = sizeof(presence_sensors)/sizeof(presence_sensors[0]);
    return length;
}
int get_open_sensors_lenght(){
    int length = sizeof(open_sensors)/sizeof(open_sensors[0]);
}
int get_light_outs_lenght(){
    int length = sizeof(light_outs)/sizeof(light_outs[0]);
}
int get_air_outs_lenght(){
    int length = sizeof(air_outs)/sizeof(air_outs[0]);
}