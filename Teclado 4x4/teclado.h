/*
 * teclado.h
 *
 *  Created on: 09/09/2017
 *      Author: Lalo
 */

#ifndef TECLADO_H_
#define TECLADO_H_

#include <MSP.h>

void Conf_Teclado(void);
char Leer_Teclado(void);

#define RETARDo 6000

#ifndef P2_6
#define P2_6
#define PUERTO_C0 P2
#define C0 BIT6
#define C0_POS 6
#endif

#ifndef P2_7
#define P2_7
#define PUERTO_C1 P2
#define C1 BIT7
#define C1_POS 7
#endif

#ifndef P1_7
#define P1_7
#define PUERTO_C2 P1
#define C2 BIT7
#define C2_POS 7
#endif

#ifndef P1_6
#define P1_6
#define PUERTO_C3 P1
#define C3 BIT6
#define C3_POS 6
#endif


#ifndef P2_5
#define P2_5
#define P2_5I 1
#define PUERTO_F0 P2
#define F0 BIT5
#define F0_POS 5
#endif

#ifndef P2_4
#define P2_4
#define P2_4I 2
#define PUERTO_F1 P2
#define F1 BIT4
#define F1_POS 4
#endif

#ifndef P2_3
#define P2_3
#define P2_3I 3
#define PUERTO_F2 P2
#define F2 BIT3
#define F2_POS 3
#endif

#ifndef P2_2
#define P2_2
#define P2_2I 4
#define PUERTO_F3 P2
#define F3 BIT2
#define F3_POS 2
#endif

//------------------ Definiciones F1 ---------------

#define F0_OUT   OUTp( PUERTO_F0 )
#define F0_DIR   DIRp(PUERTO_F0)
#define F0_REN   RENp( PUERTO_F0 )
#define F0_SEL   SELp(PUERTO_F0)
#define F0_SEL2  SEL2p(PUERTO_F0)
#define F0_IN    INp(PUERTO_F0)
#define F0_IE  IEp(PUERTO_F0)
#define F0_IES    IESp(PUERTO_F0)
#define F0_IFG  IFGp(PUERTO_F0)

//------------------ Definiciones F2 ---------------

#define F1_OUT   OUTp( PUERTO_F1 )
#define F1_DIR   DIRp(PUERTO_F1)
#define F1_REN   RENp( PUERTO_F1 )
#define F1_SEL   SELp(PUERTO_F1)
#define F1_SEL2  SEL2p(PUERTO_F1)
#define F1_IN    INp(PUERTO_F1)
#define F1_IE  IEp(PUERTO_F1)
#define F1_IES    IESp(PUERTO_F1)
#define F1_IFG  IFGp(PUERTO_F1)

//------------------ Definiciones F3 ---------------

#define F2_OUT   OUTp( PUERTO_F2 )
#define F2_DIR   DIRp(PUERTO_F2)
#define F2_REN   RENp( PUERTO_F2 )
#define F2_SEL   SELp(PUERTO_F2)
#define F2_SEL2  SEL2p(PUERTO_F2)
#define F2_IN    INp(PUERTO_F2)
#define F2_IE  IEp(PUERTO_F2)
#define F2_IES    IESp(PUERTO_F2)
#define F2_IFG  IFGp(PUERTO_F2)

//------------------ Definiciones F4 ---------------

#define F3_OUT   OUTp( PUERTO_F3 )
#define F3_DIR   DIRp(PUERTO_F3)
#define F3_REN   RENp( PUERTO_F3 )
#define F3_SEL   SELp(PUERTO_F3)
#define F3_SEL2  SEL2p(PUERTO_F3)
#define F3_IN    INp(PUERTO_F3)
#define F3_IE  IEp(PUERTO_F3)
#define F3_IES    IESp(PUERTO_F3)
#define F3_IFG  IFGp(PUERTO_F3)


//------------------ Definiciones C1 ---------------

#define C0_OUT   OUTp( PUERTO_C0 )
#define C0_DIR   DIRp(PUERTO_C0)
#define C0_REN   RENp( PUERTO_C0 )
#define C0_SEL   SELp(PUERTO_C0)
#define C0_SEL2  SEL2p(PUERTO_C0)
#define C0_IN    INp(PUERTO_C0)
#define C0_IE  IEp(PUERTO_C0)
#define C0_IES    IESp(PUERTO_C0)
#define C0_IFG  IFGp(PUERTO_C0)

//------------------ Definiciones C2 ---------------

#define C1_OUT   OUTp( PUERTO_C1 )
#define C1_DIR   DIRp(PUERTO_C1)
#define C1_REN   RENp( PUERTO_C1 )
#define C1_SEL   SELp(PUERTO_C1)
#define C1_SEL2  SEL2p(PUERTO_C1)
#define C1_IN    INp(PUERTO_C1)
#define C1_IE  IEp(PUERTO_C1)
#define C1_IES    IESp(PUERTO_C1)
#define C1_IFG  IFGp(PUERTO_C1)

//------------------ Definiciones C3 ---------------

#define C2_OUT   OUTp( PUERTO_C2 )
#define C2_DIR   DIRp(PUERTO_C2)
#define C2_REN   RENp( PUERTO_C2 )
#define C2_SEL   SELp(PUERTO_C2)
#define C2_SEL2  SEL2p(PUERTO_C2)
#define C2_IN    INp(PUERTO_C2)
#define C2_IE  IEp(PUERTO_C2)
#define C2_IES    IESp(PUERTO_C2)
#define C2_IFG  IFGp(PUERTO_C2)

//------------------ Definiciones C4 ---------------

#define C3_OUT   OUTp( PUERTO_C3 )
#define C3_DIR   DIRp(PUERTO_C3)
#define C3_REN   RENp( PUERTO_C3 )
#define C3_SEL   SELp(PUERTO_C3)
#define C3_SEL2  SEL2p(PUERTO_C3)
#define C3_IN    INp(PUERTO_C3)
#define C3_IE  IEp(PUERTO_C3)
#define C3_IES    IESp(PUERTO_C3)
#define C3_IFG  IFGp(PUERTO_C3)

#endif /* TECLADO_H_ */
