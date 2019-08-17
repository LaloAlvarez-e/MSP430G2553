/*
 * teclado.c
 *
 *  Created on: 09/09/2017
 *      Author: Lalo
 */

#include <teclado.h>

void Conf_Teclado(void)
{

    C0_DIR|=C0;
    C0_OUT&=~C0;
    C0_REN&=~C0;
    C0_SEL&=~C0;
    C0_SEL2&=~C0;

    C1_DIR|=C1;
    C1_OUT&=~C1;
    C1_REN&=~C1;
    C1_SEL&=~C1;
    C1_SEL2&=~C1;

    C2_DIR|=C2;
    C2_OUT&=~C2;
    C2_REN&=~C2;
    C2_SEL&=~C2;
    C2_SEL2&=~C2;

    C3_DIR|=C3;
    C3_OUT&=~C3;
    C3_REN&=~C3;
    C3_SEL&=~C3;
    C3_SEL2&=~C3;

    F0_DIR&=~F0; //filas son entradas con interrupciones
    F0_OUT&=~F0;
    F0_REN&=~F0;
    F0_SEL&=~F0;
    F0_SEL2&=~F0;
    F0_IES|=F0;
    F0_IFG&=~F0;
    F0_IE&=~F0;

    F1_DIR&=~F1;
    F1_OUT&=~F1;
    F1_REN&=~F1;
    F1_SEL&=~F1;
    F1_SEL2&=~F1;
    F1_IES|=F1;
    F1_IFG&=~F1;
    F1_IE&=~F1;

    F2_DIR&=~F2;
    F2_OUT&=~F2;
    F2_REN&=~F2;
    F2_SEL&=~F2;
    F2_SEL2&=~F2;
    F2_IES|=F2;
    F2_IFG&=~F2;
    F2_IE&=~F2;

    F3_DIR&=~F3;
    F3_OUT&=~F3;
    F3_REN&=~F3;
    F3_SEL&=~F3;
    F3_SEL2&=~F3;
    F3_IES|=F3;
    F3_IFG&=~F3;
    F3_IE&=~F3;

}


const unsigned char teclado[4][4]= //[Fila][columna]
{{1,2,3,15},
 {4,5,6,14},
 {7,8,9,13},
 {10,0,11,12}
};


volatile unsigned char* C_OUT[4]={&C0_OUT,&C1_OUT,&C2_OUT,&C3_OUT};
unsigned char Col[4]={C0,C1,C2,C3};

volatile unsigned char* F_IN[4]={&F0_IN,&F1_IN,&F2_IN,&F3_IN};
unsigned char Fila[4]={F0,F1,F2,F3};

char Leer_Teclado(void)
{
    register char filaTECLADO=4;  //fila presionada
    register char columnaTECLADO=4;//columna presionada
    register char tecla=16;
    register int i=0;

    for(i=3; i>=0;i--)
    {
        if(!(*F_IN[i]&Fila[i]))
        {
            filaTECLADO=i;
            break;
        }
    }

    if(filaTECLADO!=4)
    {
        while(columnaTECLADO) //columnaTECLADO inicia en 4
        {


            //realiza 4 ciclos para cada una de las columnas
            //actualiza la salida de la columna correspondiente a 1
            *C_OUT[columnaTECLADO-1]|=Col[columnaTECLADO-1];
            //retardo necesario para detectar 1
            //(carga del capacitor) por debounce
            for(i=0;i<RETARDo;i++);
            //si en la fila se detecto un 1 significa que es
            //la columna indicada

            if( *F_IN[filaTECLADO]&Fila[filaTECLADO] )
            {
                break;
            }
            columnaTECLADO--; //esta linea estaba al final del while

        }
        //si se detecto alguna columna en esa fila
        if(columnaTECLADO!=0)
            tecla=teclado[filaTECLADO][columnaTECLADO-1];
        C0_OUT&=~C0;
        C1_OUT&=~C1;
        C2_OUT&=~C2;
        C3_OUT&=~C3;
        //retardo para que se descargue el capacitor
        for(i=0;i<RETARDo;i++);
    }
    return tecla;
}

