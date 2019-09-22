/*
 * TimerA.c
 *
 *  Created on: 21/09/2019
 *      Author: Lalo
 */

#include "TimerA.h"

uint32_t SysTick_u32CountOv=0;
uint32_t SysTick_u32Count=0;
float SysTick_fUsTick=0;
float SysTick_fFrecTick=0;
uint16_t SysTick_u16CountTick=0;


SysTick_nStatus SysTick__enInitUs(float fTimeUs)
{
    uint32_t u32CPUFrec=0;
    uint32_t u32Count=0;
    float fCPUFrec=0,fCount=0;

    u32CPUFrec=16000000u;//PLL__u32GetSysClockFreq();
    fCPUFrec=(float)u32CPUFrec;
    fCPUFrec/=1000000;
    fCount=fCPUFrec*fTimeUs;
    u32Count=(uint32_t)fCount;
    u32Count>>=3;
    if(u32Count>0x10000)
    {
        SysTick_fFrecTick=0;
        SysTick_fUsTick=0;
        return SysTick_enERROR;
    }
    if(u32Count<100)
    {
        SysTick_fFrecTick=0;
        SysTick_fUsTick=0;
        return SysTick_enERROR;
    }


    SysTick_u32Count=0;

    SysTick_fFrecTick=1000000.0;
    SysTick_fFrecTick/=fTimeUs;
    SysTick_fUsTick=fTimeUs;
    SysTick_u16CountTick=u32Count;





    TA1CTL =0;
    TA1CCR0=u32Count-1;
    TA1R=0;
    /*
     * TASSEL = SMCLK
     * ID = /8
     * MC = Up yo TA1CCR0
     * TAIE = enabled
     *
     */
    TA1CTL=TASSEL_2| ID_3 |MC_1 |TAIE ;

    return SysTick_enOK;
}

void SysTick__vRestart(void)
{
    SysTick_u32Count=0;
}


float SysTick__fGetTimeUs(void)
{
    return (float)SysTick_u32Count*SysTick_fUsTick;
}

float SysTick__fGetFrec(void)
{
    return SysTick_fFrecTick/(float)SysTick_u32Count;
}


uint64_t SysTick__u64GetCount(void)
{
    return (uint64_t)SysTick_u16CountTick*(uint64_t)SysTick_u32Count;
}
uint32_t SysTick__u32GetCountOv(void)
{
    return (uint32_t)SysTick_u32CountOv;
}
uint32_t SysTick__u32GetCountMax(void)
{
    return (uint32_t)SysTick_u16CountTick*(uint32_t)0xFFFF;
}


__inline volatile void SysTick__vDelayUs(float fTimeUs)
{
    uint64_t u64Count=0;
    uint64_t u64Dif=0;
    uint64_t u64DifOv=0;

    uint32_t u32Max=SysTick__u32GetCountMax();
    float fCount= fTimeUs/SysTick_fUsTick;
    fCount*= (float)SysTick_u16CountTick;
    u64Count= (uint64_t)fCount;


    uint64_t u64ActualUs=0;
    uint64_t u64TempUs=0;
    uint32_t u32TempOv=0;

    uint64_t u64AnteriorUs=SysTick__u64GetCount();
    uint64_t u64AnteriorOv=SysTick__u32GetCountOv();
    while((uint64_t)u64Count>(uint64_t)u64ActualUs)
    {
        u32TempOv=SysTick__u32GetCountOv();
        u64DifOv=u32TempOv-u64AnteriorOv;
        u64AnteriorOv=u32TempOv;

        u64TempUs=SysTick__u64GetCount();
        u64Dif=(u64TempUs-u64AnteriorUs);

        if(u64DifOv>0){
            u64DifOv*=u32Max;
            u64Dif+=u64DifOv;

        }
        u64AnteriorUs=u64TempUs;
        u64ActualUs+=u64Dif;
    }
}


#pragma vector = TIMER1_A1_VECTOR;
__interrupt void Systick_ISR(void)
{
    switch(TA1IV)
    {
    case TA1IV_TAIFG:
        SysTick_u32Count++;
        if(SysTick_u32Count==0)
            SysTick_u32CountOv++;
       break;
    default:
        while(1);
    }

}



