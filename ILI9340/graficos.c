/*
 * graficos.c
 * configuracion para msp
 * Febrero 19, 2015
 *
 * RobG modificado porEduardo Alvarez Lopez*/

#include "graficos.h"
#include "fuentes.h"
#include "lcd.h"
#include "msp.h"
//#include "colores.h"



u_char colorLSB = 0;
u_char colorMSB = 0;
u_char bgColorLSB = 0;
u_char bgColorMSB = 0;

struct caracteres{
		void (*Funcion)(u_int x, u_int y, char c);
	};
	typedef const struct caracteres Funcioncaracteres;
	Funcioncaracteres FuncionC[6]=
			{
					&dibujarCharSm,
					&dibujarCharMd,
					&dibujarCharLg,
					&dibujarCharSmBkg,
					&dibujarCharMdBkg,
					&dibujarCharLgBkg
			};

const unsigned char TFuente[6]={6,8,13,6,8,13};

#define OFFSET 0x20

//////////////////////
// color
//////////////////////

void establecerColor(u_int color) {
	colorLSB = color;
	colorMSB = color >> 8;
}

void establecerColorFondo(u_int color) {
	bgColorLSB = color;
	bgColorMSB = color >> 8;
}

/////////////////
// limpiar pantalla , dibujar pixel
/////////////////

void limpiarPantalla(u_int Color) {
	establecer_Area(0, 0, obtener_Ancho() - 1, obtener_Largo() - 1);
	establecerColorFondo(Color);
	u_int ancho = obtener_Ancho();
	u_int largo = obtener_Largo();
	while (largo != 0) {
		while (ancho != 0) {
			escribirDato(bgColorMSB);
			escribirDato(bgColorLSB);
			ancho--;
		}
		ancho = obtener_Ancho();
		largo--;
	}
}

void dibujarPixel(u_int x, u_int y) {
	establecer_Area(x, y, x, y);
	escribirDato(colorMSB);
	escribirDato(colorLSB);
}

void dibujarPixelBg(u_int x, u_int y) {
	establecer_Area(x, y, x, y);
	escribirDato(bgColorMSB);
	escribirDato(bgColorLSB);
}
/////////////////////////////
// Dibujar Cadena
/////////////////////////////

void dibujarCadena(u_int x, u_int y, char fuenteT, char *cadena) {
	u_int xs = x;
	while (*cadena)
	{
		(FuncionC[fuenteT].Funcion)(xs, y, *cadena++);
		xs += TFuente[fuenteT];
	}

}

//////////////////////////
// 5x7 fuentes
//////////////////////////
void dibujarCharSm(u_int x, u_int y, char c) {
	u_char columna = 0;
	u_char fila = 0;
	u_char bit = 0x01;
	u_char oc = c - OFFSET;
	while (fila < 7) {
		while (columna < 5) {
			if (fuentes_5x7[oc][columna] & bit)
				dibujarPixel(x + columna, y + fila);
			columna++;
		}
		columna = 0;
		bit <<= 1;
		fila++;
	}
}

