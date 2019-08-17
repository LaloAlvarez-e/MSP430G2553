/*
 * reloj.h
 *
 *  Created on: 25/08/2017
 *      Author: Lalo
 */

#ifndef CLOCK_H_
#define CLOCK_H_



#include <MSP.h>

void Conf_Reloj(void);
void Conf_OscFault(void);
void Conf_ACLK(void);
void Conf_SMCLK(void);
void Clock_Salida(void);

typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
        volatile unsigned char MODx:5;
        volatile unsigned char DCOx:3;
    }bit;

}dcoctl;


typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
        volatile unsigned char MOD0:1;
        volatile unsigned char MOD1:1;
        volatile unsigned char MOD2:1;
        volatile unsigned char MOD3:1;
        volatile unsigned char MOD4:1;
        volatile unsigned char DCO0:1;
        volatile unsigned char DCO1:1;
        volatile unsigned char DCO2:1;
    }bit;

}dcoctl_1;

enum {
  MOD0              = 0x0001,
  MOD1              = 0x0002,
  MOD2              = 0x0004,
  MOD3              = 0x0008,
  MOD4              = 0x0010,
  DCO0              = 0x0020,
  DCO1              = 0x0040,
  DCO2              = 0x0080,
};


typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
        volatile unsigned char RSELx:4;
        volatile unsigned char DIVAx:2;
        volatile unsigned char XTS:1;
        volatile unsigned char XT2OFF:1;
    }bit;
}bcsctl1;

typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
       volatile unsigned char RSEL0:1;
       volatile unsigned char RSEL1:1;
       volatile unsigned char RSEL2:1;
       volatile unsigned char RSEL3:1;
       volatile unsigned char DIVA0:1;
       volatile unsigned char DIVA1:1;
       volatile unsigned char XTS:1;
       volatile unsigned char XT2OFF:1;
    }bit;
}bcsctl1_1;

enum {
  RSEL0           = 0x0001,
  RSEL1           = 0x0002,
  RSEL2           = 0x0004,
  RSEL3           = 0x0008,
  DIVA0           = 0x0010,
  DIVA1           = 0x0020,
  XTS             = 0x0040,
  XT2OFF          = 0x0080
};



typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
        volatile unsigned char DCOR:1;
        volatile unsigned char DIVSx:2;
        volatile unsigned char SELS:1;
        volatile unsigned char DIVMx:2;
        volatile unsigned char SELMx:2;
    }bit;
}bcsctl2;


typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
        volatile unsigned char DCOR:1;
        volatile unsigned char DIVS0:1;
        volatile unsigned char DIVS1:1;
        volatile unsigned char SELS:1;
        volatile unsigned char DIVM0:1;
        volatile unsigned char DIVM1:1;
        volatile unsigned char SELM0:1;
        volatile unsigned char SELM1:1;
    }bit;
}bcsctl2_1;

enum {
  DIVS0           = 0x0002,
  DIVS1           = 0x0004,
  SELS            = 0x0008,
  DIVM0           = 0x0010,
  DIVM1           = 0x0020,
  SELM0           = 0x0040,
  SELM1           = 0x0080
};


typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
        volatile unsigned char LFXT1OF:1;
        volatile unsigned char XT2OF:1;
        volatile unsigned char XCAPx:2;
        volatile unsigned char LFXT1Sx:2;
        volatile unsigned char XT2Sx:2;

    }bit;
}bcsctl3;
typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
        volatile unsigned char LFXT1OF:1;
        volatile unsigned char XT2OF:1;
        volatile unsigned char XCAP0:1;
        volatile unsigned char XCAP1:1;
        volatile unsigned char LFXT1S0:1;
        volatile unsigned char LFXT1S1:1;
        volatile unsigned char XT2S0:1;
        volatile unsigned char XT2S1:1;

    }bit;
}bcsctl3_1;


enum {
  LFXT1OF         = 0x0001,
  XT2OF           = 0x0002,
  XCAP0           = 0x0004,
  XCAP1           = 0x0008,
  LFXT1S0         = 0x0010,
  LFXT1S1         = 0x0020,
  XT2S0           = 0x0040,
  XT2S1           = 0x0080
};

#define DCOCTL    ((dcoctl*)  0x56)
#define DCOCTL_1  ((dcoctl_1*)  0x56)
#define BCSCTL1   ((bcsctl1*) 0x57)
#define BCSCTL1_1 ((bcsctl1_1*) 0x57)
#define BCSCTL2   ((bcsctl2*) 0x58)
#define BCSCTL2_1 ((bcsctl2_1*) 0x58)
#define BCSCTL3   ((bcsctl3*) 0x53)
#define BCSCTL3_1 ((bcsctl3_1*) 0x53)


#define _DCOCTL  DCOCTL->ALL
#define _MODx    DCOCTL->bit.MODx
#define _MOD0    DCOCTL_1->bit.MOD0
#define _MOD1    DCOCTL_1->bit.MOD1
#define _MOD2    DCOCTL_1->bit.MOD2
#define _MOD3    DCOCTL_1->bit.MOD3
#define _MOD4    DCOCTL_1->bit.MOD4
#define _DCOx    DCOCTL->bit.DCOx
#define _DCO0    DCOCTL_1->bit.DCO0
#define _DCO1    DCOCTL_1->bit.DCO1
#define _DCO2    DCOCTL_1->bit.DCO2


