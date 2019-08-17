/*
 * LCD_Nokia.h
 *
 *  Created on: 25/04/2016
 *      Author: Lalo
 */

#ifndef LCD_NOKIA_H_
#define LCD_NOKIA_H_


#include <msp430g2553.h>


#define CONTRASTE                0xB9
#define MAX_X 84
#define MAX_Y 40

extern const char ASCII[][5];
extern unsigned char Arreglo[420];//84-5 , 48-5 =425 , 79 ,43
enum Tipo_Escritura{
  COMANDO,
  DATO
};


void LCD_BMP(unsigned char xpos, unsigned char ypos, const unsigned char *ptr, unsigned char threshold);
void static LCD_Escritura(enum Tipo_Escritura tipo, char dato);
void LCD_Caracter(unsigned char dato);
void LCD_Cadena(char *puntero);
void LCD_Entero(long numero);
void CONV_NUM(long Numero, unsigned char* Conv);
void LCD_Num(long Numero);
void LCD_Cursor(unsigned char X, unsigned char Y);
void LCD_Limpiar(void);
void LCD_Dibujar(const char *puntero);
void LCD_LimpiarBuffer(void);
void Init_LCD(void);
void LCD_Dibujar(const char *puntero);
void LCD_DibujarBuffer(void);

#endif /* LCD_NOKIA_H_ */
