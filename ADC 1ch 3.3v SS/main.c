

#include <msp430g2553.h>
#include "clock.h"
#include "interrupts.h"

/**
 * main.c
 */
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock_vInit();

    /*
     * condfuracion del LED P1.6 del launchpad para indicar el valor del ejemplo
     */

    P1DIR|=BIT6;
    P1OUT&=~BIT6;
    P1SEL&=~BIT6;
    P1SEL2&=~BIT6;
    P1REN&=~BIT6;

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
     * SREF = 000 ;VR+ = VCC (3.3V) and VR- = VSS (0V)
     * ADC10SHT      (tsample= (Rs + Ri)*ln(2^11)*Ci), (tsample =(Rs + 2K)* 7.625* 27pF)m tsample = (205.875p*Rs) +0.41175u
     * in este ejemplo la resistencia de entrada sera de 1KOhm por tanto  tsample = (205.875p*1000) +0.41175u = 2.05875e-7 +0.41175u=6.17625e-7
     * ADC10SHT= 2 ; 16 × ADC10CLKs = 16* 1/6.3MHz =2.54e-6
     * ADC10SR = 0 ; ~200KHz = (13*ADC10DIV*(1/fADC10CLK))+6.349e-7  = (13*1*(1.58e-7)) +6.349e-7 =2.06e-6 +2.54e-6=4.60e-6 =217.4KHz
     * REFOUT =0 ; ref no es utilizado en este ejemplo
     * REFBURST=0; si ref es utilizado , este bit indica si el buffer se va adormir o siempre se mantiene activo se agregan 2us al sample time
     * MSC=0    ; utilizado en muestras consecutivas , en este caso no es utilizado
     * REF2_5V=0; no utilizado, idnica si la referencia interna es 2.5v o 3.3v, si referencia interna es utilizada se agregan 30us de retraso
     * REFON=0; referencia interna no utilizada
     * ADC10ON=1; se activa el ADC10
     * ADC10IE=1; activamos la interrupccion de fin de conversion
     * ADC10IFG=0; borramos una interrupcion indeseada
     *
     */

    ADC10CTL0|=ADC10SHT_2|ADC10ON|ADC10IE;



    /*
     * Para iniciar el ADC debe estar ENC de ADC10CTL0 en 011
     */
    ADC10CTL0|=ENC;

    _EINT();
    while(1)
    {
        if(u16flagADC==0)
        {
            u16flagADC=1;
            ADC10CTL0|=ADC10SC;

        }
        if(u16ValorADC>500)
            P1OUT|=BIT6;
        else
            P1OUT&=~BIT6;

    }
}


