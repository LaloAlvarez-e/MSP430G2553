
/**
 * main.c.
 */

#include <msp430g2553.h>
#include <lcd.h>
#include <reloj.h>


//          PxIE               //  1= habilitado 0= deshabilitado
//habilitación individual de interrupcion en cada pin del P1 y P2





//           PxIES               // 1= borde de bajada (high-low)
                                  //0=borde de subida (low-high)
//Selección de borde de interrupcion en cada pin del P1 y P2
/*
 *  ___                          __
 *     |   1=borde de bajada    |     0=borde de subida
 *     |__                    __|
 *
 */



//             PxIFG              //registro donde se guarda la bandera
                                  //de interupcion 1= interrupcion pendiente
//PxIFG se actualiza incluso si no esta activada la interrupcion


int contador1=0; //variable para indicar el conteo del boton 1
int contador2=0; //variable para indicar el conteo del boton 2
int actualizarLCD1=0;//variable que idnica cuantas  veces
                    //se debe de actualizar la LCD
int actualizarLCD2=0
        ;


int main(void)
{
    unsigned char columna=0,fila=0;
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602
	LCD1602_Printf("Contador1: 0\n\rContador2: 0",&columna,&fila);

	P1DIR&=~BIT6; //configura el boton1 como entrada P1.6
	P1REN&=~BIT6; //boton1 sin resistencia interna

	P2DIR&=~BIT3; //configura el boton2 como entrada P2.3
	P2REN&=~BIT3; //boton2 sin resistencia interna


	P1IES|=BIT6; //interrupcion por flanco de bajada
    P2IES|=BIT3;
    P1IFG&=~BIT6; //reinicia cualquier interrupcion pendiente
    P2IFG&=~BIT3;

    P1IE|=BIT6; //habilita las interrupciones en P1.6 y P2.3
    P2IE|=BIT3;
    _EINT(); //habilita las interrupciones GIE
	while(1)
	{
	    if(actualizarLCD1) //si necesita actualizar el contador1
	    {
	        P1IE&=~BIT6;
	        actualizarLCD1--; //disminuye las veces de
	                          //actualización de la pantalla
	        P1IE|=BIT6;
	        contador1++; //aumenta en 1 el conteo
	        fila=0; //indica en que posición imprimirá el contador1
            columna=11;
            //manda a la pantalla el contador1
	        LCD1602_Printf("%i",&columna,&fila,contador1);
	    }
        if(actualizarLCD2)
        {
            P2IE&=~BIT3;
            actualizarLCD2--;
            P2IE|=BIT3;
            contador2++;
            fila=1;
            columna=11;
            LCD1602_Printf("%i",&columna,&fila,contador2);
        }
	}
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_IRQ(void)
{
    const char Int=P1IFG; //guarda el valor de P1IFG

    if(Int&BIT6) //si la interrupcon sucedio en P1.6
    {
        P1IFG&=~BIT6; //reincia la bandera de interrupcion
        actualizarLCD1++; //indica que se necesita actualizar la LCD
    }

}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_IRQ(void)
{
    const char Int=P2IFG;
    if(Int&BIT3)
    {
        P2IFG&=~BIT3;
        actualizarLCD2++;
    }
}
