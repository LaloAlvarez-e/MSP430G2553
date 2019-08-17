
/**
 * main.c
 */

#include <msp430g2553.h>
#include <lcd.h>
#include <reloj.h>



int main(void)
{
    unsigned char columna=0,fila=0,columna1=0,fila1=0;
    char cadena[9];
    int conteo; //cantidad= numero de digitos convertidos, columna y fila pos de la LCD
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	P1DIR|=BIT0;
	P1OUT&=~BIT0;
	Conf_LCD1602();//configuracion de la pantalla LCD1602
	conteo=LCD1602_Printf("\t\t %s Printf Parte %c ",&columna,&fila,"InDevice\n\r",'3');
	LCD1602_Printf("%x %q",&columna,&fila,conteo);
	LCD1602_Lectura(1,0,5,cadena);
	columna=0;
	fila=0;
    LCD1602_Printf("\f",&columna,&fila);
	LCD1602_Printf("%p",&columna,&fila,cadena);
	LCD1602_LCom(&columna1,&fila1);
	columna1+=2;
    LCD1602_Printf("Hola mundo %%",&columna1,&fila1);


	while(1);
}
