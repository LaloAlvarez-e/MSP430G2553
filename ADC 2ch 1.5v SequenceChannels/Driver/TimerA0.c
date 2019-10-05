/*
 * TimerA.c
 *
 *  Created on: 21/09/2019
 *      Author: Lalo
 */

#include <Driver/TimerA0.h>

uint16_t TIMERA0_u16CountTick=0;


TIMERA0_nStatus TIMERA0__enInitUs(float fTimeUs)
{
    uint8_t u8Div=0;
    float fCount=(16.0*fTimeUs)+0.5;//PLL__u32GetSysClockFreq();
    uint32_t u32Count=(uint32_t)fCount;//PLL__u32GetSysClockFreq();


    while (u32Count>0xFFFF)
    {
        if(u8Div>3)
        {
            return TIMERA0_enERROR;
        }

        u8Div++;
        u32Count++;
        u32Count>>=1;
    }

    if(u32Count<(32>>u8Div))
    {
        return TIMERA0_enERROR;
    }

    TIMERA0_u16CountTick=u32Count;

    TA0CCTL0=OUTMOD_4;
    TA0CTL =0;
    TA0CCR0=u32Count-1;
    TA0R=0;
    TA0CTL=TASSEL_2| (u8Div<<6) |MC_1  ;


    return TIMERA0_enOK;
}

void TIMERA0__vEnableIntCCR1(void)
{
    TA0CCTL1 |=CCIE;
}

void TIMERA0__vDisableIntCCR1(void)
{
    TA0CCTL1 &=~CCIE;
}

void TIMERA0__vClearIntCCR1(void)
{
    TA0CCTL1 &=~CCIFG;
}

void TIMERA0__vOutputCCR1(TIMERA0_nOutputState enOut)
{
    if (enOut==TIMERA0_enHIGH)
        TA0CCTL1 |=OUT;
    else
        TA0CCTL1 &=~OUT;
}

void TIMERA0__vInitCompareCCR1(TIMERA0_nCompareType enType, TIMERA0_nOutputPin enPin)
{
    if(enPin==TIMERA0_enCCIxA)
    {
        P1DIR|=BIT2;
        P1SEL|=BIT2;
        P1SEL2&=~BIT2;
    }
    TA0CCTL1 =(enType<<5)|(enPin<<12);
}

TIMERA0_nStatus TIMERA0__enPorcentCompareCCR1(uint8_t u8Percent)
{
    uint32_t u32Total=0;
    uint32_t u32Compare=0;
    uint32_t u32Count=0;

    if(u8Percent>100)
        return TIMERA0_enERROR;

    u32Total=(uint32_t)TIMERA0_u16CountTick*(uint32_t)100;
    u32Compare=(uint32_t)TIMERA0_u16CountTick*(uint32_t)u8Percent;
    u32Count=(uint32_t)u32Total-(uint32_t)u32Compare;//PLL__u32GetSysClockFreq();
    u32Count/=(uint32_t)100;

    if(u32Count==TIMERA0_u16CountTick)
        TA0CCR1=u32Count;
    else if(u32Count==0)
        TA0CCR1=0;
    else
        TA0CCR1=u32Count-1;

    return TIMERA0_enOK;
}

#pragma vector = TIMER0_A1_VECTOR;
__interrupt void TIMERA0_ISR(void)
{
    switch(TA0IV)
    {
    case TA0IV_TACCR1:
       break;
    default:
        while(1);
    }
}



