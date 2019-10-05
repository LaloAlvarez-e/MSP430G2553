

#include <msp430g2553.h>
#include "clock.h"
//#include <Driver/TimerA1.h>
#include <Driver/TimerA0.h>
#include <Driver/ADC.h>


/**
 * main.c
 */
#define COUNTBUFFER (128u)

//filter BandPass 0.03 0.09 0.140.2 % fs=1KHz corte c=60Hz
#define BL  (40u)
const int16_t s16CoefFilter[BL+1]={
      -32,   -105,   -238,   -415,   -592,   -704,   -681,   -468,    -49,
      540,   1204,   1806,   2193,   2237,   1869,   1102,     46,  -1118,
    -2171,  -2902,  29604,  -2902,  -2171,  -1118,     46,   1102,   1869,
     2237,   2193,   1806,   1204,    540,    -49,   -468,   -681,   -704,
     -592,   -415,   -238,   -105,    -32
};


int16_t s16WindowFilter[BL+1]={0};
int16_t s16OutputBuffer[BL+1]={0};

//tracker DC IIR
#define NL  (1u)
const int32_t s16CoefFilterNUM[NL+1] = {
    32767, -32768
};
#define DL (1u) //change sign
const int32_t s16CoefFilterDEN[DL+1] = {
    32767, 32309
};

int16_t s16YWindowFilterIIR[DL+1]={0};
int16_t s16XWindowFilterIIR[NL+2]={0};

int16_t s16iCycle=0;
int32_t s32MultiplierCurrent=0,s32MultiplierPrevious=0,s32MultiplierOutput=0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock__vInit();

    /*Config P1.3 Output, Used to measure the Process Time*/
    P1DIR|=BIT3;
    P1OUT&=~BIT3;
    P1REN&=~BIT3;
    P1SEL&=~BIT3;
    P1SEL2&=~BIT3;

    P2DIR=0xFF; //DAC R2R
    P2OUT=0xAA;
    P2REN=0;
    P2SEL=0;
    P2SEL2=0;

    TIMERA0__enInitUs((float)1250); //fs=800hz, ideal must be 1Kz = 1000us
    TIMERA0__vInitCompareCCR1(TIMERA0_enSET_RESET,TIMERA0_enCCIxA);
    TIMERA0__enPorcentCompareCCR1((uint8_t)50);

    ADC__vInit((uint16_t*)&s16XWindowFilterIIR[2]);

    _EINT();
    while(1)
    {
        if(ADC__enGetStatus()==ADC_enREADY)
        {
            P1OUT|=BIT3;
            ADC__vSetBusy();
            /*IIR Filter Begins*/
            /*DC Tracker, High Pass Filter*/
            /*16 bit signed Multiplier*/
            s16XWindowFilterIIR[1]=s16XWindowFilterIIR[2];

            s32MultiplierCurrent=(int32_t)s16XWindowFilterIIR[1];/*The new input*/
            s32MultiplierCurrent*=(int32_t)s16CoefFilterNUM[0];/* the first coef in the NUM*/

            s32MultiplierPrevious=(int32_t)s16XWindowFilterIIR[0];/*The previous input*/
            s32MultiplierPrevious*=(int32_t)s16CoefFilterNUM[1];/* the second coef in the NUM*/
            s32MultiplierCurrent+=s32MultiplierPrevious; //MAC

            /* The last output is multipy for the second coef in DEN and added to the previus operation*/
            s32MultiplierOutput=(int32_t)s16WindowFilter[BL];
            s32MultiplierOutput*=(int32_t)s16CoefFilterDEN[1];
            s32MultiplierCurrent+=s32MultiplierOutput; //MAC

            /* s32MultiplierCurrent have the new output*/
            /*replace the previous input with the new input*/
            s16XWindowFilterIIR[0]=s16XWindowFilterIIR[1];

            /*FIR Filter Begins*/
            /*Save the new input in the array*/
            /*max value -335, 334*/
            s16WindowFilter[BL]=*((int16_t*)&s32MultiplierCurrent+1);
            /*Do the Signed MAC operation */
            s32MultiplierCurrent=(int32_t)s16CoefFilter[0];
            s32MultiplierCurrent*=(int32_t)s16WindowFilter[BL];
            for( s16iCycle=BL-1;s16iCycle>=0;s16iCycle--)
            {
                s32MultiplierOutput=(int32_t)s16CoefFilter[BL-s16iCycle];/*The new input*/
                s32MultiplierOutput*=(int32_t)s16WindowFilter[s16iCycle];/* the first coef in the NUM*/
                s32MultiplierCurrent+=s32MultiplierOutput;
            }

            /* the Output is signed */
            s32MultiplierOutput=(int32_t)*((int16_t*)&s32MultiplierCurrent+1);
            s16OutputBuffer[BL]=s32MultiplierOutput;
            s32MultiplierOutput>>=1;
            s32MultiplierOutput+=0x7f;
            P2OUT=(uint16_t)s32MultiplierOutput;

            /* Initialize the bubble cycle*/
            for( s16iCycle=0;s16iCycle<(BL);s16iCycle++)
            {
                s16WindowFilter[s16iCycle]=s16WindowFilter[s16iCycle+1];
                s16OutputBuffer[s16iCycle]=s16OutputBuffer[s16iCycle+1];
            }
            P1OUT&=~BIT3;
        }
    }
}



