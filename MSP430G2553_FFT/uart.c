/*
 * uart.c
 *
 *  Created on: 20/03/2019
 *      Author: InDev
 */


#include "uart.h"


/***
 * Inicializacion del Periferico UART,
 * Se tiene contemplado el reloj del micro a 16MHz
 *
 ***/
void Uart_vInit(int32_t s32BaudRate)
{
    /* declaración de registro, pensado para realizar las operaciones directamente en un registro,
    * al final guardamos en una direccion de memoria (registro de periferico)
    **/
    register uint8_t u8Reg=0; // register es no recomendado, pero en esta implementacion sencilla se puede usar
    float fBaudRateDecimal=0;
    float fModulator=0;
    uint16_t u16BaudRateReg=0;
    uint8_t u8ModulatorCounter0;


    /*
     * Primer paso configuracion de los puertos
     * conforme la tabla 16 de la hoja de datos Pag: 43
     * P1.1 RX DIR=X, SEL=1, SEL2=1,       Microcontrolador RX--> TX otro dispositivo
     * P1.2 TX DIR=X, SEL=1, SEL2=1,       Microcontrolador TX--> RX otro dispositivo
     */
        P1SEL |=BIT1|BIT2;
        P1SEL2|=BIT1|BIT2;


    /*
     *La configuracion del Periferico sera la mas sencilla posible,
     *el manejo de direccion e interrupciones serán en otro video
     *sin paridad, 1 bit de stop y 8 bits de datos.
     *---------      -------------------- --------
     * N bits |  1   |     8  bits       | 1 bit
     *         ----- --------------------
     * IDLE    START         DATOS          STOP
     *10 bits (1 bit start Low, 8 bits DATa, 1 bit stop high)
     */

    /* registro encontrados en la guia  de usuario  capitulo 15.4, pag 428-434
    condicion inical de configuracion, poner en reset UART
     */
    UCA0CTL1=UCSWRST; //RESET



    /*
     * calculo del error en el transmisor y recepcion  para
     * USART Modulation Control Register (U0MCTL)
     * USART Baud Rate Control Register 0 (U0BR0)
     * USART Baud Rate Control Register 1 (U0BR1)
     * Suponiendo un reoj de 16MHz
     */
    fBaudRateDecimal= 16000000.0/(float)s32BaudRate; //se obtiene la divison necesaria para obtener el baud rate deseado

    /*
     * NOTA: esta aproximación no es la optima , para obtener el menor error
     * se debe de encontrar la minimizacion del error conforme las formulas del
     * manual de usuario pag 422
     */
    u16BaudRateReg= (uint16_t)fBaudRateDecimal; // se obtiene la parete entera de la divison
    if(u16BaudRateReg>32)
    {
        fBaudRateDecimal/=16;
        u16BaudRateReg= (uint16_t)fBaudRateDecimal;
        fBaudRateDecimal= fBaudRateDecimal- (float)u16BaudRateReg; //se obtiene la parte decimal de la division

        *((uint16_t*)&UCA0BR0) =u16BaudRateReg; //se le asigna la parte entera al registro encargado del Baud Rate
        fModulator=(fBaudRateDecimal*16.0)+0.5; // se codifica la parte fraccionaria de la division
        u8ModulatorCounter0=(uint8_t)fModulator;
        u8ModulatorCounter0&=0xF;
        u8ModulatorCounter0<<=4;

        UCA0MCTL=u8ModulatorCounter0|UCOS16; // se ingresa el valor obtenido
    }
    else
    {

        fBaudRateDecimal= fBaudRateDecimal- (float)u16BaudRateReg; //se obtiene la parte decimal de la division
        *((uint16_t*)&UCA0BR0) =u16BaudRateReg; //se le asigna la parte entera al registro encargado del Baud Rate
        fModulator=(fBaudRateDecimal*8.0)+0.5; // se codifica la parte fraccionaria de la division
        u8ModulatorCounter0=(uint8_t)fModulator;
        UCA0MCTL=u8ModulatorCounter0<<1; // se ingresa el valor obtenido
    }







    /*Confguracion de las interrupciones del UARt, no se verá hasta en proximos videos
     * UCA0RXIE =0 (deshabilitadas interrupcion de recepcion)
     * UCA0TXIE=0(deshabilitadas interrupcion de trnasmision)
     */
    /* Configuración final para Uart0 Control (UC0CTL0)
     * UCMODE=00 (UART), UCSYNC=0 (UART mode,Asincorno), UCMSB=1 (Bit mas significativo primero)
     * UC7BIT=0 (8 bits de datos) UCSPB=0 (1 bit de Stop) UCPAR=0 (paridad no importa) UCPEN=1 (paridad deshabilitada)
     */
    u8Reg=0;
    UCA0CTL0=u8Reg;

    UCA0STAT=0;

    /* Configuración final para Uart0 Control (UC0CTL1)
     *UCRXEIE=0 (bandera interna, indica si ha ocurrido un error de recepcion, no importa)
     *UCBRKIE=0 (si se reibe un break no pone la bandera)
     *UCDORM=0  (cualquier dato recibido pone la bandera de interrupcion)
     *UCTXADDR=0   (indica si el sig dato es direcicon o dato, se idnicara en posteriores videos)
     *UCTXBRK=0     ( siguiente dato a trnamitir es un Break, se usara en proximos videos)
     *UCSSELx=10 or 11 (utilizaremos el MCLK para su funcionamiento
     */
    u8Reg=UCSSEL_2;
    UCA0CTL1=u8Reg;

    IFG2=0;
   // IE2=UCA0TXIE|UCA0RXIE;
   // IFG2=UCA0TXIFG; //borrado de banderas de interrupcion

    //hasta este momento el modulo de UART esta e funcionamiento

}


//uint8_t Uart_u8SendCharUntilComplete(char cDato)
uint8_t Uart_u8SendCharUntilLoad(char cDato)
{
    uint32_t u32TimeOut=0xFFFFFFFF;

    while(UCA0STAT & UCBUSY);

    UCA0TXBUF= cDato;
#if 0
    /*Buffer Full*/
    while(Uart_s8TxCounter==(UART_TXMAX))
    {
        u32TimeOut--;
        if(u32TimeOut==0x7FFFFFFF)
        {
            IFG2|=UCA0TXIFG;
        }
        if(u32TimeOut==0)
            return 1;
    }
    /*
     * si el buffer de salida o transmision no esta vacio regresa un error

    if((IFG2&UCA0TXIFG)==0)
        return 1;
     */

    *Uart_pu8PutTx = cDato;
    Uart_pu8PutTx++;
    if(Uart_pu8PutTx==&Uart_u8TxBuffer[UART_TXMAX])
        Uart_pu8PutTx=Uart_u8TxBuffer;

    Uart_s8TxCounter++;
    if(Uart_s8TxInit==0)
    {
        Uart_s8TxInit=1;
        IFG2|=UCA0TXIFG;
    }


#endif
    //UCA0TXBUF=cDato;
    return 0;

}






uint16_t Uart_u16SendString(char* pcDato)
{
    uint16_t u16Contador=0;
    while(*pcDato)
    {

        if(Uart_u8SendCharUntilLoad(*pcDato))
            return u16Contador;
        pcDato++;
        u16Contador++;
    }
    return u16Contador;
}

