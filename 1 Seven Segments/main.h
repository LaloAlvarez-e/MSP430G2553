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
//lugar del pin donde se encuentra cada segmento S1
#define SEG1_A BIT0
#define SEG1_B BIT1
#define SEG1_C BIT2
#define SEG1_D BIT3
#define SEG1_E BIT4
#define SEG1_F BIT5
#define SEG1_G BIT6
#define SEG1_DP BIT7

#define SEG1 P1OUT


//definciones del lugar donde se encuentra cada PIN del segmento 2
//este segmento se encuentra de forma invertida en el protoboard
#define SEG2_A SEG1_D
#define SEG2_B SEG1_E
#define SEG2_C SEG1_F
#define SEG2_D SEG1_A
#define SEG2_E SEG1_B
#define SEG2_F SEG1_C
#define SEG2_G SEG1_G
#define SEG2_DP SEG1_DP

#define SEG2 P2OUT

//definciones para imprimir numeros en un display de Anodo Común
//para activar un led debemos poner el PIN correspondiente en 0
#define SEG1_CL (0xFF) //apaga todos los LED del segmento
#define SEG1_N0 ~(SEG1_A|SEG1_B|SEG1_C|SEG1_D|SEG1_E|SEG1_F)
#define SEG1_N1 ~(SEG1_B|SEG1_C)
#define SEG1_N2 ~(SEG1_A|SEG1_B|SEG1_D|SEG1_E|SEG1_G)
#define SEG1_N3 ~(SEG1_A|SEG1_B|SEG1_C|SEG1_D|SEG1_G)
#define SEG1_N4 ~(SEG1_B|SEG1_C|SEG1_F|SEG1_G)
#define SEG1_N5 ~(SEG1_A|SEG1_C|SEG1_D|SEG1_F|SEG1_G)
#define SEG1_N6 ~(SEG1_A|SEG1_C|SEG1_D|SEG1_E|SEG1_F|SEG1_G)
#define SEG1_N7 ~(SEG1_A|SEG1_B|SEG1_C)
#define SEG1_N8 ~(SEG1_A|SEG1_B|SEG1_C|SEG1_D|SEG1_E|SEG1_F|SEG1_G)
#define SEG1_N9 ~(SEG1_A|SEG1_B|SEG1_C|SEG1_F|SEG1_G)
#define SEG1_NA ~(SEG1_A|SEG1_B|SEG1_C|SEG1_E|SEG1_F|SEG1_G)
#define SEG1_NB ~(SEG1_C|SEG1_D|SEG1_E|SEG1_F|SEG1_G)
#define SEG1_NC ~(SEG1_A|SEG1_D|SEG1_E|SEG1_F)
#define SEG1_ND ~(SEG1_B|SEG1_C|SEG1_D|SEG1_E|SEG1_G)
#define SEG1_NE ~(SEG1_A|SEG1_D|SEG1_E|SEG1_F|SEG1_G)
#define SEG1_NF ~(SEG1_A|SEG1_E|SEG1_F|SEG1_G)

//definciones para imprimir numeros en un display de Catodo Común invertido en posicion
//para activar un led debemos poner el PIN correspondiente en 0

#define SEG2_CL (0) //apaga los leds del display
#define SEG2_N0 (SEG2_A|SEG2_B|SEG2_C|SEG2_D|SEG2_E|SEG2_F)
#define SEG2_N1 (SEG2_B|SEG2_C)
#define SEG2_N2 (SEG2_A|SEG2_B|SEG2_D|SEG2_E|SEG2_G)
#define SEG2_N3 (SEG2_A|SEG2_B|SEG2_C|SEG2_D|SEG2_G)
#define SEG2_N4 (SEG2_B|SEG2_C|SEG2_F|SEG2_G)
#define SEG2_N5 (SEG2_A|SEG2_C|SEG2_D|SEG2_F|SEG2_G)
#define SEG2_N6 (SEG2_A|SEG2_C|SEG2_D|SEG2_E|SEG2_F|SEG2_G)
#define SEG2_N7 (SEG2_A|SEG2_B|SEG2_C)
#define SEG2_N8 (SEG2_A|SEG2_B|SEG2_C|SEG2_D|SEG2_E|SEG2_F|SEG2_G)
#define SEG2_N9 (SEG2_A|SEG2_B|SEG2_C|SEG2_F|SEG2_G)
#define SEG2_NA (SEG2_A|SEG2_B|SEG2_C|SEG2_E|SEG2_F|SEG2_G)
#define SEG2_NB (SEG2_C|SEG2_D|SEG2_E|SEG2_F|SEG2_G)
#define SEG2_NC (SEG2_A|SEG2_D|SEG2_E|SEG2_F)
#define SEG2_ND (SEG2_B|SEG2_C|SEG2_D|SEG2_E|SEG2_G)
#define SEG2_NE (SEG2_A|SEG2_D|SEG2_E|SEG2_F|SEG2_G)
#define SEG2_NF (SEG2_A|SEG2_E|SEG2_F|SEG2_G)



#endif /* MAIN_H_ */
