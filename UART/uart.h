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

#define UART_TXMAX 64
#define UART_RXMAX 64

void Uart_vInit(int32_t s32BaudRate);
uint8_t Uart_u8SendChar(char cDato);
uint8_t Uart_u8SendCharUntilLoad(char cDato);
uint16_t Uart_u16SendString(char* pcDato);
uint16_t Uart_u16SendMultiByte(char* cByte, uint8_t u8number ); //Nuevo

uint8_t Uart_u8ReceiveChar(char* pcDato);
uint8_t Uart_u8UntilReceiveChar(char* pcDato);
uint16_t Uart_u16ReceiveMultiByte(char* cByte, uint8_t u8Number ); //nuevo


uint8_t Uart_u8SendReadChar(char cDataTx , char* cDataRx ); //nuevo
uint8_t Uart_u8SendReadMultiChar(char* cDataTx, char* cDataRx ,uint8_t u8Cant); //nuevo



__interrupt void UARTRX_ISR(void);
__interrupt void UARTTX_ISR(void);

#endif /* UART_H_ */
