
/**
 * main.c
 */

#include <msp430g2553.h>
#include <lcd.h>
#include <reloj.h>




int main(void)
{
   unsigned char i=0,columna=0,fila=0;
   WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602

	LCD1602_Cadena("Caracteres Esp",&columna,&fila);
	columna=0;
	fila=1;
	LCD1602_Cadena("°¬¡¿\\¨´ñ",&columna,&fila);


	LCD1602_Pos(columna+1,fila);
	//°¬¡?\¨´ñ
    for(i=0;i<8;i++)
    {
        LCD1602_Dato(i);
    }


	while(1);
}
