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
#include "esp_sleep.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "flash.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "mqtt.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "send.h"
#include "wifi.h"

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle sendDataMQTTSemaphore;

#define GPIO_DHT CONFIG_ESP_DHT_GPIO_NUMBER
#define GPIO_LED CONFIG_ESP_LED_GPIO_NUMBER
#define GPIO_BUTTON CONFIG_ESP_BUTTON_GPIO_NUMBER

char central_path[150], comodo_path[150];
char humid_path[150], temp_path[150], state_path[150];
int flag_run = 0;
xQueueHandle filaDeInterrupcao;

static void IRAM_ATTR gpio_isr_handler(void *args) {
    int pino = (int)args;
    xQueueSendFromISR(filaDeInterrupcao, &pino, NULL);
}

void piscaLed() {
    for (int blips = 3; blips >= 0; blips--) {
        gpio_set_level(GPIO_LED, 1);
        vTaskDelay(400 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_LED, 0);
        vTaskDelay(400 / portTICK_PERIOD_MS);
    }
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
                        piscaLed();
                        nvs_flash_erase_partition("DadosNVS");
                        esp_restart();
                        break;
                    }
                }

                contador++;
                printf("O botão foi acionado %d vezes. Botão: %d\n", contador,
                       pino);

                int32_t estado_entrada = le_int32_nvs("estado_entrada");
                estado_entrada = estado_entrada ? 0 : 1;
                grava_int32_nvs("estado_entrada", estado_entrada);

                enviaEstadosCentral();

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

void definePaths() {
    memset(comodo_path, '\0', sizeof comodo_path);
    int result = le_valor_nvs("comodo_path", comodo_path);
    if (result > 0) {
        printf("valor lido da func: %s\n", comodo_path);
    }
    // Define "path" de Umidade
    memset(humid_path, '\0', sizeof humid_path);
    strcpy(humid_path, comodo_path);
    strcat(humid_path, "umidade");

    // Define "path" de Temperatura
    memset(temp_path, '\0', sizeof temp_path);
    strcpy(temp_path, comodo_path);
    strcat(temp_path, "temperatura");

    // Define "path" de Estado
    memset(state_path, '\0', sizeof state_path);
    strcpy(state_path, comodo_path);
    strcat(state_path, "estado");
}

void startSleep() {
    // Coloca a ESP no Deep Sleep
    esp_deep_sleep_start();
}

void trataBotaoPressionadoLowPower() {
    // Trata segurar botão para reiniciar
    int estado = gpio_get_level(GPIO_BUTTON);
    if (estado == 0) {
        gpio_isr_handler_remove(GPIO_BUTTON);
        int contadorPressionado = 0;
        printf("Apertou o botão\n");
        while (gpio_get_level(GPIO_BUTTON) == estado) {
            vTaskDelay(50 / portTICK_PERIOD_MS);
            contadorPressionado++;
            printf("Manteve o botão pressionado: %d\n", contadorPressionado);
            if (contadorPressionado == 50) {
                piscaLed();
                nvs_flash_erase_partition("DadosNVS");
                esp_restart();
                break;
            }
        }
        // Habilitar novamente a interrupção
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_isr_handler_add(GPIO_BUTTON, gpio_isr_handler,
                             (void *)GPIO_BUTTON);
    }
}

