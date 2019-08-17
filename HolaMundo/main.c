#include <msp430g2553.h>


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR=0;  //Registro para indicar Si es entrada o es salida 0=entrada 1=salida
    P1DIR|=BIT6|BIT0;//P1.0 y P1.6 son salida
    P1REN=0; //registro indica habilitación de resistencia pull-up y pull-down
    P1REN|=BIT3; //P1.3 habilita resistencia
    P1SEL=0; //vinculación a gpio
    P1SEL2=0; //vinculación a GPIO
    P1OUT=0; //Registro para entradas indica 1=pull-up 0=pull-down si PxREN=1 en el pin
    P1OUT|=BIT3|BIT0; //Registro para las salidas que indica el nivel del pin 1=3.3V 0=0V
    //P1.3 tiene pull-up y P1.0 =3.3V P1.6=0V;

    while(1)
    {
         if ((P1IN&BIT3)==0) //P1.3 está presionado
         {
           P1OUT&=~BIT0; //apaga P1.0
           P1OUT|=BIT6; //prende P1.6
         }
         else //P1.3 no está presionado
         {
           P1OUT&=~BIT6; //apaga P1.6
           P1OUT|=BIT0;  //prende P1.0;
         }
    }
}
