/*
 * interrupts.h
 *
 *  Created on: 03/04/2019
 *      Author: InDev
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


#include "I2C.h"
#include "ttp229.h"


__interrupt void USCIRX_ISR(void);
__interrupt void USCITX_ISR(void);
__interrupt void PORT1_ISR(void);
#endif /* INTERRUPTS_H_ */
