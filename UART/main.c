#include <msp430g2553.h>
#include "clock.h"
#include "uart.h"

/**
 * main.c
 */
void main(void)
{
    char cDato=0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Clock_vInit();
	Uart_vInit(9600);
	Uart_u8SendString("Inicializacion del Uart completa...\r\n ");
	//  _EINT();
	while(1)
	{
	   if(Uart_u8UntilReceiveChar(&cDato))
	    {
	        Uart_u8SendString("\r\nNo Recibi Caracter en un Determinado Tiempo");
	    }
	    else
	    {
	        Uart_u8SendString("\r\nEl caracter Recibido Fue: ");
	        Uart_u8SendCharUntilComplete(cDato);
	    }
	}
}
