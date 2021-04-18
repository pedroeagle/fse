#include "alarm.h"
void play_alarm(){
    char command[1000], cwd[500];
    strcpy(command, "aplay ");
    getcwd(cwd, sizeof(cwd));
    strcat(command, cwd);
    strcat(command, "/audio/alarm.mp3");
    while(1){
        system(command);
    }
}