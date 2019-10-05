/*
 * TimerA.h
 *
 *  Created on: 21/09/2019
 *      Author: Lalo
 */

#ifndef DRIVER_TIMERA0_H_
#define DRIVER_TIMERA0_H_




#include "msp430g2553.h"
#include "stdint.h"

typedef enum
{
    TIMERA0_enOK = 0,
    TIMERA0_enERROR = 1,
}TIMERA0_nStatus;

typedef enum
{
    TIMERA0_enLOW= 0,
    TIMERA0_enHIGH= 1,
}TIMERA0_nOutputState;
typedef enum
{
    TIMERA0_enOUT           = 0,
    TIMERA0_enSET           = 1,
    TIMERA0_enTOGGLE_RESET  = 2,
    TIMERA0_enSET_RESET     = 3,
    TIMERA0_enTOGGLE        = 4,
    TIMERA0_enRESET         = 5,
    TIMERA0_enTOGGLE_SET    = 6,
    TIMERA0_enRESET_SET     = 7,
}TIMERA0_nCompareType;

typedef enum
{
    TIMERA0_enCCIxA = 0,
    TIMERA0_enCCIxB = 1,
    TIMERA0_enGND = 2,
    TIMERA0_enVCC = 3,
}TIMERA0_nOutputPin;

TIMERA0_nStatus TIMERA0__enInitUs(float fTimeUs);
void TIMERA0__vInitCompareCCR1(TIMERA0_nCompareType enType, TIMERA0_nOutputPin enPin);
TIMERA0_nStatus TIMERA0__enPorcentCompareCCR1(uint8_t u8Percent);

void TIMERA0__vEnableIntCCR1(void);
void TIMERA0__vDisableIntCCR1(void);
void TIMERA0__vClearIntCCR1(void);
void TIMERA0__vOutputCCR1(TIMERA0_nOutputState enOut);

#endif /* DRIVER_TIMERA0_H_ */
