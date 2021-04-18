#include <pthread.h>
#include <signal.h>
#include "socket.h"
#include "menu.h"
#include "client.h"

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