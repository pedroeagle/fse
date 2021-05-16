#ifndef FLASH_H
#define FLASH_H

#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"

int le_valor_nvs(char* var_name, char* ref_value);

void grava_string_nvs(char* var_name, char* var_value);

int32_t le_int32_nvs(char* var_name);

void grava_int32_nvs(char* var_name, int32_t valor);

#endif