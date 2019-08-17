/*
 * Flash.h
 *
 *  Created on: 30 sep. 2017
 *      Author: InDev
 */

#ifndef FLASH_H_
#define FLASH_H_


#include <MSP.h>

void Borrar_Segmento(char segmento);
void Borrar_Flash();
void Escribir_Byte(char dato, char segmento, short pos);
void Escribir_Word(short dato, char segmento, short pos);
void Escribir_BlockByte(char* dato,short cantidad, char segmento, short pos);
void Escribir_BlockWord(short* dato,short cantidad, char segmento, short pos);


#define FLASH_INICIO 0xF000 //cambia si cambia el CMD
#define FLASH_LEN    0x0E00
#define FLASH_FIN    0xFE00

#define SEG_LEN 0x200
#define RAM_INICIO 0x200
#define SEG0_INICIO 0xFE00
#define SEG0_FIN    0xFFFF

#define SEG1_INICIO 0xFC00
#define SEG1_FIN    0xFDFF

#define SEG2_INICIO 0xFA00
#define SEG2_FIN    0xFBFF

#define SEG3_INICIO 0xF800
#define SEG3_FIN    0xF9FF

#define SEG4_INICIO 0xF600
#define SEG4_FIN    0xF7FF

#define SEG5_INICIO 0xF400
#define SEG5_FIN    0xF5FF

#define SEG6_INICIO 0xF200
#define SEG6_FIN    0xF3FF

#define SEG7_INICIO 0xF000
#define SEG7_FIN    0xF1FF

#define SEG8_INICIO 0xEE00
#define SEG8_FIN    0xEFFF

#define SEG9_INICIO 0xEC00
#define SEG9_FIN    0xEDFF

#define SEG10_INICIO 0xEA00
#define SEG10_FIN    0xEBFF

#define SEG11_INICIO 0xE800
#define SEG11_FIN    0xE9FF

#define SEG12_INICIO 0xE600
#define SEG12_FIN    0xE7FF

#define SEG13_INICIO 0xE400
#define SEG13_FIN    0xE5FF

#define SEG14_INICIO 0xE200
#define SEG14_FIN    0xE3FF

#define SEG15_INICIO 0xE000
#define SEG15_FIN    0xE1FF

#define SEG16_INICIO 0xDE00
#define SEG16_FIN    0xDFFF

#define SEG17_INICIO 0xDC00
#define SEG17_FIN    0xDDFF

#define SEG18_INICIO 0xDA00
#define SEG18_FIN    0xDBFF

#define SEG19_INICIO 0xD800
#define SEG19_FIN    0xD9FF

#define SEG20_INICIO 0xD600
#define SEG20_FIN    0xD7FF

#define SEG21_INICIO 0xD400
#define SEG21_FIN    0xD5FF

#define SEG22_INICIO 0xD200
#define SEG22_FIN    0xD3FF

#define SEG23_INICIO 0xD000
#define SEG23_FIN    0xD1FF



typedef volatile union
{
  unsigned short ALL;   /* FLASH Control 1  */

  struct
  {
    unsigned short                : 1;
    unsigned short ERASE           : 1; /* Enable bit for Flash segment erase  */
    unsigned short MERAS           : 1; /* Enable bit for Flash mass erase  */
    unsigned short                : 3;
    unsigned short WRT             : 1; /* Enable bit for Flash write  */
    unsigned short BLKWRT          : 1; /* Enable bit for Flash segment write  */
    unsigned short FKEY1           :8;
  }bit;
} fctl1;


enum {
  ERASE           = 0x0002,
  MERAS           = 0x0004,
  WRT             = 0x0040,
  BLKWRT          = 0x0080,
  FKEY            = 0x0100
};


typedef volatile union
{
  unsigned short ALL;   /* FLASH Control 2  */

  struct
  {
    unsigned short FN0             : 1; /* Divide Flash clock by 1 to 64 using FN0 to FN5 according to:  */
    unsigned short FN1             : 1; /* 32*FN5 + 16*FN4 + 8*FN3 + 4*FN2 + 2*FN1 + FN0 + 1  */
    unsigned short FN2             : 1; /*   */
    unsigned short FN3             : 1; /*   */
    unsigned short FN4             : 1; /*   */
    unsigned short FN5             : 1; /*   */
    unsigned short FSSEL0          : 1; /* Flash clock select 0  */
    unsigned short FSSEL1          : 1; /* Flash clock select 1  */
    unsigned short FKEY2            :8;
  }bit;
} fctl2_1;


