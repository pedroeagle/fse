#include "cJSON.h"
#include "status.h"
#include "json.h"


char * get_toggle_device_json(int port){
    char * out;
    cJSON *root;
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "toggle", cJSON_CreateNumber(port));
    out = cJSON_Print(root);
    printf("%s\n", out);
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
    }
    open = cJSON_GetObjectItem(sensors, "open");
    for(int i = 0; i < get_open_sensors_lenght(); i++){
        cJSON *item = cJSON_GetArrayItem(open, i);
        open_sensors[i].port = atoi(cJSON_Print(cJSON_GetObjectItem(item, "port")));
        open_sensors[i].value = atoi(cJSON_Print(cJSON_GetObjectItem(item, "value")));
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