/*
 * msp.h
 * configuracion para msp
 * Febrero 19, 2015
 *
 * RobG Modificado porEduardo Alvarez Lopez
 */

#ifndef MSP_H_
	#define MSP_H_

#include "definicionesvar.h"
#include "configuracion.h"
#include "msp430.h"
#include "intrinsics.h"

//----------------------------------------------------------------------------------------//
//--------------------------------- Prototipos de Funciones ------------------------------//
//----------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------//
//--------------------------------- Inicializaciones -------------------------------------//
void init_MSP430_LCD();					//Inicializa los pines de la LCD, tambien los de SD card
void init_TimerA();
void init_Reloj();						//inicializa el reloj a 16MHz

//----------------------------------------------------------------------------------------------------//
//--------------------------------- Metodo Basico de Transmision -------------------------------------//
void escribirDato(u_char dato);			//transmite por SPI un dato
void escribirComando(u_char comando);	//transmite por SPI un comando
void retardo(u_long x1ms);				//retardo por 1 milisegundo
u_char leerDato(void);
void leerDatos(u_char comando, u_char Datos, u_char Arreglo[]);
//-----------------------------------------------------------------------------------------------//
//--------------------------------- Abrevaciones de Drivers -------------------------------------//
#define puertoO(p)		p ## OUT	//abreviacion para seleccionar el puerto indicado (PxOUT)
#define puertoOut(p) 	puertoO(p)
#define puertoD(p)  	p ## DIR	//abreviacion para seleccionar el puerto indicado (PxDIR)
#define puertoDir(p) 	puertoD(p)
#define puertoI(p)   	p ## IN		//abreviacion para seleccionar el puerto indicado (PxIN)
#define puertoIn(p) 	puertoI(p)
#define puertoS(p)  	p ## SEL	//abreviacion para seleccionar el puerto indicado (PxSEL)
#define puertoSel(p)	puertoS(p)
#define puertoR(p) 	 	p ## REN	//abreviacion para seleccionar el puerto indicado (PxREN)
#define puertoRen(p) 	puertoR(p)
#define puertoS2(p)  	p##SEL2		//abreviacion para seleccionar el puerto indicado (PxSEL2)
#define puertoSel2(p) 	puertoS2(p)




//-----------------------------------------------------------------------------------------------------//
//--------------------------------- Nombre del Puerto y Direccion -------------------------------------//
//---------CLK--------// (salida)

#define LCD_SCLK_OUT	 puertoOut( PUERTO_SCLK_LCD )
#define LCD_SCLK_DIR	 puertoDir(PUERTO_SCLK_LCD)
#define LCD_SCLK_BAJO	 LCD_SCLK_OUT&=~PIN_SCLK_LCD
#define LCD_SCLK_ALTO	 LCd_SCLK_OUT|=PIN_SCLK_LCD
#define LCD_RELOJ		 LCD_SCLK_ALTO;LCD_SCLK_BAJO

//---------MOSI------// (salida)

#define OUT_MOSI_LCD	 puertoOut(PUERTO_MOSI_LCD)
#define DIR_MOSI_LCD	 puertoDir(PUERTO_MOSI_LCD)

#define ALTO_MOSI_LCD	 OUT_MOSI_LCD|=PIN_MOSI_LCD
#define BAJO_MOSI_LCD	 OUT_MOSI_LCD&=~PIN_MOSI_LCD
#define DIR_MOSI_LCD_O	 DIR_MOSI_LCD|=PIN_MOSI_LCD
#define DIR_MOSI_LCD_I	 DIR_MOSI_LCD&=~PIN_MOSI_LCD

//--------MISO-------//(entrada)

#define OUT_MISO_LCD	 puertoOut(PUERTO_MISO_LCD)
#define DIR_MISO_LCD	 puertoDir(PUERTO_MISO_LCD)
#define IN_MISO_LCD		 puertoIn(PUERTO_MISO_LCD)

#define LEER_MISO_LCD  IN_MISO_LCD&PIN_MISO_LCD

//--------CS---------//(salida)

#define OUT_CS_LCD	 puertoOut(PUERTO_CS_LCD)
#define DIR_CS_LCD	 puertoDir(PUERTO_CS_LCD)

#define ACTIVAR_CS_LCD		 OUT_CS_LCD&=~PIN_CS_LCD
#define DESACTIVAR_CS_LCD	 OUT_CS_LCD|=PIN_CS_LCD

//--------DC---------//(salida)

#define OUT_DC_LCD	 puertoOut(PUERTO_DC_LCD)
#define DIR_DC_LCD	 puertoDir(PUERTO_DC_LCD)

#define BAJO_DC_LCD	 OUT_DC_LCD&=~PIN_DC_LCD
#define ALTO_DC_LCD	 OUT_DC_LCD|=PIN_DC_LCD


//------SEL SPI------//(activar)
#define SEL_SPI_LCD  puertoSel(PUERTO_SCLK_LCD)
#define SEL2_SPI_LCD  puertoSel2(PUERTO_SCLK_LCD)
#define DESABILITA_SPI_LCD	 SEL_SPI_LCD&=~(PIN_SCLK_LCD|PIN_MOSI_LCD|PIN_MISO_LCD);SEL2_SPI_LCD&=~(PIN_SCLK_LCD|PIN_MOSI_LCD|PIN_MISO_LCD)
#define HABILITA_SPI_LCD	 SEL_SPI_LCD|=(PIN_SCLK_LCD|PIN_MOSI_LCD|PIN_MISO_LCD);SEL2_SPI_LCD|=(PIN_SCLK_LCD|PIN_MOSI_LCD|PIN_MISO_LCD)

#endif /* MSP_H_ */

