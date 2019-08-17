/*
 * TimerA.h
 *
 *  Created on: 1 oct. 2017
 *      Author: InDev
 */

#ifndef TIMERA_H_
#define TIMERA_H_

#include <MSP.h>


typedef volatile union
{
  unsigned short ALL;   /* FLASH Control 1  */

  struct
  {
    unsigned short TAIFG           : 1;
    unsigned short TAIE            : 1; /* Enable bit for Flash segment erase  */
    unsigned short TACLR           : 1; /* Enable bit for Flash mass erase  */
    unsigned short                 : 1;
    unsigned short MCx             : 2; /* Enable bit for Flash write  */
    unsigned short IDx             : 2; /* Enable bit for Flash segment write  */
    unsigned short TASSELx         : 2;
    unsigned short                 : 6;
  }bit;
} tactl;

typedef volatile union
{
  unsigned short ALL;   /* FLASH Control 1  */

  struct
  {
    unsigned short TAIFG           : 1;
    unsigned short TAIE            : 1;
    unsigned short TACLR           : 1;
    unsigned short                 : 1;
    unsigned short MC0             : 1;
    unsigned short MC1             : 1;
    unsigned short ID0             : 1;
    unsigned short ID1             : 1;
    unsigned short TASSEL0         : 1;
    unsigned short TASSEL1         : 1;
    unsigned short                 : 6;
  }bit;
} tactl_1;

enum {
  TAIFG           = 0x0001,
  TAIE            = 0x0002,
  TACLR           = 0x0004,
  MC0             = 0x0010,
  MC1             = 0x0020,
  ID0             = 0x0040,
  ID1             = 0x0080,
  TASSEL0         = 0x0100,
  TASSEL1         = 0x0200,
};


typedef volatile union
{
  unsigned short ALL;   /* Timer0_A3 Capture/Compare Control 0  */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag  */
    unsigned short COV             : 1; /* Capture/compare overflow flag  */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0  */
    unsigned short CCI             : 1; /* Capture input signal (read)  */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable  */
    unsigned short OUTMODx         : 3; /* Output mode 0  */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0  */
    unsigned short                 : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read)  */
    unsigned short SCS             : 1; /* Capture sychronize  */
    unsigned short CCISx           : 2; /* Capture input select 0  */
    unsigned short CMx             : 2; /* Capture mode 0  */
  }bit;
}tacctl;

typedef volatile union
{
  unsigned short ALL;   /* Timer0_A3 Capture/Compare Control 0  */

  struct
  {
    unsigned short CCIFG           : 1; /* Capture/compare interrupt flag  */
    unsigned short COV             : 1; /* Capture/compare overflow flag  */
    unsigned short OUT             : 1; /* PWM Output signal if output mode 0  */
    unsigned short CCI             : 1; /* Capture input signal (read)  */
    unsigned short CCIE            : 1; /* Capture/compare interrupt enable  */
    unsigned short OUTMOD0         : 1; /* Output mode 0  */
    unsigned short OUTMOD1         : 1; /* Output mode 1  */
    unsigned short OUTMOD2         : 1; /* Output mode 2  */
    unsigned short CAP             : 1; /* Capture mode: 1 /Compare mode : 0  */
    unsigned short                : 1;
    unsigned short SCCI            : 1; /* Latched capture signal (read)  */
    unsigned short SCS             : 1; /* Capture sychronize  */
    unsigned short CCIS0           : 1; /* Capture input select 0  */
    unsigned short CCIS1           : 1; /* Capture input select 1  */
    unsigned short CM0             : 1; /* Capture mode 0  */
    unsigned short CM1             : 1; /* Capture mode 1  */
  }bit;
}tacctl_1;


enum {
  CCIFG           = 0x0001,
  COV             = 0x0002,
  OUT             = 0x0004,
  CCI             = 0x0008,
  CCIE            = 0x0010,
  OUTMOD0         = 0x0020,
  OUTMOD1         = 0x0040,
  OUTMOD2         = 0x0080,
  CAP             = 0x0100,
  SCCI            = 0x0400,
  SCS             = 0x0800,
  CCIS0           = 0x1000,
  CCIS1           = 0x2000,
  CM0             = 0x4000,
  CM1             = 0x8000
};

enum {
  TAIV_CC1          = 0x0002,
  TAIV_CC2          = 0x0004,
  TAIV_IFG          = 0x000A,
};


#define TA0CTL   ((tactl*)  0x0160)
#define TA0CTL_1 ((tactl_1*) 0x0160)

