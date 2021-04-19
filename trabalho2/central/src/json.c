#include "cJSON.h"
#include "status.h"
#include "json.h"

void remove_quotes(char *string){
    int length = strlen(string);
    char fixed_string[500];
    int j = 0;
    for(int i = 0; i < length; i++){
        if(string[i]!='"'){
            fixed_string[j] = string[i];
            j++;
        }
    }
    fixed_string[j] = 0;
    strcpy(string, fixed_string);
}

char * get_json(int turn_on, int turn_off){
    char * out;
    cJSON *root;
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "turn_on", cJSON_CreateNumber(turn_on));
    cJSON_AddItemToObject(root, "turn_off", cJSON_CreateNumber(turn_off));
    out = cJSON_Print(root);
    return out;
}

void match_json_with_devices(char * json){
    cJSON *root, * bme280, * sensors, * presence, * open, * outs, * lights, * airs;
    root = cJSON_Parse(json);
    bme280 = cJSON_GetObjectItem(root, "bme280");
    TEMPERATURE = atof(cJSON_Print(cJSON_GetObjectItem(bme280, "temperature")));
    HUMIDITY = atof(cJSON_Print(cJSON_GetObjectItem(bme280, "humidity")));

    sensors = cJSON_GetObjectItem(root, "sensors");

    presence = cJSON_GetObjectItem(sensors, "presence");
    for(int i = 0; i < get_presence_sensors_lenght(); i++){
        cJSON *item = cJSON_GetArrayItem(presence, i);
        presence_sensors[i].port = atoi(cJSON_Print(cJSON_GetObjectItem(item, "port")));
        presence_sensors[i].value = atoi(cJSON_Print(cJSON_GetObjectItem(item, "value")));
        strcpy(presence_sensors[i].name, cJSON_Print(cJSON_GetObjectItem(item, "name")));
        remove_quotes(presence_sensors[i].name);
    }
    open = cJSON_GetObjectItem(sensors, "open");
    for(int i = 0; i < get_open_sensors_lenght(); i++){
        cJSON *item = cJSON_GetArrayItem(open, i);
        open_sensors[i].port = atoi(cJSON_Print(cJSON_GetObjectItem(item, "port")));
        open_sensors[i].value = atoi(cJSON_Print(cJSON_GetObjectItem(item, "value")));
        strcpy(open_sensors[i].name, cJSON_Print(cJSON_GetObjectItem(item, "name")));
        remove_quotes(open_sensors[i].name);
    }

    outs = cJSON_GetObjectItem(root, "outs");

    lights = cJSON_GetObjectItem(outs, "lights");
    for(int i = 0; i < get_light_outs_lenght(); i++){
        cJSON *item = cJSON_GetArrayItem(lights, i);
        light_outs[i].port = atoi(cJSON_Print(cJSON_GetObjectItem(item, "port")));
        light_outs[i].value = atoi(cJSON_Print(cJSON_GetObjectItem(item, "value")));
    }
    airs = cJSON_GetObjectItem(outs, "airs");
    for(int i = 0; i < get_air_outs_lenght(); i++){
        cJSON *item = cJSON_GetArrayItem(airs, i);
        air_outs[i].port = atoi(cJSON_Print(cJSON_GetObjectItem(item, "port")));
        air_outs[i].value = atoi(cJSON_Print(cJSON_GetObjectItem(item, "value")));
    }
}