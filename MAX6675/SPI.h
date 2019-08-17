/*
 * SPI.h
 *
 *  Created on: 05/04/2019
 *      Author: InDev
 */

#ifndef SPI_H_
#define SPI_H_


#include "msp430g2553.h"
#include "stdint.h"

#define SPI_TXMAX 32
#define SPI_RXMAX 32

uint16_t SPI_u16Init(uint32_t u32Frec);
uint8_t SPI_u8SendByteUntilLoad(uint8_t u8Dato);
uint16_t SPI_u16SendMultiByte(uint8_t* pu8Byte, uint8_t u8Number);
uint8_t SPI_u8ReceiveByte(uint8_t* pu8Dato);
uint16_t SPI_u16ReceiveMultiByte(uint8_t* pu8Byte, uint8_t u8Number);
uint16_t SPI_u16SendReceiveMultiByte(uint8_t* pu8ByteSend, uint8_t* pu8ByteReceive,uint8_t u8Number);

extern uint8_t SPI_u8TxBuffer[SPI_TXMAX];
extern volatile uint8_t* SPI_pu8PutTx;
extern volatile uint8_t* SPI_pu8GetTx;
extern int8_t  SPI_s8TxCounter;
extern int8_t  SPI_s8TxInit;


extern uint8_t SPI_u8RxBuffer[SPI_RXMAX];
extern volatile uint8_t* SPI_pu8PutRx;
extern volatile uint8_t* SPI_pu8GetRx;
extern int8_t  SPI_s8RxCounter;

#endif /* SPI_H_ */
