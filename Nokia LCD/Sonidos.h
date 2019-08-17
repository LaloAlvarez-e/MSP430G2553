/*
 * Sonidos.h
 *
 *  Created on: 25/04/2016
 *      Author: Lalo
 */

#ifndef SONIDOS_H_
#define SONIDOS_H_

#include "msp430g2553.h"

extern const unsigned char shoot[4080];
extern const unsigned char invaderkilled[3377];
extern const unsigned char explosion[2000];
extern const unsigned char fastinvader1[982];
extern const unsigned char fastinvader2[1042];
extern const unsigned char fastinvader3[1054];
extern const unsigned char fastinvader4[1098];
extern const unsigned char highpitch[1802];

extern unsigned int Indice_Sonido;
extern const unsigned char *Sonido;
extern unsigned int Conteo_Sonido;

void static Init_DAC(void);
void Init_SONIDO(void);
void Tocar(void);
void Tocar_Sonido(const unsigned char *pt, unsigned long conteo);
void Sonido_Shoot(void);
void Sonido_Killed(void);
void Sonido_Explosion(void);
void Sonido_Fastinvader1(void);
void Sonido_Fastinvader2(void);
void Sonido_Fastinvader3(void);
void Sonido_Fastinvader4(void);
void Sonido_Highpitch(void);

#endif /* SONIDOS_H_ */
