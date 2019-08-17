/*
 * ttp229.c
 *
 *  Created on: 03/04/2019
 *      Author: InDev
 */


#include "ttp229.h"

uint16_t TTP229__u16Tecla=0;

void TTP229_vInit(void)
{
    P1DIR&=~BIT5;

    P1DIR|=BIT4;
    P1OUT|=BIT4;
    P1IFG&~BIT5;
    P1IE|=BIT5;
    P1IES|=BIT5;
}



uint16_t TTP229_u16Value(uint16_t *u16Value)
{

    if(TTP229__u16Tecla)
    {
        *u16Value=TTP229__u16Tecla;
        return 0;
    }

    return 1;
}


