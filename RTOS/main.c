#include <MSP.h>
#include <lcd.h>



/**
 * main.c
 */

void proceso0(void);
void proceso1(void);
void proceso2(void);

long conteo0=0,conteo1=0,conteo2=0;
char x=1;

void main(void)
{
    unsigned char col=0,fila=0;
    _WDTCTL = WDT_HOLD;

    Conf_GPIO();
    Conf_Reloj();
	
	_LED1_DIR=1;
	_LED2_DIR=1;
    _LED1_OUT=0;
    _LED2_OUT=1;


    Conf_LCD1602();
    LCD1602_Printf("Hola Mundo",&col,&fila);
    //Clock_Salida();
   // Conf_OscFault();
    func=Programa;
    Agregar_Procesos(proceso0,proceso1,proceso2);
    LanzarOS();
    while(1)
    {

    }
}


void proceso0(void)
{


    _WDTCTL =WDT_INTERVAL_ACLK_64 ;
    _WDTIE=1;
    _P1DIR|=P2;
    _P1OUT&=~P2;
    while(1)
    {
        conteo0++;
        _P1OUT^=P2;
        OS_Señal(&x);
    }
}



void proceso1(void)
{
    _P1DIR|=P3;
    _P1OUT&=~P3;
    while(1)
    {
        OS_Espera(&x);
        conteo1++;
        _P1OUT^=P3;
    }
}


void proceso2(void)
{
    _P1DIR|=P5;
    _P1OUT&=~P5;
    while(1)
    {
        _P1OUT^=P5;
        conteo2++;
    }
}