#define _BCSCTL1 BCSCTL1->ALL
#define _RSELx   BCSCTL1->bit.RSELx
#define _RSEL0   BCSCTL1_1->bit.RSEL0
#define _RSEL1   BCSCTL1_1->bit.RSEL1
#define _RSEL2   BCSCTL1_1->bit.RSEL2
#define _RSEL3   BCSCTL1_1->bit.RSEL3
#define _DIVAx   BCSCTL1->bit.DIVAx
#define _DIVA0   BCSCTL1_1->bit.DIVA0
#define _DIVA1   BCSCTL1_1->bit.DIVA1
#define _XTS     BCSCTL1->bit.XTS
#define _XT2OFF  BCSCTL1->bit.XT2OFF


#define _BCSCTL2 BCSCTL2->ALL
#define _DIVSx   BCSCTL2->bit.DIVSx
#define _DIVS0   BCSCTL2_1->bit.DIVS0
#define _DIVS1   BCSCTL2_1->bit.DIVS1
#define _SELS    BCSCTL2->bit.SELS
#define _DIVMx   BCSCTL2->bit.DIVMx
#define _DIVM0   BCSCTL2_1->bit.DIVM0
#define _DIVM1   BCSCTL2_1->bit.DIVM1
#define _SELMx   BCSCTL2->bit.SELMx
#define _SELM0   BCSCTL2_1->bit.SELM0
#define _SELM1   BCSCTL2_1->bit.SELM1



#define _BCSCTL3 BCSCTL3->ALL
#define _LFXT1OF BCSCTL3->bit.LFXT1OF
#define _XT2OF   BCSCTL3->bit.XT2OF
#define _XCAPx   BCSCTL3->bit.XCAPx
#define _XCAP0   BCSCTL3_1->bit.XCAP0
#define _XCAP1   BCSCTL3_1->bit.XCAP1
#define _LFXT1Sx BCSCTL3->bit.LFXT1Sx
#define _LFXT1S0 BCSCTL3_1->bit.LFXT1S0
#define _LFXT1S1 BCSCTL3_1->bit.LFXT1S1
#define _XT2Sx   BCSCTL3->bit.XT2Sx
#define _XT2S0   BCSCTL3_1->bit.XT2S0
#define _XT2S1   BCSCTL3_1->bit.XT2S1


#define DIVA_0              (0x00)   /* ACLK Divider 0: /1 */
#define DIVA_1              (0x10)   /* ACLK Divider 1: /2 */
#define DIVA_2              (0x20)   /* ACLK Divider 2: /4 */
#define DIVA_3              (0x30)   /* ACLK Divider 3: /8 */

#define DIVS_0              (0x00)   /* SMCLK Divider 0: /1 */
#define DIVS_1              (0x02)   /* SMCLK Divider 1: /2 */
#define DIVS_2              (0x04)   /* SMCLK Divider 2: /4 */
#define DIVS_3              (0x06)   /* SMCLK Divider 3: /8 */

#define DIVM_0              (0x00)   /* MCLK Divider 0: /1 */
#define DIVM_1              (0x10)   /* MCLK Divider 1: /2 */
#define DIVM_2              (0x20)   /* MCLK Divider 2: /4 */
#define DIVM_3              (0x30)   /* MCLK Divider 3: /8 */

#define SELM_0              (0x00)   /* MCLK Source Select 0: DCOCLK */
#define SELM_1              (0x40)   /* MCLK Source Select 1: DCOCLK */
#define SELM_2              (0x80)   /* MCLK Source Select 2: XT2CLK/LFXTCLK */
#define SELM_3              (0xC0)   /* MCLK Source Select 3: LFXTCLK */

#define XCAP_0              (0x00)   /* XIN/XOUT Cap : 0 pF */
#define XCAP_1              (0x04)   /* XIN/XOUT Cap : 6 pF */
#define XCAP_2              (0x08)   /* XIN/XOUT Cap : 10 pF */
#define XCAP_3              (0x0C)   /* XIN/XOUT Cap : 12.5 pF */

#define LFXT1S_0            (0x00)   /* Mode 0 for LFXT1 : Normal operation */
#define LFXT1S_1            (0x10)   /* Mode 1 for LFXT1 : Reserved */
#define LFXT1S_2            (0x20)   /* Mode 2 for LFXT1 : VLO */
#define LFXT1S_3            (0x30)   /* Mode 3 for LFXT1 : Digital input signal */

#define XT2S_0              (0x00)   /* Mode 0 for XT2 : 0.4 - 1 MHz */
#define XT2S_1              (0x40)   /* Mode 1 for XT2 : 1 - 4 MHz */
#define XT2S_2              (0x80)   /* Mode 2 for XT2 : 2 - 16 MHz */
#define XT2S_3              (0xC0)   /* Mode 3 for XT2 : Digital input signal */


#endif /* CLOCK_H_ */
