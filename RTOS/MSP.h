/*
 * MSP.h
 *
 *  Created on: 29 sep. 2017
 *      Author: InDev
 */

#ifndef MSP_H_
#define MSP_H_

//#include <msp430g2553.h>
#include <in430.h>
#include <intrinsics.h>
#include <Calibracion.h>
#include <GPIO.h>
#include <WatchDog.h>
#include <IE.h>
#include <Clock.h>
#include <Flash.h>
#include <TimerA.h>
#include <procesos.h>

#define PUERTO_LED1 P1
#define PIN_LED1 5

//------------------ Definiciones Pin LED1 ---------------

#define _LED1_OUT   OUTp( PUERTO_LED1,PIN_LED1)
#define _LED1_DIR   DIRp( PUERTO_LED1,PIN_LED1)
#define _LED1_REN   RENp( PUERTO_LED1,PIN_LED1)
#define _LED1_SEL   SELp( PUERTO_LED1,PIN_LED1)
#define _LED1_SEL2  SEL2p( PUERTO_LED1,PIN_LED1)
#define _LED1_IN    INp( PUERTO_LED1,PIN_LED1)


#define PUERTO_LED2 P1
#define PIN_LED2 6

//------------------ Definiciones Pin LED2 ---------------

#define _LED2_OUT   OUTp( PUERTO_LED2,PIN_LED2)
#define _LED2_DIR   DIRp( PUERTO_LED2,PIN_LED2)
#define _LED2_REN   RENp( PUERTO_LED2,PIN_LED2)
#define _LED2_SEL   SELp( PUERTO_LED2,PIN_LED2)
#define _LED2_SEL2  SEL2p( PUERTO_LED2,PIN_LED2)
#define _LED2_IN    INp( PUERTO_LED2,PIN_LED2)


#endif /* MSP_H_ */
