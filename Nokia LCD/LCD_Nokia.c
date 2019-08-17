/*
 * LCD_Nokia.c
 *
 *  Created on: 25/04/2016
 *      Author: Lalo
 */

#include "LCD_Nokia.h"

unsigned char Arreglo[420];//84-5 , 48-5 =425
const char ASCII[][5] = {
  {0x00, 0x00, 0x00, 0x00, 0x00} // 20
  ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
  ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
  ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
  ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
  ,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
  ,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
  ,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
  ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
  ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
  ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
  ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
  ,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
  ,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
  ,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
  ,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
  ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
  ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
  ,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
  ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
  ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
  ,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
  ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
  ,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
  ,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
  ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
  ,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
  ,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
  ,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
  ,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
  ,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
  ,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
  ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
  ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
  ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
  ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
  ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
  ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
  ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
  ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
  ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
  ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
  ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
  ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
  ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
  ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
  ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
  ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
  ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
  ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
  ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
  ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
  ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
  ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
  ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
  ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
  ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
  ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
  ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
  ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
  ,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c '\'
  ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
  ,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
  ,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
  ,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
  ,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
  ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
  ,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
  ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
  ,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
  ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
  ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
  ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
  ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
  ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
  ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
  ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
  ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
  ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
  ,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
  ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
  ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
  ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
  ,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
  ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
  ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
  ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
  ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
  ,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
  ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
  ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
  ,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
  ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
  ,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
  ,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ~
//  ,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f DEL
  ,{0x1f, 0x24, 0x7c, 0x24, 0x1f} // 7f UT sign
};

void LCD_DibujarBuffer(void){
  LCD_Dibujar((const char*)Arreglo);
}

void LCD_Dibujar( const char *puntero){
  int i;
  LCD_Cursor(0,0);
  for(i=0; i<(MAX_X*MAX_Y/8); i=i+1){
	//if(!((i)%(MAX_X)))
		//LCD_Cursor(0, (i+1)/MAX_X);
	LCD_Escritura(DATO, puntero[i]);



  }
}


void LCD_BMP(unsigned char xpos, unsigned char ypos, const unsigned char *ptr, unsigned char threshold){
  long width = ptr[18], height = ptr[22], i, j;
  unsigned short Arreglox, Arregloy;
  unsigned char mask;
  // check for clipping
  if((height <= 0) ||              // bitmap is unexpectedly encoded in top-to-bottom pixel order
     ((width%2) != 0) ||           // must be even number of columns
     ((xpos + width) > MAX_X) || // right side cut off
     (ypos < (height - 1)) ||      // top cut off
     (ypos > MAX_Y))           { // bottom cut off
    return;
  }
  if(threshold > 14){
    threshold = 14;             // only full 'on' turns pixel on
  }
  // bitmaps are encoded backwards, so start at the bottom left corner of the image
  Arregloy = ypos/8;
  Arreglox = xpos + MAX_X*Arregloy;
  mask = ypos%8;                // row 0 to 7
  mask = 0x01<<mask;            // now stores a mask 0x01 to 0x80
  j = ptr[10];                  // byte 10 contains the offset where image data can be found
  for(i=1; i<=(width*height/2); i=i+1){
    // the left pixel is in the upper 4 bits
    if(((ptr[j]>>4)&0xF) > threshold){
      Arreglo[Arreglox] |= mask;
    } else{
      Arreglo[Arreglox] &= ~mask;
    }
    Arreglox = Arreglox + 1;
    // the right pixel is in the lower 4 bits
    if((ptr[j]&0xF) > threshold){
      Arreglo[Arreglox] |= mask;
    } else{
      Arreglo[Arreglox] &= ~mask;
    }
    Arreglox = Arreglox + 1;
    j = j + 1;
    if((i%(width/2)) == 0){     // at the end of a row
      if(mask > 0x01){
        mask = mask>>1;
      } else{
        mask = 0x80;
        Arregloy = Arregloy - 1;
      }
      Arreglox = xpos + MAX_X*Arregloy;
      // bitmaps are 32-bit word aligned
      switch((width/2)%4){      // skip any padding
        case 0: j = j + 0; break;
        case 1: j = j + 3; break;
        case 2: j = j + 2; break;
        case 3: j = j + 1; break;
      }
    }
  }
}


void LCD_LimpiarBuffer(void)
{
	int i;
  for(i=0; i<(MAX_X*MAX_Y/8); i=i+1){
	//if(((i+1)%(MAX_X)))
		Arreglo[i] = 0;              // clear buffer
	//else
	//	Arreglo[i] = 0xFF;
  }
}



void LCD_Cursor(unsigned char X, unsigned char Y){
  if((X > 11) || (Y > 5)){        // bad input
    return;                             // do nothing
  }
  // multiply newX by 7 because each character is 7 columns wide
  LCD_Escritura(COMANDO, 0x80|(X*7));     // setting bit 7 updates X-position
  LCD_Escritura(COMANDO, 0x40|Y);         // setting bit 6 updates Y-position
}

void LCD_Entero(long numero)
{
  unsigned long divisor=1000000000, valorAuxiliar=0;   					//EL EXPONENTE MAXIMO QUE PUEDE CONVERTIR
  unsigned char no_Cero=1;										//INDICA CUANDO ENCUENTRA EL PRIMER 0
  while(divisor)										//BANDERA PARA SABER QUE YA TERMINO LA CONVERSION
  {
    valorAuxiliar=((numero/divisor)%10)+'0';
    if(valorAuxiliar!='0'| no_Cero==0)		//EMPIEZA EXTRAYENDO LA PRIMERA UNIDAD DEL NUMERO Y CHECA SI ES DIFERENTE A 0 O SI YA SE ENCONTRO UN 0 ANTES
    {
      LCD_Caracter(valorAuxiliar);			//CONVIERTE LA UNIDAD EN ASCII Y LO TRANSMITE
      no_Cero=0;									// INDICA QUE YA SE ENCONTRO EL PRIMER 0
    }
    if (divisor== 1)										//CUANDO VALE UNO SIGNIFICA QUE TEMRINO DE CONVERTIR EL NUMERO
    {
      divisor=0;									//HACE QUE J TENGA EL VALOR DE LA BANDERA
      if(no_Cero==1)								//SI NO SE ENCONTRO NINGUN VALOR DIFERENTE A 0 ENTONCES HACE QUE SE TRANMITA UN 0
        LCD_Caracter('0');
    }
    else
      divisor/=10;										// DIVIDE LA BANDERA O J EN 10 PARA OBTENER LAS SIGUEINTE UNIDAD
  }
}


