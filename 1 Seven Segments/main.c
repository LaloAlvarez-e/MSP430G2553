#include <main.h>


const unsigned char segmento1[16]=
{
 SEG1_N0,SEG1_N1,SEG1_N2,SEG1_N3,SEG1_N4,SEG1_N5,SEG1_N6,SEG1_N7,
 SEG1_N8,SEG1_N9,SEG1_NA,SEG1_NB,SEG1_NC,SEG1_ND,SEG1_NE,SEG1_NF
};


const unsigned char segmento2[16]=
{
 SEG2_N0,SEG2_N1,SEG2_N2,SEG2_N3,SEG2_N4,SEG2_N5,SEG2_N6,SEG2_N7,
 SEG2_N8,SEG2_N9,SEG2_NA,SEG2_NB,SEG2_NC,SEG2_ND,SEG2_NE,SEG2_NF
};

void Conf_IO(void) //funcion de configuracion de los Puertos de entrada y salida
{
    P1OUT=0xFF; //manda a 3.3V las salidas del puerto 1
    P1DIR =0xFF; //todos los pines del puerto 1 son salidas
    P1REN=0; //desactiva las resistencia internas en las entradas del puerto 2
    P1SEL=0;
    P1SEL2=0; //vincula el puerto 1 a GPIO

    P2OUT=0; //manda a 0V las salidas del puerto 2
    P2DIR =0xFF; //todos los pines del puerto 2 son salidas
    P2REN=0; //desactiva las resistencia internas en las entradas del puerto 2
    P2SEL=0;
    P2SEL2=0; //vincula el puerto 2 a GPIO
}



/**
 * main.c
 */
void main(void)
{
    unsigned char contador=0;
    unsigned long i=0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_IO();
	while(1)
	{
	    for(i=0;i<50000;i++); //retardar el conteo
	    SEG1=segmento1[(contador>>4)&0xF];
	    SEG2=segmento2[contador&0xF];



	    contador++;
	}
}
