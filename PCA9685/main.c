

#include <msp430g2553.h>
#include "clock.h"
#include "I2C.h"
#include "lcd.h"
#include "PCA9685.h"

/**
 * main.c
 */
int main(void)
{
    uint8_t u8Columna=0,u8Fila=0,u8Cycle=0,u8Channel=0;
    uint8_t u8Dir[9]={1,1,1,1,1,1,1,1,1};
    float fDegree[9]={0.0};
    uint32_t u32Delay=0; //cantidad= numero de digitos convertidos, columna y fila pos de la LCD
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Clock_vInit();
    I2C_vInitMaster(100000);
    _EINT();
    u8Columna=0;
    u8Fila=0;
    PCA9685_ChangeDevice(0x40);
    PCA9685_vInit();
    for(u8Cycle=0;u8Cycle<5; u8Cycle++)
    {
    PCA9685_u16ChangeServoDegree_MG90(fDegree[u8Cycle],u8Cycle);
    }
    LCD1602_ChangeDevice(0x3F);
    Conf_LCD1602();//configuracion de la pantalla LCD1602
    LCD1602_Printf("All Channel\n\r",&u8Columna,&u8Fila,u8Channel);
    LCD1602_Printf("Degree %f",&u8Columna,&u8Fila,fDegree[0]);
    while(1)
    {
        for(u8Cycle=0;u8Cycle<5; u8Cycle++)
        {
            u8Columna=0;
            u8Fila=0;
            if(fDegree[u8Cycle]>90.0)
            {
                fDegree[u8Cycle]=90.0;
                u8Dir[u8Cycle]=0;
            }
            else if(fDegree[u8Cycle]<-90.0)
            {
                fDegree[u8Cycle]=-90.0;
                u8Dir[u8Cycle]=1;
            }
            PCA9685_u16ChangeServoDegree_MG90(fDegree[u8Cycle],u8Cycle);
            LCD1602_Printf("Channel: %d   \n\r",&u8Columna,&u8Fila,u8Cycle);
            LCD1602_Printf("Degree: %f  ",&u8Columna,&u8Fila,fDegree[u8Cycle]);
            if(u8Dir[u8Cycle])
                fDegree[u8Cycle]+=(1+u8Cycle)*4;
            else
                fDegree[u8Cycle]-=(1+u8Cycle)*3;

            for(u32Delay=0;u32Delay<1500000;u32Delay++ );
        }
    }
}

