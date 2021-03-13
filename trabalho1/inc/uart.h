#ifndef UART_
#define UART_
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <stdio.h>
#include <string.h>
#include "crc16.h"
int UART();
float get_internal_temperature(int uart);
#endif