/* 
 * File:   USART.h
 * Author: JIRS
 *
 * Created on 12 de febrero de 2020, 01:36 AM
 */

#include <stdint.h>

#ifndef USART_H
#define	USART_H

void configUSART(uint8_t intRC, uint8_t intTX, uint8_t sync, uint8_t bits);
void sendUSART (uint8_t dataOut);

#endif	/* USART_H */