#define TA0CCTL0   ((tacctl*) 0x0162)
#define TA0CCTL0_1 ((tacctl_1*) 0x0162)

#define TA0CCTL1   ((tacctl*) 0x0164)
#define TA0CCTL1_1 ((tacctl_1*) 0x0164)

#define TA0CCTL2   ((tacctl*) 0x0166)
#define TA0CCTL2_1 ((tacctl_1*) 0x0166)

#define _TA0CCR0     *((unsigned short*) 0x0172)
#define _TA0CCR1     *((unsigned short*) 0x0174)
#define _TA0CCR2     *((unsigned short*) 0x0176)

#define _TA0R     *((unsigned short*) 0x0170)
#define _TA0IV    *((unsigned short*) 0x012E)


#define _TA0CTL    TA0CTL->ALL
#define _TA0IFG    TA0CTL->bit.TAIFG
#define _TA0IE     TA0CTL->bit.TAIE
#define _TA0CLR    TA0CTL->bit.TACLR
#define _TA0MCx       TA0CTL->bit.MCx
#define _TA0MC0       TA0CTL_1->bit.MC0
#define _TA0MC1       TA0CTL_1->bit.MC1
#define _TA0MC2       TA0CTL_1->bit.MC2
#define _TA0IDx       TA0CTL->bit.IDx
#define _TA0ID0       TA0CTL_1->bit.ID0
#define _TA0ID1       TA0CTL_1->bit.ID1
#define _TA0SSELx   TA0CTL->bit.TASSELx
#define _TA0SSEL0   TA0CTL_1->bit.TASSEL0
#define _TA0SSEL1   TA0CTL_1->bit.TASSEL1



#define _TA0CCTL0    TA0CCTL0->ALL
#define _TA0COV0        TA0CCTL0->bit.COV
#define _TA0OUT0        TA0CCTL0->bit.OUT
#define _TA0CCI0        TA0CCTL0->bit.CCI
#define _TA0CCIE0       TA0CCTL0->bit.CCIE
#define _TA0OUTMODx0    TA0CCTL0->bit.OUTMODx
#define _TA0OUTMOD00    TA0CCTL0_1->bit.OUTMOD0
#define _TA0OUTMOD10    TA0CCTL0_1->bit.OUTMOD1
#define _TA0OUTMOD20    TA0CCTL0_1->bit.OUTMOD2
#define _TA0CAP0        TA0CCTL0->bit.CAP
#define _TA0SCCI0       TA0CCTL0->bit.SCCI
#define _TA0SCS0        TA0CCTL0->bit.SCS
#define _TA0CCISx0    TA0CCTL0->bit.CCISx
#define _TA0CCIS00    TA0CCTL0_1->bit.CCIS0
#define _TA0CCIS10    TA0CCTL0_1->bit.CCIS1
#define _TA0CMx0    TA0CCTL0->bit.CMx
#define _TA0CM00    TA0CCTL0_1->bit.CM0
#define _TA0CM10    TA0CCTL0_1->bit.CM1


#define _TA0CCTL1    TA0CCTL1->ALL
#define _TA0COV1        TA0CCTL1->bit.COV
#define _TA0OUT1        TA0CCTL1->bit.OUT
#define _TA0CCI1        TA0CCTL1->bit.CCI
#define _TA0CCIE1       TA0CCTL1->bit.CCIE
#define _TA0OUTMODx1    TA0CCTL1->bit.OUTMODx
#define _TA0OUTMOD01    TA0CCTL1_1->bit.OUTMOD0
#define _TA0OUTMOD11    TA0CCTL1_1->bit.OUTMOD1
#define _TA0OUTMOD21    TA0CCTL1_1->bit.OUTMOD2
#define _TA0CAP1        TA0CCTL1->bit.CAP
#define _TA0SCCI1       TA0CCTL1->bit.SCCI
#define _TA0SCS1        TA0CCTL1->bit.SCS
#define _TA0CCISx1      TA0CCTL1->bit.CCISx
#define _TA0CCIS01      TA0CCTL1_1->bit.CCIS0
#define _TA0CCIS11      TA0CCTL1_1->bit.CCIS1
#define _TA0CMx1        TA0CCTL1->bit.CMx
#define _TA0CM01        TA0CCTL1_1->bit.CM0
#define _TA0CM11        TA0CCTL1_1->bit.CM1


