
/**
 * main.c
 */

#include <msp430g2553.h>
#include <lcd.h>
#include <reloj.h>


int main(void)
{
    double a=-17.302946838194; //mumero double a imprimir
    unsigned char cantidad=0,columna=0,fila=0; //cantidad= numero de digitos convertidos, columna y fila pos de la LCD
    char cadena[20]; //arreglo donde se guarda el numero a convertir
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602
	LCD1602_Cadena("Funcion C.Float",&columna,&fila);
	columna=0; fila=1; //cambia a la 2 fila
    cantidad=Conv_Float(a,2, cadena); //convierte el numero con 2 decimales y lo guarda en cadena
	LCD1602_Cadena(cadena,&columna,&fila); //imprime el numero

	columna++; //aumenta en 1 la columna simulando espacio en blanco
    cantidad=Conv_Entero(cantidad, cadena);//convierte el numero de digitos comvertidos
    LCD1602_Cadena(cadena,&columna,&fila); //imprime los digitos

    columna++;
    cantidad=Conv_Float(a,0, cadena);
    LCD1602_Cadena(cadena,&columna,&fila);

    columna++;
    cantidad=Conv_Entero(cantidad, cadena);
    LCD1602_Cadena(cadena,&columna,&fila);

	while(1);
}
