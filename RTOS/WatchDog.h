/*
 * WatchDog.h
 *
 *  Created on: 29 sep. 2017
 *      Author: InDev
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <MSP.h>

typedef volatile union
{
    volatile unsigned int ALL;
    struct
    {
        volatile unsigned short WDTISx:2;
        volatile unsigned short WDTSSEL:1;
        volatile unsigned short WDTCNTCL:1;
        volatile unsigned short WDTTMSEL:1;
        volatile unsigned short WDTNMI:1;
        volatile unsigned short WDTNMIES:1;
        volatile unsigned short WDTHOLD:1;
        volatile unsigned short WDTPW:8;
    }bit;

}watchdog;

typedef volatile union
{
    volatile unsigned int ALL;
    struct
    {
        volatile unsigned short WDTIS0:1;
        volatile unsigned short WDTIS1:1;
        volatile unsigned short WDTSSEL:1;
        volatile unsigned short WDTCNTCL:1;
        volatile unsigned short WDTTMSEL:1;
        volatile unsigned short WDTNMI:1;
        volatile unsigned short WDTNMIES:1;
        volatile unsigned short WDTHOLD:1;
        volatile unsigned short WDTPW:8;
    }bit;

}watchdog_1;

typedef volatile union
{
    volatile unsigned short ALL;
    struct
    {
        volatile unsigned short :5;
        volatile unsigned short NMI:1;
        volatile unsigned short NMIES:1;
        volatile unsigned short :1;
        volatile unsigned short WDTPW:8;
    }bit;

}nmi;

#define WDTCTL ((watchdog*) 0x120)
#define WDTCTL_1 ((watchdog_1*) 0x120)
#define NMICTL ((nmi*) 0x120)

enum {
  WDTIS0          = 0x0001,
  WDTIS1          = 0x0002,
  WDTSSEL         = 0x0004,
  WDTCNTCL        = 0x0008,
  WDTTMSEL        = 0x0010,
  WDTNMI          = 0x0020,
  WDTNMIES        = 0x0040,
  WDTHOLD         = 0x0080,
  WDTPW           = 0x5A00
};


#define _WDTCTL   WDTCTL->ALL
//sirven para solo lectura
#define _WDTPW    WDTCTL->bit.WDTPW
#define _WDTHOLD  WDTCTL->bit.WDTHOLD
#define _WDTNMIES WDTCTL->bit.WDTNMIES
#define _WDTNMI   WDTCTL->bit.WDTNMI
#define _WDTTMSEL WDTCTL->bit.WDTTMSEL
#define _WDTCNTCL WDTCTL->bit.WDTCNTCL
#define _WDTSSEL  WDTCTL->bit.WDTSSEL
#define _WDTIS0   WDTCTL_1->bit.WDTIS0
#define _WDTIS1   WDTCTL_1->bit.WDTIS1
#define _WDTISx   WDTCTL->bit.WDTISx

#define _NMICTL   WDTCTL->ALL
#define _NMIIES   WDTCTL->bit.WDTNMIES
#define _NMI      WDTCTL->bit.WDTNMI

//NMI
#define NMI_RISING_NMI  (WDTPW+WDTNMI)
#define NMI_FALLING_NMI (WDTPW+WDTNMI+WDTNMIES)
#define NMI_RESET       (WDTPW)


#define WDT_HOLD (WDTPW + WDTHOLD)

//WDT modo intervalo  SMCLK
#define WDT_INTERVAL_SMCLK_64 (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTIS0)
#define WDT_INTERVAL_SMCLK_512 (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1)
#define WDT_INTERVAL_SMCLK_8192 (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0)
#define WDT_INTERVAL_SMCLK_32768 (WDTPW+WDTTMSEL+WDTCNTCL)

//WDT modo watchdog SMCLK
#define WDT_WATCH_SMCLK_64 (WDTPW+WDTCNTCL+WDTIS1+WDTIS0)
#define WDT_WATCH_SMCLK_512 (WDTPW+WDTCNTCL+WDTIS1)
#define WDT_WATCH_SMCLK_8192 (WDTPW+WDTCNTCL+WDTIS0)
#define WDT_WATCH_SMCLK_32768 (WDTPW+WDTCNTCL)


//WDT modo intervalo ACLK
#define WDT_INTERVAL_ACLK_64 (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTIS0+WDTSSEL)
#define WDT_INTERVAL_ACLK_512 (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTSSEL)
#define WDT_INTERVAL_ACLK_8192 (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0+WDTSSEL)
#define WDT_INTERVAL_ACLK_32768 (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL)

//WDT modo watchdog
#define WDT_WATCH_ACLK_64 (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)
#define WDT_WATCH_ACLK_512 (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1)
#define WDT_WATCH_ACLK_8192 (WDTPW+WDTCNTCL+WDTSSEL+WDTIS0)
#define WDT_WATCH_ACLK_32768 (WDTPW+WDTCNTCL+WDTSSEL)




#endif /* WATCHDOG_H_ */
