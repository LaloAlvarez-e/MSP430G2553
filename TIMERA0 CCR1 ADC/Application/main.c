

#include <msp430g2553.h>
#include "clock.h"
#include "Interrupts.h"
#include <Driver/TimerA1.h>
#include <Driver/TimerA0.h>

void ADC_vInit(void);
/**
 * main.c
 */
int main(void)
{
    uint16_t u16Sum=0;
    uint16_t u16Count=0;
    uint32_t u32Porcentage=0;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock__vInit();

    SysTick__enInitUs((uint16_t)1000);
    TIMERA0__enInitUs((float)10000);
    TIMERA0__vInitCompareCCR1(TIMERA0_enSET_RESET,TIMERA0_enCCIxA);
    TIMERA0__enPorcentCompareCCR1(u32Porcentage);

    ADC_vInit();

    _EINT();
    while(1)
    {
        if(u16flagADC==0)
        {
            u16flagADC=1;
            u16Count++;
            if(u16Count>60)
            {
                u16Count=0;
                u32Porcentage=(uint32_t)(u16Sum)*(uint32_t)100;
                u32Porcentage/=(uint32_t)1023;
                u32Porcentage/=(uint32_t)60;
                TIMERA0__enPorcentCompareCCR1((uint8_t)u32Porcentage);
                u16Sum=0;

            }
            else
            {
                u16Sum+=u16ValorADC;
            }

            ADC10CTL0|=ADC10SC;
        }


    }
}


void ADC_vInit(void)
{

    /*
     * PIN configuration PSEL =x PDIR=x ADC10AE0=BIT
     */
    ADC10AE0=BIT1;

    /*
     * Para iniciar la configuración del ADC debe estar ENC de ADC10CTL0 en 0
     */
    ADC10CTL0&=~ENC;

    //  DTC data transfer  no es utilizado en este ejemplo (ADC10DTC0, ADC10DTC1, ADC10SA)

    /*
     *INCHx = 0001 = BIT1 A1 P1.1
     *SHSx  = 00 = inciio de conversion por medio de software ADC10SC bit
     *ADC10DF= 0 = utiizacion del rango completo de 10bits 0- 1023
     *ISSH= 0 =no utilizado
     *ADC10DIVx= 0 = el reloj a utilizar es el ADC0SC , el valor ideal para el ADC 6.3MHz, por eso no requiere divisor
     *ADC10SSELx= 0 =ADC10OSC
     *CONSEQx= 0; este ejemplo va a ser single channel single conversion
     */
    ADC10CTL1=INCH_1; //reinicio todos los parametros del registro ADC10CTL1







    ADC10CTL0=0;  //reinicio todos los parametros del registro ADC10CTL0

    /*
     * SREF = 000 ;VR+ = REF (2.5V) and VR- = VSS (0V)
     * ADC10SHT      (tsample= (Rs + Ri)*ln(2^11)*Ci), (tsample =(Rs + 2K)* 7.625* 27pF)m tsample = (205.875p*Rs) +0.41175u
     * in este ejemplo la resistencia de entrada sera de 1KOhm por tanto  tsample = (205.875p*1000) +0.41175u = 2.05875e-7 +0.41175u=6.17625e-7
     * ADC10SHT= 3 ; 64 × ADC10CLKs = 16* 1/6.3MHz =2.54e-6
     * ADC10SR = 0 ; ~200KHz = (13*ADC10DIV*(1/fADC10CLK))+6.349e-7  = (13*1*(1.58e-7)) +6.349e-7 =2.06e-6 +2.54e-6=4.60e-6 =217.4KHz
     * REFOUT =0 ; ref no es utilizado en este ejemplo
     * REFBURST=1; si ref es utilizado , este bit indica si el buffer se va adormir o siempre se mantiene activo se agregan 2us al sample time
     * MSC=0    ; utilizado en muestras consecutivas , en este caso no es utilizado
     * REF2_5V=1; la referencia interna es 2.5v o 3.3v, si referencia interna es utilizada se agregan 30us de retraso
     * REFON=1; referencia interna no utilizada
     * ADC10ON=1; se activa el ADC10
     * ADC10IE=1; activamos la interrupccion de fin de conversion
     * ADC10IFG=0; borramos una interrupcion indeseada
     *
     */

    ADC10CTL0|=SREF_1|REFBURST|REF2_5V|REFON| ADC10SHT_3|ADC10ON|ADC10IE;



    /*
     * Para iniciar el ADC debe estar ENC de ADC10CTL0 en 011
     */
    ADC10CTL0|=ENC;
}

