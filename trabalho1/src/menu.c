#include "menu.h"
#include "temperature.h"

void clear_terminal(){
    system("clear");
    fflush(stdin);
}
void temperature_menu(){
    while(!get_potentiometer_temperature() || !get_internal_temperature() || !get_external_temperature()){
        usleep(500);
    }
    printf("OK!\n");
    float temperatura_potenciometro = get_potentiometer_temperature();
    float temperatura_interna = get_internal_temperature();
    float temperatura_externa= get_external_temperature();
    float temperatura_referencia = get_reference_temperature();
    float temperatura_terminal = get_terminal_temperature();
    printf("####################    MONITOR  DE TEMPERATURA   ####################\n");
    printf("Temperaturas atuais: \n");
    printf("TI: %.2f, TE: %.2f, TP: %.2f, TT: %.2f, TR: %.2f\n\n", temperatura_interna, temperatura_externa, temperatura_potenciometro, temperatura_terminal, temperatura_referencia);
    printf("----------------------------------------------------------------------\n");
}
float read_terminal(){
    float MAX = 100.00, MIN = get_external_temperature();
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
                set_terminal_temperature(-1.0);
                set_reference_temperature(get_potentiometer_temperature());
                break;
            case '2':
                set_terminal_temperature(read_terminal());
                set_reference_temperature(get_terminal_temperature());
                break;
        }
    }while(option!='0');
    finish();
    return;
}