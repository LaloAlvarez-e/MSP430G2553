/*
 * lcd.h
 *
 *  Created on: 25/08/2017
 *      Author: Lalo
 */

#ifndef LCD_H_
#define LCD_H_

#include <MSP.h>
#include <stdarg.h>

void Conf_LCD1602(void);
void LCD1602_Com(char comando);
void LCD1602_Dato(char dato);
char LCD1602_LDato();
char LCD1602_LCom(unsigned char*columna,unsigned char*fila);
void LCD1602_Busy();
void LCD1602_Lectura(unsigned char columna,unsigned char fila,char cantidad,char* conv);

void LCD1602_E(void);
void LCD1602_Pos(unsigned char columna, unsigned char fila);
void LCD1602_Limites(unsigned char* columna, unsigned char* fila);
int LCD1602_Cadena(char* cadena,unsigned char* columna, unsigned char* fila);
void LCD1602_GC (const char* datos,char dir);

void LCD1602_Char(char dato);
unsigned char LCD1602_Print(char* conv,unsigned char* columna, unsigned char* fila);
unsigned char LCD1602_Printf(char* conv,unsigned char* columna, unsigned char* fila,...);


unsigned char Conv_Entero(long long numero,char* conv);
unsigned char Conv_Hex(long long numero,char* conv);
unsigned char Conv_HEX(long long numero,char* conv);
unsigned char Conv_Oct(long long numero,char* conv);
unsigned char Conv_Bin(long numero,char* conv);
unsigned char Conv_Float(double numero,int decimales, char* conv);

/*DEfinciones de Comando*/

#define GCRAM 0x40 //comando para guardar algun caracter personalizado

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



#ifndef P1_2
#define P1_2
#define PUERTO_E  P1
#define E  0x4//2
#endif

#ifndef P1_0
#define P1_0
#define PUERTO_RS P1
#define RS 0x1//0
#endif

#ifndef P1_1
#define P1_1
#define PUERTO_RW P1
#define RW 0x2//1
#endif

#ifndef P1_4
#define P1_4
#define PUERTO_D4 P1
#define D4 0x10//4
#endif

#ifndef P1_5
#define P1_5
#define PUERTO_D5 P1
#define D5 0x20//5
#endif

#ifndef P2_0
#define P2_0
#define PUERTO_D6 P2
#define D6 0x1//0
#endif

#ifndef P2_1
#define P2_1
#define PUERTO_D7 P2
#define D7 0x2//1
#endif



//------------------ Definiciones Pin E ---------------

#define E_OUT   OUTp1( PUERTO_E)
#define E_DIR   DIRp1(PUERTO_E)
#define E_REN   RENp1( PUERTO_E )
#define E_SEL   SELp1(PUERTO_E)
#define E_SEL2  SEL2p1(PUERTO_E)
#define E_IN    INp1(PUERTO_E)

//------------------ Definiciones Pin RS ---------------

#define RS_OUT   OUTp1( PUERTO_RS)
#define RS_DIR   DIRp1(PUERTO_RS)
#define RS_REN   RENp1( PUERTO_RS)
#define RS_SEL   SELp1(PUERTO_RS)
#define RS_SEL2  SEL2p1(PUERTO_RS)
#define RS_IN    INp1(PUERTO_RS)

//------------------ Definiciones Pin RW ---------------

#define RW_OUT   OUTp1( PUERTO_RW )
#define RW_DIR   DIRp1(PUERTO_RW)
#define RW_REN   RENp1( PUERTO_RW)
#define RW_SEL   SELp1(PUERTO_RW)
#define RW_SEL2  SEL2p1(PUERTO_RW)
#define RW_IN    INp1(PUERTO_RW)

//------------------ Definiciones Pin D4 ---------------

#define D4_OUT   OUTp1( PUERTO_D4)
#define D4_DIR   DIRp1(PUERTO_D4)
#define D4_REN   RENp1( PUERTO_D4)
#define D4_SEL   SELp1(PUERTO_D4)
#define D4_SEL2  SEL2p1(PUERTO_D4)
#define D4_IN    INp1(PUERTO_D4)

//------------------ Definiciones Pin D5 ---------------

#define D5_OUT   OUTp1( PUERTO_D5)
#define D5_DIR   DIRp1(PUERTO_D5)
#define D5_REN   RENp1( PUERTO_D5)
#define D5_SEL   SELp1(PUERTO_D5)
#define D5_SEL2  SEL2p1(PUERTO_D5)
#define D5_IN    INp1(PUERTO_D5)

//------------------ Definiciones Pin D6 ---------------

#define D6_OUT   OUTp1( PUERTO_D6)
#define D6_DIR   DIRp1(PUERTO_D6)
#define D6_REN   RENp1( PUERTO_D6)
#define D6_SEL   SELp1(PUERTO_D6)
#define D6_SEL2  SEL2p1(PUERTO_D6)
#define D6_IN    INp1(PUERTO_D6)
//------------------ Definiciones Pin D7 ---------------

#define D7_OUT   OUTp1( PUERTO_D7)
#define D7_DIR   DIRp1(PUERTO_D7)
#define D7_REN   RENp1( PUERTO_D7)
#define D7_SEL   SELp1(PUERTO_D7)
#define D7_SEL2  SEL2p1(PUERTO_D7)
#define D7_IN    INp1(PUERTO_D7)




#endif /* LCD_H_ */
