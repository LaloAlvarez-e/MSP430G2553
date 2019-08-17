#include <main.h>


/**
 * main.c
 */




void Conf_IO(void)
{
   P1OUT=0; //salidas a 0V y entradas si PREN=1 estaran en pulldown
   P1DIR=BIT6|BIT0; //P1.0 y P1.6 son salida , los demas son entrada
   P1REN=BIT3; //P1.3 habilitada resistencia
   P1OUT|=BIT3; // P1.3 tiene pull-up

   P1SEL=0;
   P1SEL2=0; //vinvular a GPIO

}

void main(void)
{
    unsigned char conteo=0;
    unsigned int i=0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_IO(); //mandamos llamar la configuración de los GPIO
	while(1)
	{
	  for(i=0; i<30000; i++);
	  if((P1IN&BIT3)==0) // esta presionado el boton
	  {
	      conteo++; //suma 1 al valor del contador
	      switch(conteo&0x3)
	            {
	            case 0:
	                P1OUT&=~BIT0; //P1.0=0V P1OUT=P1OUT & (~BIT0) ó P1OUT=P1OUT & (0xFE)
	                P1OUT&=~BIT6; //P1.6=0V
	                break;
	            case 1:
	                P1OUT|=BIT0; //P1.0=3.3V
	               // P1OUT&=~BIT6; //P1.6=0V
	                break;
	            case 2:
	                P1OUT&=~BIT0; //P1.0=0V
	                P1OUT|=BIT6; //P1.6=3.3V
	                break;
	            case 3:
	                P1OUT|=BIT0; //P1.0=3.3V
	                //P1OUT|=BIT6; //P1.6=3.3V
	                break;
	            default:
	                break;
	            }

	  }


	}
}
