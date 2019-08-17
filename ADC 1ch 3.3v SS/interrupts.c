/*
 * interrupts.c
 *
 *  Created on: 03/04/2019
 *      Author: InDev
 */



#include "interrupts.h"

uint16_t u16ValorADC=0;
//uint16_t u16flagADC=0;

#pragma vector=ADC10_VECTOR;
__interrupt void ADC_vIsr(void)
{
    u16ValorADC=ADC10MEM;
    //u16flagADC=0;
}
