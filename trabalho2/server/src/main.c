#include "gpio.h"
#include "socket.h"
#include "gpio.h"
#include "i2c.h"

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

pthread_t UPDATE_TEMPERATURES_PTHREAD_ID, READ_PTHREAD_ID;
void * continue_function(void * argp){
    while(1){
        printf("temperatura: %lf, umidade: %lf\n", read_temperature(), read_humidity());
        sleep(1);
    };
}
void start(){
    //CRIANDO TODAS AS THREADS QUE EXECUTARÃO SIMULTANEAMENTE
    pthread_create(&UPDATE_TEMPERATURES_PTHREAD_ID, NULL, get_i2c_values, NULL);
    pthread_create(&READ_PTHREAD_ID, NULL, continue_function, NULL);
    pthread_join(UPDATE_TEMPERATURES_PTHREAD_ID, NULL);
    pthread_join(READ_PTHREAD_ID, NULL);
}

int main(int argc, const char * argv[]) {
    start();
}