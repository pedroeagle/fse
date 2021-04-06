#include "gpio.h"

#define LAMPADA_1_OUT 17
#define LAMPADA_2_OUT 18
#define LAMPADA_3_OUT 27
#define LAMPADA_4_OUT 22
#define AR_COND_1_OUT 13
#define AR_COND_2_OUT 19
#define SENSOR_PRESENCA_1_IN 25
#define SENSOR_PRESENCA_2_IN 26
#define SENSOR_ABERTURA_1_IN 5
#define SENSOR_ABERTURA_2_IN 6
#define SENSOR_ABERTURA_3_IN 12
#define SENSOR_ABERTURA_4_IN 16
#define SENSOR_ABERTURA_5_IN 20
#define SENSOR_ABERTURA_6_IN 21

int main(int argc, const char * argv[]) {
    printf("%d\n", GPIO());
    while(1){
        read_gpio(SENSOR_PRESENCA_1_IN);
        usleep(700000);
    };
}