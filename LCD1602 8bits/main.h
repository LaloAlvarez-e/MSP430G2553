/*
 * main.h
 *
 *  Created on: 21/08/2017
 *      Author: Lalo
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <msp430g2553.h>


void Conf_Reloj(void);
void Conf_LCD1602(void);
void LCD1602_Com(char comando);
void LCD1602_Dato(char dato);
void LCD1602_E(void);
void LCD1602_Pos(char columna, char fila);

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

#define RS BIT0
#define RW BIT1
#define E  BIT2
#define PRS P2OUT
#define PRW P2OUT
#define PE  P2OUT

#define D0 BIT0
#define D1 BIT1
#define D2 BIT2
#define D3 BIT3
#define D4 BIT4
#define D5 BIT5
#define D6 BIT6
#define D7 BIT7

#define PD0 P1OUT
#define PD1 P1OUT
#define PD2 P1OUT
#define PD3 P1OUT
#define PD4 P1OUT
#define PD5 P1OUT
#define PD6 P1OUT
#define PD7 P1OUT

#endif /* MAIN_H_ */
