/*
 * main.h
 *
 *  Created on: 11/09/2017
 *      Author: Lalo
 */

#ifndef MAIN_H_
#define MAIN_H_


#include<MSP.h>

#define RETARDo 4000

#ifndef P1_6
#define P1_6
#define PUERTO_LED P1
#define LED BIT6
#define LED_POS 6
#endif

//------------------ Definiciones F1 ---------------

#define LED_OUT   OUTp( PUERTO_LED )
#define LED_DIR   DIRp(PUERTO_LED)
#define LED_REN   RENp( PUERTO_LED )
#define LED_SEL   SELp(PUERTO_LED)
#define LED_SEL2  SEL2p(PUERTO_LED)
#define LED_IN    INp(PUERTO_LED)
#define LED_IE  IEp(PUERTO_LED)
#define LED_IES    IESp(PUERTO_LED)
#define LED_IFG  IFGp(PUERTO_LED)

//------------------ Definiciones F2 ---------------



#endif /* MAIN_H_ */
