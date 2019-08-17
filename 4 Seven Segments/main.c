#include <main.h>


const unsigned char codificacion[16]=
{
 SEG_N0,SEG_N1,SEG_N2,SEG_N3,SEG_N4,SEG_N5,SEG_N6,SEG_N7,
 SEG_N8,SEG_N9,SEG_NA,SEG_NB,SEG_NC,SEG_ND,SEG_NE,SEG_NF
};

const unsigned char comunes[4]=
{
 CE3,CE2,CE1,CE0
};


void Conf_IO(void) //funcion de configuracion de los Puertos de entrada y salida
{
    P1OUT=0xFF; //manda a 3.3V las salidas del puerto 1
    P1DIR =0xFF; //todos los pines del puerto 1 son salidas
    P1REN=0; //desactiva las resistencia internas en las entradas del puerto 2
    P1SEL=0;
    P1SEL2=0; //vincula el puerto 1 a GPIO

    P2OUT=0x0; //manda a 0V las salidas del puerto 2
    P2DIR =BIT0|BIT1|BIT2|BIT3; //todos los pines del puerto 2 son salidas
    P2REN=0; //desactiva las resistencia internas en las entradas del puerto 2
    P2SEL=0;
    P2SEL2=0; //vincula el puerto 2 a GPIO
}



/**
 * main.c
 */
void main(void)
{
    unsigned int contador=0; //mantiene el valor actual del contador
    unsigned int numero=0; //variable ue sirve para obtenel el nibble apropiado
    unsigned long i=0; //variable para el ciclo de obtencion de los 4 valores
    unsigned long j=0; //variable del retardo intermedio entre los display
    unsigned long retardo=0; //variable para el retardo del aumento de contador
    unsigned long aux=0; //variable para guardar los nibbles restantes
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Conf_IO(); //funcion de configuracion de GPIO
    while(1)
    {
        aux=contador;
        for(i=0;i<4;i++) //ciclo necesario para imprimir a los 4 display
        {
            for(j=0;j<150;j++);//retardo necesario para evitar interferencia entre dsplay
            PCE=comunes[i];//selecciona cual Display se va a modificar o visualizar
            numero=aux&0xF; //obtiene el siguiente nibble de menor peso
            PSEG=codificacion[numero];//manda la codificacion del numero
            aux>>=4; //obtiene el siguiente nibble
        }
        retardo++;
        if(retardo>30)
        {
            retardo=0;
            contador++;//aumento del contador
        }
    }
}
