#include <stdio.h>
#include <string.h>

#include "cJSON.h"
#include "parser.h"

void parse_json(const char *response) {
    const cJSON *esp_host = NULL;
    cJSON *response_json = cJSON_Parse(response);
    if (response_json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error before: %s\n", error_ptr);
            cJSON_Delete(response_json);
        }
    }

    esp_host = cJSON_GetObjectItemCaseSensitive(response_json, "esp_host");
    if (cJSON_IsString(esp_host) && (esp_host->valuestring != NULL))
    {
        printf("String recebida: \"%s\"\n", esp_host->valuestring);
    }
}