

#include <msp430g2553.h>
#include "clock.h"
#include <Driver/TimerA1.h>
#include <Driver/TimerA0.h>
#include <Driver/ADC.h>


/**
 * main.c
 */
#define COUNTBUFFER (128u)

uint32_t u32Porcentage=0;
uint16_t u16ValorADC[2];
uint16_t u16BufferSignal[COUNTBUFFER];
uint8_t u8Count=0;


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock__vInit();
    P1DIR|=BIT3;
    P1OUT&=~BIT3;
    P1REN&=~BIT3;
    P1SEL&=~BIT3;
    P1SEL2&=~BIT3;

    P2DIR=0xFF;
    P2OUT=0xAA;
    P2REN=0;
    P2SEL=0;
    P2SEL2=0;

    SysTick__enInitUs((uint16_t)1000);
    TIMERA0__enInitUs((float)50);
    TIMERA0__vInitCompareCCR1(TIMERA0_enSET_RESET,TIMERA0_enCCIxA);
    TIMERA0__enPorcentCompareCCR1((uint8_t)50);

    ADC__vInit(u16ValorADC);

    _EINT();
    while(1)
    {
        if(ADC__enGetStatus()==ADC_enREADY)
        {
            ADC__vSetBusy();
            u16BufferSignal[u8Count&0x7F]=u16ValorADC[0];
            P2OUT=u16ValorADC[0]>>3;
        }
    }
}



