#include "crc16.h"
#include "uart.h"
#include "display.h"
#include "gpio.h"
#include "pid.h"
#include "csv.h"
#include "main.h"

#define CODIGO_CLIENTE 0x00
#define CODIGO_SERVIDOR 0x01
#define CODIGO_CMD_SOLICITA 0x23
#define CODIGO_CMD_ESCREVE 0x16

#define CMD_SOLICITA_INT    0xA1
#define CMD_SOLICITA_FLOAT  0xA2
#define CMD_SOLICITA_STRING 0xA3

#define CMD_ENVIA_INT    0xB1
#define CMD_ENVIA_FLOAT  0xB2
#define CMD_ENVIA_STRING 0xB3

#define CMD_ERROR 0xE1
#define CMD_STRING_OK 0xC1


int main(int argc, const char * argv[]) {
    menu();
    /*CSV();
    float a[5];
    a[0] = 1.5;
    a[1] = 3.6;
    a[2] = 89.5;
    a[3] = 100;
    a[4] = 105;
    insert_line(a, 5);*/
    /*int uart = UART();
    int internal_temperature = get_internal_temperature(uart);
    pid_configura_constantes(100, 1, 1.5);
    pid_atualiza_referencia(internal_temperature);
    printf("%lf", pid_controle(20));*/
    /*printf("Começou\n");
    printf("Start GPIO: %d\n", GPIO());
    turn_on_fan();
    delay(1000);
    printf("Terminou\n");*/
    /*DISPLAY();
    write_first("Teste 123");
    write_second("321 etseT");*/

    
    //int potentiometer_temperature =  get_potentiometer_temperature(uart);
    // == SOLICITAR INTEIRO ==
    /*unsigned char codigo_inteiro[3] = {CODIGO_SERVIDOR, CODIGO_CMD_SOLICITA, CMD_SOLICITA_INTEIRO};
    bytesCRC crc;
    crc.crc = calcula_CRC(codigo_inteiro, 3);
    unsigned char msg[5];
    printf("%i\n", crc)
    memcpy(msg, codigo_inteiro, 3);
    memcpy(&msg[3], crc.bytes, 2);
    int tamanho_msg = 5;*/
    // == SOLICITAR STRING ==
    /*unsigned char codigo_string[3] = {CODIGO_SERVIDOR, CODIGO_CMD_SOLICITA, CMD_SOLICITA_STRING};
    bytesCRC crc;
    crc.crc = calcula_CRC(codigo_string, 3);
    unsigned char msg[5];
    memcpy(msg, codigo_string, 3);
    memcpy(&msg[3], crc.bytes, 2);
    int tamanho_msg = 5;*/
    // == ENVIAR INTEIRO ==
    /*int inteiro = 0x48;
    unsigned char codigo_inteiro[7] = {CODIGO_SERVIDOR, CODIGO_CMD_ESCREVE, CMD_ENVIA_INT, inteiro};
    bytesCRC crc;
    crc.crc = calcula_CRC(codigo_inteiro, 7);
    unsigned char msg[9];
    memcpy(msg, codigo_inteiro, 7);
    memcpy(&msg[7], crc.bytes, 2);
    int tamanho_msg = 9;
    for(int i =0; i < tamanho_msg; i++){
        printf("%x ", msg[i]);
    }*/
    // == ENVIAR STRING ==
    
    /*char texto[100] = "OLAAAAAAAAA";
    int tamanho_texto = strlen(texto);
    texto[tamanho_texto] = '\0';
    int tamanho_codigo = tamanho_texto+4;
    int tamanho_msg = tamanho_codigo+2;
    unsigned char codigo_string[200] = {CODIGO_SERVIDOR, CODIGO_CMD_ESCREVE, CMD_ENVIA_STRING, tamanho_texto};
    memcpy(&codigo_string[4], texto, tamanho_texto); 
    unsigned char msg[tamanho_msg];
    bytesCRC crc;
    crc.crc = calcula_CRC(codigo_string, tamanho_codigo);
    
    memcpy(msg, codigo_string, tamanho_codigo);
    memcpy(&msg[tamanho_codigo], crc.bytes, 2);*/

    // == ENVIAR FLOAT ==
    /*numero n;
    n.n = 1.5;
    unsigned char codigo_float[200] = {CODIGO_SERVIDOR, CODIGO_CMD_ESCREVE, CMD_ENVIA_FLOAT, n.bytes};
    int tamanho_codigo = sizeof(float)+3;
    int tamanho_msg = tamanho_codigo+2;
    unsigned char msg[tamanho_msg];
    bytesCRC crc;
    crc.crc = calcula_CRC(codigo_float, tamanho_codigo);
    memcpy(msg, codigo_float, tamanho_codigo);
    memcpy(&msg[tamanho_codigo], crc.bytes, 2);*/
   return 0;
}
