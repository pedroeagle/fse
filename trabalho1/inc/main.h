#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clear_terminal(){
    system("clear");
    fflush(stdin);
}
void temperature_menu(){
    printf("####################    MONITOR  DE TEMPERATURA   ####################\n");
    printf("Temperaturas atuais: \n");
    printf("XXXXXXXXXXXX\n\n");
    printf("-----------------------------------------------------------------------\n");
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
void menu(){
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
}


#endif