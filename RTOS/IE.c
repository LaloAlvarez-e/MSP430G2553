/*
 * IE.c
 *
 *  Created on: 29 sep. 2017
 *      Author: InDev
 */

#include <IE.h>

#pragma vector=15
__interrupt void RESET_IRQ(void)
{
    if(_IFG1&PORIFG) //Power Up Reset
    {
        _IFG1&=~PORIFG;
    }
    if(_IFG1&RSTIFG ) //reset
    {
        _IFG1&=~RSTIFG;
    }
    if((_IFG1&WDTIFG) && !(_WDTCTL&WDTTMSEL) ) //watchdog
    {
        _IFG1&=~WDTIFG;
    }
    if(_FCTL3&KEYV)
    {
        _FCTL3&=~KEYV;
    }
}

#pragma vector=14
__interrupt void NMI_IRQ(void)
{
    if(_IFG1&NMIIFG)
    {
        _IFG1&=~NMIIFG;
        _IE1|=NMIIE;
    }

    if(_IFG1&OFIFG )
    {
        _IFG1&=~OFIFG; //borra la bandera indicando que ya se atendio la int
        if(_BCSCTL3&LFXT1OF) //falla en el oscilador de baja frecuencia
        {
          if((_BCSCTL3&LFXT1S_3)!=LFXT1S_2) //si ACLK no esta conf para VLOCLK
              _BCSCTL3&=~LFXT1S_3;
              _BCSCTL3|=LFXT1S_2; //asocia ACLK a VLOCLK
        }

        if((_BCSCTL3&XT2OF)) //si existe una falla en el OSc de alta frec
        {
          if((_BCSCTL2&SELM_3)==SELM_2) //si MCLK esta vinculado a XT2
              _BCSCTL2&=~SELM_3; //vincula MCLK a DCOCLK
          if((_BCSCTL2&SELS)) //si SMCLK esta vinculado a XT2
              _BCSCTL2&=~SELS; //vincula SMCLK a DCOCLK
        }
        _IE1|=OFIE;
    }

    if(_FCTL3&ACCVIFG )
    {
        _FCTL3&=~ACCVIFG;
        _IE1|=ACCVIE;
    }

}

#pragma vector=6
__interrupt void TX_IRQ(void)
{

}

#pragma vector=7
__interrupt void RX_IRQ(void)
{

}
