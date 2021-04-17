#include "gpio.h"
#include "socket.h"
#include "gpio.h"
#include "i2c.h"

pthread_t HANDLE_GPIO_PTHREAD_ID, SOCKET_PTHREAD_ID, UPDATE_I2C_VALUES;
void * continue_function(void * argp){
    while(1){
        printf("temperatura: %lf, umidade: %lf\n", read_temperature(), read_humidity());
        sleep(1);
    };
}
void start(){
    //CRIANDO TODAS AS THREADS QUE EXECUTARÃO SIMULTANEAMENTE
    pthread_create(&HANDLE_GPIO_PTHREAD_ID, NULL, GPIO, NULL);
    pthread_create(&SOCKET_PTHREAD_ID, NULL, start_socket, NULL);
    pthread_create(&UPDATE_I2C_VALUES, NULL, I2C, NULL);
    pthread_join(HANDLE_GPIO_PTHREAD_ID, NULL);
    pthread_join(SOCKET_PTHREAD_ID, NULL);
    pthread_join(UPDATE_I2C_VALUES, NULL);
}

int main(int argc, const char * argv[]) {
    start();
}