#include <msp430.h> 

#include "clock.h"
#include "uart.h"
#include "TimerA0.h"

void ADC__vInit(void);
unsigned char Conv_Entero(long long numero, char* conv);

#define FFT_POINTS (16U)
#define FFT_RE1 (7071)
#define FFT_IM1 (7071)
#define FFT_RE2 (9239)
#define FFT_IM2 (3827)
#define FFT_RE3 (-3827)
#define FFT_IM3 (-9239)

unsigned short pu16SignalValues[FFT_POINTS * 2];
unsigned short pu16CurrentSignalValues[FFT_POINTS];
unsigned short u16InitFFTCalculation = 0U;
long ps32FFT_i[FFT_POINTS];
long ps32FFT_M[FFT_POINTS];
long ps32FFT_I[FFT_POINTS];
long ps32FFT_X[FFT_POINTS];
char pcString[10];
long s32BiggerData;

/**
 * main.c
 */
int main(void)
{
    long i=0, j=0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	Clock_vInit();
    _EINT();

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
    P1SEL &= ~BIT0;
    P1SEL2 &= ~BIT0;
    P1REN &= ~BIT0;

    TIMERA0__enInitUs(32000.0f);
    TIMERA0__enPorcentCompareCCR1(50);
    TIMERA0__vInitCompareCCR1(TIMERA0_enTOGGLE_RESET, TIMERA0_enCCIxB);
	Uart_vInit(9600);
	Uart_u16SendString("FFT test:\n\r");
    Uart_u16SendString("UART Init OK : 9600 Baudios\n\r");
    Uart_u16SendString("Muestreo Init OK - Period 33 ms, Frec - 31.25 hz \n\r");
    ADC__vInit();

	while(1U)
	{
	    if(0U != u16InitFFTCalculation)
	    {
	        u16InitFFTCalculation = 0U;


            ps32FFT_X[0] = pu16CurrentSignalValues[0] + pu16CurrentSignalValues[4];
            ps32FFT_X[1] = pu16CurrentSignalValues[2] + pu16CurrentSignalValues[6];
            ps32FFT_X[2] = pu16CurrentSignalValues[8] + pu16CurrentSignalValues[12];
            ps32FFT_X[3] = pu16CurrentSignalValues[10] + pu16CurrentSignalValues[14];
            ps32FFT_X[4] = pu16CurrentSignalValues[0 + 1] + pu16CurrentSignalValues[4 + 1];
            ps32FFT_X[5] = pu16CurrentSignalValues[2 + 1] + pu16CurrentSignalValues[6 + 1];
            ps32FFT_X[6] = pu16CurrentSignalValues[8 + 1] + pu16CurrentSignalValues[12 + 1];
            ps32FFT_X[7] = pu16CurrentSignalValues[10 + 1] + pu16CurrentSignalValues[14 +1];
            ps32FFT_X[8] = pu16CurrentSignalValues[0] - pu16CurrentSignalValues[4];
            ps32FFT_X[9] = pu16CurrentSignalValues[2] - pu16CurrentSignalValues[6];
            ps32FFT_X[10] = pu16CurrentSignalValues[8] - pu16CurrentSignalValues[12];
            ps32FFT_X[11] = pu16CurrentSignalValues[10] - pu16CurrentSignalValues[14];
            ps32FFT_X[12] = pu16CurrentSignalValues[0 + 1] - pu16CurrentSignalValues[4 + 1];
            ps32FFT_X[13] = pu16CurrentSignalValues[2 + 1] - pu16CurrentSignalValues[6 + 1];
            ps32FFT_X[14] = pu16CurrentSignalValues[8 + 1] - pu16CurrentSignalValues[12 + 1];
            ps32FFT_X[15] = pu16CurrentSignalValues[10 + 1] - pu16CurrentSignalValues[14 +1];

            ps32FFT_M[0] = ps32FFT_X[0] + ps32FFT_X[1];
            ps32FFT_M[1] = ps32FFT_X[2] + ps32FFT_X[3];
            ps32FFT_M[2] = ps32FFT_X[4] + ps32FFT_X[5];
            ps32FFT_M[3] = ps32FFT_X[6] + ps32FFT_X[7];
            ps32FFT_M[4] = ps32FFT_X[8];                    ps32FFT_i[0] = -ps32FFT_X[9];
            ps32FFT_M[5] = ps32FFT_X[10];                   ps32FFT_i[1] = -ps32FFT_X[11];
            ps32FFT_M[6] = ps32FFT_X[12];                   ps32FFT_i[2] = -ps32FFT_X[13];
            ps32FFT_M[7] = ps32FFT_X[14];                   ps32FFT_i[3] = -ps32FFT_X[15];
            ps32FFT_M[8] = ps32FFT_X[0] - ps32FFT_X[1];
            ps32FFT_M[9] = ps32FFT_X[2] - ps32FFT_X[3];
            ps32FFT_M[10] = ps32FFT_X[4] - ps32FFT_X[5];
            ps32FFT_M[11] = ps32FFT_X[6] - ps32FFT_X[7];
            ps32FFT_M[12] = ps32FFT_X[8];                    ps32FFT_i[4] = ps32FFT_X[9];
            ps32FFT_M[13] = ps32FFT_X[10];                   ps32FFT_i[5] = ps32FFT_X[11];
            ps32FFT_M[14] = ps32FFT_X[12];                   ps32FFT_i[6] = ps32FFT_X[13];
            ps32FFT_M[15] = ps32FFT_X[14];                   ps32FFT_i[7] = ps32FFT_X[15];

            ps32FFT_M[0] *= 10000;
            ps32FFT_M[1] *= 10000;
            ps32FFT_M[2] *= 10000;
            ps32FFT_M[3] *= 10000;
            ps32FFT_M[4] *= 10000;
            ps32FFT_M[5] *= 10000;
            ps32FFT_M[6] *= 10000;
            ps32FFT_M[7] *= 10000;
            ps32FFT_M[8] *= 10000;
            ps32FFT_M[9] *= 10000;
            ps32FFT_M[10] *= 10000;
            ps32FFT_M[11] *= 10000;
            ps32FFT_M[12] *= 10000;
            ps32FFT_M[13] *= 10000;
            ps32FFT_M[14] *= 10000;
            ps32FFT_M[15] *= 10000;

            ps32FFT_i[0] *= 10000;
            ps32FFT_i[1] *= 10000;
            ps32FFT_i[2] *= 10000;
            ps32FFT_i[3] *= 10000;
            ps32FFT_i[4] *= 10000;
            ps32FFT_i[5] *= 10000;
            ps32FFT_i[6] *= 10000;
            ps32FFT_i[7] *= 10000;

            ps32FFT_X[0] = ps32FFT_M[0] + ps32FFT_M[1];
            ps32FFT_X[1] = ps32FFT_M[2] + ps32FFT_M[3];
            ps32FFT_X[2] = ps32FFT_M[4] + (FFT_RE1 * ps32FFT_M[5]) + (FFT_IM1 * ps32FFT_i[1]);
            ps32FFT_X[3] = ps32FFT_M[6] + (FFT_RE1 * ps32FFT_M[7]) + (FFT_IM1 * ps32FFT_i[3]);
            ps32FFT_X[4] = ps32FFT_M[8];
            ps32FFT_X[5] = ps32FFT_M[10];
            ps32FFT_X[6] = ps32FFT_M[12] + (FFT_RE1 * ps32FFT_M[13]) + (FFT_IM1 * ps32FFT_i[5]);
            ps32FFT_X[7] = ps32FFT_M[14] + (FFT_RE1 * ps32FFT_M[15]) + (FFT_IM1 * ps32FFT_i[7]);
            ps32FFT_X[8] = ps32FFT_M[0] - ps32FFT_M[1];
            ps32FFT_X[9] = ps32FFT_M[2] - ps32FFT_M[3];
            ps32FFT_X[10] = ps32FFT_X[6];
            ps32FFT_X[11] = ps32FFT_X[3];
            ps32FFT_X[12] = ps32FFT_X[4];
            ps32FFT_X[13] = ps32FFT_X[5];
            ps32FFT_X[14] = ps32FFT_X[2];
            ps32FFT_X[15] = ps32FFT_X[7];

            ps32FFT_I[0] = ps32FFT_i[0] - (FFT_IM1 * ps32FFT_M[5]) + (FFT_RE1 * ps32FFT_i[1]);
            ps32FFT_I[1] = ps32FFT_i[2] - (FFT_IM1 * ps32FFT_M[7]) + (FFT_RE1 * ps32FFT_i[3]);
            ps32FFT_I[2] = -ps32FFT_M[9];
            ps32FFT_I[3] = -ps32FFT_M[11];
            ps32FFT_I[4] = ps32FFT_i[4] - (FFT_IM1 * ps32FFT_M[13]) + (FFT_RE1 * ps32FFT_i[5]);
            ps32FFT_I[5] = ps32FFT_i[6] - (FFT_IM1 * ps32FFT_M[15]) + (FFT_RE1 * ps32FFT_i[7]);
            ps32FFT_I[6] = -ps32FFT_I[4];
            ps32FFT_I[7] = -ps32FFT_I[5];
            ps32FFT_I[8] = -ps32FFT_I[2];
            ps32FFT_I[9] = -ps32FFT_I[3];
            ps32FFT_I[10] = -ps32FFT_I[0];
            ps32FFT_I[11] = -ps32FFT_I[1];

            ps32FFT_M[0] = ps32FFT_X[0] + ps32FFT_X[1];
            ps32FFT_M[1] = ps32FFT_X[2] + (FFT_RE2 * ps32FFT_X[3]) - (FFT_IM2 * ps32FFT_I[1]);
            ps32FFT_M[2] = ps32FFT_X[4] + (FFT_RE1 * ps32FFT_X[5]) + (FFT_IM1 * ps32FFT_I[3]);
            ps32FFT_M[3] = ps32FFT_X[6] + (FFT_RE3 * ps32FFT_X[7]) - (FFT_IM3 * ps32FFT_I[5]);
            ps32FFT_M[4] = ps32FFT_X[8];
            ps32FFT_M[5] = ps32FFT_X[10] - (FFT_RE3 * ps32FFT_X[11]) - (FFT_IM3 * ps32FFT_I[7]);
            ps32FFT_M[6] = ps32FFT_X[12] - (FFT_RE1 * ps32FFT_X[13]) + (FFT_IM1 * ps32FFT_I[9]);
            ps32FFT_M[7] = ps32FFT_X[14] - (FFT_RE2 * ps32FFT_X[15]) - (FFT_IM2 * ps32FFT_I[11]);
            ps32FFT_M[8] = ps32FFT_X[0] - ps32FFT_X[1];

            ps32FFT_i[0] = 0;
            ps32FFT_i[1] = ps32FFT_I[0] + (FFT_IM2 * ps32FFT_X[3]) + (FFT_RE2 * ps32FFT_I[1]);
            ps32FFT_i[2] = ps32FFT_I[2] - (FFT_IM1 * ps32FFT_X[5]) + (FFT_RE1 * ps32FFT_I[3]);
            ps32FFT_i[3] = ps32FFT_I[4] + (FFT_IM3 * ps32FFT_X[7]) + (FFT_RE3 * ps32FFT_I[5]);
            ps32FFT_i[4] = -ps32FFT_X[9];
            ps32FFT_i[5] = ps32FFT_I[6] + (FFT_IM3 * ps32FFT_X[11]) - (FFT_RE3 * ps32FFT_I[7]);
            ps32FFT_i[6] = ps32FFT_I[8] - (FFT_IM1 * ps32FFT_X[13]) - (FFT_RE1 * ps32FFT_I[9]);
            ps32FFT_i[7] = ps32FFT_I[10] + (FFT_IM2 * ps32FFT_X[15]) - (FFT_RE2 * ps32FFT_I[11]);
            ps32FFT_i[8] = 0;


            ps32FFT_M[0] /= 10000000;
            ps32FFT_M[1] /= 10000000;
            ps32FFT_M[2] /= 10000000;
            ps32FFT_M[3] /= 10000000;
            ps32FFT_M[4] /= 10000000;
            ps32FFT_M[5] /= 10000000;
            ps32FFT_M[6] /= 10000000;
            ps32FFT_M[7] /= 10000000;
            ps32FFT_M[8] /= 10000000;


            ps32FFT_i[0] /= 1000000;
            ps32FFT_i[1] /= 1000000;
            ps32FFT_i[2] /= 1000000;
            ps32FFT_i[3] /= 1000000;
            ps32FFT_i[4] /= 1000000;
            ps32FFT_i[5] /= 1000000;
            ps32FFT_i[6] /= 1000000;
            ps32FFT_i[7] /= 1000000;
            ps32FFT_i[8] /= 1000000;



            ps32FFT_M[0] *= ps32FFT_M[0];
            ps32FFT_M[1] *= ps32FFT_M[1];
            ps32FFT_M[2] *= ps32FFT_M[2];
            ps32FFT_M[3] *= ps32FFT_M[3];
            ps32FFT_M[4] *= ps32FFT_M[4];
            ps32FFT_M[5] *= ps32FFT_M[5];
            ps32FFT_M[6] *= ps32FFT_M[6];
            ps32FFT_M[7] *= ps32FFT_M[7];
            ps32FFT_M[8] *= ps32FFT_M[8];

            ps32FFT_i[0] *= ps32FFT_i[0];
            ps32FFT_i[1] *= ps32FFT_i[1];
            ps32FFT_i[2] *= ps32FFT_i[2];
            ps32FFT_i[3] *= ps32FFT_i[3];
            ps32FFT_i[4] *= ps32FFT_i[4];
            ps32FFT_i[5] *= ps32FFT_i[5];
            ps32FFT_i[6] *= ps32FFT_i[6];
            ps32FFT_i[7] *= ps32FFT_i[7];
            ps32FFT_i[8] *= ps32FFT_i[8];


            ps32FFT_X[0] = ps32FFT_M[0];
            ps32FFT_X[1] = (ps32FFT_M[1]) + (ps32FFT_i[1]);
            ps32FFT_X[2] = (ps32FFT_M[2]) + (ps32FFT_i[2]);
            ps32FFT_X[3] = (ps32FFT_M[3]) + (ps32FFT_i[3]);
            ps32FFT_X[4] = (ps32FFT_M[4]) + (ps32FFT_i[4]);
            ps32FFT_X[5] = (ps32FFT_M[5]) + (ps32FFT_i[5]);
            ps32FFT_X[6] = (ps32FFT_M[6]) + (ps32FFT_i[6]);
            ps32FFT_X[7] = (ps32FFT_M[7]) + (ps32FFT_i[7]);
            ps32FFT_X[8] = (ps32FFT_M[8]) + (ps32FFT_i[8]);

#if 0
                        ps32FFT_X[0]=( pu16CurrentSignalValues[0] + pu16CurrentSignalValues[4] + pu16CurrentSignalValues[2] + pu16CurrentSignalValues[6] + pu16CurrentSignalValues[1] + pu16CurrentSignalValues[5] + pu16CurrentSignalValues[3] + pu16CurrentSignalValues[7]) * 100;

                        ps32FFT_X[1]=( pu16CurrentSignalValues[0] - pu16CurrentSignalValues[4]) * 100 + (((707) * ( pu16CurrentSignalValues[1] - pu16CurrentSignalValues[5] - pu16CurrentSignalValues[3] + pu16CurrentSignalValues[7])) / 10);
                        ps32FFT_X[2]=(-pu16CurrentSignalValues[2] + pu16CurrentSignalValues[6]) * 100 + (((707) * (-pu16CurrentSignalValues[1] + pu16CurrentSignalValues[5] - pu16CurrentSignalValues[3] + pu16CurrentSignalValues[7])) / 10);

                        ps32FFT_X[3]=( pu16CurrentSignalValues[0] + pu16CurrentSignalValues[4] - pu16CurrentSignalValues[2] - pu16CurrentSignalValues[6]) * 100;
                        ps32FFT_X[4]=(-pu16CurrentSignalValues[1] - pu16CurrentSignalValues[5] + pu16CurrentSignalValues[3] + pu16CurrentSignalValues[7]) * 100;

                        ps32FFT_X[5]=( pu16CurrentSignalValues[0] - pu16CurrentSignalValues[4]) * 100 + (((707) * (-pu16CurrentSignalValues[1] + pu16CurrentSignalValues[5] + pu16CurrentSignalValues[3] - pu16CurrentSignalValues[7])) / 10);
                        ps32FFT_X[6]=( pu16CurrentSignalValues[2] - pu16CurrentSignalValues[6]) * 100 + (((707) * (-pu16CurrentSignalValues[1] + pu16CurrentSignalValues[5] - pu16CurrentSignalValues[3] + pu16CurrentSignalValues[7])) / 10);

                        ps32FFT_X[7]=( pu16CurrentSignalValues[0] + pu16CurrentSignalValues[4] + pu16CurrentSignalValues[2] + pu16CurrentSignalValues[6]- pu16CurrentSignalValues[1] - pu16CurrentSignalValues[5] - pu16CurrentSignalValues[3] - pu16CurrentSignalValues[7]) * 100;

                        ps32FFT_X[8]=( pu16CurrentSignalValues[0] - pu16CurrentSignalValues[4]) * 100 + (((707) * (-pu16CurrentSignalValues[1] + pu16CurrentSignalValues[5] + pu16CurrentSignalValues[3] - pu16CurrentSignalValues[7])) / 10);
                        ps32FFT_X[9]=(-pu16CurrentSignalValues[2] + pu16CurrentSignalValues[6]) * 100 + (((707) * ( pu16CurrentSignalValues[1] - pu16CurrentSignalValues[5] + pu16CurrentSignalValues[3] - pu16CurrentSignalValues[7])) / 10);

                        ps32FFT_X[10]=( pu16CurrentSignalValues[0] + pu16CurrentSignalValues[4] - pu16CurrentSignalValues[2] - pu16CurrentSignalValues[6]) * 100;
                        ps32FFT_X[11]=( pu16CurrentSignalValues[1] + pu16CurrentSignalValues[5] - pu16CurrentSignalValues[3] - pu16CurrentSignalValues[7]) * 100;

                        ps32FFT_X[12]=( pu16CurrentSignalValues[0] - pu16CurrentSignalValues[4]) * 100 + (((707) * ( pu16CurrentSignalValues[1] - pu16CurrentSignalValues[5] - pu16CurrentSignalValues[3] + pu16CurrentSignalValues[7])) / 10);
                        ps32FFT_X[13]=( pu16CurrentSignalValues[2] - pu16CurrentSignalValues[6]) * 100 + (((707) * ( pu16CurrentSignalValues[1] - pu16CurrentSignalValues[5] + pu16CurrentSignalValues[3] - pu16CurrentSignalValues[7])) / 10);

#endif
            s32BiggerData = 0;
            Uart_u16SendString("FFT calculated:\n\r");
            for(i = 0; i < 9; i++)
            {
                if(s32BiggerData < ps32FFT_X[i])
                {
                    s32BiggerData = ps32FFT_X[i];
                }
/*
                Uart_u16SendString("Coef ");
                Conv_Entero(i,pcString);
                Uart_u16SendString(pcString);
                Uart_u16SendString(" :");
                Conv_Entero(ps32FFT_X[i],pcString);
                Uart_u16SendString(pcString);
                Uart_u16SendString("\r\n");
                */
            }
            s32BiggerData /= 10;
            for(i = 0; i < 9; i++)
            {
                ps32FFT_X[i] /= s32BiggerData;
            }

            for(i = 10; i >=0; i--)
            {
                for(j = 0; j < 9; j++)
                {
                    if(ps32FFT_X[j] >= i)
                    {
                        Uart_u16SendString("*");
                    }
                    else
                    {
                        Uart_u16SendString(" ");
                    }
                }
                Uart_u16SendString("\r\n");
            }
            Uart_u16SendString("\r\n");



            P1OUT &= ~BIT0;
	    }

	}
}