void enviaDadosServidor(void *params) {
    if (xSemaphoreTake(sendDataMQTTSemaphore, portMAX_DELAY)) {
        // Define os paths
        definePaths();

#ifdef CONFIG_BATERIA
        // Trata Botão pressionado
        trataBotaoPressionadoLowPower();

        // Trata botão pressionado ao acordar
        if (flag_run) {
            printf("O botão foi acionado. Botão: %d\n", GPIO_BUTTON);
            int32_t estado_entrada = le_int32_nvs("estado_entrada");
            estado_entrada = estado_entrada ? 0 : 1;
            grava_int32_nvs("estado_entrada", estado_entrada);

            enviaEstadosCentral();
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        } else {
            enviaEstadosCentral();
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }

        printf("Entrando em modo sleep...\n");
        startSleep();
#else
        enviaEstadosCentral();
#endif

        // Loop da task
        while (true) {
#ifdef CONFIG_ENERGIA
            float humValue, tempValue;
            dht_read_float_data(DHT_TYPE_DHT11, GPIO_DHT, &humValue,
                                &tempValue);

            cJSON *humidity = cJSON_CreateNumber(humValue);
            cJSON *temperature = cJSON_CreateNumber(tempValue);

            cJSON *resHumidity = cJSON_CreateObject();
            cJSON *resTemperature = cJSON_CreateObject();

            cJSON_AddItemReferenceToObject(resHumidity, "umidade", humidity);
            cJSON_AddItemReferenceToObject(resTemperature, "temperatura",
                                           temperature);

            mqtt_envia_mensagem(humid_path, cJSON_Print(resHumidity));
            vTaskDelay(50 / portTICK_PERIOD_MS);
            mqtt_envia_mensagem(temp_path, cJSON_Print(resTemperature));
            vTaskDelay(2000 / portTICK_PERIOD_MS);

            cJSON_Delete(resHumidity);
            cJSON_Delete(resTemperature);
#endif
        }
    }
}

void configuraGPIO() {
    // Configuração dos pinos dos LEDs
    gpio_pad_select_gpio(GPIO_LED);
    // Configura os pinos dos LEDs como Output
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);

    // Configuração do pino do Botão
    gpio_pad_select_gpio(GPIO_BUTTON);
    // Configura o pino do Botão como Entrada
    gpio_set_direction(GPIO_BUTTON, GPIO_MODE_INPUT);

    int32_t estado_saida = le_int32_nvs("estado_saida");
    gpio_set_level(GPIO_LED, estado_saida);

    // Configura o resistor de Pull-up para o botão (por padrão a entrada
    // estará em Um)
    gpio_pullup_en(GPIO_BUTTON);

    // Desabilita o resistor de Pull-down por segurança.
    gpio_pulldown_dis(GPIO_BUTTON);

    // Configura pino para interrupção
    gpio_set_intr_type(GPIO_BUTTON, GPIO_INTR_NEGEDGE);

#ifdef CONFIG_BATERIA
    // Configura o retorno
    esp_sleep_enable_ext0_wakeup(GPIO_BUTTON, 0);
    printf("Botão: Interrupções em modo Wake\n");
#endif
}

void defineCentralPath() {
    // Cria e salva o path home
    uint8_t mac[6] = {0};
    char mac_address[14];

    memset(mac_address, '\0', sizeof mac_address);
    memset(central_path, '\0', sizeof central_path);

    esp_efuse_mac_get_default(mac);
    sprintf(mac_address, "%x%x%x%x%x%x", mac[0], mac[1], mac[2], mac[3], mac[4],
            mac[5]);
    strcpy(central_path, "fse2020/160000840/dispositivos/");
    strcat(central_path, mac_address);
    grava_string_nvs("central_path", central_path);
}

void defineVariaveisEstado() {
    int32_t estado_entrada = le_int32_nvs("estado_entrada");
    if (estado_entrada == -1) {
        estado_entrada = 0;
        grava_int32_nvs("estado_entrada", estado_entrada);
    }

    int32_t estado_saida = le_int32_nvs("estado_saida");
    if (estado_saida == -1) {
        estado_saida = 0;
        grava_int32_nvs("estado_saida", estado_saida);
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

    int result = le_valor_nvs("central_path", central_path);
    if (result == -1) {
        defineCentralPath();
        defineVariaveisEstado();
    } else {
        printf("Path central: %s\n", central_path);
        flag_run = 1;
    }

    // Configura GPIO
    configuraGPIO();

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
    if (flag_run) {
        xSemaphoreGive(sendDataMQTTSemaphore);
    }
}