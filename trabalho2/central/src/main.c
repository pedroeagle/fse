#include <pthread.h>
#include <signal.h>
#include "socket.h"
#include "menu.h"
#include "client.h"
#include "csv.h"
#include "alarm.h"

pthread_t SOCKET_PTHREAD_ID, READ_PTHREAD_ID;

void start(){
    CSV();
    //CRIANDO TODAS AS THREADS QUE EXECUTARÃO SIMULTANEAMENTE
    pthread_create(&SOCKET_PTHREAD_ID, NULL, start_socket, NULL);
    pthread_create(&READ_PTHREAD_ID, NULL, read_menu, NULL);
    pthread_join(SOCKET_PTHREAD_ID, NULL);
    pthread_join(READ_PTHREAD_ID, NULL);
}
void finish(){
    pthread_cancel(SOCKET_PTHREAD_ID);
    pthread_cancel(READ_PTHREAD_ID);
}
void force_finish(int signal){
    finish();
}
int main(int argc, const char * argv[]) {
    signal(SIGINT, force_finish);
    signal(SIGKILL, force_finish);
    start();
}