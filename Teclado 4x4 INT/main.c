
/**
 * main.c.
 */

#include <MSP.h>
#include <main.h>
#include <lcd.h>
#include <reloj.h>
#include <teclado.h>




int leerTeclado=0;//variable que idnica cuantas  veces
                    //se debe de actualizar la LCD
int teclaNUEVA=0; //bandera que indica nueva tecla presionada
int actualizarTECLA=0;//bandera que actualiza la LCD con la nueva tecla
int actualizarCONTEO=0;//bandera que actualiza la LCD con el nuevo conteo
int actualizarLED=0;//banderaq ue actualiza el LED
int led=0;//estado del LED
int tecl=0;//valor de la tecla presionada


int main(void)
{
    unsigned char columnaLCD=0,filaLCD=0;//columan y fila de la LCD
    long i=0;//variable para los retardos
    unsigned char contador=0;//conteo de las veces que se han presionado las teclas
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
	//4 bits , 2 lineas, 5x8 puntos, incr cursor
	Conf_LCD1602();//configuracion de la pantalla LCD1602
    LCD1602_Printf("TECLADO: \n\rCONTADOR:0",&columnaLCD,&filaLCD);
    Conf_Teclado();//configuracion de los pines del teclado
    LED_DIR|=LED;//configuracion del LED como salida
    LED_OUT&=~LED;//estado inicial LED=0
    _EINT(); //habilita las interrupciones GIE
	while(1)
	{

	    /*   TAREA 1*/
	    if(leerTeclado)//si se ha detectado un borde de bajada en alguna fila
	    {

            F0_IE&=~F0;//se deshabilitan las interrupciones
            F1_IE&=~F1;
            F2_IE&=~F2;
	        F3_IE&=~F3;
	        //tod el proceso es critico por lo tanto las inte
	        //vinculadas se habilitan hasta el final

            leerTeclado--; //indica que se atendio la peticion
            if(tecla[filaTECLADO]==16) //si en esa fila no se ha presionado ningun boton
            {
                //la columna de esa fila se pone en 0
                //por si no se detecta boton no actualice la tecla
                teclaFC[filaTECLADO]=0;
                columnaTECLADO=4;
                //estado incial de las columnas=0
                while(columnaTECLADO)
                {
                    //si alguna fila tiene esa misma columna vinculada
                    //no actualiza la salida vinculada a esa columna
                    if((teclaFC[0]!=columnaTECLADO) && (teclaFC[1]!=columnaTECLADO)&&
                       (teclaFC[2]!=columnaTECLADO) &&(teclaFC[3]!=columnaTECLADO))
                        //actualiza la columna corrpondente a 1
                        *cOUT[columnaTECLADO-1]|=cBIT[columnaTECLADO-1];
                    //retardo necesario para detectar 1
                    //(carga del capacitor) por debounce
                    for(i=0;i<RETARDo;i++);
                    //si en la fila se detecto un 1 significa que es
                    //la columna indicada
                    if((*(fIn[filaTECLADO])&fBit[filaTECLADO]))
                    {
                        //cambia el flanco de la fila
                        //para poder detectar los 2 flancos
                        *fIes[filaTECLADO]&=~fBit[filaTECLADO];
                        //vincula la columna correspondiente a la fila en cuestion
                        teclaFC[filaTECLADO]=columnaTECLADO;
                        break;
                    }
                //realiza 4 ciclos para cada una de las columnas
                columnaTECLADO--;
                }
                //se detecte columna o no se reinician las columnas
                //para poder detectar cualquier flanco
                C0_OUT&=~C0;
                C1_OUT&=~C1;
                C2_OUT&=~C2;
                C3_OUT&=~C3;
                //si se detecto alguna columna en esa fila
                if(teclaFC[filaTECLADO])
                {
                    //guarda el valor de la tecla presionada en esa fila
                    //por medio del arreglo del teclado
                    tecl=tecla[filaTECLADO]=teclado[filaTECLADO][columnaTECLADO-1];
                    //indica que se presiono nueva tecla
                    teclaNUEVA++;
                    //indica que se debe actualizar la LCD
                    actualizarTECLA++;

                    //condiciones para cada tecla presionada
                    switch(tecl)
                    {
                    case 7:
                        actualizarLED++;
                        led=0;
                        break;
                    case 10:
                        actualizarLED++;
                        led=1;
                        break;
                    case 2:
                        actualizarLED++;
                        led^=1;
                        break;
                    case 6:
                        actualizarLED++;
                        led=1;
                        break;
                    default:
                        break;
                    }
                }
                //retardo para que se descargue el capacitor
                for(i=0;i<RETARDo;i++);
                //si se identifico un flanco indeseado se elimina
                *fIfg[filaTECLADO]&=~fBit[filaTECLADO];
            }
            //se vuelve a actualizar las iterrupcionses
            F0_IE|=F0;
            F1_IE|=F1;
            F2_IE|=F2;
            F3_IE|=F3;

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
	        LCD1602_Printf("%c",&columnaLCD,&filaLCD,tabla[tecl]);
	    }


        /*TAREA 4*/
	    //tarea que actualiza el conteo de las teclas
	    if(actualizarCONTEO)
	    {
	        //tarea 4 depende de tarea 2, ´no afectan intrrupciones
	       actualizarCONTEO--;//indica que se atendio la tarea
	       filaLCD=1; //indica en que posición imprimirá el contador
	       columnaLCD=9;
	      if(contador)//si el valor es 0 reinica la seccion
	           LCD1602_Printf("%u",&columnaLCD,&filaLCD,contador);//actualiza el valor
	       else
	           LCD1602_Printf("0   ",&columnaLCD,&filaLCD,contador);//reinicia los valores
	    }


        /*TAREA 5*/
	    //encargado de actualizar el estado del LED
	    if(actualizarLED)
	    {
	        //Tarea 5 depende de tarea 1 y de interrupciones
	        //interfiere en este caso la fila 0 pero si se tiene en otra intrrupcion
	        //la modificacion del led tiene que desactivarse su intrrupcion
	        F0_IE&=~F0;
	        //F1_IE&=~F1;
	        //F2_IE&=~F2;
	        //F3_IE&=~F3;
	        actualizarLED--;//indica que se atendio la tarea

	        //seccion critica porque interifere vriable global modificable en interrupciones
	        if(led)
	            LED_OUT|=LED;
	        else
	            LED_OUT&=~LED;

	        F0_IE|=F0;
	        //F1_IE&=~F1;
	        //F2_IE&=~F2;
	        //F3_IE&=~F3;
	    }


	}
}


