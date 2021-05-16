#include "flash.h"

#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"

int le_valor_nvs(char* var_name, char* ref_value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition("DadosNVS"));

    // Declara o handle
    nvs_handle particao_padrao_handle;

    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(
        "DadosNVS", "armazenamento", NVS_READONLY, &particao_padrao_handle);

    if (res_nvs == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGE("NVS", "Namespace: armazenamento, não encontrado");
    } else {
        // Lê tamanho do dado armazenado
        size_t required_size;
        nvs_get_str(particao_padrao_handle, var_name, NULL, &required_size);

        // Obtem variável
        char* value = malloc(required_size);
        esp_err_t res = nvs_get_str(particao_padrao_handle, var_name, value,
                                    &required_size);
        switch (res) {
            case ESP_OK:
                strcpy(ref_value, value);
                printf("Valor armazenado: %s\n", value);
                break;
            case ESP_ERR_NOT_FOUND:
                ESP_LOGE("NVS", "Valor não encontrado");
                return -1;
            default:
                ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)",
                         esp_err_to_name(res));
                return -1;
                break;
        }
    }
    nvs_close(particao_padrao_handle);
    return 1;
}

void grava_string_nvs(char* var_name, char* var_value) {
    // Inicia partição
    ESP_ERROR_CHECK(nvs_flash_init_partition("DadosNVS"));

    nvs_handle particao_padrao_handle;

    // Abre partição para escrita
    esp_err_t res_nvs = nvs_open_from_partition(
        "DadosNVS", "armazenamento", NVS_READWRITE, &particao_padrao_handle);

    if (res_nvs == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGE("NVS", "Namespace: armazenamento, não encontrado");
    }
    esp_err_t res = nvs_set_str(particao_padrao_handle, var_name, var_value);
    if (res != ESP_OK) {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)",
                 esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}
