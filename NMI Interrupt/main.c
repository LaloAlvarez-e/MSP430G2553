#include <msp430g2553.h>

void Conf_Reloj(void);
void Conf_NMI(void);
void Conf_Reset(void);

void Conf_Reloj(void)
{
    DCOCTL=CALDCO_16MHZ;
    BCSCTL1=CALBC1_16MHZ; //conf para DCO=16MHz aprox 15.62 a 15.72MHz

    /*Seleccion de ACLK*/
    BCSCTL3&=~(LFXT1S_3);
    BCSCTL3|=LFXT1S_2;  //ACLK=VLOCLK aprox 14.43 a 14.63KHz
    /*Division de ACLK*/
    BCSCTL1&=~DIVA_3; //Division de ACLK/1;

    /*SEleccion de MCLK*/
    BCSCTL2&=~SELM_3; //MCLK=DCOCLK
    /*Division de MCLK*/
    BCSCTL2&=~DIVM_3; //Division de MCLK/1;

    /*Seleccion de SMCLK*/
    BCSCTL2&=~SELS; // 0=DCOCLK 1=ACLK
    /*Division de SMCLK*/
    BCSCTL2&=~DIVS_3; //Division de SMCLK/1;
}

void Conf_NMI(void)
{
    //WDTPW=0x05A llave para modificar el registro
    //WDTNMIES 1=borde de bajada 0 =borde de subida en NMI.pin reset
    //WDTNMI 1= funcion NMI 0=funcion reset
    WDTCTL=WDTPW |WDTNMIES|WDTNMI|WDTHOLD;
    IFG1&=~NMIIFG;
    IE1|=NMIIE;//habilitacion de la interrupcion local del pin NMI
}

void Conf_Reset(void)
{
    //WDTPW=0x05A llave para modificar el registro
    //WDTNMIES 1=borde de bajada 0 =borde de subida en NMI.pin reset
    //WDTNMI 1= funcion NMI 0=funcion reset
    IFG1&=~NMIIFG;
    IE1&=~NMIIE;//habilitacion de la interrupcion local del pin NMI
    WDTCTL=WDTPW |WDTHOLD;

}

/**
 * main.c
 */

unsigned char contador=10;
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj();
    P1DIR=0xFF;
    P1OUT=0xFF;
    P1REN=0;
	Conf_NMI();
	while(1)
	{
	    if(contador==0)
	    {
	       Conf_Reset();
	    }
	}
}


#pragma vector=NMI_VECTOR
__interrupt void NMI_IRQ(void)
{
    unsigned long i=0;
    if((IFG1&NMIIFG)==NMIIFG)
    {
        P1OUT&=~BIT6;
        P1OUT^=BIT0;
        contador--;
        for(i=0;i<1000000;i++);
        IFG1 &= ~NMIIFG;
        IE1 |= NMIIE;
    }
}