#define _TA0CCTL2    TA0CCTL2->ALL
#define _TA0COV2        TA0CCTL2->bit.COV
#define _TA0OUT2        TA0CCTL2->bit.OUT
#define _TA0CCI2        TA0CCTL2->bit.CCI
#define _TA0CCIE2       TA0CCTL2->bit.CCIE
#define _TA0OUTMODx2    TA0CCTL2->bit.OUTMODx
#define _TA0OUTMOD02    TA0CCTL2_1->bit.OUTMOD0
#define _TA0OUTMOD12    TA0CCTL2_1->bit.OUTMOD1
#define _TA0OUTMOD22    TA0CCTL2_1->bit.OUTMOD2
#define _TA0CAP2        TA0CCTL2->bit.CAP
#define _TA0SCCI2       TA0CCTL2->bit.SCCI
#define _TA0SCS2        TA0CCTL2->bit.SCS
#define _TA0CCISx2      TA0CCTL2->bit.CCISx
#define _TA0CCIS02      TA0CCTL2_1->bit.CCIS0
#define _TA0CCIS12      TA0CCTL2_1->bit.CCIS1
#define _TA0CMx2        TA0CCTL2->bit.CMx
#define _TA0CM02        TA0CCTL2_1->bit.CM0
#define _TA0CM12        TA0CCTL2_1->bit.CM1



#define TA1CTL   ((tactl*)  0x0160)
#define TA1CTL_1 ((tactl_1*) 0x0160)

#define TA1CCTL0   ((tacctl*) 0x0162)
#define TA1CCTL0_1 ((tacctl_1*) 0x0162)

#define TA1CCTL1   ((tacctl*) 0x0164)
#define TA1CCTL1_1 ((tacctl_1*) 0x0164)

#define TA1CCTL2   ((tacctl*) 0x0166)
#define TA1CCTL2_1 ((tacctl_1*) 0x0166)

#define _TA1CCR0     *((unsigned short*) 0x0172)
#define _TA1CCR1     *((unsigned short*) 0x0174)
#define _TA1CCR2     *((unsigned short*) 0x0176)

#define _TA1R     *((unsigned short*) 0x0170)
#define _TA1IV    *((unsigned short*) 0x012E)


#define _TA1CTL    TA1CTL->ALL
#define _TA1IFG    TA1CTL->bit.TAIFG
#define _TA1IE     TA1CTL->bit.TAIE
#define _TA1CLR    TA1CTL->bit.TACLR
#define _TA1MCx       TA1CTL->bit.MCx
#define _TA1MC0       TA1CTL_1->bit.MC0
#define _TA1MC1       TA1CTL_1->bit.MC1
#define _TA1MC2       TA1CTL_1->bit.MC2
#define _TA1IDx       TA1CTL->bit.IDx
#define _TA1ID0       TA1CTL_1->bit.ID0
#define _TA1ID1       TA1CTL_1->bit.ID1
#define _TA1SSELx   TA1CTL->bit.TASSELx
#define _TA1SSEL0   TA1CTL_1->bit.TASSEL0
#define _TA1SSEL1   TA1CTL_1->bit.TASSEL1



#define _TA1CCTL0    TA1CCTL0->ALL
#define _TA1COV0        TA1CCTL0->bit.COV
#define _TA1OUT0        TA1CCTL0->bit.OUT
#define _TA1CCI0        TA1CCTL0->bit.CCI
#define _TA1CCIE0       TA1CCTL0->bit.CCIE
#define _TA1OUTMODx0    TA1CCTL0->bit.OUTMODx
#define _TA1OUTMOD00    TA1CCTL0_1->bit.OUTMOD0
#define _TA1OUTMOD10    TA1CCTL0_1->bit.OUTMOD1
#define _TA1OUTMOD20    TA1CCTL0_1->bit.OUTMOD2
#define _TA1CAP0        TA1CCTL0->bit.CAP
#define _TA1SCCI0       TA1CCTL0->bit.SCCI
#define _TA1SCS0        TA1CCTL0->bit.SCS
#define _TA1CCISx0    TA1CCTL0->bit.CCISx
#define _TA1CCIS00    TA1CCTL0_1->bit.CCIS0
#define _TA1CCIS10    TA1CCTL0_1->bit.CCIS1
#define _TA1CMx0    TA1CCTL0->bit.CMx
#define _TA1CM00    TA1CCTL0_1->bit.CM0
#define _TA1CM10    TA1CCTL0_1->bit.CM1


