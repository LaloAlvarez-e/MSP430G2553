/*
 * interrupts.h
 *
 *  Created on: 03/04/2019
 *      Author: InDev
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include "msp430g2553.h"
#include "stdint.h"

__interrupt void ADC_vIsr(void);


extern uint16_t u16ValorADC;
extern uint16_t u16flagADC;

#endif /* INTERRUPTS_H_ */
