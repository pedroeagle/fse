#include "parser.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "cJSON.h"
#include "flash.h"

extern xSemaphoreHandle sendDataMQTTSemaphore;

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
    if (cJSON_IsString(esp_host) && (esp_host->valuestring != NULL)) {
        grava_string_nvs("comodo_path", esp_host->valuestring);
        printf("String recebida: \"%s\"\n", esp_host->valuestring);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        xSemaphoreGive(sendDataMQTTSemaphore);
    }
    cJSON_Delete(response_json);
}