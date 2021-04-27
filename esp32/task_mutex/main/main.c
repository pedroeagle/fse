#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

float temperatura;
xSemaphoreHandle mutexIC;
float acessa_i2c(int comando){
    if(comando == 1){
        ESP_LOGI("I2C", "Leitura do sensor de Temperatura");
        return 20.0 + ((float) rand()/(float)(RAND_MAX/10));
    }else{
        ESP_LOGI("I2C", "Escrita do LCD");
        printf("Tela LCD - Temperatura = %f", temperatura);
    }
    return 0;
}
void le_sensor(void * params){
    while(true){
        if(xSemaphoreTake(mutexIC, 1000/portTICK_PERIOD_MS)){
            temperatura = acessa_i2c(1);
            ESP_LOGI("Leitura", "Temperatura lida: %f", temperatura);
            xSemaphoreGive(mutexIC);
        }else{
            ESP_LOGE("Leitura", "Não foi possível ler o sensor");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void lcd_display(void * params){
    while(true){
        if(xSemaphoreTake(mutexIC, 1000/portTICK_PERIOD_MS)){
            ESP_LOGI("Display", "Escreve no LCD");
            acessa_i2c(2);
            xSemaphoreGive(mutexIC);
        }
        else{
            ESP_LOGE("Display", "Não foi possível escrever no display");
        }
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    mutexIC = xSemaphoreCreateMutex();

    xTaskCreate(&le_sensor, "Leitura Sensor 1", 2048, NULL, 2, NULL);
    xTaskCreate(&lcd_display, "Display Sensor", 2048, NULL, 2, NULL);
}
