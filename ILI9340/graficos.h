/*
 * graficos.c
 * configuracion para msp
 * Febrero 19, 2015
 *
 * RobG modificado porEduardo Alvarez Lopez
 */
#ifndef GRAFICOS_H_
	#define GRAFICOS_H_

	#include "definicionesvar.h"

		//----------------------------	Definiciones para indicar tamaño de fuente ------------------------//
		//-------------------------------------------------------------------------------------------------//

	#define FUENTE_PEQUENA		0
	#define FUENTE_MEDIANA		1
	#define FUENTE_GRANDE		2
	#define FUENTE_PEQUENA_BACK	3
	#define FUENTE_MEDIANA_BACK	4
	#define FUENTE_GRANDE_BACK	5

	void establecerColor(u_int color);
	void establecerColorFondo(u_int color);

	void limpiarPantalla(u_int Color);
	void dibujarPixel(u_int x, u_int y);
	void dibujarPixelBg(u_int x, u_int y);


	void dibujarCadena(u_int x, u_int y, char fuenteT, char *cadena);

	void dibujarCharLg(u_int x, u_int y, char c);
	void dibujarCharMd(u_int x, u_int y, char c);
	void dibujarCharSm(u_int x, u_int y, char c);
	void dibujarCharLgBkg(u_int x, u_int y, char c);
	void dibujarCharMdBkg(u_int x, u_int y, char c);
	void dibujarCharSmBkg(u_int x, u_int y, char c);





	void dibujarLinea(u_int xInicio, u_int yInicio, u_int xFinal, u_int yFinal);
	void dibujarRect(u_int xInicio, u_int yInicio, u_int xFinal, u_int yFinal);
	void dibujarCirculo(u_int x, u_int y, u_char radio);

	void rellenarRect(u_int xInicio, u_int yInicio, u_int xFinal, u_int yFinal);
	void rellenarCirculo(u_int x, u_int y, u_char radio);

	void dibujarLineaLogica(u_int x, u_int y, u_int longitud, u_char altura,const u_char * dato);

	void dibujarImagen8bit(u_int x, u_int y, u_int ancho, u_int altura,const u_char * dato, u_int color);
	void dibujarImagen16bit(u_int x, u_int y, u_int ancho, u_int altura,const u_int * dato, u_int color);
	void dibujarImagen32bit(u_int x, u_int y, u_int ancho, u_int altura,const u_long * dato, u_int color);
	void dibujarImagen64bit(u_int x, u_int y, u_int ancho, u_int altura,const u_longlong * dato, u_int color);
	void dibujarImagen8bitInvertida(u_int x, u_int y, u_int ancho, u_int altura,const u_char * dato, u_int color);
	void dibujarImagen16bitInvertida(u_int x, u_int y, u_int ancho, u_int altura,const u_int * dato, u_int color);
	void dibujarImagen32bitInvertida(u_int x, u_int y, u_int ancho, u_int altura,const u_long * dato, u_int color);
	void dibujarImagen8bitAmpliada(u_int x, u_int y, u_int ancho, u_int largo,const u_char * dato, u_int color,u_int Amplificacion) ;
	void dibujarImagenLut(u_int x, u_int y, u_int ancho, u_int altura, u_char * dato, u_int * lut);
	void dibujarImagenMono(u_int x, u_int y, u_int ancho, u_int altura, u_char * dato);

	void dibujarBMP(u_int xPos, u_int yPos,u_int ancho, u_int alto, const u_char *ptr, u_char limite, u_int color,u_char Amplificacion );

#endif /* GRAFICOS_H_ */