void ADC__vInit(void)
{
    /*
     * PIN configuration PSEL =x PDIR=x ADC10AE0=BIT
     */
    ADC10AE0=BIT4;

    /*
     * Para iniciar la configuración del ADC debe estar ENC de ADC10CTL0 en 0
     */
    ADC10CTL0&=~ENC;

    //  DTC data transfer  no es utilizado en este ejemplo (ADC10DTC0, ADC10DTC1, ADC10SA)

    /*
     *INCHx = 0001 = BIT1 A1 P1.1 a P1.0
     *SHSx  = 01 = inciio de conversion por medio de TIMERA0 CCR1
     *ADC10DF= 0 = utiizacion del rango completo de 10bits 0- 1023
     *ISSH= 0 =no utilizado
     *ADC10DIVx= 0 = el reloj a utilizar es el ADC0SC , el valor ideal para el ADC 6.3MHz, por eso no requiere divisor
     *ADC10SSELx= 0 =ADC10OSC
     *CONSEQx= 2; este ejemplo va a ser un solo canal continamente
     */
    ADC10CTL1=INCH_4|SHS_1|CONSEQ_2; //reinicio todos los parametros del registro ADC10CTL1


    /*
       *ADC10TB = 0 = Tranferencia de 2 bloques, usando ping pong
       *ADC10CT  = 1 = Modo continuo
       */
    ADC10DTC0 = ADC10TB | ADC10CT;

    /*
      Transferencia por bloque, 16 tranferencias
       */
    ADC10DTC1=FFT_POINTS;

    /*
      Asignacion al puntero donde se guardaran los datos
       */
    ADC10SA = (unsigned short) pu16SignalValues;


    /*
     * SREF = 000 ;VR+ = VCC and VR- = VSS (0V)
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

    ADC10CTL0|=SREF_0|ADC10SHT_0|ADC10ON|ADC10IE;



    /*
     * Para iniciar el ADC debe estar ENC de ADC10CTL0 en 011
     */
    ADC10CTL0|=ENC;
}

