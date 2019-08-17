/*
 * reloj.c
 *
 *  Created on: 25/08/2017
 *      Author: Lalo
 */


#include <Clock.h>

void Conf_Reloj(void)
{

    _P2REN&=~P7;
    _P2OUT&=~P7;
    _P2DIR|=P7;
    _P2SEL2&=~P7;
    _P2SEL|=P7;

    _P2REN&=~P6;
    _P2OUT&=~P6;
    _P2DIR|=P6;
    _P2SEL2&=~P6;
    _P2SEL|=P6;

    _DCOCTL=CALDCO_16MHZ;
    _BCSCTL1=CALBC1_16MHZ; //conf para DCO=16MHz aprox 15.62 a 15.72MHz

    /*Seleccion de ACLK*/

    _BCSCTL1&=~XTS;
    _BCSCTL3|=XCAP_3;
    _BCSCTL3&=~LFXT1S_3; //ACLK=VLOCLK
    /*Division de ACLK*/
    _BCSCTL1&=~DIVA_3; //Division de ACLK/1;

    /*SEleccion de MCLK*/
    _BCSCTL2&=~SELM_3; //MCLK=DCOCLK
    /*Division de MCLK*/
    _BCSCTL2&=~DIVM_3; //Division de MCLK/1;

    /*Seleccion de SMCLK*/
    _BCSCTL2&=~SELS; // 0=DCOCLK 1=ACLK
    /*Division de SMCLK*/
    _BCSCTL2&=~DIVS_3; //Division de SMCLK/1;
}

void Conf_OscFault(void)
{

    _IFG1&=~OFIFG; //borra bandera de interrupcion
    _IE1|=OFIE;//habilitacion de la interrupcion local del pin NMI
}

void Conf_ACLK(void)
{
    _P1IE&=~P0;
    _P1IES&=~P0;
    _P1IFG&=~P0;
    _P1OUT&=~P0;
    _P1DIR|=P0;
    _P1REN&=~P0;
    _P1SEL|=P0;
    _P1SEL2&=~P0;
}

void Conf_SMCLK(void)
{
    _P1IE&=~P4;
    _P1IES&=~P4;
    _P1IFG&=~P4;
    _P1OUT&=~P4;
    _P1DIR|=P4;
    _P1REN&=~P4;
    _P1SEL|=P4;
    _P1SEL2&=~P4;
}

void Clock_Salida(void)
{
    Conf_SMCLK();
    Conf_ACLK();
}
