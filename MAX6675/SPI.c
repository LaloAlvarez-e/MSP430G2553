/*
 * SPI.c
 *
 *  Created on: 05/04/2019
 *      Author: InDev
 */



#include "SPI.h"


uint8_t SPI_u8TxBuffer[SPI_TXMAX]={0};
volatile uint8_t* SPI_pu8PutTx=&SPI_u8TxBuffer[0];
volatile uint8_t* SPI_pu8GetTx=&SPI_u8TxBuffer[0];
int8_t  SPI_s8TxCounter=0;
int8_t  SPI_s8TxInit=0;


uint8_t SPI_u8RxBuffer[SPI_RXMAX]={0};
volatile uint8_t* SPI_pu8PutRx=&SPI_u8RxBuffer[0];
volatile uint8_t* SPI_pu8GetRx=&SPI_u8RxBuffer[0];
int8_t  SPI_s8RxCounter=0;


uint16_t SPI_u16Init(uint32_t u32Frec)
{

    uint32_t u32Baud= 16000000;
    if(u32Frec==0)
        return 1;

    u32Baud/=u32Frec;

    if ((u32Baud==0) || (u32Baud>0xFFFF))
        return 2;

    UCA0CTL1|=UCSWRST;

    //MSB first ,falling edge, SCK always in 0 CS active 0
    //CKPH=0, CKPL=0;
    UCA0CTL0= UCMSB|UCMST|UCSYNC;

    *((uint16_t*)&UCA0BR0) =u32Baud;

    // SOMI o MISO =P1.1, SIMO o MOSI =P1.2, SCK = P1.4 CE1= P1.3
    P1SEL|=BIT1|BIT2|BIT4;
    P1SEL2|=BIT1|BIT2|BIT4;
    P1DIR|=BIT3;
    P1OUT|=BIT3;

    UCA0CTL1=UCSSEL_2;

    IFG2&=~(UCA0TXIFG|UCA0RXIFG);
    IE2|=(UCA0TXIE|UCA0RXIE);

    return  0;
}



uint8_t SPI_u8SendChar(uint8_t u8Dato)
{
    /*Buffer Full*/
    if(SPI_s8TxCounter==(SPI_TXMAX))
           return 1;
    *SPI_pu8PutTx = u8Dato;
    SPI_pu8PutTx++;
    if(SPI_pu8PutTx==&SPI_u8TxBuffer[SPI_TXMAX])
        SPI_pu8PutTx=&SPI_u8TxBuffer[0];

    SPI_s8TxCounter++;
    if(SPI_s8TxInit==0)
    {
        SPI_s8TxInit=1;
        IFG2|=UCA0TXIFG;
    }
    return 0;
}

uint8_t SPI_u8SendByteUntilLoad(uint8_t u8Dato)
{
    uint32_t u32TimeOut=0xFF;

    /*Buffer Full*/
    while(SPI_s8TxCounter==(SPI_TXMAX))
    {
        u32TimeOut--;
        if(u32TimeOut==0x7F)
        {
            IFG2|=UCA0TXIFG;
        }
        if(u32TimeOut==0)
            return 1;
    }

    *SPI_pu8PutTx = u8Dato;
    SPI_pu8PutTx++;
    if(SPI_pu8PutTx==&SPI_u8TxBuffer[SPI_TXMAX])
        SPI_pu8PutTx=SPI_u8TxBuffer;

    SPI_s8TxCounter++;
    if(SPI_s8TxInit==0)
    {
        SPI_s8TxInit=1;
        IFG2|=UCA0TXIFG;
    }

    return 0;

}


uint16_t SPI_u16SendMultiByte(uint8_t* pu8Byte, uint8_t u8Number)
{
    uint8_t u8Counter=0;
    P1OUT&=~BIT3;
    while (u8Counter!=u8Number)
    {
        if(SPI_u8SendChar(pu8Byte[u8Counter]))
        {

            P1OUT|=BIT3;
            return u8Number-u8Counter;
        }
        u8Counter++;
    }

    P1OUT|=BIT3;
    return 0;
}


uint8_t SPI_u8ReceiveByte(uint8_t* pu8Dato)
{
    /*Buffer Empty*/
    if(SPI_s8RxCounter==0)
          return 1;
    /*
     * si el buffer de entrada no tiene datos regresa un error
     */
   /* if((IFG2&UCA0RXIFG)==0)
        return 1;
*/
    SPI_s8RxCounter--;
    *pu8Dato=*SPI_pu8GetRx;
    SPI_pu8GetRx++;
    if(SPI_pu8GetRx==&SPI_u8RxBuffer[SPI_TXMAX])
        SPI_pu8GetRx=SPI_u8RxBuffer;

   // *pcDato=UCA0RXBUF;
    return 0;
}


uint16_t SPI_u16ReceiveMultiByte(uint8_t* pu8Byte, uint8_t u8Number)
{
    uint8_t u8Counter=0;
    while (u8Counter!=u8Number)
    {
        if(SPI_u8ReceiveByte(&pu8Byte[u8Counter]))
            return u8Number-u8Counter;
        u8Counter++;
    }
    return 0;
}


uint16_t SPI_u16SendReceiveMultiByte(uint8_t* pu8ByteSend, uint8_t* pu8ByteReceive,uint8_t u8Number)
{
    uint8_t u8Counter=0;
    P1OUT&=~BIT3;
    while (u8Counter!=u8Number)
    {
        if(SPI_u8SendChar(pu8ByteSend[u8Counter]))
        {

            P1OUT|=BIT3;
            return u8Number-u8Counter;
        }
        if(SPI_u8ReceiveByte(&pu8ByteReceive[u8Counter]))
            return u8Number-u8Counter;
        u8Counter++;
    }
    P1OUT|=BIT3;
    return 0;
}

