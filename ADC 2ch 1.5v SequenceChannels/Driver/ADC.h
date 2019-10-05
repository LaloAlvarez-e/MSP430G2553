/*
 * ADC.h
 *
 *  Created on: 04/10/2019
 *      Author: Lalo
 */

#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_

#include "msp430g2553.h"
#include "stdint.h"

typedef enum
{
    ADC_enREADY = 0,
    ADC_enBUSY = 1,
}ADC_nStatus;

typedef enum
{
    ADC_enOK = 0,
    ADC_enERROR = 1,
}ADC_nError;

void ADC__vInit(uint16_t* pu16Data);
__inline ADC_nStatus ADC__enGetStatus(void);
__inline void ADC__vSetStatus(ADC_nStatus enStatus);
__inline void ADC__vSetBusy(void);
__inline void ADC__vSetReady(void);
__interrupt void ADC_vIsr(void);



#endif /* DRIVER_ADC_H_ */