#pragma vector=ADC10_VECTOR;
__interrupt void ADC_vIsr(void)
{
    unsigned short u16Iter = 0U;

    P1OUT |= BIT0;
    if(ADC10DTC0 & ADC10B1)
    {
        for(u16Iter = 0U; u16Iter < FFT_POINTS; u16Iter++)
        {
            pu16CurrentSignalValues[u16Iter]  = pu16SignalValues[u16Iter];
        }
    }
    else
    {
        for(u16Iter = 0U; u16Iter < FFT_POINTS; u16Iter++)
        {
            pu16CurrentSignalValues[u16Iter]  = pu16SignalValues[FFT_POINTS + u16Iter];
        }
    }
    u16InitFFTCalculation = 1U;
}

unsigned char Conv_Entero(long long numero, char* conv)
{
    char           convTemp[21]; //longitud maxima de long 12 digitos con signo
    register char *punteroActual;
    register int num=0;
    register char i=0;
    register long long  numeroReg = numero;//paso el numero a un registro para aumentar rendimiento

    punteroActual = &convTemp[21 - 1]; //empezamos llenando desde la ultima posicion
    *punteroActual = 0; //guarda el fin de cadena en la ultima posicion
    if( numeroReg < 0)
    {
        numeroReg*=-1;
    }

    do {
        punteroActual--;//se decrementa la posicion donse guardara el valor
        num=numeroReg % 10; //obtiene el digito de menor peso
        //num1=abs(num);//un if es mas rapido que una multiplicacion por -1 si es negativo el valor
        *punteroActual = num  + '0'; //convierte el valor en caracter
    }  while((numeroReg /= 10)); //mientras exista un digito sigue el ciclo

    if ( numero < 0)
    {
        punteroActual--;
        *punteroActual = '-';//si el numero es negativo guarda el signo negativo
    }

    numeroReg=convTemp+21-punteroActual;//realiza la resta de cuantos caracteres se utilizaron
    for (i = 0; i< numeroReg; i++) //hace un ciclo burbuja optimizado
    {
       ((unsigned char *)conv)[i] = ((const unsigned char *)punteroActual)[i];
    }

    return numeroReg - 1;
}
