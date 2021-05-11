#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_system.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "dht.h"
//#include <dht/dht.h>
#include "wifi.h"
#include "http_client.h"
#include "mqtt.h"
xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle conexaoMQTTSemaphore;
gpio_num_t GPIO_SENSOR_NUM = 16;
void conectadoWifi(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }
  }
}

void trataComunicacaoComServidor(void *params)
{
  char mensagem[50];
  if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    while (true)
    {
      uint8_t mac;
      esp_base_mac_addr_get(&mac);
      float t, h;
      dht_read_float_data(DHT_TYPE_DHT11, GPIO_SENSOR_NUM, &t, &h);
      sprintf(mensagem, "temperatura1: %f", t);
      char path[100];
      strcpy(path, "fse2020/170062635/dispositivos/");
      itoa(mac, &path[strlen(path)], 10);
      ESP_LOGI("A", "%d\n", mac);
      mqtt_envia_mensagem(path, mensagem);
      vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
  }
}

void app_main()
{
  // Inicializa o NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();
  wifi_start();

  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
  xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
}