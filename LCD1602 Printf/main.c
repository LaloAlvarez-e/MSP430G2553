
/**
 * main.c
 */

#include <msp430g2553.h>
#include <lcd.h>
#include <reloj.h>


int main(void)
{
    unsigned char columna=0,fila=0; //cantidad= numero de digitos convertidos, columna y fila pos de la LCD
   WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602
	LCD1602_Printf("°C In\tDevice\n\rPrintAlgo",&columna,&fila);
	LCD1602_Printf("\a\a\a\af",&columna,&fila);
	LCD1602_Printf("\f",&columna,&fila);
	LCD1602_Printf("Fin del Programa",&columna,&fila);


	while(1);
}
