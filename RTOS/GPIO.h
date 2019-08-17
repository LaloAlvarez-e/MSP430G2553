/*
 * GPIO.h
 *
 *  Created on: 29 sep. 2017
 *      Author: InDev
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <MSP.h>

void Conf_GPIO(void);

typedef volatile union
{
    volatile unsigned char ALL;
    struct
    {
      volatile unsigned char P0 :1;
      volatile unsigned char P1 :1;
      volatile unsigned char P2 :1;
      volatile unsigned char P3 :1;
      volatile unsigned char P4 :1;
      volatile unsigned char P5 :1;
      volatile unsigned char P6 :1;
      volatile unsigned char P7 :1;
    }Px;
}pines;


#define P1IN   ((pines*) 0x20)
#define P1OUT  ((pines*) 0x21)
#define P1DIR  ((pines*) 0x22)
#define P1IFG  ((pines*) 0x23)
#define P1IES  ((pines*) 0x24)
#define P1IE   ((pines*) 0x25)
#define P1SEL  ((pines*) 0x26)
#define P1REN  ((pines*) 0x27)
#define P1SEL2 ((pines*) 0x41)

#define P2IN   ((pines*) 0x28)
#define P2OUT  ((pines*) 0x29)
#define P2DIR  ((pines*) 0x2A)
#define P2IFG  ((pines*) 0x2B)
#define P2IES  ((pines*) 0x2C)
#define P2IE   ((pines*) 0x2D)
#define P2SEL  ((pines*) 0x2E)
#define P2REN  ((pines*) 0x2F)
#define P2SEL2 ((pines*) 0x42)


enum {
  P0              = 0x0001,
  P1              = 0x0002,
  P2              = 0x0004,
  P3              = 0x0008,
  P4              = 0x0010,
  P5              = 0x0020,
  P6              = 0x0040,
  P7              = 0x0080,
};

#define _P1IN P1IN->ALL
#define _P1IN_0 P1IN->Px.P0
#define _P1IN_1 P1IN->Px.P1
#define _P1IN_2 P1IN->Px.P2
#define _P1IN_3 P1IN->Px.P3
#define _P1IN_4 P1IN->Px.P4
#define _P1IN_5 P1IN->Px.P5
#define _P1IN_6 P1IN->Px.P6
#define _P1IN_7 P1IN->Px.P7

#define _P1OUT P1OUT->ALL
#define _P1OUT_0 P1OUT->Px.P0
#define _P1OUT_1 P1OUT->Px.P1
#define _P1OUT_2 P1OUT->Px.P2
#define _P1OUT_3 P1OUT->Px.P3
#define _P1OUT_4 P1OUT->Px.P4
#define _P1OUT_5 P1OUT->Px.P5
#define _P1OUT_6 P1OUT->Px.P6
#define _P1OUT_7 P1OUT->Px.P7

#define _P1DIR   P1DIR->ALL
#define _P1DIR_0 P1DIR->Px.P0
#define _P1DIR_1 P1DIR->Px.P1
#define _P1DIR_2 P1DIR->Px.P2
#define _P1DIR_3 P1DIR->Px.P3
#define _P1DIR_4 P1DIR->Px.P4
#define _P1DIR_5 P1DIR->Px.P5
#define _P1DIR_6 P1DIR->Px.P6
#define _P1DIR_7 P1DIR->Px.P7

#define _P1REN P1REN->ALL
#define _P1REN_0 P1REN->Px.P0
#define _P1REN_1 P1REN->Px.P1
#define _P1REN_2 P1REN->Px.P2
#define _P1REN_3 P1REN->Px.P3
#define _P1REN_4 P1REN->Px.P4
#define _P1REN_5 P1REN->Px.P5
#define _P1REN_6 P1REN->Px.P6
#define _P1REN_7 P1REN->Px.P7

#define _P1SEL P1SEL->ALL
#define _P1SEL_0 P1SEL->Px.P0
#define _P1SEL_1 P1SEL->Px.P1
#define _P1SEL_2 P1SEL->Px.P2
#define _P1SEL_3 P1SEL->Px.P3
#define _P1SEL_4 P1SEL->Px.P4
#define _P1SEL_5 P1SEL->Px.P5
#define _P1SEL_6 P1SEL->Px.P6
#define _P1SEL_7 P1SEL->Px.P7

#define _P1SEL2 P1SEL2->ALL
#define _P1SEL2_0 P1SEL2->Px.P0
#define _P1SEL2_1 P1SEL2->Px.P1
#define _P1SEL2_2 P1SEL2->Px.P2
#define _P1SEL2_3 P1SEL2->Px.P3
#define _P1SEL2_4 P1SEL2->Px.P4
#define _P1SEL2_5 P1SEL2->Px.P5
#define _P1SEL2_6 P1SEL2->Px.P6
#define _P1SEL2_7 P1SEL2->Px.P7

#define _P1IFG P1IFG->ALL
#define _P1IFG_0 P1IFG->Px.P0
#define _P1IFG_1 P1IFG->Px.P1
#define _P1IFG_2 P1IFG->Px.P2
#define _P1IFG_3 P1IFG->Px.P3
#define _P1IFG_4 P1IFG->Px.P4
#define _P1IFG_5 P1IFG->Px.P5
#define _P1IFG_6 P1IFG->Px.P6
#define _P1IFG_7 P1IFG->Px.P7

#define _P1IE P1IE->ALL
#define _P1IE_0 P1IE->Px.P0
#define _P1IE_1 P1IE->Px.P1
#define _P1IE_2 P1IE->Px.P2
#define _P1IE_3 P1IE->Px.P3
#define _P1IE_4 P1IE->Px.P4
#define _P1IE_5 P1IE->Px.P5
#define _P1IE_6 P1IE->Px.P6
#define _P1IE_7 P1IE->Px.P7

#define _P1IES P1IES->ALL
#define _P1IES_0 P1IES->Px.P0
#define _P1IES_1 P1IES->Px.P1
#define _P1IES_2 P1IES->Px.P2
#define _P1IES_3 P1IES->Px.P3
#define _P1IES_4 P1IES->Px.P4
#define _P1IES_5 P1IES->Px.P5
#define _P1IES_6 P1IES->Px.P6
#define _P1IES_7 P1IES->Px.P7

#define _P2IN P2IN->ALL
#define _P2IN_0 P2IN->Px.P0
#define _P2IN_1 P2IN->Px.P1
#define _P2IN_2 P2IN->Px.P2
#define _P2IN_3 P2IN->Px.P3
#define _P2IN_4 P2IN->Px.P4
#define _P2IN_5 P2IN->Px.P5
#define _P2IN_6 P2IN->Px.P6
#define _P2IN_7 P2IN->Px.P7

#define _P2OUT P2OUT->ALL
#define _P2OUT_0 P2OUT->Px.P0
#define _P2OUT_1 P2OUT->Px.P1
#define _P2OUT_2 P2OUT->Px.P2
#define _P2OUT_3 P2OUT->Px.P3
#define _P2OUT_4 P2OUT->Px.P4
#define _P2OUT_5 P2OUT->Px.P5
#define _P2OUT_6 P2OUT->Px.P6
#define _P2OUT_7 P2OUT->Px.P7

#define _P2DIR P2DIR->ALL
#define _P2DIR_0 P2DIR->Px.P0
#define _P2DIR_1 P2DIR->Px.P1
#define _P2DIR_2 P2DIR->Px.P2
#define _P2DIR_3 P2DIR->Px.P3
#define _P2DIR_4 P2DIR->Px.P4
#define _P2DIR_5 P2DIR->Px.P5
#define _P2DIR_6 P2DIR->Px.P6
#define _P2DIR_7 P2DIR->Px.P7

#define _P2REN P2REN->ALL
#define _P2REN_0 P2REN->Px.P0
#define _P2REN_1 P2REN->Px.P1
#define _P2REN_2 P2REN->Px.P2
#define _P2REN_3 P2REN->Px.P3
#define _P2REN_4 P2REN->Px.P4
#define _P2REN_5 P2REN->Px.P5
#define _P2REN_6 P2REN->Px.P6
#define _P2REN_7 P2REN->Px.P7

#define _P2SEL P2SEL->ALL
#define _P2SEL_0 P2SEL->Px.P0
#define _P2SEL_1 P2SEL->Px.P1
#define _P2SEL_2 P2SEL->Px.P2
#define _P2SEL_3 P2SEL->Px.P3
#define _P2SEL_4 P2SEL->Px.P4
#define _P2SEL_5 P2SEL->Px.P5
#define _P2SEL_6 P2SEL->Px.P6
#define _P2SEL_7 P2SEL->Px.P7

#define _P2SEL2 P2SEL2->ALL
#define _P2SEL2_0 P2SEL2->Px.P0
#define _P2SEL2_1 P2SEL2->Px.P1
#define _P2SEL2_2 P2SEL2->Px.P2
#define _P2SEL2_3 P2SEL2->Px.P3
#define _P2SEL2_4 P2SEL2->Px.P4
#define _P2SEL2_5 P2SEL2->Px.P5
#define _P2SEL2_6 P2SEL2->Px.P6
#define _P2SEL2_7 P2SEL2->Px.P7

#define _P2IFG P2IFG->ALL
#define _P2IFG_0 P2IFG->Px.P0
#define _P2IFG_1 P2IFG->Px.P1
#define _P2IFG_2 P2IFG->Px.P2
#define _P2IFG_3 P2IFG->Px.P3
#define _P2IFG_4 P2IFG->Px.P4
#define _P2IFG_5 P2IFG->Px.P5
#define _P2IFG_6 P2IFG->Px.P6
#define _P2IFG_7 P2IFG->Px.P7

#define _P2IE P2IE->ALL
#define _P2IE_0 P2IE->Px.P0
#define _P2IE_1 P2IE->Px.P1
#define _P2IE_2 P2IE->Px.P2
#define _P2IE_3 P2IE->Px.P3
#define _P2IE_4 P2IE->Px.P4
#define _P2IE_5 P2IE->Px.P5
#define _P2IE_6 P2IE->Px.P6
#define _P2IE_7 P2IE->Px.P7

#define _P2IES P2IES->ALL
#define _P2IES_0 P2IES->Px.P0
#define _P2IES_1 P2IES->Px.P1
#define _P2IES_2 P2IES->Px.P2
#define _P2IES_3 P2IES->Px.P3
#define _P2IES_4 P2IES->Px.P4
#define _P2IES_5 P2IES->Px.P5
#define _P2IES_6 P2IES->Px.P6
#define _P2IES_7 P2IES->Px.P7


#define OUTp(z,w)    Out(z,w)
#define Out(z,w)     _##z##OUT_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define DIRp(z,w)    Dir(z,w)
#define Dir(z,w)     _##z##DIR_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define INp(z,w)    In(z,w)
#define In(z,w)     _##z##IN_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define RENp(z,w)    Ren(z,w)
#define Ren(z,w)     _##z##REN_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define SELp(z,w)    Sel(z,w)
#define Sel(z,w)     _##z##SEL_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define SEL2p(z,w)   Sel2(z,w)
#define Sel2(z,w)    _##z##SEL2_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define IFGp(z,w)    Ifg(z,w)
#define Ifg(z,w)     _##z##IFG_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define IEp(z,w)    Ie(z,w)
#define Ie(z,w)     _##z##IE_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define IESp(z,w)    Ies(z,w)
#define Ies(z,w)     _##z##IES_##w    //abreviacion para seleccionar el puerto indicado (PxOUT)



#define OUTp1(z)    Out1(z)
#define Out1(z)     _##z##OUT    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define DIRp1(z)    Dir1(z)
#define Dir1(z)     _##z##DIR    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define INp1(z)    In1(z)
#define In1(z)     _##z##IN    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define RENp1(z)    Ren1(z)
#define Ren1(z)     _##z##REN    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define SELp1(z)    Sel1(z)
#define Sel1(z)     _##z##SEL    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define SEL2p1(z)   Sel21(z)
#define Sel21(z)    _##z##SEL2    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define IFGp1(z)    Ifg1(z)
#define Ifg1(z)     _##z##IFG    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define IEp1(z)    Ie1(z)
#define Ie1(z)     _##z##IE    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define IESp1(z)    Ies1(z)
#define Ies1(z)     _##z##IES    //abreviacion para seleccionar el puerto indicado (PxOUT)


#endif /* GPIO_H_ */
