/*
 * uart.h
 *
 *  Created on: 20/03/2019
 *      Author: InDev
 */

#ifndef I2C_H_
#define I2C_H_


#include "msp430g2553.h"
#include "stdint.h"

#define I2C_MAX 64

uint16_t I2C_vInitMaster(int32_t s32Frecuency);
uint16_t I2C_u16SendMultiByteMaster(uint8_t u8Address,uint8_t* u8Byte, int8_t s8number ); //Nuevo

uint8_t Uart_u8ReceiveByteMaster(uint8_t u8Address,uint8_t* pu8Dato);
uint16_t Uart_u16ReceiveMultiByteMaster(uint8_t u8Address,uint8_t* pu8Byte, uint8_t u8Number ); //nuevo

uint8_t Uart_u8SendReadByteMaster(uint8_t u8Address,uint8_t u8DataTx , uint8_t* pu8DataRx ); //nuevo
uint8_t Uart_u8SendReadMultiByteMaster(uint8_t u8Address,uint8_t* pu8DataTx, uint8_t* pu8DataRx ,uint8_t u8Cant); //nuevo


uint16_t I2C_u16Busy(void);

__interrupt void UARTRX_ISR(void);
__interrupt void UARTTX_ISR(void);

#endif /* I2C_H_ */
