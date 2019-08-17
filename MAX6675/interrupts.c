/*
 * interrupts.c
 *
 *  Created on: 03/04/2019
 *      Author: InDev
 */



#include "interrupts.h"

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIRX_ISR(void) //Maquina de Estados del I2C
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
                    if(I2C__u8TxTry<I2C_TXTRIES)
                    {
                        I2C__u8TxTry++;
                        if(I2C__s8TxCounter)
                        {
                            I2C__pu8TxData--;
                            I2C__s8TxCounter--;
                        }
                        UCB0CTL1|=UCTXSTT;
                    }
                    else
                    {
                        UCB0CTL1|=UCTXSTP;
                        I2C__s8TxInit=0;
                    }
            }
            /*
             * NACK Master-Receive
             */
            else
            {
                /*
                 * Realiza I2C_TXTRIES intentos de reestrasmision, si no lo logra detiene el envio
                 */
                if(I2C__u8RxTry<I2C_RXTRIES)
                {
                    I2C__u8RxTry++;
                    UCB0CTL1|=UCTXSTT;
                }
                else
                {
                    UCB0CTL1|=UCTXSTP;
                    I2C__s8RxInit=0;
                }
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

    if(IFG2&UCA0RXIFG)
    {
        *SPI_pu8PutRx=UCA0RXBUF;
        SPI_pu8PutRx++;
        if(SPI_pu8PutRx==&SPI_u8RxBuffer[SPI_RXMAX])
            SPI_pu8PutRx=SPI_u8RxBuffer;
        SPI_s8RxCounter++;
    }


}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCITX_ISR(void) //Manejo de los datos del I2C
{

        if((IFG2&UCB0RXIFG)) //interrupcion para obtener datos del bus I2C
        {
            if((UCB0CTL1 &UCTR)==0)
            {
                /*Master-Receiver data*/
                if((UCB0CTL0 &UCMST))//condiciones cuando el MSP es maestro
                {
                    if(I2C__s8RxCounter<I2C__s8RxNum)
                    {
                        *I2C__pu8RxData=UCB0RXBUF;
                        I2C__pu8RxData++;
                        I2C__s8RxCounter++;
                    }
                    else
                    {

                        IFG2&=~UCB0RXIFG;
                        UCB0CTL1|=UCTXSTP;
                        I2C__s8RxInit=0;
                    }
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
                    if(I2C__s8TxCounter<I2C__s8TxNum)
                    {
                        //I2C__u8TxTry=0;
                        UCB0TXBUF=*I2C__pu8TxData;
                        I2C__pu8TxData++;
                        I2C__s8TxCounter++;
                    }
                    else
                    {
                        IFG2&=~UCB0TXIFG;
                        UCB0CTL1|=UCTXSTP;
                        I2C__s8TxInit=0;
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


        if(IFG2&UCA0TXIFG)
        {
            if(SPI_s8TxCounter>0)
             {

                SPI_s8TxCounter--;
                 UCA0TXBUF=*SPI_pu8GetTx;
                 SPI_pu8GetTx++;
                 if(SPI_pu8GetTx==&SPI_u8TxBuffer[SPI_TXMAX])
                     SPI_pu8GetTx=&SPI_u8TxBuffer[0];

             }
            else
            {
                IFG2&=~UCA0TXIFG;
                SPI_s8TxInit=0;
            }
        }
}
