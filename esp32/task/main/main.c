#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void task1(void * params){
    while(true){
        //printf("Leitura de sensores\n");
        ESP_LOGI("TASK 1", "Realizando leitura de sensores");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void task2(void * params){
    while(true){
        ESP_LOGI("TASK 2", "Mostrando no Display");
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(&task1, "leitura", 2048, "Task 1", 1, NULL);
    xTaskCreate(&task2, "display", 2048, "Task 2", 1, NULL);
}