#define _TA1CCTL1    TA1CCTL1->ALL
#define _TA1COV1        TA1CCTL1->bit.COV
#define _TA1OUT1        TA1CCTL1->bit.OUT
#define _TA1CCI1        TA1CCTL1->bit.CCI
#define _TA1CCIE1       TA1CCTL1->bit.CCIE
#define _TA1OUTMODx1    TA1CCTL1->bit.OUTMODx
#define _TA1OUTMOD01    TA1CCTL1_1->bit.OUTMOD0
#define _TA1OUTMOD11    TA1CCTL1_1->bit.OUTMOD1
#define _TA1OUTMOD21    TA1CCTL1_1->bit.OUTMOD2
#define _TA1CAP1        TA1CCTL1->bit.CAP
#define _TA1SCCI1       TA1CCTL1->bit.SCCI
#define _TA1SCS1        TA1CCTL1->bit.SCS
#define _TA1CCISx1      TA1CCTL1->bit.CCISx
#define _TA1CCIS01      TA1CCTL1_1->bit.CCIS0
#define _TA1CCIS11      TA1CCTL1_1->bit.CCIS1
#define _TA1CMx1        TA1CCTL1->bit.CMx
#define _TA1CM01        TA1CCTL1_1->bit.CM0
#define _TA1CM11        TA1CCTL1_1->bit.CM1


#define _TA1CCTL2    TA1CCTL2->ALL
#define _TA1COV2        TA1CCTL2->bit.COV
#define _TA1OUT2        TA1CCTL2->bit.OUT
#define _TA1CCI2        TA1CCTL2->bit.CCI
#define _TA1CCIE2       TA1CCTL2->bit.CCIE
#define _TA1OUTMODx2    TA1CCTL2->bit.OUTMODx
#define _TA1OUTMOD02    TA1CCTL2_1->bit.OUTMOD0
#define _TA1OUTMOD12    TA1CCTL2_1->bit.OUTMOD1
#define _TA1OUTMOD22    TA1CCTL2_1->bit.OUTMOD2
#define _TA1CAP2        TA1CCTL2->bit.CAP
#define _TA1SCCI2       TA1CCTL2->bit.SCCI
#define _TA1SCS2        TA1CCTL2->bit.SCS
#define _TA1CCISx2      TA1CCTL2->bit.CCISx
#define _TA1CCIS02      TA1CCTL2_1->bit.CCIS0
#define _TA1CCIS12      TA1CCTL2_1->bit.CCIS1
#define _TA1CMx2        TA1CCTL2->bit.CMx
#define _TA1CM02        TA1CCTL2_1->bit.CM0
#define _TA1CM12        TA1CCTL2_1->bit.CM1

#define MC_0                (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC_1                (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                (2*0x10u)  /* Timer A mode control: 2 - Continous up */
#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID_0                (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID_1                (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID_2                (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID_3                (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0            (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1            (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2            (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3            (3*0x100u) /* Timer A clock source select: 3 - INCLK */

#define OUTMOD_0            (0*0x20u)  /* PWM output mode: 0 - output only */
#define OUTMOD_1            (1*0x20u)  /* PWM output mode: 1 - set */
#define OUTMOD_2            (2*0x20u)  /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3            (3*0x20u)  /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4            (4*0x20u)  /* PWM output mode: 4 - toggle */
#define OUTMOD_5            (5*0x20u)  /* PWM output mode: 5 - Reset */
#define OUTMOD_6            (6*0x20u)  /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7            (7*0x20u)  /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0              (0*0x1000u) /* Capture input select: 0 - CCIxA */
#define CCIS_1              (1*0x1000u) /* Capture input select: 1 - CCIxB */
#define CCIS_2              (2*0x1000u) /* Capture input select: 2 - GND */
#define CCIS_3              (3*0x1000u) /* Capture input select: 3 - Vcc */
#define CM_0                (0*0x4000u) /* Capture mode: 0 - disabled */
#define CM_1                (1*0x4000u) /* Capture mode: 1 - pos. edge */
#define CM_2                (2*0x4000u) /* Capture mode: 1 - neg. edge */
#define CM_3                (3*0x4000u) /* Capture mode: 1 - both edges */
/* T0_A3IV Definitions */
#define TA0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA0IV_TACCR1        (0x0002u)    /* TA0CCR1_CCIFG */
#define TA0IV_TACCR2        (0x0004u)    /* TA0CCR2_CCIFG */
#define TA0IV_6             (0x0006u)    /* Reserved */
#define TA0IV_8             (0x0008u)    /* Reserved */
#define TA0IV_TAIFG         (0x000Au)    /* TA0IFG */

#endif /* TIMERA_H_ */