////////////////
// 5x7 fuentes
////////////////
void dibujarCharSmBkg(u_int x, u_int y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_char bit = 0x01;
	u_char oc = c - OFFSET;
	establecer_Area(x, y, x + 4, y + 7);
	while (row < 7) {
		while (col < 5) {
			if (fuentes_5x7[oc][col] & bit) {
				//foreground
				escribirDato(colorMSB);
				escribirDato(colorLSB);
			} else {
				//background
				escribirDato(bgColorMSB);
				escribirDato(bgColorLSB);
			}
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

////////////////
// 11x16 fuentes
////////////////
void dibujarCharLg(u_int x, u_int y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_int bit = 0x0001;
	u_char oc = c - OFFSET;
	while (row < 16) {
		while (col < 11) {
			if (fuentes_11x16[oc][col] & bit)
				dibujarPixel(x + col, y + row);
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

////////////////
// 11x16 fuentes
////////////////
void dibujarCharLgBkg(u_int x, u_int y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_int bit = 0x0001;
	u_char oc = c - OFFSET;
	establecer_Area(x, y, x + 10, y + 15);
	while (row < 16) {
		while (col < 11) {
			if (fuentes_11x16[oc][col] & bit) {
				//foreground
				escribirDato(colorMSB);
				escribirDato(colorLSB);
			} else {
				//background
				escribirDato(bgColorMSB);
				escribirDato(bgColorLSB);
			}
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

////////////////
// 8x12 fuentes
////////////////
void dibujarCharMd(u_int x, u_int y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_char bit = 0x80;
	u_char oc = c - OFFSET;
	while (row < 12) {
		while (col < 8) {
			if (fuentes_8x12[oc][row] & bit)
				dibujarPixel(x + col, y + row);
			bit >>= 1;
			col++;
		}
		bit = 0x80;
		col = 0;
		row++;
	}
}

////////////////
// 8x12 fuentes
////////////////
void dibujarCharMdBkg(u_int x, u_int y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_char bit = 0x80;
	u_char oc = c - OFFSET;
	establecer_Area(x, y, x + 7, y + 11);
	while (row < 12) {
		while (col < 8) {
			if (fuentes_8x12[oc][row] & bit) {
				//foreground
				escribirDato(colorMSB);
				escribirDato(colorLSB);
			} else {
				//background
				escribirDato(bgColorMSB);
				escribirDato(bgColorLSB);
			}
			bit >>= 1;
			col++;
		}
		bit = 0x80;
		col = 0;
		row++;
	}

}

////////////////////////
// images
////////////////////////
void dibujarImagen8bit(u_int x, u_int y, u_int ancho, u_int largo,const u_char * dato, u_int color) {
	u_int xInicio=x,yInicio=y;
	establecerColor(color);
	u_int contAncho = 0, contLargo=0,LL=0,contL=0;
	u_int bit=0x01;
	while (contL < largo)
	{
		while(contAncho<ancho)
		{
			while(bit<=0x80)
			{
				if(*dato&bit)
					dibujarPixel(xInicio+contAncho, yInicio+contLargo);
				bit<<=1;
				contLargo++;
			}
			bit=0x01;
			contAncho++;
			dato++;
			contLargo=LL;
		}
		LL+=8;
		contLargo=LL;
		contL++;
		contAncho=0;
	}
}


void dibujarImagen8bitAmpliada(u_int x, u_int y, u_int ancho, u_int largo,const u_char * dato, u_int color,u_int Amplificacion) {
	u_int xInicio=x,yInicio=y;
	establecerColor(color);
	u_int contAncho = 0, contLargo=0,LL=0,contL=0;
	u_int bit=0x01, contAmpl=0,contAmpl1=0;
	while (contL < largo)
	{
		while(contAncho<ancho*Amplificacion)
		{
			while(contAmpl<Amplificacion)
			{
			while(bit<=0x80)
			{
				while(contAmpl1<Amplificacion)
				{
				if(*dato&bit)
					dibujarPixel(xInicio+contAncho, yInicio+contLargo);

				contLargo++;
				contAmpl1++;
				}
				contAmpl1=0;
				bit<<=1;
			}
			bit=0x01;
			contAncho++;
			contAmpl++;
			contLargo=LL;
			}
			dato++;
			contAmpl=0;
		}
		LL+=8*Amplificacion;
		contLargo=LL;
		contL++;
		contAncho=0;
	}
}

void dibujarImagen8bitInvertida(u_int x, u_int y, u_int ancho, u_int largo,const u_char * dato, u_int color) {
	u_int xInicio=x,yInicio=y;
	establecerColor(color);
	u_int contAncho = 0, contLargo=0,LL=0,contL=0;
	u_int bit=0x80;
	while (contL < largo)
	{
		while(contAncho<ancho)
		{
			while(bit>=0x01)
			{
				if(*dato&bit)
					dibujarPixel(xInicio+contAncho, yInicio+contLargo);
				bit>>=1;
				contLargo++;
			}
			bit=0x80;
			contAncho++;
			dato++;
			contLargo=LL;
		}
		LL+=8;
		contLargo=LL;
		contL++;
		contAncho=0;
	}
}

void dibujarImagen16bit(u_int x, u_int y, u_int ancho, u_int largo,const u_int * dato, u_int color) {
	u_int xInicio=x,yInicio=y;
	establecerColor(color);
	u_int contAncho = 0, contLargo=0,LL=0,contL=0;
	u_long bit=0x0001;
	while (contL < largo)
	{
		while(contAncho<ancho)
		{
			while(bit<=0x8000)
			{
				if(*dato&bit)
					dibujarPixel(xInicio+contAncho, yInicio+contLargo);
				bit<<=1;
				contLargo++;
			}
			bit=0x0001;
			contAncho++;
			dato++;
			contLargo=LL;
		}
		LL+=16;
		contLargo=LL;
		contL++;
		contAncho=0;
	}
}

void dibujarImagen16bitInvertida(u_int x, u_int y, u_int ancho, u_int largo,const u_int * dato, u_int color) {
	u_int xInicio=x,yInicio=y;
	establecerColor(color);
	u_int contAncho = 0, contLargo=0,LL=0,contL=0;
	u_long bit=0x8000;
	while (contL < largo)
	{
		while(contAncho<ancho)
		{
			while(bit>=1)
			{
				if(*dato&bit)
					dibujarPixel(xInicio+contAncho, yInicio+contLargo);
				bit>>=1;
				contLargo++;
			}
			bit=0x8000;
			contAncho++;
			dato++;
			contLargo=LL;
		}
		LL+=16;
		contLargo=LL;
		contL++;
		contAncho=0;
	}
}

void dibujarImagen32bit(u_int x, u_int y, u_int ancho, u_int largo,const u_long * dato, u_int color) {
	u_int xInicio=x,yInicio=y;
	establecerColor(color);
	u_int contAncho = 0, contLargo=0,LL=0,contL=0;
	u_longlong bit=0x00000001;
	while (contL < largo)
	{
		while(contAncho<ancho)
		{
			while(bit<=0x80000000)
			{
				if(*dato&bit)
					dibujarPixel(xInicio+contAncho, yInicio+contLargo);
				bit<<=1;
				contLargo++;
			}
			bit=0x00000001;
			contAncho++;
			dato++;
			contLargo=LL;
		}
		LL+=32;
		contLargo=LL;
		contL++;
		contAncho=0;
	}
}

void dibujarImagen32bitInvertida(u_int x, u_int y, u_int ancho, u_int largo,const u_long * dato, u_int color) {
	u_int xInicio=x,yInicio=y;
	establecerColor(color);
	u_int contAncho = 0, contLargo=0,LL=0,contL=0;
	u_longlong bit=0x80000000;
	while (contL < largo)
	{
		while(contAncho<ancho)
		{
			while(bit>=0x00000001)
			{
				if(*dato&bit)
					dibujarPixel(xInicio+contAncho, yInicio+contLargo);
				bit>>=1;
				contLargo++;
			}
			bit=0x80000000;
			contAncho++;
			dato++;
			contLargo=LL;
		}
		LL+=32;
		contLargo=LL;
		contL++;
		contAncho=0;
	}
}

void dibujarImagen64bit(u_int x, u_int y, u_int ancho, u_int largo,const u_longlong * dato, u_int color) {
	u_int xInicio=x,yInicio=y;
	establecerColor(color);
	u_int contAncho = 0, contLargo=0,LL=0,contL=0;
	u_int bit=0x0000000000000001;
	while (contL < largo)
	{
		while(contAncho<=ancho)
		{
			while(bit<0x8000000000000000)
			{
				if(*dato&bit)
					dibujarPixel(xInicio+contAncho, yInicio+contLargo);
				bit<<=1;
				contLargo++;
			}
			bit=0x0000000000000001;
			contAncho++;
			dato++;
			contLargo=LL;
		}
		LL+=64;
		contLargo=LL;
		contL++;
		contAncho=0;
	}
}


/*void dibujarBMP(u_int xPos, u_int yPos,u_int ancho, u_int alto, const u_char *ptr, u_char limite, u_int color ){
	establecerColor(color);
  u_int i, j;
  u_int puntoX, puntoY;
  if((ancho <= 0) ||              // bitmap is unexpectedly encoded in top-to-bottom pixel order
     ((ancho%2) != 0) ||           // must be even number of columns
     ((xPos + ancho) >obtener_Ancho()) || // right side cut off
     (yPos < (alto - 1)) ||      // top cut off
     (yPos > obtener_Largo()))           { // bottom cut off
    return;
  }
  if(limite > 14){
    limite = 14;             // only full 'on' turns pixel on
  }
  // bitmaps are encoded backwards, so start at the bottom left corner of the image
  puntoY = yPos;
  puntoX = xPos;
  j =0;                  		// byte 10 contains the offset where image data can be found
  for(i=1; i<=(ancho*(alto>>1)); i++){
    // the left pixel is in the upper 4 bits
    if(((ptr[j]>>4)&0xF) > limite)
    {
    	dibujarPixel(puntoX, puntoY);
    }
    else
    {
    	dibujarPixelBg(puntoX, puntoY);
    }
    puntoX ++;
    // the right pixel is in the lower 4 bits
    if((ptr[j]&0xF) > limite){
       	dibujarPixel(puntoX, puntoY);
    }
    else
    {
    	dibujarPixelBg(puntoX, puntoY);
    }
    puntoX++;
    j = j + 1;
    if((i%(ancho/2)) == 0){     // at the end of a row
        puntoY--;
      puntoX=xPos;
      // bitmaps are 32-bit word aligned
      //switch((ancho/2)%4){      // skip any padding
       // case 0: j = j + 0; break;
       // case 1: j = j + 3; break;
       // case 2: j = j + 2; break;
       // case 3: j = j + 1; break;
     // }
    }
  }
}*/

void dibujarBMP(u_int xPos, u_int yPos,u_int ancho, u_int alto, const u_char *ptr, u_char limite, u_int color,u_char Amplificacion ){
	establecerColor(color);
  u_int i, j;
  u_int puntoX, puntoY,contAmpl=0,contAmpl1=0,contX=0;
  if((ancho*Amplificacion <= 0) ||              // bitmap is unexpectedly encoded in top-to-bottom pixel order
     (((ancho*Amplificacion)%2) != 0) ||           // must be even number of columns
     ((xPos + ancho*Amplificacion) >obtener_Ancho()) || // right side cut off
     (yPos < (alto*Amplificacion - 1)) ||      // top cut off
     (yPos > obtener_Largo()))           { // bottom cut off
    return;
  }
  if(limite > 14){
    limite = 14;             // only full 'on' turns pixel on
  }
  // bitmaps are encoded backwards, so start at the bottom left corner of the image
  puntoY = yPos;
  puntoX = xPos;
  j =0;                  		// byte 10 contains the offset where image data can be found
  for(i=1; i<=(ancho*(alto>>1)); i++)
  {
    // the left pixel is in the upper 4 bits
	while(contAmpl1<Amplificacion)
	{
		while(contAmpl<Amplificacion)
		{
			if(((ptr[j]>>4)&0xF) > limite)
			{
				dibujarPixel(puntoX, puntoY);
			}
			else
			{
				dibujarPixelBg(puntoX, puntoY);
			}
			puntoX ++;
			contAmpl++;
		}
		contAmpl=0;
		while(contAmpl<Amplificacion)
		{
			// the right pixel is in the lower 4 bits
			if((ptr[j]&0xF) > limite){
				dibujarPixel(puntoX, puntoY);
			}
			else
			{
				dibujarPixelBg(puntoX, puntoY);
			}
			puntoX++;
			contAmpl++;
		}
		puntoX=xPos+contX;
		puntoY--;
		contAmpl=0;
		contAmpl1++;
  	}
	puntoY+=Amplificacion;
	contX+=2*Amplificacion;
	puntoX=xPos+contX;
	contAmpl1=0;
    j = j + 1;
	if((i%(ancho/2)) == 0)
	{     // at the end of a row
		puntoY-=Amplificacion;
		puntoX=xPos;
		contX=0;
	}
  }
}

// lut is used, ?0 means skip, sort of a mask?
void dibujarImagenLut(u_int x, u_int y, u_int w, u_int h, u_char * dato,
		u_int * lut) {

}

// each bit represents color, fg and bg colors are used, ?how about 0 as a mask?
void dibujarImagenMono(u_int x, u_int y, u_int w, u_int h, u_char * dato) {

}

////////////////////////
// shapes
////////////////////////

void dibujarLineaLogica(u_int x, u_int y, u_int longitud, u_char altura, const u_char * dato) {
	u_char ultimo = (*dato & 0x80);
	u_int contador = 0;
	while (contador < longitud)
	{
		u_char contadorBit = 0;
		u_char byte = *dato;
		while (contadorBit < 8 && contador < longitud)
		{
			if (ultimo == (byte & 0x80))
			{
				//dibujar pixel
				u_int h = (byte & 0x80) ? (altura + y) : y;
				dibujarPixel(x + contador, h);
			}
			else
			{
				// dibujar line
				if (byte & 0x80)
				{
					dibujarLinea(x + contador - 1, y, x + contador, y + altura);
				}
				else
				{
					dibujarLinea(x + contador - 1, y + altura, x + contador, y);
				}
			}
			ultimo = byte & 0x80;
			byte <<= 1;
			contadorBit++;
			contador++;
		}
		*dato++;
	}
}

void dibujarLinea(u_int xInicio, u_int yInicio, u_int xFin, u_int yFin) {

	u_int x0=xInicio, x1=xFin, y0=yInicio, y1=yFin;
	u_int d = 0;

	if (yInicio > yFin)
	{
		y0 = yFin;
		y1 = yInicio;
	}
	if (xInicio > xFin)
	{
		x0 = xFin;
		x1 = xInicio;
	}

	if (y0 == y1)
	{
		d = x1 - x0 + 1;
		establecer_Area(x0, y0, x1, y1);
		while (d-- > 0)
		{
			escribirDato(colorMSB);
			escribirDato(colorLSB);
		}

	}
	else
		if (x0 == x1)
		{
			d = y1 - y0 + 1;
			establecer_Area(x0, y0, x1, y1);
			while (d-- > 0)
			{
				escribirDato(colorMSB);
				escribirDato(colorLSB);
			}

		}
		else
		{
			int dx=x1-x0, dy=y1-y0;
			int sx, sy;

			if (xInicio < xFin)
				sx = 1;
			else
				sx = -1;
			if (yInicio < yFin)
				sy = 1;
			else
				sy = -1;

			int e1 = dx - dy;
			int e2;

			while (1)
			{
				dibujarPixel(xInicio, yInicio);
				if (xInicio == xFin && yInicio == yFin)
					break;
				e2 = (e1<<1);
				if (e2 > -dy)
				{
					e1 = e1 - dy;
					xInicio = xInicio + sx;
				}
				if (e2 < dx)
				{
					e1 = e1 + dx;
					yInicio = yInicio + sy;
				}
			}
		}
}

void dibujarRect(u_int xInicio, u_int yInicio, u_int xFin, u_int yFin) {

	dibujarLinea(xInicio, yInicio, xFin, yInicio);
	dibujarLinea(xInicio, yFin, xFin, yFin);
	dibujarLinea(xInicio, yInicio, xInicio, yFin);
	dibujarLinea(xFin, yInicio, xFin, yFin);
}

void dibujarCirculo(u_int x, u_int y, u_char radio) {
	int dx = radio;
	int dy = 0;
	int xCambio = 1 - (radio<<1);
	int yCambio = 1;
	int errorRadio = 0;
	while (dx >= dy) {
		dibujarPixel(x + dx, y + dy);
		dibujarPixel(x - dx, y + dy);
		dibujarPixel(x - dx, y - dy);
		dibujarPixel(x + dx, y - dy);
		dibujarPixel(x + dy, y + dx);
		dibujarPixel(x - dy, y + dx);
		dibujarPixel(x - dy, y - dx);
		dibujarPixel(x + dy, y - dx);
		dy++;
		errorRadio += yCambio;
		yCambio += 2;
		if ((errorRadio<<1) + xCambio > 0) {
			dx--;
			errorRadio += xCambio;
			xCambio += 2;
		}
	}
}

/////////////////////////
// fill
/////////////////////////

void rellenarRect(u_int xInicio, u_int yInicio, u_int xFin, u_int yFin) {
	establecer_Area(xInicio, yInicio, xFin, yFin);
	u_int x = xFin - xInicio + 1;
	u_int y = yFin - yInicio + 1;
	u_int z = y;
	while (x != 0) {
		while (z != 0) {
			escribirDato(colorMSB);
			escribirDato(colorLSB);
			z--;
		}
		z = y;
		x--;
	}
}

void rellenarCirculo(u_int x, u_int y, u_char radio) {
	int dx = radio;
	int dy = 0;
	int xCambio = 1 -  (radio<<1);
	int yCambio = 1;
	int errorRadio = 0;
	while (dx >= dy) {
		dibujarLinea(x + dy, y + dx, x - dy, y + dx);
		dibujarLinea(x - dy, y - dx, x + dy, y - dx);
		dibujarLinea(x - dx, y + dy, x + dx, y + dy);
		dibujarLinea(x - dx, y - dy, x + dx, y - dy);
		dy++;
		errorRadio += yCambio;
		yCambio += 2;
		if ((errorRadio<<1) + xCambio > 0) {
			dx--;
			errorRadio += xCambio;
			xCambio += 2;
		}
	}
}
