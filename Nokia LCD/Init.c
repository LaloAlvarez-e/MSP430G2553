/*
 * Init.c
 *
 *  Created on: 25/04/2016
 *      Author: Lalo
 */


#include "Init.h"


void static Init_RELOJ(void)
{
    DCOCTL=CALDCO_16MHZ;
    BCSCTL1=CALBC1_16MHZ;
    BCSCTL3&=~(LFXT1S1|LFXT1S0);
    _nop();
    BCSCTL3|=LFXT1S1;
}


void static Init_PORT(void)
{
	P1DIR=0;
	P1REN=0xFF;
	P1OUT=0xFF;
	P1SEL=0;
	P1SEL2=0;
	P2DIR=0;
	P2REN=0xFF;
	P2OUT=0xFF;
	P2SEL=0;
	P2SEL2=0;
	P3DIR=0;
	P3REN=0xFF;
	P3OUT=0xFF;
	P3SEL=0;
	P3SEL2=0;

	P1IE=0;
	P1IES=0;
	P1IFG=0;

	P2IE=0;
	P2IES=0;
	P2IFG=0;


}

void static Init_LED(void)
{
	P2DIR|=(BIT0|BIT1);
	P2REN&=~(BIT0|BIT1);
	P2OUT&=~(BIT0|BIT1);
	P2SEL&=~(BIT0|BIT1);
	P2SEL2&=~(BIT0|BIT1);

	P2IE&=~(BIT0|BIT1);
	P2IES&=~(BIT0|BIT1);
	P2IFG&=~(BIT0|BIT1);
}




void static Init_SWITCH(void)
{
	P2DIR&=~(BIT7);
	P2REN|=(BIT7);
	P2OUT&=~(BIT7);
	P2SEL&=~(BIT7);
	P2SEL2&=~(BIT7);

	P2IE|=(BIT7);
	P2IES|=(BIT7);
	P2IFG&=~(BIT7);

	P1DIR&=~(BIT0);
	P1REN|=(BIT0);
	P1OUT&=~(BIT0);
	P1SEL&=~(BIT0);
	P1SEL2&=~(BIT0);

	P1IE|=(BIT0);
	P1IES|=(BIT0);
	P1IFG&=~(BIT0);
}

void static Init_POT(void)
{
	TA0CTL=0x2E0; //VLO 4 a 20KHz tipicamente 12KHz
	TA0CCTL1=0x70;
	TA0CCTL0=0x10;
	TA0CCTL2=0x10;
	TA0CCR0=0xFFFE; //aprox 30 Hz programa principal
	TA0CCR1=0x7FFF; //aprox 60Hz lectura del pot

	TA1CTL=0x2D2; //VLO 4 a 20KHz tipicamente 12KHz
	TA1CCTL0=0x0;
	TA1CCR0=181;//725; //aprox 11025Hz para el DAC

	ADC10CTL0&=~ENC;
	ADC10CTL0|= 0x1C08;
	ADC10CTL1=0x64FC;
	ADC10AE0=0x40;
	ADC10CTL0|=(ADC10ON|ENC);
}

void Init_BOARD(void)
{
	 Init_RELOJ();
	 Init_PORT();
	 Init_LED();
	 Init_SWITCH();
	 Init_POT();
}
