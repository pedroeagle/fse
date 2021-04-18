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
    printf("|");
    printf(White_Bold);
    printf(" ARES-CONDICIONADOS                                                ");
    printf(Blue);
    printf("|\n");
    printf("|   ");
    for(int i = 0; i < get_air_outs_lenght(); i++){
        if(air_outs[i].value){
            printf(Green);
            printf("AR-CONDICIONADO %d: ON           ", i+1);
        }else{
            printf(White);
            printf("AR-CONDICIONADO %d: OFF          ", i+1);
        }
    }
    printf(Blue);
    printf("|\n");
    printf("|");
    printf(White_Bold);
    printf(" SENSORES DE PRESENCA                                              ");
    printf(Blue);
    printf("|\n");
    printf("|   ");
    for(int i = 0; i < get_presence_sensors_lenght(); i++){
        if(presence_sensors[i].value){
            printf(Green);
            printf("%s %d: ON                  ", presence_sensors[i].name, i+1);
        }else{
            printf(White);
            printf("%s %d: OFF                 ", presence_sensors[i].name, i+1);
        }
    }
    printf(Blue);
    printf("|\n");
    printf("|");
    printf(White_Bold);
    printf(" SENSORES DE ABERTURA                                              ");
    printf(Blue);
    printf("|\n");
    printf("|   ");
    for(int i = 0; i < get_open_sensors_lenght(); i++){
        if(i == 2 || i == 4){
            printf(Blue);
            printf("|\n");
            printf("|   ");
        }
        if(open_sensors[i].value){
            printf(Green);
            printf("%s: ON          ", open_sensors[i].name);
        }else{
            printf(White);
            printf("%s: OFF         ", open_sensors[i].name);
        }
    }
    printf(Blue);
    printf("|\n");
    printf("|");
    printf(White_Bold);
    printf(" CONTROLE GERAL                                                    ");
    printf(Blue);
    printf("|\n");
    printf("|       ");
    if(ALARM){
        printf(Green);
        printf("ALARME: ATIVADO   ");
    }else{
        printf(Red);
        printf("ALARME: DESATIVADO");
    }
    printf("                                          ");
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
        printf("       3 - LIGAR AR CONDICIONADO                                   ");
        printf(Blue);
        printf("|\n");
        printf("|");
        printf(Yellow);
        printf("       4 - DESLIGAR AR CONDICIONADO                                ");
        printf(Blue);
        printf("|\n");
        printf("|");
        printf(Yellow);
        if(ALARM){
            printf("       5 - DESATIVAR ALARME                                        ");
        }else{
            printf("       5 - ATIVAR ALARME                                           ");
        }
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
        printf("Digite o número da lâmpada a qual deseja LIGAR. Digite 0 para voltar.\n");
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
        printf("Digite o número da lâmpada a qual deseja DESLIGAR. Digite 0 para voltar.\n");
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
int read_air_to_turn_on(){
    int index;
    while(1){
        printf("Digite o número do ar-condicionado a qual deseja LIGAR. Digite 0 para voltar.\n");
        scanf("%d", &index);
        if(!index){
            return -1;
        }
        if(air_outs[index-1].value){
            printf("Este ar-condicionado já está ligado. Escolha outro.\n");
        }else{
            break;
        }
    }
    return air_outs[index-1].port;
}
int read_air_to_turn_off(){
    int index;
    while(1){
        printf("Digite o número do ar-condicionado o qual deseja DESLIGAR. Digite 0 para voltar.\n");
        scanf("%d", &index);
        if(!index){
            return -1;
        }
        if(!air_outs[index-1].value){
            printf("Esta ar-condicionado já está desligado. Escolha outro.\n");
        }else{
            break;
        }
    }
    return air_outs[index-1].port;
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
                    send_message(get_json(port, -1));
                }
                show_read = 1;
                break;
            case '2':
                show_read = 0;
                port = read_lampada_to_turn_off();
                if(port>=0){
                    send_message(get_json(-1, port));
                }
                show_read = 1;
                break;
            case '3':
                show_read = 0;
                port = read_air_to_turn_on();
                if(port>=0){
                    send_message(get_json(port, -1));
                }
                show_read = 1;
                break;
            case '4':
                show_read = 0;
                port = read_air_to_turn_off();
                if(port>=0){
                    send_message(get_json(-1, port));
                }
                show_read = 1;
                break;
            case '5':
                show_read = 0;
                ALARM = !ALARM;
                send_message(get_json(-1, -1));
                show_read = 1;
                break;
        }
        menu();
    }while(option!='0');
    finish();
}