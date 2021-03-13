/*
 * crc16.h
 *
 *  Created on: 18/03/2014
 *      Author: Renato Coral Sampaio
 */

#ifndef CRC16_H_
#define CRC16_H_
#include <stdint.h>

short CRC16(short crc, char data);
short calcula_CRC(unsigned char *commands, int size);

typedef union {
    short crc;
    uint8_t bytes[2];
} bytesCRC;

typedef union {
    float n;
    uint8_t bytes[sizeof(float)];
} numero;

#endif /* CRC16_H_ */
