/*
 * uart.h
 *
 *  Created on: 20/03/2019
 *      Author: InDev
 */

#ifndef UART_H_
#define UART_H_


#include "msp430g2553.h"
#include "stdint.h"

void Uart_vInit(int32_t s32BaudRate);
uint8_t Uart_u8SendChar(char cDato);
uint8_t Uart_u8ReceiveChar(char* pcDato);
uint8_t Uart_u8SendCharUntilComplete(char cDato);
uint8_t Uart_u8UntilReceiveChar(char* pcDato);
uint16_t Uart_u8SendString(char* pcDato);

#endif /* UART_H_ */
