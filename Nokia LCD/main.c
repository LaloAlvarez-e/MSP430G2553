#include <msp430g2553.h>
#include "Imagenes.h"
#include "LCD_Nokia.h"
#include "Init.h"
#include "Sonidos.h"
/*
 * main.c
 */

void Init_Enemigos(void);
void Mover_Enemigos(void);
void Dibujar_Enemigos(void);

struct Estado
{
	unsigned char x;
	unsigned char y;
	const unsigned char* Imagen[2];
	char vida;
};


typedef struct Estado STipo;
STipo Enemigos[1];
STipo Nave;
unsigned char Dibujar=0;

void Init_Enemigos(void)
{
    for(unsigned char i=0; i<1 ; i++)
    {
    	Enemigos[i].x=i*20;
    	Enemigos[i].y=ENEMY10H-1;
    	Enemigos[i].Imagen[0]=SmallEnemy10PointA;
    	Enemigos[i].Imagen[1]=SmallEnemy10PointB;
    	Enemigos[i].vida=1;
    }
	Nave.x=33;
	Nave.y=39;
	Nave.Imagen[0]=PlayerShip0;
	Nave.vida=1;
}

void Mover_Nave(unsigned char pos)
{
    		Nave.x=pos;
}

void Mover_Enemigos(void)
{
    for(unsigned char i=0; i<1 ; i++)
    {
    	if(Enemigos[i].x<(MAX_X-ENEMY10H-1))
    		Enemigos[i].x+=2;
    	else
    		Enemigos[i].vida=0;
    }
}

void Dibujar_Enemigos(void)
{
	static unsigned char Movimiento=0;
    LCD_LimpiarBuffer();
    for(unsigned char i=0; i<1 ; i++)
    {
    	if(Enemigos[i].vida>0)
    		LCD_BMP(Enemigos[i].x,Enemigos[i].y,Enemigos[i].Imagen[Movimiento],0);
    }
    LCD_BMP(Nave.x,Nave.y,Nave.Imagen[0],0);
    LCD_DibujarBuffer();
    Movimiento = (Movimiento+1)&0x01;
}

void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    Init_BOARD();
    Init_LCD();
    Init_SONIDO();
    _EINT();
    Init_Enemigos();
    while(1)
    {


    }
}


#pragma vector=ADC10_VECTOR
__interrupt void ADC_IRQ (void)
{
	unsigned long contador=0;
	contador=ADC10MEM;
	contador*=70;
	contador/=1023;
	Mover_Nave(contador);

}


#pragma vector=PORT2_VECTOR
__interrupt void PORT2_IRQ(void)
{
	//P2OUT|=BIT1;
	LCD_Limpiar();
	P2IFG&=~BIT7;
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_IRQ(void)
{
	P2OUT|=BIT0;

	Sonido_Shoot();
	P1IFG&=~BIT0;
}




#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMERA01_IRQ(void)
{

	switch(TA0IV)
	{
	case 0x2:
		P2OUT&=~BIT0;

		//P2OUT&=~BIT1;
		Mover_Enemigos();
		break;
	case 0x4:
		break;
	default:
		break;
	}


}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMERA0_IRQ(void) //programa principal
{
	Dibujar_Enemigos();


}
/*
#pragma vector=TRAPINT_VECTOR
#pragma vector=RESET_VECTOR
#pragma vector=USCIAB0TX_VECTOR
#pragma vector=USCIAB0RX_VECTOR
#pragma vector=WDT_VECTOR
#pragma vector=COMPARATORA_VECTOR
#pragma vector=NMI_VECTOR
*/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMERA10_IRQ(void)
{

}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMERA1_IRQ(void)
{
	switch(TA1IV)
	{
	case 10:
		P2OUT^=BIT1;
		Tocar();
		break;
	default:
		break;
	}
}

