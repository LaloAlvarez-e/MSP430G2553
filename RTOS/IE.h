/*
 * IE.h
 *
 *  Created on: 29 sep. 2017
 *      Author: InDev
 */

#ifndef IE_H_
#define IE_H_


#include <MSP.h>

typedef volatile union
{
  unsigned char ALL;   /* Interrupt Enable 1  */

  struct
  {
    unsigned char WDTIE           : 1; /* Watchdog Interrupt Enable  */
    unsigned char OFIE            : 1; /* Osc. Fault  Interrupt Enable  */
    unsigned char                 : 2;
    unsigned char NMIIE           : 1; /* NMI Interrupt Enable  */
    unsigned char ACCVIE          : 1; /* Flash Access Violation Interrupt Enable  */
    unsigned char                 : 1;
  }bit;
} ie1;


enum {
  WDTIE           = 0x0001,
  OFIE            = 0x0002,
  NMIIE           = 0x0010,
  ACCVIE          = 0x0020
};



typedef volatile union
{
  unsigned char ALL;   /* Interrupt Flag 1  */

  struct
  {
    unsigned char WDTIFG          : 1; /* Watchdog Interrupt Flag  */
    unsigned char OFIFG           : 1; /* Osc. Fault Interrupt Flag  */
    unsigned char PORIFG          : 1; /* Power On Interrupt Flag  */
    unsigned char RSTIFG          : 1; /* Reset Interrupt Flag  */
    unsigned char NMIIFG          : 1; /* NMI Interrupt Flag  */
  }bit;
} ifg1;


enum {
  WDTIFG          = 0x0001,
  OFIFG           = 0x0002,
  PORIFG          = 0x0004,
  RSTIFG          = 0x0008,
  NMIIFG          = 0x0010
};


typedef volatile union
{
  unsigned char ALL;   /* Interrupt Enable 2  */

  struct
  {
    unsigned char UCA0RXIE        : 1; /*   */
    unsigned char UCA0TXIE        : 1; /*   */
    unsigned char UCB0RXIE        : 1; /*   */
    unsigned char UCB0TXIE        : 1; /*   */
  }bit;
} ie2;


enum {
  UCA0RXIE        = 0x0001,
  UCA0TXIE        = 0x0002,
  UCB0RXIE        = 0x0004,
  UCB0TXIE        = 0x0008
};


typedef volatile union
{
  unsigned char ALL;   /* Interrupt Flag 2  */

  struct
  {
    unsigned char UCA0RXIFG       : 1; /*   */
    unsigned char UCA0TXIFG       : 1; /*   */
    unsigned char UCB0RXIFG       : 1; /*   */
    unsigned char UCB0TXIFG       : 1; /*   */
  }bit;
} ifg2;


enum {
  UCA0RXIFG       = 0x0001,
  UCA0TXIFG       = 0x0002,
  UCB0RXIFG       = 0x0004,
  UCB0TXIFG       = 0x0008
};


#define IE1 ((ie1*) 0x0)
#define IE2 ((ie2*) 0x1)
#define IFG1 ((ifg1*) 0x2)
#define IFG2 ((ifg2*) 0x3)

#define UC0IE   IE2
#define UC0IFG  IFG2

#define _UCA0RXIE   IE2->bit.UCA0RXIE
#define _UCA0RXIFG  IFG2->bit.UCA0RXIFG
#define _UCA0TXIE   IE2->bit.UCA0TXIE
#define _UCA0TXIFG  IFG2->bit.UCA0TXIFG

#define _UCB0RXIE   IE2->bit.UCB0RXIE
#define _UCB0RXIFG  IFG2->bit.UCB0RXIFG
#define _UCB0TXIE   IE2->bit.UCB0TXIE
#define _UCB0TXIFG  IFG2->bit.UCB0TXIFG

#define _IE1 IE1->ALL
#define _IE2 IE2->ALL
#define _IFG1 IFG1->ALL
#define _IFG2 IFG2->ALL

/*RESET VECTOR*/
#define _WDTIE    IE1->bit.WDTIE
#define _WDTIFG   IFG1->bit.WDTIFG
//ToDo crear definciion de _KEYVIFG
#define _PORIFG   IFG1->bit.PORIFG
#define _RSTIFG   IFG1->bit.RSTIFG

/* NMI VECTOR */
#define _ACCVIE   IE1->bit.ACCVIE
//ToDo crear defincion de _ACCVIFG

#define _NMIIE    IE1->bit.NMIIE
#define _NMIIFG   IFG1->bit.NMIIFG

#define _OFIE     IE1->bit.OFIE
#define _OFIFG    IFG1->bit.OFIFG
#endif /* IE_H_ */
