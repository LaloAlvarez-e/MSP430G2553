
/**
 * main.c.
 */

#include <MSP.h>
#include <lcd.h>
#include <reloj.h>
#include <teclado.h>


const unsigned char teclado[4][4]= //[Fila][columna]
{{1,2,3,15},
 {4,5,6,14},
 {7,8,9,13},
 {10,0,11,12}
};
unsigned char volatile* cOUT[]={&C0_OUT,&C1_OUT,&C2_OUT,&C3_OUT};
const unsigned char cBIT[]={C0,C1,C2,C3};

volatile unsigned char *volatile fIn[]={&F0_IN,&F1_IN,&F2_IN,&F3_IN};
unsigned char volatile* fIfg[]={&F0_IFG,&F1_IFG,&F2_IFG,&F3_IFG};
const unsigned char fBit[]={F0,F1,F2,F3};

unsigned char *tabla="0123456789*#CDEF";

int fila=0;  //estado del LED
int columna=0;
int tecla=0;
int leerTeclado=0;//variable que idnica cuantas  veces
                    //se debe de actualizar la LCD
int teclaNUEVA=0;

int main(void)
    {
    unsigned char columnaLCD=0,filaLCD=0;
    long i=0;
    char contador=0;
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602
    LCD1602_Printf("TECLADO: \n\rCONTADOR:0",&columnaLCD,&filaLCD);
    Conf_Teclado();
    P1DIR|=BIT3;
    P1OUT&=~BIT3;
    _EINT(); //habilita las interrupciones GIE
	while(1)
	{

	    /*   TAREA 1*/
	    if(leerTeclado)
	    {

            F0_IE&=~F0;
            F1_IE&=~F1;
            F2_IE&=~F2;
	        F3_IE&=~F3;
            leerTeclado--; //indica que se atendio la peticion
            columna=4;
            while(columna)
            {
                *cOUT[columna-1]|=cBIT[columna-1];
                for(i=0;i<270;i++);
                if((*(fIn[fila])&fBit[fila]))
                {
                    *cOUT[columna-1]&=~cBIT[columna-1];
                    contador++;
                    break;
                }
                columna--;
            }

            C0_OUT&=~C0;
            C1_OUT&=~C1;
            C2_OUT&=~C2;
            C3_OUT&=~C3;
            for(i=0;i<200;i++);
            *fIfg[fila]&=~fBit[fila];
            F0_IE|=F0;
            F1_IE|=F1;
            F2_IE|=F2;
            F3_IE|=F3;
            if(columna)
            {
                tecla=tabla[teclado[fila][columna-1]];
                teclaNUEVA++;
            }

	    }

	    if(teclaNUEVA)
	    {
	        teclaNUEVA--;
	       filaLCD=0; //indica en que posición imprimirá el contador1
	       columnaLCD=8;
	       LCD1602_Printf("%c",&columnaLCD,&filaLCD,tecla);//reinicia los valores
	       filaLCD=1; //indica en que posición imprimirá el contador1
	       columnaLCD=9;
	      if(contador)
	           LCD1602_Printf("%i",&columnaLCD,&filaLCD,contador);//reinicia los valores
	       else
	           LCD1602_Printf("0   ",&columnaLCD,&filaLCD,contador);//reinicia los valores
	    }


	}
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_IRQ(void)
{
    const char Int=P1IFG; //guarda el valor de P1IFG
    P1IFG=0;
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_IRQ(void)
{
    const char Int=P2IFG;
    const char Ie=P2IE;


    if((Int&F0)&&(Ie&F0))
    {
        P2IFG&=~F0;
        leerTeclado++;
        fila=0;
    }

    if((Int&F1)&&(Ie&F1))
    {
        P2IFG&=~F1;
        leerTeclado++;
        fila=1;
    }

    if((Int&F2)&&(Ie&F2))
    {
        P2IFG&=~F2;
        leerTeclado++;
        fila=2;
    }

    if((Int&F3)&&(Ie&F3))
    {
        P2IFG&=~F3;
        leerTeclado++;
        fila=3;

    }


}
