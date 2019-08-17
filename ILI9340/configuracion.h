/*
 * colores.h
 * configuracion para msp
 * Febrero 19, 2015
 *
 * RobG Modificado por Eduardo Alvarez Lopez
 */


//----------------------------------------------------------------------------------------//
//------------------------ Definiciones Condifuracion de Pantalla ------------------------//
//----------------------------------------------------------------------------------------//

#ifndef CONFIGURACION_H_		// comprueba sino se ha definido ya esta libreria para evitar errores
	#define CONFIGURACION_H_	//de compilacion y sino se ha definido lo define
	#include "msp430.h"
	//----------------------------	Descomentar la pantalla que se utilizara ----------------------//
	//---------------------------------------------------------------------------------------------//
		#define ILI9340	// QVGA 2.2" TFT SPI  240x320 sin touch

	//----------------------------	Definiciones para indicar plus de la pantalla ----------------------//
	//-------------------------------------------------------------------------------------------------//
		#define COMUNICACION_SPI	// descomentar si se utilizara protocolo SPI
		#define ORIENTACION 0		// 0 90 180 270 indicar la orientacion de la pantalla
		//#define PANTALLA_TOUCH	// descomentar si se tiene pantalla touch
		//#define MEMORY			// descomentar si se tiene la posibilidad de poner memoria

	#include "msp.h"
	#define UCBxTXBUF	UCB0TXBUF
	#define UCBxRXBUF	UCB0RXBUF
	#define UCBxSTAT	UCB0STAT
	#define UCBxCTL0	UCB0CTL0
	#define UCBxCTL1	UCB0CTL1
	#define UCBxBR0		UCB0BR0
	#define UCBxBR1		UCB0BR1

	#define PIN_SCLK_LCD	BIT5
	#define PUERTO_SCLK_LCD	P1

	#define PIN_MOSI_LCD 	BIT7
	#define PUERTO_MOSI_LCD	P1

	#define PIN_MISO_LCD 	BIT6
	#define PUERTO_MISO_LCD	P1

	#define PIN_CS_LCD 		BIT0
	#define PUERTO_CS_LCD 	P1

	#define PIN_DC_LCD 		BIT4
	#define PUERTO_DC_LCD 	P1



#endif /* CONFIG_H_ */
