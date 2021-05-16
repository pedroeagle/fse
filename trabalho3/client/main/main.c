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

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle sendDataMQTTSemaphore;

#define GPIO_DHT CONFIG_ESP_DHT_GPIO_NUMBER
#define GPIO_LED CONFIG_ESP_LED_GPIO_NUMBER
#define GPIO_BUTTON CONFIG_ESP_BUTTON_GPIO_NUMBER

xQueueHandle filaDeInterrupcao;
cJSON *temperature = NULL;
cJSON *humidity = NULL;

static void IRAM_ATTR gpio_isr_handler(void *args) {
    int pino = (int)args;
    xQueueSendFromISR(filaDeInterrupcao, &pino, NULL);
}

void trataInterrupcaoBotao(void *params) {
    int pino;
    int contador = 0;

    while (true) {
        if (xQueueReceive(filaDeInterrupcao, &pino, portMAX_DELAY)) {
            int estado = gpio_get_level(pino);
            if (estado == 0) {
                gpio_isr_handler_remove(pino);
                int contadorPressionado = 0;
                printf("Apertou o botão\n");
                while (gpio_get_level(pino) == estado) {
                    vTaskDelay(50 / portTICK_PERIOD_MS);
                    contadorPressionado++;
                    printf("Manteve o botão pressionado: %d\n",
                           contadorPressionado);
                    if (contadorPressionado == 50) {
                        printf("Reseta ESP-32\n");
                        break;
                    }
                }

                contador++;
                printf("Os botões foram acionados %d vezes. Botão: %d\n",
                       contador, pino);
                gpio_set_level(GPIO_LED, contador % 2);

                char valor_lido[200];
                int result = le_valor_nvs("comodo_path", valor_lido);
                if (result > 0) {
                    printf("Valor que li: %s\n", valor_lido);
                }

                // Habilitar novamente a interrupção
                vTaskDelay(50 / portTICK_PERIOD_MS);
                gpio_isr_handler_add(pino, gpio_isr_handler, (void *)pino);
            }
        }
    }
}

void conectadoWifi(void *params) {
    while (true) {
        if (xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY)) {
            // Processamento Internet
            mqtt_start();
        }
    }
}

void enviaDadosServidor(void *params) {
    if (xSemaphoreTake(sendDataMQTTSemaphore, portMAX_DELAY)) {
        char comodo_path[200];
        int result = le_valor_nvs("comodo_path", comodo_path);
        if (result > 0) {
            printf("valor lido da func: %s\n", comodo_path);
        }

        while (true) {
            float humValue, tempValue;
            dht_read_float_data(DHT_TYPE_DHT11, GPIO_DHT, &humValue,
                                &tempValue);

            humidity = cJSON_CreateNumber(humValue);
            temperature = cJSON_CreateNumber(tempValue);

            char pathHum[200], pathTemp[200];

            strcpy(pathHum, comodo_path);
            strcat(pathHum, "umidade");

            strcpy(pathTemp, comodo_path);
            strcat(pathTemp, "temperatura");

            printf("%s\n", pathHum);
            printf("%s\n", cJSON_Print(humidity));
            printf("%s\n", pathTemp);
            printf("%s\n", cJSON_Print(temperature));

            

            mqtt_envia_mensagem(pathHum, cJSON_Print(humidity));
            vTaskDelay(50 / portTICK_PERIOD_MS);
            mqtt_envia_mensagem(pathTemp, cJSON_Print(temperature));
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
}

void app_main() {
    // Inicializa o NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    uint8_t mac;
    esp_base_mac_addr_get(&mac);
    char central_path[100];
    strcpy(central_path, "fse2020/160000840/dispositivos/");
    itoa(mac, &central_path[strlen(central_path)], 10);

    grava_string_nvs("central_path", central_path);

    // Configuração dos pinos dos LEDs
    gpio_pad_select_gpio(GPIO_LED);
    // Configura os pinos dos LEDs como Output
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);

    // Configuração do pino do Botão
    gpio_pad_select_gpio(GPIO_BUTTON);
    // Configura o pino do Botão como Entrada
    gpio_set_direction(GPIO_BUTTON, GPIO_MODE_INPUT);

    // Configura o resistor de Pull-up para o botão (por padrão a entrada
    // estará em Um)
    gpio_pullup_en(GPIO_BUTTON);

    // Desabilita o resistor de Pull-down por segurança.
    gpio_pulldown_dis(GPIO_BUTTON);

    // Configura pino para interrupção
    gpio_set_intr_type(GPIO_BUTTON, GPIO_INTR_NEGEDGE);

    // Inicializa semáforos
    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    sendDataMQTTSemaphore = xSemaphoreCreateBinary();

    // Inicializa módulo WI-FI
    wifi_start();

    filaDeInterrupcao = xQueueCreate(10, sizeof(int));
    xTaskCreate(&trataInterrupcaoBotao, "TrataBotao", 2048, NULL, 1, NULL);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_BUTTON, gpio_isr_handler, (void *)GPIO_BUTTON);

    xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
    xTaskCreate(&enviaDadosServidor, "Envio de dados", 4096, NULL, 1, NULL);

    // xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096,
    //             NULL, 1, NULL);
}