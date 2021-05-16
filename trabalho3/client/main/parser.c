#include "parser.h"

#include <string.h>

#include "cJSON.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "nvs_flash.h"

extern xSemaphoreHandle sendDataMQTTSemaphore;
extern int flag_run;

// #define MODO_ENERGIA CONFIG_ENERGIA
// #define MODO_BATERIA CONFIG_BATERIA

char *define_modo_json() {
    cJSON *modo_json;
    cJSON *res_modo = cJSON_CreateObject();

    #ifdef CONFIG_BATERIA
        modo_json = cJSON_CreateString("bateria");
    #else
        modo_json = cJSON_CreateString("energia");
    #endif
    cJSON_AddItemReferenceToObject(res_modo, "modo", modo_json);
    return cJSON_Print(res_modo);
    // cJSON_Delete(res_modo);
}

void parse_json(const char *response) {
    const cJSON *esp_host = NULL;
    cJSON *response_json = cJSON_Parse(response);
    if (response_json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error before: %s\n", error_ptr);
        }
    }

    esp_host = cJSON_GetObjectItemCaseSensitive(response_json, "esp_host");
    if (cJSON_IsString(esp_host) && (esp_host->valuestring != NULL) && flag_run == 0) {
        grava_string_nvs("comodo_path", esp_host->valuestring);
        printf("String recebida: \"%s\"\n", esp_host->valuestring);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        xSemaphoreGive(sendDataMQTTSemaphore);
    }
    cJSON_Delete(response_json);
}