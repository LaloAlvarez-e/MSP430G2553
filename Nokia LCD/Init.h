/*
 * Init.h
 *
 *  Created on: 25/04/2016
 *      Author: Lalo
 */

#ifndef INIT_H_
#define INIT_H_

#include "msp430g2553.h"

void static Init_RELOJ(void);
void static Init_PORT(void);
void static Init_LED(void);
void static Init_SWITCH(void);
void static Init_POT(void);
void Init_BOARD(void);

#endif /* INIT_H_ */
