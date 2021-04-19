#include "alarm.h"
#include "status.h"
#include <pthread.h>
void  * play_alarm(void *vargp){
    printf("ALARM %d\n", check_alarm());
    while(check_alarm()==1){
        char command[1000], cwd[500];
        strcpy(command, "aplay ");
        getcwd(cwd, sizeof(cwd));
        strcat(command, cwd);
        strcat(command, "/audio/alarm.mp3");
        system(command);
        printf("Tocando alarme\n");
    }
    pthread_exit(NULL);
}

int check_alarm(){
    for(int i = 0; i < get_open_sensors_lenght(); i++){
        if(open_sensors[i].value){
            return getAlarm();
        }
    }
    for(int i = 0; i < get_presence_sensors_lenght(); i++){
        if(presence_sensors[i].value){
            return getAlarm();
        }
    }
}