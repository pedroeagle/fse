#include "gpio.h"
#include "socket.h"
#include "gpio.h"
#include "i2c.h"

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
    GPIO();
}