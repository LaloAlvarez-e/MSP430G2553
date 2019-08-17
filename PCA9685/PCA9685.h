/*
 * PCA9685.h
 *
 *  Created on: 30/03/2019
 *      Author: InDev
 */

#ifndef PCA9685_H_
#define PCA9685_H_

#include <msp430g2553.h>
#include "stdint.h"
#include "I2C.h"

#define PCA8695_ADDRESS1 0x40
#define Reset   0x01         // Reset the device
#define MODE1   0x00          // 0x00 location for Mode1 register address
#define MODE2   0x01          // 0x01 location for Mode2 reigster address
#define PRE_SCALE    0xfe          // 0xfe location for PRE_SCALE reigster address
#define CHANNEL0    0x06          // location for start of LED0 registers
#define LEDCOUNT 15          // number of LEDS to light 15 max

/* MODE1 bits */
#define PCA9685_RESTART 0x80
#define PCA9685_EXTCLK  0x40
#define PCA9685_AI      0x20
#define PCA9685_SLEEP   0x10
#define PCA9685_SUB1    0x08
#define PCA9685_SUB2    0x04
#define PCA9685_SUB3    0x02
#define PCA9685_ALLCALL 0x01

/* MODE2 bits */
#define PCA9685_INVRT   0x10
#define PCA9685_OCH     0x08
#define PCA9685_OUTDRV  0x04
#define PCA9685_OUTNE1  0x02
#define PCA9685_OUTNE0  0x01

/* LEDX_ON_H bits */
#define PCA9685_LED_ON 0x10

/* LEDX_OFF_H bits */
#define PCA9685_LED_OFF 0x10


void PCA9685_vInit(void);
uint16_t PCA9685_u16ChangeServoDegree_MG90(float fDegree, uint8_t u8Channel);
uint16_t PCA9685_u16ChangeServoDegree_MG995(float fDegree, uint8_t u8Channel);
void PCA9685_ChangeDevice(uint8_t u8Address);
#endif /* PCA9685_H_ */
