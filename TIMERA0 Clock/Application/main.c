

#include <msp430g2553.h>
#include "clock.h"
#include "TimerA.h"

/**
 * main.c
 */
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock__vInit();

    SysTick__enInitUs((uint16_t)1000);

    P1DIR|=BIT6;
    P1OUT&=~BIT6;
    P1REN&=~BIT6;
    P1SEL&=~BIT6;
    P1SEL2&=~BIT6;

    _EINT();
    while(1)
    {

        P1OUT|=BIT6;
        SysTick__vDelayUs((uint32_t)200000);

        P1OUT&=~BIT6;
        SysTick__vDelayUs((uint32_t)50000);

    }
}


