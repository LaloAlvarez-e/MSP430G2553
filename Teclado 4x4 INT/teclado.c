/*
 * teclado.c
 *
 *  Created on: 09/09/2017
 *      Author: Lalo
 */

#include <teclado.h>


//interpretacion del valor de cada posicion del teclado
const unsigned char teclado[4][4]= //[Fila][columna]
{{1,2,3,15},
 {4,5,6,14},
 {7,8,9,13},
 {10,0,11,12}
};

//variable auxiliar de la PxOUT de las columnas para un facil cambio de pines
unsigned char volatile* cOUT[]={&C0_OUT,&C1_OUT,&C2_OUT,&C3_OUT};
//variable que mantiene losbits de cada columna
const unsigned char cBIT[]={C0,C1,C2,C3};


//mismas variables para PxIN, PxIFG PXIES en las filas y suspines asociados
volatile unsigned char *volatile fIn[]={&F0_IN,&F1_IN,&F2_IN,&F3_IN};
unsigned char volatile* fIfg[]={&F0_IFG,&F1_IFG,&F2_IFG,&F3_IFG};
unsigned char volatile* fIes[]={&F0_IES,&F1_IES,&F2_IES,&F3_IES};
const unsigned char fBit[]={F0,F1,F2,F3};

//vincula el valor de cada boton con un valro en caracter
unsigned char *tabla="0123456789*#CDEF";

//variable que guarda el valor de  cada fila
unsigned char tecla[4]={16,16,16,16};
//variable que guarda la column asociada a la fila
unsigned char teclaFC[4]={0,0,0,0};

int filaTECLADO=0;  //fila presionada
int columnaTECLADO=0;//columna presionada

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
    F0_IE|=F0;
    F0_IES|=F0;
    F0_IFG&=~F0;

    F1_DIR&=~F1;
    F1_OUT&=~F1;
    F1_REN&=~F1;
    F1_SEL&=~F1;
    F1_SEL2&=~F1;
    F1_IE|=F1;
    F1_IES|=F1;
    F1_IFG&=~F1;

    F2_DIR&=~F2;
    F2_OUT&=~F2;
    F2_REN&=~F2;
    F2_SEL&=~F2;
    F2_SEL2&=~F2;
    F2_IE|=F2;
    F2_IES|=F2;
    F2_IFG&=~F2;

    F3_DIR&=~F3;
    F3_OUT&=~F3;
    F3_REN&=~F3;
    F3_SEL&=~F3;
    F3_SEL2&=~F3;
    F3_IE|=F3;
    F3_IES|=F3;
    F3_IFG&=~F3;

}