//en el puerto 1 no existen interrupciones
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_IRQ(void)
{
    const char Int=P1IFG; //guarda el valor de P1IFG
    P1IFG=0;
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_IRQ(void)
{
    const char Int=P2IFG;//guarda el valor actual de las bandera del puerto 2
    const char Ie=P2IE;//guada que interrupiones estan activadas


    if((Int&F0)&&(Ie&F0))//si se activo la bandera y esta activa la int
    {
        P2IFG&=~F0;//indica que se ha atendido la int
        filaTECLADO=0;//la fila 0 del teclado esta vnculado a esta int
        if(F0_IES&F0)//si detecto flanco de bajada
        {
            leerTeclado++;//indica que debe leer el teclado
        }
        else//si se detecta flanco de subida
        {
            F0_IES|=F0;//se cambia la deteccion de flanco a bajada
            //accion cuando se deja de presionar la tecla
            switch(tecla[0])//depende del valor de tecla que existe en la fila 0
            {
            case 1://los casos de la fila 0
            case 2:
            case 3:
            case 15:
            default:
                break;
            }
            tecla[0]=16;//reinicia el valor de la tecla(ya no esta presionado la tecla)
            teclaFC[0]=0;//reinicia la columna asociada a la fila
        }
    }

    if((Int&F1)&&(Ie&F1))
    {
        P2IFG&=~F1;
        filaTECLADO=1;
        if(F1_IES&F1)
        {
        leerTeclado++;
        }
        else
        {
            F1_IES|=F1;
            switch(tecla[1])
            {
            case 4:
            case 5:
                break;
            case 6:
                actualizarLED++;
                led=0;
                break;
            case 14:
            default:
                break;
            }
            tecla[1]=16;
            teclaFC[1]=0;
        }

    }

    if((Int&F2)&&(Ie&F2))
    {
        P2IFG&=~F2;
        filaTECLADO=2;
        if(F2_IES&F2)
        {
        leerTeclado++;
        }
        else
        {
            F2_IES|=F2;
            switch(tecla[2])
            {
            case 7:
            case 8:
            case 9:
            case 13:
            default:
                break;
            }
            tecla[2]=16;
            teclaFC[2]=0;
        }
    }

    if((Int&F3)&&(Ie&F3))
    {
        P2IFG&=~F3;
        filaTECLADO=3;
        if(F3_IES&F3)
        {
        leerTeclado++;
        }
        else
        {
            F3_IES|=F3;
            switch(tecla[3])
            {
            case 10:
            case 0:
            case 11:
            case 12:
            default:
                break;
            }
            tecla[3]=16;
            teclaFC[3]=0;
        }

    }


}
