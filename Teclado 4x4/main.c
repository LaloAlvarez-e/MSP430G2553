
/**
 * main.c.
 */

#include <MSP.h>
#include <lcd.h>
#include <reloj.h>
#include <teclado.h>



//interpretacion del valor de cada posicion del teclado


int teclaActual=0, teclaAnterior=0;//valor de la tecla presionada

int teclaNUEVA=0; //bandera que indica nueva tecla presionada
int actualizarCONTEO=0;//bandera que actualiza la LCD con el nuevo conteo
int actualizarTECLA=0;//bandera que actualiza la LCD con la nueva tecla

//vincula el valor de cada boton con un valor en caracter
unsigned char *tabla="0123456789*#CDEF";

int main(void)
{
    unsigned char columnaLCD=0,filaLCD=0;//columan y fila de la LCD
    int contador=0;//conteo de las veces que se han presionado las teclas
    long tiempoProcesos=0;
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602
    LCD1602_Printf("TECLADO: \n\rCONTADOR:0",&columnaLCD,&filaLCD);
    Conf_Teclado();
    while(1)
	{

	    /*   TAREA 1*/
        teclaAnterior=teclaActual;
	    teclaActual=Leer_Teclado();
	    if((teclaActual!=16) && (teclaActual!=teclaAnterior))//si se ha detectado alguna tecla
	    {
	        teclaNUEVA++;
            //indica que se debe actualizar la LCD
            actualizarTECLA++;
            //condiciones para cada tecla presionada
	        switch(teclaActual)
            {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            default:
                break;
            }
	    }

	    /*TAREA 2*/
        //tarea especializada paraaumntar el conteo de los botones
        if(teclaNUEVA)
        {
            //tarea 2 depende de tarea 1
           // como ninguna int afecta esta tarea no se desactivan
           teclaNUEVA--;//se atiende la actualizacion
           actualizarCONTEO++;//se indica que se actualice la pantalla con el nuevo conteo
           contador++;//aumenta el conteo
        }

        /*TAREA 3*/
        //tarea que actualiza la pantalla LCD con la nueva tecla
        if(actualizarTECLA)
        {
            //Tarea 3 depende de Tarea 1 por tanto no afectan las interrupciones
            actualizarTECLA--;//indica que se atendio esta tarea
            filaLCD=0; //indica en que posición imprimirá el contador1
            columnaLCD=8;
            //imprime la tecla presionada por medio del arreglo creado
            LCD1602_Printf("%c",&columnaLCD,&filaLCD,tabla[teclaActual]);
        }


        /*TAREA 4*/
        if(actualizarCONTEO)
        {
            //tarea que actualiza el conteo de las teclas
           actualizarCONTEO--;
           filaLCD=1; //indica en que posición imprimirá el contador
           columnaLCD=9;
           if(contador)
               LCD1602_Printf("%u",&columnaLCD,&filaLCD,contador);//actualiza el valor
           else
               LCD1602_Printf("0   ",&columnaLCD,&filaLCD,contador);//reinicia los valores
        }

        for(tiempoProcesos=0; tiempoProcesos<200000;tiempoProcesos++);


	}
}
