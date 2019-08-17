/*
 * WatchDog.c
 *
 *  Created on: 29 sep. 2017
 *      Author: InDev
 */

#include <WatchDog.h>




#pragma vector=10
__interrupt void WDT_IRQ(void)
{

    asm(
            " push R15 \n"
            " push R14 \n"
            " push R13 \n"
            " push R12 \n"
            " push R11 \n"
            " push R10 \n"
            " push R9 \n"
            " push R8 \n"
            " push R7 \n"
            " push R6 \n"
            " push R5 \n"
            " push R4 \n"
            " mov.w &RunPt,R15 \n"
            " mov.w SP,0(R15) \n"
            //" mov.w 2(R15),R14 \n"
            //" mov.w R14,RunPt \n"
            " push R15 \n"
            " mov.w &func,R15 \n"
            " call R15 \n"
            " pop R15 \n"
            " mov.w &RunPt,R15 \n"
            " mov.w 0(R15),SP \n"
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
            " nop \n "
        );
}

