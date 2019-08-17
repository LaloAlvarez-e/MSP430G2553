#include <msp430g2553.h>
#include "clock.h"
#include "I2C.h"
#include "lcd.h"

/**
 * main.c
 */
int main(void)
{
    uint8_t u8Columna=0,u8Fila=0,u8Cycle=0;
    int16_t s16conteo[8]={0}; //cantidad= numero de digitos convertidos, columna y fila pos de la LCD
    uint32_t u32Delay=0; //cantidad= numero de digitos convertidos, columna y fila pos de la LCD
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock_vInit();
    I2C_vInitMaster(100000);
    _EINT();
    for(u8Cycle=0;u8Cycle<8;u8Cycle++ )
    {
        u8Columna=0;
        u8Fila=0;
        LCD1602_ChangeDevice(0x3F-u8Cycle);
        Conf_LCD1602();//configuracion de la pantalla LCD1602
        LCD1602_Printf("%s LCD%d\n\r",&u8Columna,&u8Fila,"InDevice",u8Cycle+1);
        LCD1602_Printf("Counter %d",&u8Columna,&u8Fila,s16conteo[u8Cycle]);
    }
    while(1)
    {

        for(u8Cycle=0;u8Cycle<8;u8Cycle++ )
        {
            u8Columna=8;
            u8Fila=1;
            LCD1602_ChangeDevice(0x3F-u8Cycle);
            LCD1602_Printf("%d",&u8Columna,&u8Fila,s16conteo[u8Cycle]);
            s16conteo[u8Cycle]+=1+u8Cycle;
        }

        for(u32Delay=0;u32Delay<500000;u32Delay++ );
    }
}
