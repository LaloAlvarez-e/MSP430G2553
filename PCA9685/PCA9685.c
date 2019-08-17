
#include "PCA9685.h"


uint8_t PCA9685_u8ActualDevice=0x40;

void PCA9685_ChangeDevice(uint8_t u8Address)
{
    PCA9685_u8ActualDevice=u8Address;
}
void PCA9685_vInit(void)
{
    uint8_t u8Dato[20];
    uint16_t u16Delay;

    u8Dato[0]=MODE1;
    u8Dato[1]=PCA9685_AI|PCA9685_SLEEP |PCA9685_ALLCALL;
    I2C_u16SendMultiByteMaster(PCA9685_u8ActualDevice,u8Dato,2);
    for(u16Delay=0; u16Delay<5000;u16Delay++);

    u8Dato[0]=PRE_SCALE;
    u8Dato[1]=121;
    I2C_u16SendMultiByteMaster(PCA9685_u8ActualDevice,u8Dato,2);
    for(u16Delay=0; u16Delay<5000;u16Delay++);

    u8Dato[0]=MODE1;
    u8Dato[1]=PCA9685_RESTART|PCA9685_AI|PCA9685_ALLCALL;
    I2C_u16SendMultiByteMaster(PCA9685_u8ActualDevice,u8Dato,2);
    for(u16Delay=0; u16Delay<5000;u16Delay++);


    u8Dato[0]=MODE2;
    u8Dato[1]=PCA9685_OUTDRV;
    I2C_u16SendMultiByteMaster(PCA9685_u8ActualDevice,u8Dato,2);
    for(u16Delay=0; u16Delay<5000;u16Delay++);

}

uint16_t PCA9685_u16ChangeServoDegree_MG90(float fDegree, uint8_t u8Channel)
{
    uint8_t u8Dato[20];
    uint16_t u16Delay;
    uint16_t u16PWM;
    float valuePWM=0;
    if((fDegree>90.0) || (fDegree<-90.0))
        return 1;
    if(u8Channel>15)
        return 2;

    valuePWM=fDegree+90.0; //lo convierto en positivo
    valuePWM/=180.0; //normalizo el valor 0 = -90° , 1=90° 0.5 = 0°
    valuePWM*=204.8; //periodo=20ms=50Hz=4096 cuentas, 90°=2ms=(204.8*1)+204.8 cuentas 0°= (204.8*0.5)+204.8, -90°=204.8
    valuePWM+=204.8+0.5;

    u16PWM=(uint16_t)valuePWM;


    u8Dato[0]=CHANNEL0 + 4 * u8Channel;
    u8Dato[1]=0;
    u8Dato[2]=0;
    u8Dato[3]=u16PWM&0xFF;
    u8Dato[4]=(u16PWM>>8)&0xF;
    I2C_u16SendMultiByteMaster(PCA9685_u8ActualDevice,u8Dato,5);
    for(u16Delay=0; u16Delay<5000;u16Delay++);


    return 0;
}


uint16_t PCA9685_u16ChangeServoDegree_MG995(float fDegree, uint8_t u8Channel)
{
    uint8_t u8Dato[20];
    uint16_t u16Delay;
    uint16_t u16PWM;
    float valuePWM=0; //lo convierto en positivo

    if((fDegree>60.0) || (fDegree<-60.0))
        return 1;
    if(u8Channel>15)
        return 2;

    valuePWM=fDegree+60.0; //lo convierto en positivo
    valuePWM/=120.0; //normalizo el valor 0 = -90° , 1=90° 0.5 = 0°
    valuePWM*=204.8; //periodo=20ms=50Hz=4096 cuentas, 90°=2ms=(204.8*1)+204.8 cuentas 0°= (204.8*0.5)+204.8, -90°=204.8
    valuePWM+=204.8+0.5;

    u16PWM=(uint16_t)valuePWM;


    u8Dato[0]=MODE1;
    u8Dato[1]=CHANNEL0 + 4 * u8Channel;
    u8Dato[2]=0;
    u8Dato[3]=0;
    u8Dato[4]=u16PWM&0xFF;
    u8Dato[5]=(u16PWM>>8)&0xF;
    I2C_u16SendMultiByteMaster(PCA9685_u8ActualDevice,u8Dato,6);
    for(u16Delay=0; u16Delay<5000;u16Delay++);


    return 0;
}
