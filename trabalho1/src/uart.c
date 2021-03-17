#include "uart.h"

#define CODIGO_SERVIDOR 0x01
#define SUB_CODIGO 0x23
#define CODIGO_TEMPERATURA_INTERNA 0xC1
#define CODIGO_TEMPERATURA_POTENCIOMETRO 0xC2

const unsigned char MATRICULA[4] = {2, 6, 3, 5};
int UART() {
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
    return uart0_filestream;
}
unsigned char read_uart(int uart, unsigned char * code, int size){
    unsigned char msg[size+4+2];
    memcpy(msg, code, size);
    memcpy(&msg[size], MATRICULA, 4);
    bytesCRC crc;
    crc.crc = calcula_CRC(msg, size+4);
    memcpy(&msg[size+4], crc.bytes, 2);

    if (uart != -1)
    {
        printf("Escrevendo caracteres na UART ...");
        int count = write(uart, msg, size+4+2);
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
    if (uart != -1)
    {
        // Read up to 255 characters from the port if they are there
       	unsigned char rx_buffer[256];
        int rx_length = read(uart, (void*)rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
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
            numero resposta;
            bytesCRC crc_recebido;
            unsigned char mensagem[7];
            //movendo 2 bytes do CRC + 4 da mensagem pra iniciar a leitura do número
            memcpy(resposta.bytes, &rx_buffer[rx_length-6], 4);
            //movendo 2 bytes do CRC pra iniciar a leitura do CRC
            memcpy(crc_recebido.bytes, &rx_buffer[rx_length-2], 2);
            //copiando a mensagem removendo os 2 bytes do CRC
            memcpy(mensagem, rx_buffer, 7);

            if(verifica_crc(rx_buffer, 7, crc_recebido)){
                return resposta.n;
            }else{
                return -1;
            }
        }
    }

    close(uart);
}
float get_internal_temperature(int uart) {
    unsigned char code[3] = {CODIGO_SERVIDOR, SUB_CODIGO, CODIGO_TEMPERATURA_INTERNA};
    return read_uart(uart, code, 3);
}
float get_potentiometer_temperature(int uart){
    unsigned char code[3] = {CODIGO_SERVIDOR, SUB_CODIGO, CODIGO_TEMPERATURA_POTENCIOMETRO};
    return read_uart(uart, code, 3);
}