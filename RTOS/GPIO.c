/*
 * GPIO.c
 *
 *  Created on: 29 sep. 2017
 *      Author: InDev
 */



#include <GPIO.h>


void Conf_GPIO(void)
{
    _P1DIR=0;
    _P1REN=0xFF;
    _P1OUT=0;
    _P1SEL=0;
    _P1SEL2=0;
    _P1IFG=0;
    _P1IES=0xFF;
    _P1IE=0;
}


#pragma vector=2
__interrupt void PORT1_IRQ(void)
{
    volatile unsigned char p1ifg= _P1IFG;

    if((p1ifg&P0) && ( _P1IE&P0) )
    {
        _P1IFG&=~P0;
    }
    if((p1ifg&P1) && ( _P1IE&P1) )
    {
        _P1IFG&=~P1;
    }
    if((p1ifg&P2) &&( _P1IE&P2))
    {
        _P1IFG&=~P2;
    }
    if((p1ifg&P3) && (_P1IE&P3) )
    {
        _P1IFG&=~P3;
    }
    if((p1ifg&P4) && (_P1IE&P4) )
    {
        _P1IFG&=~P4;
    }
    if((p1ifg&P5) && (_P1IE&P5) )
    {
        _P1IFG&=~P5;
    }
    if((p1ifg&P6) && (_P1IE&P6) )
    {
        _P1IFG&=~P6;
    }
    if((p1ifg&P7) && (_P1IE&P7) )
    {
        _P1IFG&=~P7;
    }
}


#pragma vector=3
__interrupt void PORT2_IRQ(void)
{
    volatile unsigned char p2ifg= _P2IFG;

    if((p2ifg&P0) && (_P2IE&P0) )
    {
        _P2IFG&=~P0;
    }
    if((p2ifg&P1) && (_P2IE&P1) )
    {
        _P2IFG&=~P1;
    }
    if((p2ifg&P2) && (_P2IE&P2) )
    {
        _P2IFG&=~P2;
    }
    if((p2ifg&P3) && (_P2IE&P3) )
    {
        _P2IFG&=~P3;
    }
    if((p2ifg&P4) && (_P2IE&P4) )
    {
        _P2IFG&=~P4;
    }
    if((p2ifg&P5) && (_P2IE&P5) )
    {
        _P2IFG&=~P5;
    }
    if((p2ifg&P6) && (_P2IE&P6) )
    {
        _P2IFG&=~P6;
    }
    if((p2ifg&P7) && (_P2IE&P7) )
    {
        _P2IFG&=~P7;
    }
}



