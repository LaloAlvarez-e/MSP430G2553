/*
 * main.h
 *
 *  Created on: 14/08/2017
 *      Author: Lalo
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <msp430g2553.h>

void Conf_IO(void);//prototipo de configuracion de puertos
//lugar del pin donde se encuentra cada segmento
#define SEG_A BIT0 //P1.0 = seg A
#define SEG_B BIT1 //P1.1 = seg B
#define SEG_C BIT2 //P1.2 = seg C
#define SEG_D BIT3 //P1.3 = seg D
#define SEG_E BIT4 //P1.4 = seg E
#define SEG_F BIT5 //P1.5 = seg F
#define SEG_G BIT6 //P1.6 = seg G
#define SEG_DP BIT7//P1.7 = seg DP

#define PSEG P1OUT //P1 segmentos

#define CE0 BIT0 //P2.0 = Com0
#define CE1 BIT1 //P2.1 = Com1
#define CE2 BIT2 //P2.2 = Com2
#define CE3 BIT3 //P2.3 = Com3

#define PCE P2OUT //P1 comunes



//definciones para imprimir numeros en un display de Anodo Común
//para activar un led debemos poner el PIN correspondiente en 0
#define SEG_CL (0xFF) //apaga todos los LED del segmento
#define SEG_N0 ~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F)
#define SEG_N1 ~(SEG_B|SEG_C)
#define SEG_N2 ~(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G)
#define SEG_N3 ~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G)
#define SEG_N4 ~(SEG_B|SEG_C|SEG_F|SEG_G)
#define SEG_N5 ~(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G)
#define SEG_N6 ~(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define SEG_N7 ~(SEG_A|SEG_B|SEG_C)
#define SEG_N8 ~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define SEG_N9 ~(SEG_A|SEG_B|SEG_C|SEG_F|SEG_G)
#define SEG_NA ~(SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G)
#define SEG_NB ~(SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define SEG_NC ~(SEG_A|SEG_D|SEG_E|SEG_F)
#define SEG_ND ~(SEG_B|SEG_C|SEG_D|SEG_E|SEG_G)
#define SEG_NE ~(SEG_A|SEG_D|SEG_E|SEG_F|SEG_G)
#define SEG_NF ~(SEG_A|SEG_E|SEG_F|SEG_G)



#endif /* MAIN_H_ */
