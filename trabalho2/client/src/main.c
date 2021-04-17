#include <pthread.h>
#include <signal.h>
#include "socket.h"
#include "menu.h"

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

pthread_t SOCKET_PTHREAD_ID, READ_PTHREAD_ID;

void start(){
    //CRIANDO TODAS AS THREADS QUE EXECUTARÃO SIMULTANEAMENTE
    pthread_create(&SOCKET_PTHREAD_ID, NULL, start_socket, NULL);
    pthread_create(&READ_PTHREAD_ID, NULL, read_menu, NULL);
    pthread_join(SOCKET_PTHREAD_ID, NULL);
    pthread_join(READ_PTHREAD_ID, NULL);
}
int main(int argc, const char * argv[]) {
    start();
}