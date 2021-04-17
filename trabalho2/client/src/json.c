#include "cJSON.h"
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