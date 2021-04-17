#include "menu.h"
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

/*void * read_menu(void *vargp){
    menu();
}*/

void status_menu(){
    printf(Blue);
    printf("█████████████████████");
    printf(White_Bold);
    printf("   CENTRAL DE CONTROLE    ");
    printf(Blue);
    printf("██████████████████████\n");
    printf("|                                                                   |\n");
    printf("|");
    printf(White_Bold);
    printf(" Temperatura: %05.2f Umidade: %05.2f                                 ", TEMPERATURE, HUMIDITY);
    printf(Blue);
    printf("|\n");
    printf("|");
    printf(White_Bold);
    printf(" LAMPADAS                                                          ");
    printf(Blue);
    printf("|\n");
    printf("|   ");
    for(int i = 0; i < get_light_outs_lenght(); i++){
        if(light_outs[i].value){
            printf(Green);
            printf("LAMPADA %d: ON   ", i+1);
        }else{
            printf(White);
            printf("LAMPADA %d: OFF  ", i+1);
        }
    }
    printf(Blue);
    printf("|\n");
    /*printf("|");
    printf(Green);
    printf("%s", "teste");
    printf(Blue);
    printf("|\n");*/
    printf("|                                                                   |\n");
    printf("|");
    printf(Blue);
    printf("___________________________________________________________________");
    printf("|\n");
    printf("|                                                                   |\n");
}
int show_read = 1;
void menu(){
    if(show_read){
        clear_terminal();
        status_menu();
        printf(Blue);
        printf("|");
        printf(White_Bold);
        printf("   Selecione uma das opções:                                       ");
        printf(Blue);
        printf("|\n");
        printf("|");
        printf(Yellow);
        printf("       1 - ACENDER LAMPADA                                         ");
        printf(Blue);
        printf("|\n");
        printf("|");
        printf(Yellow);
        printf("       2 - APAGAR LAMPADA                                          ");
        printf(Blue);
        printf("|\n");
        printf("|");
        printf(Yellow);
        printf("       3 - ATIVAR ALARME                                           ");
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
int read_lampada_to_turn_on(){
    int index;
    while(1){
        printf("Qual o número da lâmpada deseja ligar? Digite 0 para voltar.\n");
        scanf("%d", &index);
        if(!index){
            return -1;
        }
        if(light_outs[index-1].value){
            printf("Esta lâmpada já está ligada. Escolha outra.\n");
        }else{
            break;
        }
    }
    return light_outs[index-1].port;
}
int read_lampada_to_turn_off(){
    int index;
    while(1){
        printf("Qual o número da lâmpada deseja desligar? Digite 0 para voltar.\n");
        scanf("%d", &index);
        if(!index){
            return -1;
        }
        if(!light_outs[index-1].value){
            printf("Esta lâmpada já está desligada. Escolha outra.\n");
        }else{
            break;
        }
    }
    return light_outs[index-1].port;
}
void * read_menu(void *vargp){
    char option;
    int port;
    do{
        printf(White);
        option = getchar();
        switch(option){
            case '1':
                show_read = 0;
                port = read_lampada_to_turn_on();
                if(port>=0){
                    send_message(get_toggle_device_json(port));
                }
                show_read = 1;
                break;
            case '2':
                show_read = 0;
                port = read_lampada_to_turn_off();
                if(port>=0){
                    send_message(get_toggle_device_json(port));
                }
                show_read = 1;
                break;
        }
    }while(option!='0');
    //finish();
}