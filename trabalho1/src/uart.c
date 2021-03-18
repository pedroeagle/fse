#include "uart.h"

#define CODIGO_SERVIDOR 0x01
#define SUB_CODIGO 0x23
#define CODIGO_TEMPERATURA_INTERNA 0xC1
#define CODIGO_TEMPERATURA_POTENCIOMETRO 0xC2

const unsigned char MATRICULA[4] = {2, 6, 3, 5};
//float potentiometer = 0.0, internal = 0.0, external = 0.0;

int UART() {
    int uart0_filestream = -1;

    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    else
    {
        //printf("UART inicializada!\n");
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
float read_uart(int uart, unsigned char * code, int size){
    unsigned char msg[size+4+2];
    memcpy(msg, code, size);
    memcpy(&msg[size], MATRICULA, 4);
    bytesCRC crc;
    crc.crc = calcula_CRC(msg, size+4);
    memcpy(&msg[size+4], crc.bytes, 2);

    if (uart != -1)
    {
        //printf("Escrevendo caracteres na UART ...");
        int count = write(uart, msg, size+4+2);
        if (count < 0)
        {
            printf("UART TX error\n");
            return count;
        }
    }

    sleep(1);

    //----- CHECK FOR ANY RX BYTES -----
    if (uart != -1)
    {
        // Read up to 255 characters from the port if they are there
       	unsigned char rx_buffer[256];
        int rx_length = read(uart, (void*)rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length <= 0)
        {
            return -1;
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
float get_internal_temperature_uart(int uart) {
    unsigned char code[3] = {CODIGO_SERVIDOR, SUB_CODIGO, CODIGO_TEMPERATURA_INTERNA};
    float temperature = read_uart(uart, code, 3);
    float diff = abs(abs(get_internal_temperature()) - abs(temperature));
    if(temperature < 0){
        return get_internal_temperature();
    }
    return temperature;
}
float get_potentiometer_temperature_uart(int uart){
    unsigned char code[3] = {CODIGO_SERVIDOR, SUB_CODIGO, CODIGO_TEMPERATURA_POTENCIOMETRO};
    float temperature = read_uart(uart, code, 3);
    float diff = abs(abs(get_potentiometer_temperature()) - abs(temperature));
    if(temperature < 0){
        return get_potentiometer_temperature();
    }
    return temperature;
}