typedef volatile union
{
  unsigned short ALL;   /* FLASH Control 2  */

  struct
  {
    unsigned short FNx             : 6;
    unsigned short FSSELx          : 2;
  }bit;
} fctl2;

enum {
  FN0             = 0x0001,
  FN1             = 0x0002,
  FN2             = 0x0004,
  FN3             = 0x0008,
  FN4             = 0x0010,
  FN5             = 0x0020,
  FSSEL0          = 0x0040,
  FSSEL1          = 0x0080
};


typedef volatile union
{
  unsigned short ALL;   /* FLASH Control 3  */

  struct
  {
    unsigned short BUSY            : 1; /* Flash busy: 1  */
    unsigned short KEYV            : 1; /* Flash Key violation flag  */
    unsigned short ACCVIFG         : 1; /* Flash Access violation flag  */
    unsigned short WAIT            : 1; /* Wait flag for segment write  */
    unsigned short LOCK            : 1; /* Lock bit: 1 - Flash is locked (read only)  */
    unsigned short EMEX            : 1; /* Flash Emergency Exit  */
    unsigned short LOCKA           : 1; /* Segment A Lock bit: read = 1 - Segment is locked (read only)  */
    unsigned short FAIL            : 1; /* Last Program or Erase failed  */
    unsigned short FKEY3            :8;
  }bit;
} fctl3;


enum {
  BUSY            = 0x0001,
  KEYV            = 0x0002,
  ACCVIFG         = 0x0004,
  WAIT            = 0x0008,
  LOCK            = 0x0010,
  EMEX            = 0x0020,
  LOCKA           = 0x0040,
  FAIL            = 0x0080
};



#define FCTL1   ((fctl1*)  0x0128)
#define FCTL2   ((fctl2*) 0x012A)
#define FCTL2_1 ((fctl2_1*) 0x012A)
#define FCTL3   ((fctl3*) 0x012C)


#define _FCTL1    FCTL1->ALL
#define _FKEY1     FCTL1->bit.FKEY1
#define _BLKWRT   FCTL1->bit.BLKWRT
#define _WRT      FCTL1->bit.WRT
#define _MERAS    FCTL1->bit.MERAS
#define _ERASE    FCTL1->bit.ERASE

#define _FCTL2    FCTL2->ALL
#define _FKEY2    FCTL2->bit.FKEY2
#define _FSSELx   FCTL2->bit.FSSELx
#define _FSSEL0   FCTL2_1->bit.FSSEL0
#define _FSSEL1   FCTL2_1->bit.FSSEL1
#define _FNx      FN2->bit.FNx
#define _FN0      FN2_1->bit.FN0
#define _FN1      FN2_1->bit.FN1
#define _FN2      FN2_1->bit.FN2
#define _FN3      FN2_1->bit.FN3
#define _FN4      FN2_1->bit.FN4
#define _FN5      FN2_1->bit.FN5


#define _FCTL3    FCTL3->ALL
#define _FKEY3    FCTL3->bit.FKEY3
#define _FAIL     FCTL3->bit.FAIL
#define _LOCKA    FCTL3->bit.LOCKA
#define _EMEX     FCTL3->bit.EMEX
#define _LOCK     FCTL3->bit.LOCK
#define _WAIT     FCTL3->bit.WAIT
#define _ACCVIFG  FCTL3->bit.ACCVIFG
#define _KEYV     FCTL3->bit.KEYV
#define _BUSY     FCTL3->bit.BUSY

#define FRKEY               (0x9600u)  /* Flash key returned by read */
#define FWKEY               (0xA500u)  /* Flash key for write */
#define FXKEY               (0x3300u)  /* for use with XOR instruction */
#define SEGWRT              (0x0080u)  /* old definition */ /* Enable bit for Flash segment write */

#define ERASE_KEY           (ERASE|FWKEY)
#define MERAS_KEY           (MERAS|FWKEY)
#define LOCK_KEY            (LOCK|FWKEY)
#define WRT_KEY             (WRT|FWKEY)
#define BLKWRT_KEY           (WRT|FWKEY|BLKWRT)
#define FSSEL_0             (0x0000u)  /* Flash clock select: 0 - ACLK */
#define FSSEL_1             (0x0040u)  /* Flash clock select: 1 - MCLK */
#define FSSEL_2             (0x0080u)  /* Flash clock select: 2 - SMCLK */
#define FSSEL_3             (0x00C0u)  /* Flash clock select: 3 - SMCLK */




#endif /* FLASH_H_ */
