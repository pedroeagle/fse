#ifndef GPIO_H_
#define GPIO_H_

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 

int GPIO();
int TURN_OFF_GPIO();
void turn_on_fan(int intensity);
void turn_on_resistor(int intensity);
void turn_off();
#endif