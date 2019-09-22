/*
 * TimerA.h
 *
 *  Created on: 21/09/2019
 *      Author: Lalo
 */

#ifndef DRIVER_TIMERA_H_
#define DRIVER_TIMERA_H_




#include "msp430g2553.h"
#include "stdint.h"

typedef enum
{
    SysTick_enOK = 0,
    SysTick_enERROR = 1,
}SysTick_nStatus;

SysTick_nStatus SysTick__enInitUs(float fTimeUs);
void SysTick__vRestart(void);
float SysTick__fGetTimeUs(void);
float SysTick__fGetFrec(void);
uint64_t SysTick__u64GetCount(void);
uint32_t SysTick__u32GetCountMax(void);
uint32_t SysTick__u32GetCountOv(void);


__inline volatile void SysTick__vDelayUs(float fTimeUs);

#endif /* DRIVER_TIMERA_H_ */
