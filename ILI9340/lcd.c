/*
 * lcd.c
 * configuracion para msp
 * Febrero 19, 2015
 *
 * RobG modificado por Eduardo Alvarez Lopez
 */

#include "lcd.h"


#include "msp.h"
#include "configuracion.h"

	//----------------------------------------------------------------------------------------//
	//--------------------------------- Definicion de Funciones ------------------------------//
	//----------------------------------------------------------------------------------------//

u_char _orientacion = ORIENTACION_VERTICAL;

u_int obtener_Ancho() {
	if (_orientacion == ORIENTACION_VERTICAL || _orientacion == ORIENTACION_VERTICAL_INVERTIDO)
		return PIXEL_ANCHO;
	else
		return PIXEL_LARGO;
}

u_int obtener_Largo() {
	if (_orientacion == ORIENTACION_VERTICAL || _orientacion == ORIENTACION_VERTICAL_INVERTIDO)
		return PIXEL_LARGO;
	else
		return PIXEL_ANCHO;
}

void establecer_Area(u_int xInicio, u_int yInicio, u_int xTermino, u_int yTermino) {

	u_char yInicioMSB = yInicio >> 8;
	u_char yTerminoMSB = yTermino >> 8;
	u_char xInicioMSB = xInicio >> 8;
	u_char xTerminoMSB = xTermino >> 8;
	escribirComando(CASET);
	escribirDato(xInicioMSB);
	escribirDato(xInicio);

	escribirDato(xTerminoMSB);
	escribirDato(xTermino);

	escribirComando(PASET);
	escribirDato(yInicioMSB);
	escribirDato(yInicio);

	escribirDato(yTerminoMSB);
	escribirDato(yTermino);

	escribirComando(RAMWR);

}

void init_LCD()
{

		escribirComando(SWRESET);
		retardo(25);
		escribirComando(DINVOFF);

		escribirComando(WRDISBV);
		escribirDato(0xFF);

		escribirComando(WRCTRLD);
		escribirDato(0x2C);

		escribirComando(PWCTRL1);
		escribirDato(V330);
		escribirDato(RV300);

		escribirComando(PWCTRL2);
		escribirDato(0);

		escribirComando(PWCTRL3);
		escribirDato(OSC1);
		escribirComando(PWCTRL4);
		escribirDato(OSC1);
		escribirComando(PWCTRL5);
		escribirDato(OSC1);

		escribirComando(VMCTRL1);
		escribirDato(V280);
		escribirDato(MV150);
		escribirComando(VMCTRL2	);
		escribirDato(OFFSET10);

		establecer_Orientacion(ORIENTACION_VERTICAL);

		escribirComando(PIXSET);
		escribirDato(bits16_16);

		escribirComando(FRMCTR1	);
		escribirDato(DOSC1);
		escribirDato(FRAME_RATE_119);

		escribirComando(DISCTRL);
		escribirDato(0x08);
		escribirDato(0x82);
		escribirDato(0x27);

		escribirComando(GAMSET);
		escribirDato(CURVA_1);

		escribirComando(PGAMCTRL);	//configuracion de gamma obtenida de internet
		const u_char gamma1[] = { 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1,
				0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00 };
		u_char c = 0;
		while (c < 16) {
			escribirDato(gamma1[c]);
			c++;
		}

		escribirComando(NGAMCTRL);	//configuracion de gamma obtenida de internet
		const u_char gamma2[] = { 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1,
				0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F };
		c = 0;
		while (c < 16) {
			escribirDato(gamma2[c]);
			c++;
		}

		escribirComando(SLPOUT);
		retardo(25);
		escribirComando(DISPON);
		escribirComando(RAMWR);

	}

	void establecer_Orientacion(u_char orientacion) {

		escribirComando(MADCTL);

		switch (orientacion) {
		case 1:
			escribirDato(0xE8);
			_orientacion = ORIENTACION_HORIZONTAL;
			break;
		case 2:
			escribirDato(0x88);
			_orientacion = ORIENTACION_VERTICAL_INVERTIDO;
			break;
		case 3:
			escribirDato(0x28);
			_orientacion = ORIENTACION_HORIZONTAL_INVERTIDO;
			break;
		default:
			escribirDato(0x48);
			_orientacion = ORIENTACION_VERTICAL;
		}
	}


