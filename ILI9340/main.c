/*
 * main.c
 *
 *  Created on: May 6, 2013
 *      Author: RobG
 */
#include "intrinsics.h"
#include "graficos.h"
#include "lcd.h"
#include "colores.h"
#include "definicionesvar.h"
#include "configuracion.h"
#include "spaceinvader.h"
//#include "fuentes.h"

extern const u_char fuentes_5x7[][5];
extern const u_char fuentes_8x12[95][12];
extern const u_int fuentes_11x16[95][11];
u_char Datos[6];
void main(void) {

	WDTCTL = WDTPW + WDTHOLD; // disable WDT
	init_Reloj();
	init_TimerA();
	init_MSP430_LCD();
	init_LCD();
	limpiarPantalla(COLOR_WHITE);
	establecer_Orientacion(ORIENTACION_HORIZONTAL);
	dibujarBMP((obtener_Ancho()>>1)-(PLAYERW<<1),obtener_Largo(),PLAYERW,PLAYERH,PlayerShip0,0,COLOR_GREEN,4);
	dibujarBMP((obtener_Ancho()>>1)-(BUNKERW<<1),obtener_Largo()-(PLAYERH<<2)-20,BUNKERW,BUNKERH,Bunker0,0,COLOR_PURPLE,4);

	dibujarBMP(0,(ENEMY10H)<<2,ENEMY10W,ENEMY10H,SmallEnemy10PointA,4,COLOR_BLUE,4);
	dibujarBMP(ENEMY10W<<2,(ENEMY10H)<<2,ENEMY10W,ENEMY10H,SmallEnemy20PointA,4,COLOR_BLUE,4);
	dibujarBMP(ENEMY10W<<3,(ENEMY10H)<<2,ENEMY10W,ENEMY10H,SmallEnemy20PointA,4,COLOR_BLUE,4);
	dibujarBMP(12*ENEMY10W,(ENEMY10H)<<2,ENEMY10W,ENEMY10H,SmallEnemy30PointA,4,COLOR_BLUE,4);
	dibujarBMP(ENEMY10W<<4,(ENEMY10H)<<2,ENEMY10W,ENEMY10H,SmallEnemy30PointA,4,COLOR_BLUE,4);
	dibujarImagen8bitAmpliada(80U,140U,5,1,&fuentes_5x7[33][0],COLOR_GREEN,2);
	dibujarCadena(95, 140U, FUENTE_GRANDE_BACK,"A");
	dibujarCadena(80, 160U, FUENTE_GRANDE_BACK,"A");
	while (1) {

		establecerColor(COLOR_RED);
		establecerColorFondo(COLOR_GREEN);
		dibujarCadena(80, 55, FUENTE_MEDIANA_BACK, "Maestria En Ciencias");
		establecerColor(COLOR_GREEN);
		establecerColorFondo(COLOR_GREEN);
		dibujarCadena(97, 80, FUENTE_PEQUENA_BACK, "LaunchPad MSP430G2553");
		establecerColor(COLOR_BLUE);
		establecerColorFondo(COLOR_GREEN);
		dibujarCadena(76, 95, FUENTE_MEDIANA_BACK, "Eduardo Alvarez Lopez");


	}
}


		//rellenarRect(x - d - getO(), y - d - getO(), x + d + getO(),
			//	y + d + getO());

		//dibujarRect(x - d - getO(), y - d - getO(), x + d + getO(),
		//		y + d + getO());

		//rellenarCirculo(x, y, d + getO());

		//dibujarLinea(x - d - getO(), y + d + getO(), x + d + getO(),
		//		y - d - getO());

		//dibujarCirculo(x, y, d + getO());