void LCD_Limpiar(void){
  int i=0;
  //LCD_Cursor(0, 0);
  for(i=0; i<(MAX_X*MAX_Y)/8; i=i+1){
    LCD_Escritura(DATO,0x00);
  }
  LCD_Cursor(0, 0);
}

void LCD_Num(long Numero)
{
	unsigned char Conv[20];
	CONV_NUM(Numero,Conv);
	LCD_Cadena((char*)Conv);
}

void CONV_NUM(long Numero, unsigned char* Conv)
{
	unsigned int Valores=0;
	long aux=0,signo=0,i=0;
	if(Numero<0)
	{
		*(Conv+Valores)='-';
		Numero*=-1;
		Valores++;
		signo=1;
	}
	while(Numero)
	{
		aux=Numero%10;
		*(Conv+Valores)= 0x30+aux;
		Numero/=10;
		Valores++;
	}
	for(i=Valores-1; i>=(signo+(Valores)/2);i--)
	{
		aux=Conv[i];
		Conv[i]=Conv[Valores-1-i+signo];
		Conv[Valores-1-i+signo]=aux;
	}
	Conv[Valores]=0;
}

void static LCD_Escritura(enum Tipo_Escritura tipo, char dato){
//	int basura=0;
	P1OUT&=~BIT4;
  if(tipo == COMANDO)
	  P2OUT &=~BIT2;                              // wait until SSI0 not busy/transmit FIFO empty
  else
    P2OUT |= BIT2;
  while((!(IFG2&UCB0TXIFG))){}; // wait until transmit FIFO not full
  UCB0TXBUF = dato;                // data out
  while((!(IFG2&UCB0TXIFG))){};
  while((UCB0STAT&1)){};
  //basura= UCB0RXBUF;
  P1OUT|=BIT4;
}

void LCD_Cadena(char *puntero){
  while(*puntero){
    LCD_Caracter((unsigned char)*puntero);
    puntero++;
  }
}

void LCD_Caracter(unsigned char dato){
  int i;
  LCD_Escritura(DATO, 0x00);
  for(i=0; i<5; i=i+1){
    LCD_Escritura(DATO, ASCII[dato - 0x20][i]);
  }
  LCD_Escritura(DATO, 0x00);
}

void Init_LCD(void)
{
	int delay=0;
	UCB0CTL1|=UCSWRST;

	UCB0CTL0=UCCKPH|UCMSB|UCMST |UCSYNC;//|UCMODE1;
	UCB0CTL1|=UCSSEL1;
	UCB0BR0=2;
	UCB0BR1=0;
	P1DIR|=(BIT5|BIT7|BIT4); //1.4 CE 1.5 clk 1.7 SIMO 1.8 SOMI
	P1REN&=~(BIT5|BIT7|BIT4);
	P1OUT&=~(BIT5|BIT7|BIT4);
	P1SEL|=(BIT5|BIT7);
	P1SEL2|=(BIT5|BIT7);

	P1DIR|=(BIT3);//reset
	P1REN&=~(BIT3);
	P1OUT&=~(BIT3);
	P1SEL&=~(BIT3|BIT4);
	P1SEL2&=~(BIT3|BIT4);

	P2DIR|=(BIT2); //DC
	P2REN&=~(BIT2);
	P2OUT&=~(BIT2);
	P2SEL&=~(BIT2);
	P2SEL2&=~(BIT2);

	P1IE&=~(BIT3|BIT4|BIT5|BIT7);
	P1IES&=~(BIT3|BIT4|BIT5|BIT7);
	P1IFG&=~(BIT3|BIT4|BIT5|BIT7);

	P2IE&=~(BIT2);
	P2IES&=~(BIT2);
	P2IFG&=~(BIT2);

	UCB0CTL1&=~UCSWRST;

	P1OUT &=~ BIT3;                    // reset the LCD to a known state
	for(delay=0; delay<1000; delay=delay+1);// delay minimum 100 ns
	P1OUT |= BIT3;                   // negative logic
	LCD_Escritura(COMANDO, 0x21);              // chip active; horizontal addressing mode (V = 0); use extended instruction set (H = 1)
	                                        // set LCD Vop (contrast), which may require some tweaking:
	//LCD_Escritura(COMANDO, 0x90);
	LCD_Escritura(COMANDO, 0xB1);          // try 0xB1 (for 3.3V red SparkFun), 0xB8 (for 3.3V blue SparkFun), 0xBF if your display is too dark, or 0x80 to 0xFF if experimenting
	LCD_Escritura(COMANDO, 0x04);              // set temp coefficient
	LCD_Escritura(COMANDO, 0x14);              // LCD bias mode 1:48: try 0x13 or 0x14

	LCD_Escritura(COMANDO, 0x20);              // we must send 0x20 before modifying the display control mode
	LCD_Escritura(COMANDO, 0x0C);              // set display control to normal mode: 0x0D for inverse
}



