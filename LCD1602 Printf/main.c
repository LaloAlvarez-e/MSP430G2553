
/**
 * main.c
 */

#include <msp430g2553.h>
#include <lcd.h>
#include <reloj.h>


int main(void)
{
    unsigned char columna=0,fila=0; //cantidad= numero de digitos convertidos, columna y fila pos de la LCD
    char cadena[25]; //arreglo donde se guarda el numero a convertir
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602
	LCD1602_Cadena("Funcion Hex,Oct",&columna,&fila);
	columna=0; fila=0; //cambia a la 1 fila
	LCD1602_Cadena("HEX:",&columna,&fila);
    Conv_HEX(-1234736225664, cadena); //convierte el numero en su representacion hexadecimal
	LCD1602_Cadena(cadena,&columna,&fila); //imprime el numero

	columna=0; fila=1; //cambia a la 2 fila
	LCD1602_Cadena("Oct:",&columna,&fila);
    Conv_Oct(45,cadena);//convierte 45 en su representacion octal
    LCD1602_Cadena(cadena,&columna,&fila); //imprime los digitos

    columna++;
    LCD1602_Cadena("Hex:",&columna,&fila);
    Conv_Hex(126, cadena);//convierte 45 en su representacion hexa
    LCD1602_Cadena(cadena,&columna,&fila);


	while(1);
}
