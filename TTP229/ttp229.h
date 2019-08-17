/*
 * ttp229.h
 *
 *  Created on: 03/04/2019
 *      Author: InDev
 */

#ifndef TTP229_H_
#define TTP229_H_


#include "msp430g2553.h"
#include <stdint.h>

void TTP229_vInit(void);
uint16_t TTP229_u16Value(uint16_t *u16Value);
extern uint16_t TTP229__u16Tecla;

#endif /* TTP229_H_ */
