#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART

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

    unsigned char tx_buffer[20];
    unsigned char *p_tx_buffer;
    
    p_tx_buffer = &tx_buffer[0];
    //0xA1 - Recebe um inteiro 
    //*p_tx_buffer++ = 161;
    //0xA2 - Recebe um float
    //*p_tx_buffer++ = 162;
    //0xA3 - Recebe um a string
    *p_tx_buffer++ = 163;  
    *p_tx_buffer++ = 2;
    *p_tx_buffer++ = 6;
    *p_tx_buffer++ = 3;
    *p_tx_buffer++ = 5;

    printf("Buffers de memória criados!\n");
    
    if (uart0_filestream != -1)
    {
        printf("Escrevendo caracteres na UART ...");
        int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));
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
            rx_buffer[rx_length] = '\0';
            //0xA1 - Recebe um inteiro
	    //printf("%i Bytes lidos : %d\n", rx_length, rx_buffer[0]);
   	    //0xA1 - Recebe um float
            //printf("%i Bytes lidos : %f\n", rx_length, rx_buffer[0]);
	    //0xA3 - Recebe uma string
	    //rx_buffer[1][rx_buffer[0]] = '\0';
	    printf("%i Bytes lidos : %d\n", rx_length, rx_buffer[0]);
        }
    }

    close(uart0_filestream);
   return 0;
}
