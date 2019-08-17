/*
 * uart.c
 *
 *  Created on: 20/03/2019
 *      Author: InDev
 */


#include <I2C.h>


uint8_t I2C_u8RxData[I2C_MAX]={0};
volatile uint8_t* I2C_pu8PutRx=&I2C_u8RxData[0];
volatile uint8_t* I2C_pu8GetRx=&I2C_u8RxData[0];
int8_t  I2C_s8RxCounter=0;

volatile uint8_t* I2C_pu8TxData=0;
int8_t  I2C_s8TxCounter=0;
int8_t  I2C_s8TxNum=0;
int8_t  I2C_s8SlaveAddress=0;
int8_t  I2C_s8Master=0;
int8_t  I2C_s8TxInit=0;

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

#define I2C_TXTRIES 3
uint8_t I2C_u8TxTry=0;
uint16_t I2C_u16SendMultiByteMaster(uint8_t u8Address,uint8_t* u8Byte, int8_t s8number )
{
    if(I2C_s8TxInit)
        return 1; //indica que existe una transferencia en proceso

    I2C_s8TxNum=s8number;
    I2C_pu8TxData=u8Byte;
    I2C_s8TxCounter=0;
    I2C_s8TxInit=1;
    I2C_u8TxTry=0;
    UCB0I2CSA=u8Address;

    UCB0CTL1|=UCTR|UCTXSTT;
    return 0;
}


uint16_t I2C_u16Busy(void)
{
    return I2C_s8TxInit;
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void UARTRX_ISR(void) //Maquina de Estados del I2C
{
    /*
     * Receive a NACK
     */
    if(UCB0STAT & UCNACKIFG)
    {

        UCB0STAT &=~ UCNACKIFG;
        if(UCB0CTL0 &UCMST)
        {
            /*
             * NACK Master-Transmiter
             */
            if(UCB0CTL1 &UCTR)
            {
                    /*
                     * Realiza I2C_TXTRIES intentos de reestrasmision, si no lo logra detiene el envio
                     */
                    if(I2C_u8TxTry<I2C_TXTRIES)
                    {
                        I2C_u8TxTry++;
                        if(I2C_s8TxCounter)
                        {
                            I2C_pu8TxData--;
                            I2C_s8TxCounter--;
                        }
                        UCB0CTL1|=UCTR|UCTXSTT;
                    }
                    else
                    {
                        UCB0CTL1|=UCTXSTP;
                        I2C_s8TxInit=0;
                    }
            }
            /*
             * NACK Master-Receive
             */
            else
            {
            }
        }
        else
        {

            /*
             * NACK Slave-Transmiter
             */
            if(UCB0CTL1 &UCTR)
            {
            }
            /*
             * NACK Slave-Receive
             */
            else
            {
            }
        }
    }






}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void UARTTX_ISR(void) //Manejo de los datos del I2C
{

        if((IFG2&UCB0RXIFG)) //interrupcion para obtener datos del bus I2C
        {
            if((UCB0CTL1 &UCTR)==0)
            {
                /*Master-Receiver data*/
                if((UCB0CTL0 &UCMST))//condiciones cuando el MSP es maestro
                {

                }
                /*Slave-Receiver data*/
                else//condiciones cuando el MSP es esclavo
                {

                }
            }
            else
            {
                /*
                 * intenta recibir cuando se esta configurado como transmisor
                 */
            }

        }

        if((IFG2&UCB0TXIFG)) //interrupcion para enviar datos al bus I2C
        {
            if(UCB0CTL1 &UCTR)
            {
                /*Master-transmitter data*/
                if(UCB0CTL0 &UCMST) //condiciones cuando el MSP es maestro
                {
                    if(I2C_s8TxCounter<I2C_s8TxNum)
                    {
                        //I2C_u8TxTry=0;
                        UCB0TXBUF=*I2C_pu8TxData;
                        I2C_pu8TxData++;
                        I2C_s8TxCounter++;
                    }
                    else
                    {
                        IFG2&=~UCB0TXIFG;
                        UCB0CTL1|=UCTXSTP;
                        I2C_s8TxInit=0;
                    }
                }
                /*Slave-transmitter data*/
                else//condiciones cuando el MSP es esclavo
                {

                }
            }
            else
            {
                /*
                 * Intento transmitir cuando se esta configurado como receptor
                 */
            }

        }
}
