/*
 * Calibracion.h
 *
 *  Created on: 29 sep. 2017
 *      Author: InDev
 */

#ifndef CALIBRACION_H_
#define CALIBRACION_H_

#define TAG_DCO_30  (*(unsigned char*)0x10F6)
#define LEN_DCO_30  (*(unsigned char*)(0x1+0x10F6))
#define TAG_ADC10_1 (*(unsigned char*)0x10DA)
#define LEN_ADC10_1 (*(unsigned char*)(0x1+0x10DA))
#define CHECKSUM    (*(unsigned short*)0x10CA)
#define TAG_EMPTY   0xFE

#define CAL_ADC_25T85           (*(unsigned short*)(0x10+0x10DA))
#define CAL_ADC_25T35           (*(unsigned short*)(0xE+0x10DA))
#define CAL_ADC_25VREF_FACTOR   (*(unsigned short*)(0xC+0x10DA))
#define CAL_ADC_15T85           (*(unsigned short*)(0xA+0x10DA))
#define CAL_ADC_15T30           (*(unsigned short*)(0x8+0x10DA))
#define CAL_ADC_15VREF_FACTOR   (*(unsigned short*)(0x6+0x10DA))
#define CAL_ADC_OFFSET          (*(unsigned short*)(0x4+0x10DA))
#define CAL_ADC_GAIN_FACTOR     (*(unsigned short*)(0x2+0x10DA))

#define CAL_BC1_1MHZ    (*(unsigned char*)(0x9+0x10F6))
#define CAL_DCO_1MHZ    (*(unsigned char*)(0x8+0x10F6))
#define CAL_BC1_8MHZ    (*(unsigned char*)(0x7+0x10F6))
#define CAL_DCO_8MHZ    (*(unsigned char*)(0x6+0x10F6))
#define CAL_BC1_12MHZ   (*(unsigned char*)(0x5+0x10F6))
#define CAL_DCO_12MHZ   (*(unsigned char*)(0x4+0x10F6))
#define CAL_BC1_16MHZ   (*(unsigned char*)(0x3+0x10F6))
#define CAL_DCO_16MHZ   (*(unsigned char*)(0x2+0x10F6))

#define CALBC1_1MHZ    (*(unsigned char*)(0x9+0x10F6))
#define CALDCO_1MHZ    (*(unsigned char*)(0x8+0x10F6))
#define CALBC1_8MHZ    (*(unsigned char*)(0x7+0x10F6))
#define CALDCO_8MHZ    (*(unsigned char*)(0x6+0x10F6))
#define CALBC1_12MHZ   (*(unsigned char*)(0x5+0x10F6))
#define CALDCO_12MHZ   (*(unsigned char*)(0x4+0x10F6))
#define CALBC1_16MHZ   (*(unsigned char*)(0x3+0x10F6))
#define CALDCO_16MHZ   (*(unsigned char*)(0x2+0x10F6))



#endif /* CALIBRACION_H_ */
