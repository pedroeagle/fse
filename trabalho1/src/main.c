#include <pthread.h>
#include <signal.h>
#include "menu.h"
#include "temperature.h"
#include "display.h"
#include "gpio.h"

#define CODIGO_CLIENTE 0x00
#define CODIGO_SERVIDOR 0x01
#define CODIGO_CMD_SOLICITA 0x23
#define CODIGO_CMD_ESCREVE 0x16

#define CMD_SOLICITA_INT    0xA1
#define CMD_SOLICITA_FLOAT  0xA2
#define CMD_SOLICITA_STRING 0xA3

#define CMD_ENVIA_INT    0xB1
#define CMD_ENVIA_FLOAT  0xB2
#define CMD_ENVIA_STRING 0xB3

#define CMD_ERROR 0xE1
#define CMD_STRING_OK 0xC1

pthread_t UPDATE_TEMPERATURES_PTHREAD_ID, READ_PTHREAD_ID;
pthread_t get_update_temperatures_pthread_id(){
    return UPDATE_TEMPERATURES_PTHREAD_ID;
}
void start(){
    //CRIANDO TODAS AS THREADS QUE EXECUTARÃO SIMULTANEAMENTE
    pthread_create(&UPDATE_TEMPERATURES_PTHREAD_ID, NULL, update_temperatures, NULL);
    pthread_create(&READ_PTHREAD_ID, NULL, read_menu, NULL);
    pthread_join(UPDATE_TEMPERATURES_PTHREAD_ID, NULL);
    pthread_join(READ_PTHREAD_ID, NULL);
}
void finish(){
    DISPLAY();
    turn_off();
    pthread_cancel(READ_PTHREAD_ID);
    pthread_cancel(UPDATE_TEMPERATURES_PTHREAD_ID);
}
void force_finish(int signal){
    finish();
}
int main(int argc, const char * argv[]) {

    signal(SIGINT, force_finish);
    signal(SIGKILL, force_finish);
    start();
    
   return 0;
}
