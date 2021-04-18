#include "status.h"
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