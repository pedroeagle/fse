#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <string.h>
#include "crc16.h"

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

    int uart0_filestream = -1;

    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    else
    {
        printf("UART inicializada!\n");
    }    
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
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
    
    char texto[100] = "OLAAAAAAAAA";
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
    memcpy(&msg[tamanho_codigo], crc.bytes, 2);
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
    printf("Buffers de memória criados!\n");
    if (uart0_filestream != -1)
    {
        printf("Escrevendo caracteres na UART ...");
        int count = write(uart0_filestream, &msg, tamanho_msg);
        if (count < 0)
        {
            printf("UART TX error\n");
        }
        else
        {
            printf("escrito.\n");
        }
    }

    sleep(1);

    //----- CHECK FOR ANY RX BYTES -----
    if (uart0_filestream != -1)
    {
        // Read up to 255 characters from the port if they are there
       	unsigned char rx_buffer[256];
        int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length < 0)
        {
            printf("Erro na leitura.\n"); //An error occured (will occur if there are no bytes)
        }
        else if (rx_length == 0)
        {
            printf("Nenhum dado disponível.\n"); //No data waiting
        }
        else
        {
            //Bytes received
            //rx_buffer[rx_length] = '\0';
            //0xA1 - Recebe um inteiro
            //printf("%i Bytes lidos : %d\n", rx_length, rx_buffer[2]);
            //0xA1 - Recebe um float
            printf("%i Bytes lidos : %d\n", rx_length, rx_buffer[0]);
            for(int i = 3; i < rx_length-1; i++){
                printf("%c", rx_buffer[i]);
            }
            //0xA3 - Recebe uma string
            //rx_buffer[1][rx_buffer[0]] = '\0';
            //printf("%i Bytes lidos : %s\n", rx_length, rx_buffer);
        }
    }

    close(uart0_filestream);
   return 0;
}
