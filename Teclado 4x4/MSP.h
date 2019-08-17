/*
 * MSP.h
 *
 *  Created on: 09/09/2017
 *      Author: Lalo
 */

#ifndef MSP_H_
#define MSP_H_

#include "msp430g2553.h"



#define OUTp(p)    Out(p)
#define Out(p)    p ## OUT    //abreviacion para seleccionar el puerto indicado (PxOUT)

#define DIRp(p)    Dir(p)
#define Dir(p)    p ## DIR    //abreviacion para seleccionar el puerto indicado (PxDIR)

#define INp(p)     In(p)
#define In(p)     p ## IN     //abreviacion para seleccionar el puerto indicado (PxIN)

#define SELp(p)    Sel(p)
#define Sel(p)    p ## SEL    //abreviacion para seleccionar el puerto indicado (PxSEL)

#define RENp(p)    Ren(p)
#define Ren(p)    p ## REN    //abreviacion para seleccionar el puerto indicado (PxREN)

#define SEL2p(p)   Sel2(p)
#define Sel2(p)   p##SEL2

#define IEp(p)   Ie(p)
#define Ie(p)   p##IE

#define IESp(p)   Ies(p)
#define Ies(p)   p##IES

#define IFGp(p)   Ifg(p)
#define Ifg(p)   p##IFG



#endif /* MSP_H_ */
