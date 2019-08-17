/*
 * interrupts.c
 *
 *  Created on: 03/04/2019
 *      Author: InDev
 */



#include "interrupts.h"


#pragma vector =PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    uint8_t u8Count=0;
    if(P1IFG&BIT5)
    {
        if(P1IES&BIT5)
        {
            P1IES&=~BIT5;
            P1IFG&=~BIT5;

        }
        else
        {
            P1IES|=BIT5;
            TTP229__u16Tecla=0;
            for(u8Count=0; u8Count<16; u8Count++)
            {
                P1OUT&=~BIT4;
                P1OUT|=BIT4;
                TTP229__u16Tecla|=((P1IN>>5)&BIT0)<<u8Count;
            }
            TTP229__u16Tecla=~TTP229__u16Tecla;
            P1IFG&=~BIT5;
        }
    }
}

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
}
