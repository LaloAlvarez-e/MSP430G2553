

#include <msp430g2553.h>
#include "clock.h"
#include "I2C.h"
#include "lcd.h"
#include "ttp229.h"

/**
 * main.c
 */
int main(void)
{
    uint8_t u8Columna=0,u8Fila=0,u8Tecla=0;
    uint32_t u32Delay=0;
    uint16_t u16Teclas={0};
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock_vInit();
    I2C_vInitMaster(100000);
    _EINT();
    u8Columna=0;
    u8Fila=0;
    TTP229_vInit();
    LCD1602_ChangeDevice(0x3F);
    Conf_LCD1602();//configuracion de la pantalla LCD1602
    LCD1602_Printf("InDevice \n\r",&u8Columna,&u8Fila);
    //LCD1602_Printf("Tecla: %d",&u8Columna,&u8Fila,a);
    while(1)
    {

        u8Columna=7;
        u8Fila=1;
        if(!TTP229_u16Value(&u16Teclas))
            for(u32Delay=0; u32Delay<16;u32Delay++)
            {
                if((u16Teclas>>u32Delay)&1)
                    u8Tecla=u32Delay+1;
            }

        if(u8Tecla)
            LCD1602_Printf("%d ",&u8Columna,&u8Fila,u8Tecla);

        for(u32Delay=0;u32Delay<500000;u32Delay++);
    }
}

