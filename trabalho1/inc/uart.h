#ifndef UART_
#define UART_
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include "crc16.h"
int UART();
float get_internal_temperature_uart(int uart);
float get_potentiometer_temperature_uart(int uart);
void * update_temperatures(void * vargp);
float get_potentiometer_temperature();
float get_internal_temperature();
#endif