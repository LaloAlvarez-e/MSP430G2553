/*
 * procesos.c
 *
 *  Created on: 2 oct. 2017
 *      Author: InDev
 */

#include <procesos.h>


void Iniciar_Stack(unsigned int i)
{
    short* direccion = &stacks[i][STACK-14];
    tcbs[i].sp =direccion;
    stacks[i][STACK-2]=0x0008; //SR
    stacks[i][STACK-3]=0x1515; //R15
    stacks[i][STACK-4]=0x1414; //R14
    stacks[i][STACK-5]=0x1313; //R13
    stacks[i][STACK-6]=0x1212; //R12
    stacks[i][STACK-7]=0x1111; //R11
    stacks[i][STACK-8]=0x1010; //R10
    stacks[i][STACK-9]=0x0909; //R9
    stacks[i][STACK-10]=0x0808; //R8
    stacks[i][STACK-11]=0x0707; //R7
    stacks[i][STACK-12]=0x0606; //R6
    stacks[i][STACK-13]=0x0505; //R5
    stacks[i][STACK-14]=0x0404; //R4
}


int Agregar_Procesos(void(*proceso0)(void),void(*proceso1)(void),void(*proceso2)(void))
{
    short estado;

    estado =__get_SR_register()&0x8;
    _DINT();
    tcbs[0].sig = &tcbs[1];
    tcbs[1].sig = &tcbs[2];
    tcbs[2].sig = &tcbs[0];

    Iniciar_Stack(0);
    stacks[0][STACK-1]= (short)(proceso0);
    Iniciar_Stack(1);
    stacks[1][STACK-1]= (short)(proceso1);
    Iniciar_Stack(2);
    stacks[2][STACK-1]= (short)(proceso2);
    RunPt=&tcbs[0];
    __bis_SR_register(estado);
    return 1;
}


void LanzarOS(void)
{
    asm(
            " mov &RunPt,R15 \n"
            " mov 0(R15),SP \n"
            " nop \n "
            " pop R4 \n"
            " pop R5 \n"
            " pop R6 \n"
            " pop R7 \n"
            " pop R8 \n"
            " pop R9 \n"
            " pop R10 \n"
            " pop R11 \n"
            " pop R12 \n"
            " pop R13 \n"
            " pop R14 \n"
            " pop R15 \n"
            " pop SR \n"
            " pop PC \n"
            );

}



void Programa(void)
{
    RunPt = RunPt->sig;  // Round Robin
}



void OS_Espera(char* señal)
{
    const register short IntGeneral=__get_SR_register()&0x8;

    while(!(*señal));
    _DINT();
    *señal--;
    __bis_SR_register(IntGeneral);
}

void OS_Señal(char* señal)
{
    const register short IntGeneral=__get_SR_register()&0x8;
    _DINT();

    *señal++;

    __bis_SR_register(IntGeneral);
}
