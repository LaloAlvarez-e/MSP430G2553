
/**
 * main.c
 */

#include <msp430g2553.h>
#include <lcd.h>
#include <reloj.h>



int main(void)
{
    unsigned char columna=0,fila=0;
    int conteo; //cantidad= numero de digitos convertidos, columna y fila pos de la LCD
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602
	conteo=LCD1602_Printf("\t\t %s Printf Parte %c ",&columna,&fila,"InDevice\n\r",'3');
	conteo+=LCD1602_Printf("%lf %q",&columna,&fila,(double)conteo);


	while(1);
}
