/*
 * teclado.c
 *
 *  Created on: 09/09/2017
 *      Author: Lalo
 */

#include <teclado.h>

/*
const unsigned char teclado[4][4]= //[Fila][columna]
{{1,2,3,15},
 {4,5,6,14},
 {7,8,9,13},
 {10,0,11,12}
};
unsigned char volatile* cOUT[]={&C0_OUT,&C1_OUT,&C2_OUT,&C3_OUT};
const unsigned char cBIT[]={C0,C1,C2,C3};

unsigned char const volatile* fIn[]={&F0_IN,&F1_IN,&F2_IN,&F3_IN};
const unsigned char fBit[]={F0,F1,F2,F3};
unsigned char *tabla="0123456789*#CDEF";

*/

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
/*
char Leer_Teclado(char fila)

{
    unsigned char columna=0;
    unsigned char valorTeclado=0;


    for(columna=4;columna>=1;columna--)
    {
        *(cOUT[columna-1])|=(cBIT[columna-1]);
        _NOP();
         if((*fIn[fila]&fBit[fila]))
         {
             valorTeclado=tabla[teclado[fila][columna-1]];
             _NOP();
             break;
         }
    }
    C0_OUT&=~C0;
    C1_OUT&=~C1;
    C2_OUT&=~C2;
    C3_OUT&=~C3;

    return valorTeclado;
}
*/

