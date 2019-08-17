/*
 * lcd.h
 *
 *  Created on: 25/08/2017
 *      Author: Lalo
 */

#ifndef LCD_H_
#define LCD_H_

#include "msp430g2553.h"
#include "I2C.h"
#include <stdarg.h>
#include <stdlib.h>

void LCD1602_ChangeDevice(uint8_t u8Address);
void Conf_LCD1602(void);
void LCD1602_Com(char comando);
void LCD1602_Dato(char dato);


void LCD1602_E(void);
void LCD1602_Pos(char columna, char fila);
int LCD1602_Cadena(char* cadena,unsigned char* columna, unsigned char* fila);
void LCD1602_GC (const char* datos,char dir);

void LCD1602_Char(char dato);
unsigned char LCD1602_Print(char* conv,unsigned char* columna, unsigned char* fila);
unsigned char LCD1602_Printf(char* conv,unsigned char* columna, unsigned char* fila,...);


unsigned char Conv_Entero(long long numero,char* conv);
unsigned char Conv_Hex(long long numero,char* conv);
unsigned char Conv_HEX(long long numero,char* conv);
unsigned char Conv_Oct(long long numero,char* conv);
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

#define RS  0x1
#define RW  0x2
#define EN  0x4
#define BL 0x8
#define D4 0x10
#define D5 0x20
#define D6 0x40
#define D7 0x80




#endif /* LCD_H_ */
