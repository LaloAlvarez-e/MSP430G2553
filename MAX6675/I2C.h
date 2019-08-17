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
#define I2C_RXTRIES 3
#define I2C_TXTRIES 3
uint16_t I2C_vInitMaster(int32_t s32Frecuency);
uint16_t I2C_u16SendMultiByteMaster(uint8_t u8Address,uint8_t* u8Byte, int8_t s8number ); //Nuevo
uint16_t I2C_u16ReceiveMultiByteMaster(uint8_t u8Address,uint8_t* u8Byte, int8_t s8number);
uint16_t I2C_u16Busy(void);



extern volatile uint8_t* I2C__pu8RxData;
extern int8_t  I2C__s8RxCounter;
extern int8_t  I2C__s8RxNum;
extern int8_t  I2C__s8RxInit;

extern volatile uint8_t* I2C__pu8TxData;
extern int8_t  I2C__s8TxCounter;
extern int8_t  I2C__s8TxNum;
extern int8_t  I2C__s8TxInit;

extern uint8_t I2C__u8RxTry;
extern uint8_t I2C__u8TxTry;


#endif /* I2C_H_ */
