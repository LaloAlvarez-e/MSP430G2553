/*
 * TimerA.c
 *
 *  Created on: 21/09/2019
 *      Author: Lalo
 */

#include <Driver/TimerA1.h>

uint16_t SysTick_u16CountOv=0;
uint16_t SysTick_u16Count=0;
uint16_t SysTick_u16UsTick=0;
uint32_t SysTick_u32FrecTick=0;
uint16_t SysTick_u16CountTick=0;


SysTick_nStatus SysTick__enInitUs(uint16_t u16TimeUs)
{
    uint8_t u8Div=0;
    uint32_t u32Count=(uint32_t)((uint32_t)16*(uint32_t)u16TimeUs);//PLL__u32GetSysClockFreq();


    while (u32Count>0x10000)
    {
        if(u8Div>3)
        {
            SysTick_u32FrecTick=0;
            SysTick_u16UsTick=0;
            return SysTick_enERROR;
        }

        u8Div++;
        u32Count>>=1;
    }

    if(u32Count<(64>>u8Div))
    {
        SysTick_u32FrecTick=0;
        SysTick_u16UsTick=0;
        return SysTick_enERROR;
    }

    SysTick_u16Count=0;

    SysTick_u32FrecTick=(1000000/u16TimeUs);
    SysTick_u16UsTick=u16TimeUs;
    SysTick_u16CountTick=u32Count;





    TA1CTL =0;
    TA1CCR0=u32Count-1;
    TA1R=0;
    /*
     * TASSEL = SMCLK
     * ID = u8Div
     * MC = Up yo TA1CCR0
     * TAIE = enabled
     *
     */
    TA1CTL=TASSEL_2| (u8Div<<6) |MC_1 |TAIE ;

    return SysTick_enOK;
}

__inline void SysTick__vRestart(void)
{
    SysTick_u16Count=0;
}


__inline uint32_t SysTick__u32GetTimeUs(void)
{
    return (uint32_t)SysTick_u16Count*SysTick_u16UsTick;
}

__inline float SysTick__fGetFrec(void)
{
    return SysTick_u32FrecTick/(float)SysTick_u16Count;
}


__inline uint32_t SysTick__u32GetCount(void)
{
    return (uint32_t)SysTick_u16CountTick*SysTick_u16Count;
}
__inline uint16_t SysTick__u16GetCountOv(void)
{
    return (uint16_t)SysTick_u16CountOv;
}
__inline uint32_t SysTick__u32GetCountMax(void)
{
    return (uint32_t)SysTick_u16CountTick*0xFFFF;
}

__inline volatile void SysTick__vDelayUs(uint32_t u32TimeUs)
{
    uint64_t u64Dif=0;
    uint64_t u64DifOv=0;

    uint32_t u32Max=SysTick__u32GetCountMax();
    uint64_t u64Count= (uint64_t)((uint64_t)u32TimeUs*(uint64_t)SysTick_u16CountTick);

    u64Count/=(uint64_t)SysTick_u16UsTick;


    uint64_t u64ActualUs=0;
    uint32_t u32TempUs=0;
    uint16_t u16TempOv=0;

    uint32_t u32AnteriorUs=SysTick__u32GetCount();
    uint16_t u16AnteriorOv=SysTick__u16GetCountOv();
    while((uint64_t)u64Count>(uint64_t)u64ActualUs)
    {
        u16TempOv=SysTick__u16GetCountOv();
        u64DifOv=u16TempOv-u16AnteriorOv;
        u16AnteriorOv=u16TempOv;

        u32TempUs=SysTick__u32GetCount();
        u64Dif=(u32TempUs-u32AnteriorUs);

        if(u64DifOv>0){
            u64DifOv*=u32Max;
            u64Dif+=u64DifOv;

        }
        u32AnteriorUs=u32TempUs;
        u64ActualUs+=u64Dif;
    }
}


#pragma vector = TIMER1_A1_VECTOR;
__interrupt void Systick_ISR(void)
{
    switch(TA1IV)
    {
    case TA1IV_TAIFG:
        SysTick_u16Count++;
        if(SysTick_u16Count==0)
            SysTick_u16CountOv++;
       break;
    default:
        while(1);
    }

}



