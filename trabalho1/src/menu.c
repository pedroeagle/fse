#include "menu.h"
#include "temperature.h"

const char * Black = "\033[0;30m";
const char * Red = "\033[0;31m";
const char * Green = "\033[0;32m";
const char * Yellow = "\033[0;33m";
const char * Blue = "\033[0;34m";
const char * Purple = "\033[0;35m";
const char * Cyan = "\033[0;36m";
const char * White = "\033[0;37m";
const char * White_Bold = "\033[1;37m";
const char * Blue_Bold = "\033[1;34m";

void clear_terminal(){
    system("clear");
    fflush(stdout);
}
void temperature_menu(){
    while(!get_potentiometer_temperature() || !get_internal_temperature() || !get_external_temperature()){
        usleep(500);
    }
    float temperatura_potenciometro = get_potentiometer_temperature();
    float temperatura_interna = get_internal_temperature();
    float temperatura_externa= get_external_temperature();
    float temperatura_referencia = get_reference_temperature();
    float temperatura_terminal = get_terminal_temperature();
    float temperatures_string[100];
    sprintf(temperatures_string, "       TI: %.2f, TE: %.2f, TP: %.2f, TT: %.2f, TR: %.2f", temperatura_interna, temperatura_externa, temperatura_potenciometro, temperatura_terminal, temperatura_referencia);
    for(int i = strlen(temperatures_string)+1; i < 68; i++){
        strcat(temperatures_string, " ");
    }
    printf(Blue);
    printf("████████████████████");
    printf(White_Bold);
    printf("   MONITOR  DE TEMPERATURA    ");
    printf(Blue);
    printf("███████████████████\n");
    printf("|                                                                   |\n");
    printf("|");
    printf(White_Bold);
    printf(" Temperaturas atuais:                                              ");
    printf(Blue);
    printf("|\n");
    printf("|");
    printf(Green);
    printf("%s", temperatures_string);
    printf(Blue);
    printf("|\n");
    printf("|                                                                   |\n");
    printf("|");
    printf(Blue);
    printf("___________________________________________________________________");
    printf("|\n");
    printf("|                                                                   |\n");
}
float read_terminal(){
    float MAX = 100.00, MIN = get_external_temperature();
    float temperature = -1;
    int error = 0;
    do{
        clear_terminal();
        temperature_menu();
        if(error){
            printf(Blue);
            printf("|");
            char warn_string[100];
            sprintf(warn_string, "     A temperatura deve ser maior que %.2f e menor que %.2f", MIN, MAX);
            for(int i = strlen(warn_string)+1; i < 68; i++){
                strcat(warn_string, " ");
            }
            printf(Red);
            printf(warn_string);
            printf(Blue);
            printf("|\n");
        }
        printf(Blue);
        printf("|");
        printf(Yellow);
        printf("       Digite a temperatura desejada:                              ");
        printf(Blue);
        printf("|\n");
        printf(Blue);
        printf("|___________________________________________________________________|\n");
        printf(White_Bold);
        printf("\nTemperatura de Referência: ");
        printf(White);
        scanf("%f", &temperature);
        getchar();
        if(temperature < MIN || temperature > MAX ){
            error=1;
        }
    }while(temperature < MIN || temperature > MAX);
    return temperature;
}
int show_read = 1;
void menu(){
    if(show_read){
        clear_terminal();
        temperature_menu();
        printf(Blue);
        printf("|");
        printf(White_Bold);
        printf("   Selecione uma das opções:                                       ");
        printf(Blue);
        printf("|\n");
        printf("|");
        printf(Yellow);
        printf("       1 - DEFINIR TEMPERATURA A PARTIR DO POTENCIÔMETRO           ");
        printf(Blue);
        printf("|\n");
        printf("|");
        printf(Yellow);
        printf("       2 - DEFINIR TEMPERATURA A PARTIR DO TERMINAL                ");
        printf(Blue);
        printf("|\n");
        printf("|");
        printf(Red);
        printf("       0 - FINALIZAR O PROGRAMA                                    ");
        printf(Blue);
        printf("|\n");
        printf("|                                                                   |\n");
        printf("|___________________________________________________________________|\n");
        printf(White);
        printf("\n");
        return;
    }
}
void * read_menu(void *vargp){
    char option;
    do{
        option = 0;
        printf(White);
        option = getchar();
        switch(option){
            case '1':
                set_terminal_temperature(-1.0);
                set_reference_temperature(get_potentiometer_temperature());
                break;
            case '2':
                show_read = 0;
                set_terminal_temperature(read_terminal());
                show_read = 1;
                set_reference_temperature(get_terminal_temperature());
                break;
        }
    }while(option!='0');
    finish();
}
