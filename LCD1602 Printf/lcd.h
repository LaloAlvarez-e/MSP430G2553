/*
 * lcd.h
 *
 *  Created on: 25/08/2017
 *      Author: Lalo
 */

#ifndef LCD_H_
#define LCD_H_

#include "msp430g2553.h"
#include <stdarg.h>
#include <stdlib.h>

void Conf_LCD1602(void);
void LCD1602_Com(char comando);
void LCD1602_Dato(char dato);
void LCD1602_E(void);
void LCD1602_Pos(char columna, char fila);
int LCD1602_Cadena(char* cadena,unsigned char* columna, unsigned char* fila);
unsigned char Conv_Entero(long long numero,char* conv);
unsigned char Conv_Float(double numero,int decimales, char* conv);

/*DEfinciones de Comando*/
#define CLEAR 0x1 //limpia la pantalla

#define HOME  0x2 //manda cursor a Home 0,0

//Combinacion de los siguientes parametros para mandar comando
#define IncAdd  0x6 //Incrementa la direccion en cada escritura
#define DecAdd  0x4 //Decrementa la direccion en cada escritura

#define NSDisp 0x4 //no desplaza la pantalla
#define SDisp 0x5 //desplaza la pantalla 1 posicion

//combinacion de los siguientes parametros para mandar comando
#define ONDisp    0xC //enciende la pantalla
#define OFFDisp   0x8 //apaga la pantalla

#define ONCursor  0xA //prende el cursor visual
#define OFFCursor 0x8 //apaga el cursor visual

#define ONBlink   0x9 //hace que el cursor parpadee
#define OFFBlink  0x8 //El parpadeo se desactiva

//mandar solo una defincion en este comando
#define SRDisp  0x1C //Desplaza la pantalla a la der, la dir no cambia
#define SLDisp  0x18 //Desplaza la pantalla a la izq, la dir no cambia
#define CRDisp  0x14 //mueve el cursor a la der, la dir aumenta en 1
#define CLDisp  0x10 //mueve el cursor a la izq, la dir disminuye en 1

//combinacion de los siguientes parametros para mandar comando
#define M8BIT     0x30 //modo 8bit
#define M4BIT     0x20 //modo 4bit

#define M1LINE    0x20 //modo 1 linea
#define M2LINE    0x28 //modo 2 lineas

#define M5_8_Font 0x20 //fuente 5x8
#define M5_11_Font 0x24 //fuente 5x11 solo para 1 linea

#define PUERTO_E  P2
#define PUERTO_RS P2
#define PUERTO_RW P1
#define PUERTO_D4 P1
#define PUERTO_D5 P1
#define PUERTO_D6 P2
#define PUERTO_D7 P2

#define E  BIT5
#define RS BIT4
#define RW BIT1
#define D4 BIT5
#define D5 BIT7
#define D6 BIT1
#define D7 BIT2

#define E_POS  5
#define RS_POS 4
#define RW_POS 1
#define D4_POS 5
#define D5_POS 7
#define D6_POS 1
#define D7_POS 2


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



//------------------ Definiciones Pin E ---------------

#define E_OUT   OUTp( PUERTO_E )
#define E_DIR   DIRp(PUERTO_E)
#define E_REN   RENp( PUERTO_E )
#define E_SEL   SELp(PUERTO_E)
#define E_SEL2  SEL2p(PUERTO_E)
#define E_IN    INp(PUERTO_E)

//------------------ Definiciones Pin RS ---------------

#define RS_OUT   OUTp( PUERTO_RS )
#define RS_DIR   DIRp(PUERTO_RS)
#define RS_REN   RENp( PUERTO_RS )
#define RS_SEL   SELp(PUERTO_RS)
#define RS_SEL2  SEL2p(PUERTO_RS)
#define RS_IN    INp(PUERTO_RS)

//------------------ Definiciones Pin RW ---------------

#define RW_OUT   OUTp( PUERTO_RW )
#define RW_DIR   DIRp(PUERTO_RW)
#define RW_REN   RENp( PUERTO_RW )
#define RW_SEL   SELp(PUERTO_RW)
#define RW_SEL2  SEL2p(PUERTO_RW)
#define RW_IN    INp(PUERTO_RW)

//------------------ Definiciones Pin D4 ---------------

#define D4_OUT   OUTp( PUERTO_D4 )
#define D4_DIR   DIRp(PUERTO_D4)
#define D4_REN   RENp( PUERTO_D4 )
#define D4_SEL   SELp(PUERTO_D4)
#define D4_SEL2  SEL2p(PUERTO_D4)
#define D4_IN    INp(PUERTO_D4)

//------------------ Definiciones Pin D5 ---------------

#define D5_OUT   OUTp( PUERTO_D5 )
#define D5_DIR   DIRp(PUERTO_D5)
#define D5_REN   RENp( PUERTO_D5 )
#define D5_SEL   SELp(PUERTO_D5)
#define D5_SEL2  SEL2p(PUERTO_D5)
#define D5_IN    INp(PUERTO_D5)

//------------------ Definiciones Pin D6 ---------------

#define D6_OUT   OUTp( PUERTO_D6 )
#define D6_DIR   DIRp(PUERTO_D6)
#define D6_REN   RENp( PUERTO_D6 )
#define D6_SEL   SELp(PUERTO_D6)
#define D6_SEL2  SEL2p(PUERTO_D6)
#define D6_IN    INp(PUERTO_D6)
//------------------ Definiciones Pin D7 ---------------

#define D7_OUT   OUTp( PUERTO_D7 )
#define D7_DIR   DIRp(PUERTO_D7)
#define D7_REN   RENp( PUERTO_D7 )
#define D7_SEL   SELp(PUERTO_D7)
#define D7_SEL2  SEL2p(PUERTO_D7)
#define D7_IN    INp(PUERTO_D7)




#endif /* LCD_H_ */
