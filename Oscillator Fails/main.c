#include <msp430g2553.h>

void Conf_Reloj(void);
void Conf_OscFault(void);

void Conf_Reloj(void)
{
    DCOCTL=CALDCO_16MHZ;
    BCSCTL1=CALBC1_16MHZ; //conf para DCO=16MHz aprox 15.62 a 15.72MHz

    /*Seleccion de ACLK*/
    BCSCTL3&=~(LFXT1S_3);
    BCSCTL3|=LFXT1S_0;  //ACLK=LFXT1 , reloj externo
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

void Conf_OscFault(void)
{
    IFG1&=~OFIFG; //borra bandera de interrupcion
    IE1|=OFIE;//habilitacion de la interrupcion local del pin NMI
}

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //configura el reloj del sistema
	P1DIR|=BIT0;
	P1SEL|=BIT0;
	P1SEL2&=~BIT0;
	Conf_OscFault(); //activa las interrupciones NMI del oscilador
	while(1)
	{

	}
}


#pragma vector=NMI_VECTOR
__interrupt void OF_IRQ(void)
{
    if((IFG1&OFIFG)==OFIFG) //Si existe una falla en los osc externos
    {
        if((BCSCTL3&LFXT1OF)) //falla en el oscilador de baja frecuencia
        {
          if((BCSCTL3&LFXT1S_3)!=LFXT1S_2) //si ACLK no esta conf para VLOCLK
              BCSCTL3|=LFXT1S_2; //asocia ACLK a VLOCLK
        }

        if((BCSCTL3&XT2OF)) //si existe una falla en el OSc de alta frec
        {
          if((BCSCTL2&SELM_3)==SELM_2) //si MCLK esta vinculado a XT2
              BCSCTL2&=~SELM_3; //vincula MCLK a DCOCLK
          if((BCSCTL2&SELS)) //si SMCLK esta vinculado a XT2
              BCSCTL2&=~SELS; //vincula SMCLK a DCOCLK
        }
        IFG1&=~OFIFG; //borra la bandera indicando que ya se atendio la int
        IE1|=OFIE;//reactiva la NMI por si vuelve a ocurrir otra falla
    }
}

