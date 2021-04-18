#include "json.h"
#include "cJSON.h"

char * gpio_component_to_json_string(gpio_component * gpio_comps, int length){
    char * out;
    cJSON *root, *sensor;
    root = cJSON_CreateArray();
    for(int i =0; i < length; i++){
        cJSON_AddItemToArray(root, sensor = cJSON_CreateObject());
        cJSON_AddItemToObject(sensor, "port", cJSON_CreateNumber(gpio_comps[i].port));
        cJSON_AddItemToObject(sensor, "value", cJSON_CreateNumber(gpio_comps[i].value));
        cJSON_AddItemToObject(sensor, "name", cJSON_CreateString(gpio_comps[i].name));
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
    return out;
}

char * get_json(){
    char * out; 
    cJSON * root, * sensors, * open, * presence, * air, * light, * outs;
    open = cJSON_Parse(gpio_component_to_json_string(open_sensors, get_open_sensors_lenght()));
    presence = cJSON_Parse(gpio_component_to_json_string(presence_sensors, get_presence_sensors_lenght()));
    light = cJSON_Parse(gpio_component_to_json_string(light_outs, get_light_outs_lenght()));
    air = cJSON_Parse(gpio_component_to_json_string(air_outs, get_air_outs_lenght()));
    root = cJSON_CreateObject();
    sensors = cJSON_CreateObject();
    outs = cJSON_CreateObject();
    cJSON_AddItemToObject(sensors, "presence", presence);
    cJSON_AddItemToObject(sensors, "open", open);
    cJSON_AddItemToObject(outs, "lights", light);
    cJSON_AddItemToObject(outs, "airs", air);
    cJSON_AddItemToObject(root, "bme280", cJSON_Parse(i2c_values_to_json_string()));
    cJSON_AddItemToObject(root, "sensors", sensors);
    cJSON_AddItemToObject(root, "outs", outs);
    out = cJSON_Print(root);
    return out;
}

void parse_json(char * json){
    cJSON *root, *toggle, *alarm, *auto_mode;
    root = cJSON_Parse(json);
    toggle = cJSON_GetObjectItem(root, "toggle");
    alarm = cJSON_GetObjectItem(root, "alarm");
    auto_mode = cJSON_GetObjectItem(root, "auto_mode");
    ALARM = atoi(cJSON_Print(alarm));
    AUTO_MODE = atoi(cJSON_Print(auto_mode));
    int port = atoi(cJSON_Print(toggle));
    if(port>=0){
        toggle(port);
    }
}