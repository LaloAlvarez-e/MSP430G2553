/*
 * procesos.h
 *
 *  Created on: 2 oct. 2017
 *      Author: InDev
 */

#ifndef PROCESOS_H_
#define PROCESOS_H_

#include <MSP.h>

void Programa(void);
void Iniciar_Stack(unsigned int i);
int Agregar_Procesos(void(*proceso0)(void),void(*proceso1)(void),void(*proceso2)(void));
void LanzarOS(void);
void OS_Espera(char* señal);
void OS_Señal(char* señal);



#define NUMPROCESOS 3
#define STACK 20

struct tcb{
    short *sp;
    struct tcb *sig;
};

typedef struct tcb tcbTipo;
tcbTipo tcbs[NUMPROCESOS];
tcbTipo *RunPt;
short stacks[NUMPROCESOS][STACK];

void(*func)(void);

#endif /* PROCESOS_H_ */
