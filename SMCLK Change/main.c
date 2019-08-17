#include <msp430g2553.h>


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer


	/* Configuracion para frec de DCO*/
	DCOCTL=CALDCO_16MHZ;
	BCSCTL1=CALBC1_16MHZ; //conf para DCO=16MHz
//	DCOCTL=CALDCO_12MHZ;
//	BCSCTL1=CALBC1_12MHZ; //conf para DCO=12MHz
//  DCOCTL=CALDCO_8MHZ;
//  BCSCTL1=CALBC1_8MHZ; //conf para DCO=8MHz
//  DCOCTL=CALDCO_1MHZ;
//  BCSCTL1=CALBC1_1MHZ;  //conf para DCO=1MHz

	/*Seleccion de ACLK*/
    BCSCTL3&=~(LFXT1S_3); //reincia los bits de seleccion de ACLK
    //LFXT1S_0=cristal externo LFXT1S_2=VLOCLK LFXT1S_3=reloj digital externo
    BCSCTL3|=LFXT1S_2;  //seleccion VLOCLK como ACLK

    /*Division de ACLK*/
    BCSCTL1&=~DIVA_3; //Division de ACLK/1;
    // DIVA_0= ACLK/1 DIVA_1= ACLK/2 DIVA_2=ACLK/4 DIVA_3=ACLK/8
    BCSCTL1|=DIVA_3;

    /*SEleccion de MCLK*/
    BCSCTL2&=~SELM_3; //reincia los bits de seleccion de MCLK
    //SELM_0=DCOCLK SELM_1=DCOCLK SELM_2=ACLK SELM_3=ACLK
    BCSCTL2|=SELM_0;

    /*Division de MCLK*/
    BCSCTL2&=~DIVM_3; //Division de MCLK/1;
    // DIVM_0= MCLK/1 DIVM_1= MCLK/2 DIVM_2=MCLK/4 DIVM_3=MCLK/8
    BCSCTL2|=DIVM_0;

    /*Seleccion de SMCLK*/
    BCSCTL2&=~SELS; // 0=DCOCLK 1=ACLK

    /*Division de SMCLK*/
    BCSCTL2&=~DIVS_3; //Division de SMCLK/1;
    // DIVS_0= SMCLK/1 DIVS_1= SMCLK/2 DIVS_2=SMCLK/4 DIVS_3=SMCLK/8
    BCSCTL2|=DIVS_3;

	P1DIR|=BIT0|BIT4; //config P1.0 =ACLK y P1.4 =SMCLK
	P1SEL|=BIT0|BIT4;
	P1SEL2=0;
	while(1);
}
