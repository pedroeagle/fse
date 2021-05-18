#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>

#include "cJSON.h"
#include "dht.h"
#include "driver/gpio.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "flash.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "mqtt.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "wifi.h"

extern char state_path[100];

void enviaEstadosCentral() {
    cJSON *estado_json = cJSON_CreateObject();

    cJSON *entrada_json;
    int32_t estado_entrada = le_int32_nvs("estado_entrada");
    if (estado_entrada) {
        entrada_json = cJSON_CreateTrue();
    } else {
        entrada_json = cJSON_CreateFalse();
    }
    cJSON_AddItemReferenceToObject(estado_json, "entrada", entrada_json);

#ifdef CONFIG_ENERGIA
    cJSON *saida_json = cJSON_CreateFalse();
    int32_t estado_saida = le_int32_nvs("estado_saida");
    if (estado_saida) {
        saida_json = cJSON_CreateTrue();
    } else {
        saida_json = cJSON_CreateFalse();
    }
    cJSON_AddItemReferenceToObject(estado_json, "saida", saida_json);
#endif

    cJSON *res_estado = cJSON_CreateObject();
    cJSON_AddItemReferenceToObject(res_estado, "estado", estado_json);
    mqtt_envia_mensagem(state_path, cJSON_Print(res_estado));
    cJSON_Delete(res_estado);
}