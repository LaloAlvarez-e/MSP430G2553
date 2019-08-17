#include <msp430g2553.h>


void Conf_Reloj(void);
void Conf_NMI(void);
void Conf_Reset(void);

unsigned char LPM[5]=
{
     LPM0_bits,LPM1_bits,
     LPM2_bits,LPM3_bits,
     LPM4_bits
};

unsigned char LPM_actual=1,interrupcion=0;
void Conf_Reloj(void)
{
    DCOCTL=CALDCO_16MHZ;
    BCSCTL1=CALBC1_16MHZ; //conf para DCO=16MHz aprox 15.62 a 15.72MHz

    /*Seleccion de ACLK*/
    BCSCTL3&=~(LFXT1S_3);
    BCSCTL3|=LFXT1S_2;  //ACLK=VLOCLK
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
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	Conf_Reloj();
	Conf_NMI();

	P1DIR|=BIT0|BIT4;
	P1SEL|=BIT0|BIT4;
	P1SEL2&=~(BIT0|BIT4);
	//__bis_SR_register(LPM2_bits);
	while(1)
	{
	    if(interrupcion)
	    {

	    interrupcion=0;
        if(LPM_actual<5)
        {
            LPM_actual++;
        }
        else
        {
            LPM_actual=1;
        }
        IE1 |= NMIIE;
        __bis_SR_register(LPM[LPM_actual-1]);
	    }
	}
}


#pragma vector=NMI_VECTOR
__interrupt void NMI_IRQ(void)
{
    unsigned long i=0;
    if((IFG1&NMIIFG)==NMIIFG)
    {
        interrupcion++;
        for(i=0;i<500000;i++);
        IFG1 &= ~NMIIFG;
        __low_power_mode_off_on_exit();
    }
}
