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

SysTick_nStatus SysTick__enInitUs(uint16_t u16TimeUs);
__inline void SysTick__vRestart(void);
__inline uint32_t SysTick__u32GetTimeUs(void);
__inline float SysTick__fGetFrec(void);
__inline uint32_t SysTick__u32GetCount(void);
__inline uint32_t SysTick__u32GetCountMax(void);
__inline uint16_t SysTick__u16GetCountOv(void);


__inline volatile void SysTick__vDelayUs(uint32_t u32TimeUs);

#endif /* DRIVER_TIMERA_H_ */
