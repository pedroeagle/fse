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

void conectadoWifi(void * params)
{
  while(true)
  {
    if(xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }
  }
}

void trataComunicacaoComServidor(void * params)
{
  char mensagem[50];
  if(xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    while(true)
    {
       float temperatura = 20.0 + (float)rand()/(float)(RAND_MAX/10.0);
       sprintf(mensagem, "temperatura1: %f", temperatura);
       mqtt_envia_mensagem("sensores/temperatura", mensagem);
       vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
  }
}

void app_main()
{
  gpio_num_t GPIO_SENSOR_NUM = 16;
  float t, h;
  while(true){
    dht_read_float_data(DHT_TYPE_DHT11, GPIO_SENSOR_NUM, &t, &h);
    ESP_LOGI("DHT11", "temperature: %f, humidity: %f", t, h);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
  }
}