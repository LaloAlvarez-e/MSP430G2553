

#include <msp430g2553.h>
#include "clock.h"
#include "I2C.h"
#include "SPI.h"
#include "lcd.h"

/**
 * main.c
 */
int main(void)
{
    uint8_t u8Columna=0,u8Fila=0,u8Count=0;
    uint32_t u32Delay=0;
    float fTemp=0.0;
    uint16_t u16Temp=0;
    uint16_t u16Dummy=0;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock_vInit();
    I2C_vInitMaster(100000);
    SPI_u16Init(600000);
    _EINT();
    u8Columna=0;
    u8Fila=0;
    LCD1602_ChangeDevice(0x3F);
    Conf_LCD1602();//configuracion de la pantalla LCD1602
    LCD1602_Printf("InDevice \n\r",&u8Columna,&u8Fila);
    LCD1602_Printf("Temp: %f",&u8Columna,&u8Fila,fTemp);
    while(1)
    {

        u8Columna=6;
        u8Fila=1;
        SPI_u16SendReceiveMultiByte(((uint8_t*)&u16Dummy),((uint8_t*)&u16Temp),2);

        if((u16Temp&2)==0)
            if(u16Temp&4)
                LCD1602_Printf("Z        ",&u8Columna,&u8Fila);
            else
            {
                u16Temp>>=3;
                fTemp=u16Temp*0.25;
                LCD1602_Printf("%f   ",&u8Columna,&u8Fila,fTemp);
            }


        for(u32Delay=0;u32Delay<800000;u32Delay++);
    }
}

