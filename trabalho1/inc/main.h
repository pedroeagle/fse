#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uart.h"
#include "crc16.h"
#include "uart.h"
#include "display.h"
#include "gpio.h"
#include "pid.h"
#include "csv.h"
#include "i2c.h"

pthread_t get_update_temperatures_pthread_id();
void clear_terminal(){
    system("clear");
    fflush(stdin);
}
void temperature_menu(){
    if(!get_potentiometer_temperature() || !get_internal_temperature()){
        delay(2000);
    }
    float temperatura_potenciometro = get_potentiometer_temperature();
    float temperatura_interna = get_internal_temperature();
    float temperatura_externa= get_external_temperature();
    //while(!temperatura_potenciometro || !temperatura_interna);
    printf("####################    MONITOR  DE TEMPERATURA   ####################\n");
    printf("Temperaturas atuais: \n");
    printf("TI: %lf, TR: %lf, TE: %lf\n\n", temperatura_interna, temperatura_potenciometro, temperatura_externa);
    printf("----------------------------------------------------------------------\n");
}
float read_terminal(){
    float MAX = 80.00, MIN = 10.0;
    float temperature = -1;
    int error = 0;
    do{
        clear_terminal();
        temperature_menu();
        if(error){
            
            printf("A temperatura deve ser maior que %f e menor que %f\n", MIN, MAX);
        }
        printf("Digite a temperatura desejada: ");
        scanf("%f", &temperature);
        getchar();
        if(temperature < MIN || temperature > MAX ){
            error=1;
        }
    }while(temperature < MIN || temperature > MAX);
    return temperature;
}
void  * menu(void *vargp){
    char option;
    do{
        clear_terminal();
        temperature_menu();
        printf("Selecione uma das opções:\n");
        printf("1 - DEFINIR TEMPERATURA A PARTIR DO POTENCIÔMETRO\n");
        printf("2 - DEFINIR TEMPERATURA A PARTIR DO TERMINAL\n");
        printf("0 - FINALIZAR O PROGRAMA\n");

        printf("Pressione ENTER para atualizar as temperaturas.\n");
        option = getchar();
        switch(option){
            case '1':
                break;
            case '2':
                read_terminal();
        }
    }while(option!='0');
    pthread_cancel(get_update_temperatures_pthread_id());
}


#endif