/*
 * uart.c
 *
 *  Created on: 20/03/2019
 *      Author: InDev
 */


#include <I2C.h>


volatile uint8_t* I2C__pu8RxData=0;
int8_t  I2C__s8RxCounter=0;
int8_t  I2C__s8RxNum=0;
int8_t  I2C__s8RxInit=0;

volatile uint8_t* I2C__pu8TxData=0;
int8_t  I2C__s8TxCounter=0;
int8_t  I2C__s8TxNum=0;
int8_t  I2C__s8TxInit=0;

uint8_t I2C__u8RxTry=0;
uint8_t I2C__u8TxTry=0;
/***
 * Inicializacion del Periferico UART,
 * Se tiene contemplado el reloj del micro a 16MHz
 *
 ***/
uint16_t I2C_vInitMaster(int32_t s32Frecuency)
{
    /* declaración de registro, pensado para realizar las operaciones directamente en un registro,
    * al final guardamos en una direccion de memoria (registro de periferico)
    **/
    register uint8_t u8Reg=0; // register es no recomendado, pero en esta implementacion sencilla se puede usar
    uint16_t u16BRReg=0;



    UCB0CTL1=UCSWRST; //RESET



    /*
     * I2C Baud Rate Control Register 0 (U0BR0)
     * I2C Baud Rate Control Register 1 (U0BR1)
     * Suponiendo un reoj de 16MHz
     */
    u16BRReg= 16000000/(float)s32Frecuency; //se obtiene la divison necesaria para obtener la frecuencia deseada

    if(u16BRReg<8) //frecuencia no permitida
        return 1;

    *((uint16_t*)&UCB0BR0) =u16BRReg; //se le asigna la parte entera al registro encargado d ela frecuencia




    /* Configuración final para I2C0 Control (UC0CTL0)
     * UCMODE=11 (I2C), UCSYNC=1 (I2C mode,Sincrono), UCMST=1 (Modo maestro)
     * UCMM=0 (solo un maestro) UCSLA10=0 (direccion esclavo 7 bits) UCA10=0 (direccion propia 7 bits)
     */
    u8Reg=UCMODE_3|UCSYNC|UCMST;
    UCB0CTL0=u8Reg;

    UCB0STAT=0;
    UCB0I2COA= 0x1A; //nuestra proipia direccion, arbitrario

    /* 6543 210 Bits
     * 0100 xxx for PCF8574/PCF8574T
     * 0111 xxx    for PCF8574A
    */
    UCB0I2CSA = 0x3F; //direccion del modulo

    /*la configuracion del registro cambiara depende del la funcion requerida(UC0CTL1)
     *UCTXSTT=0 (generacion de START)
     *UCTXSTP=0  (generacion de STOP)
     *UCTXNACK=0   (generacion de NACK)
     *UCTR=1     ( en primera instancia seremos transmisores, cambiara conforme la necesidades)
     *UCSSELx=10 or 11 (utilizaremos el MCLK para su funcionamiento
     */


    u8Reg=UCSSEL_2;
    UCB0CTL1=u8Reg;

    /*
     *P1.6 = SCL
     *P1.7 = SDA
     */
    P1SEL |=BIT6|BIT7;
    P1SEL2|=BIT6|BIT7;


    IFG2=0;
    IE2=UCB0TXIE|UCB0RXIE;
    UCB0I2CIE=UCALIE|UCSTTIE|UCSTPIE|UCNACKIE;

    //hasta este momento el modulo de I2C esta en funcionamiento

    return 0;
}

uint16_t I2C_u16SendMultiByteMaster(uint8_t u8Address,uint8_t* u8Byte, int8_t s8number )
{
    if(I2C__s8TxInit)
        return 1; //indica que existe una transferencia en proceso

    I2C__s8TxNum=s8number;
    I2C__pu8TxData=u8Byte;
    I2C__s8TxCounter=0;
    I2C__s8TxInit=1;
    I2C__u8TxTry=0;
    UCB0I2CSA=u8Address;
    UCB0CTL0|=UCMST;
    UCB0CTL1|=UCTR|UCTXSTT;
    return 0;
}

uint16_t I2C_u16ReceiveMultiByteMaster(uint8_t u8Address,uint8_t* u8Byte, int8_t s8number )
{
    if(I2C__s8RxInit)
        return 1; //indica que existe una recepcion en proceso

    if(UCB0STAT&UCBBUSY)
    {
        UCB0CTL1|=UCSWRST; //RESET
        UCB0CTL1&=~UCSWRST; //RESET
        IE2=UCB0TXIE|UCB0RXIE;
    }

    I2C__s8RxNum=s8number;
    I2C__pu8RxData=u8Byte;
    I2C__s8RxCounter=0;
    I2C__s8RxInit=1;
    I2C__u8RxTry=0;
    UCB0I2CSA=u8Address;
    UCB0CTL0|=UCMST;
    UCB0CTL1&=~UCTR;
    UCB0CTL1|=UCTXSTT;
    return 0;
}

uint16_t I2C_u16Busy(void)
{
    return I2C__s8TxInit|I2C__s8RxInit;
}

