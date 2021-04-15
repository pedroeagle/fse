#include "json.h"
#include "cJSON.h"
char * open_sensors_to_json_string(){
    char * out;
    cJSON *root, *sensores_list, *sensor;
    root = cJSON_CreateArray();
    int length = sizeof(open_sensors)/sizeof(open_sensors[0]);
    for(int i =0; i < length; i++){
        cJSON_AddItemToArray(root, sensor = cJSON_CreateObject());
        cJSON_AddItemToObject(sensor, "port", cJSON_CreateNumber(open_sensors[i].port));
        cJSON_AddItemToObject(sensor, "value", cJSON_CreateNumber(open_sensors[i].value));
        out = cJSON_Print(root);
    }
    return out;
}
char * presence_sensors_to_json_string(){
    char * out;
    cJSON *root, *sensores_list, *sensor;
    root = cJSON_CreateArray();
    int length = sizeof(presence_sensors)/sizeof(presence_sensors[0]);
    for(int i =0; i < length; i++){
        cJSON_AddItemToArray(root, sensor = cJSON_CreateObject());
        cJSON_AddItemToObject(sensor, "port", cJSON_CreateNumber(presence_sensors[i].port));
        cJSON_AddItemToObject(sensor, "value", cJSON_CreateNumber(presence_sensors[i].value));
        out = cJSON_Print(root);
    }
    return out;
}
char * i2c_values_to_json_string(){
    char * out;
    cJSON *root, *values;
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "temperature", cJSON_CreateNumber(read_temperature()));
    cJSON_AddItemToObject(root, "humidity", cJSON_CreateNumber(read_humidity()));
    out = cJSON_Print(root);
    printf("%s\n", out);
    return out;
}

char * get_json(){
    char * out;
    cJSON * root, * sensors, * open, * presence;
    open = cJSON_Parse(open_sensors_to_json_string());
    presence = cJSON_Parse(presence_sensors_to_json_string());
    root = cJSON_CreateObject();
    sensors = cJSON_CreateObject();
    cJSON_AddItemToObject(sensors, "presence", presence);
    cJSON_AddItemToObject(sensors, "open", open);
    cJSON_AddItemToObject(root, "bme280", cJSON_Parse(i2c_values_to_json_string()));
    cJSON_AddItemToObject(root, "sensors", sensors);
    out = cJSON_Print(root);
    printf("%s\n", out);
    return out;
}