/*
 * ADC.c
 *
 *  Created on: 04/10/2019
 *      Author: Lalo
 */


#include <Driver/ADC.h>


uint16_t* ADC_pu16ValorADC;
ADC_nStatus ADC_enFlagADC=ADC_enBUSY;

void ADC__vInit(uint16_t* pu16Data)
{

    /*
     * PIN configuration PSEL =x PDIR=x ADC10AE0=BIT
     */
    ADC10AE0=BIT1|BIT0;

    /*
     * Para iniciar la configuración del ADC debe estar ENC de ADC10CTL0 en 0
     */
    ADC10CTL0&=~ENC;

    //  DTC data transfer  no es utilizado en este ejemplo (ADC10DTC0, ADC10DTC1, ADC10SA)

    /*
     *INCHx = 0001 = BIT1 A1 P1.1 a P1.0
     *SHSx  = 10 = inciio de conversion por medio de TIMERA0 CCR0
     *ADC10DF= 0 = utiizacion del rango completo de 10bits 0- 1023
     *ISSH= 0 =no utilizado
     *ADC10DIVx= 0 = el reloj a utilizar es el ADC0SC , el valor ideal para el ADC 6.3MHz, por eso no requiere divisor
     *ADC10SSELx= 0 =ADC10OSC
     *CONSEQx= 3; este ejemplo va a ser secuencia de canales continamente
     */
    ADC10CTL1=INCH_1|SHS_1|CONSEQ_2; //reinicio todos los parametros del registro ADC10CTL1


    /*
       *ADC10TB = 0 = Tranferencia de un bloque
       *ADC10CT  = 1 = Modo continuo
       */
    ADC10DTC0=ADC10CT;

    /*
      Transferencia por bloque, 2 tranferencias
       */
    ADC10DTC1=1;

    /*
      Asignacion al puntero donde se guardaran los datos
       */
    ADC_pu16ValorADC=pu16Data;
    ADC10SA=(uint32_t)ADC_pu16ValorADC;


    /*
     * SREF = 001 ;VR+ = REF (2.5V) and VR- = VSS (0V)
     * ADC10SHT      (tsample= (Rs + Ri)*ln(2^11)*Ci), (tsample =(Rs + 2K)* 7.625* 27pF)m tsample = (205.875p*Rs) +0.41175u
     * in este ejemplo la resistencia de entrada sera de 1KOhm por tanto  tsample = (205.875p*1000) +0.41175u = 2.05875e-7 +0.41175u=6.17625e-7
     * ADC10SHT= 2 ; 16 × ADC10CLKs = 16* 1/6.3MHz =2.54e-6
     * ADC10SR = 0 ; ~200KHz = (13*ADC10DIV*(1/fADC10CLK))+6.349e-7  = (13*1*(1.58e-7)) +6.349e-7 =2.06e-6 +2.54e-6=4.60e-6 =217.4KHz
     * REFOUT =0 ; ref no es utilizado en este ejemplo
     * REFBURST=0; Reference buffer on continuously
     * MSC=0    ; utilizado en muestras consecutivas , en este caso no es utilizado
     * REF2_5V=0; la referencia interna es 1.5v
     * REFON=1; referencia interna utilizada
     * ADC10ON=1; se activa el ADC10
     * ADC10IE=1; activamos la interrupccion de fin de conversion
     * ADC10IFG=0; borramos una interrupcion indeseada
     *
     */

    ADC10CTL0|=SREF_1|ADC10SHT_2|REFON|ADC10ON|ADC10IE;



    /*
     * Para iniciar el ADC debe estar ENC de ADC10CTL0 en 011
     */
    ADC10CTL0|=ENC;
}

__inline ADC_nStatus ADC__enGetStatus(void)
{
    return ADC_enFlagADC;
}

__inline void ADC__vSetStatus(ADC_nStatus enStatus)
{
    ADC_enFlagADC=enStatus;
}

__inline void ADC__vSetBusy(void)
{
    ADC_enFlagADC=ADC_enBUSY;
}

__inline void ADC__vSetReady(void)
{
    ADC_enFlagADC=ADC_enREADY;
}


#pragma vector=ADC10_VECTOR;
__interrupt void ADC_vIsr(void)
{
    ADC_enFlagADC=ADC_enREADY;
}
