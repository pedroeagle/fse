#ifndef UART_H_
#define UART_H_
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include "crc16.h"
#include "display.h"
#include "i2c.h"
int UART();
float get_internal_temperature_uart(int uart);
float get_potentiometer_temperature_uart(int uart);
//void * update_temperatures(void * vargp);
float get_potentiometer_temperature();
float get_internal_temperature();
float get_external_temperature();
#endif