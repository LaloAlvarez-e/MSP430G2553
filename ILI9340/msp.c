/*
 * msp.c
 * configuracion para msp
 * Febrero 19, 2015
 *
 * RobG modificado porEduardo Alvarez Lopez
 */

#include "msp.h"
#include "lcd.h"
#include "configuracion.h"
#include "msp430.h"

//---------------------------------//
// MSP430 Inicializacion Puerto----//
void init_MSP430_LCD(void)
{
	LCD_SCLK_OUT	|= PIN_SCLK_LCD;	//confiugra los pines del SPI
	LCD_SCLK_DIR 	|= PIN_SCLK_LCD;
	OUT_CS_LCD 		|= PIN_CS_LCD;
	DIR_CS_LCD 		|= PIN_CS_LCD;
	OUT_MOSI_LCD 	|= PIN_MOSI_LCD;
	DIR_MOSI_LCD 	|= PIN_MOSI_LCD;
	OUT_DC_LCD 		|= PIN_DC_LCD;
	DIR_DC_LCD 		|= PIN_DC_LCD;

	HABILITA_SPI_LCD;
	UCBxCTL0	=  (UCCKPH|UCMSB|UCMST|UCSYNC); // 3-pines, 8-bits SPI maestro
	UCBxCTL1 	|= UCSSEL_2;// SMCLK
	UCBxBR0 	|= 0x01;// 1:1
	UCBxBR1 	=  0;
	UCBxCTL1 	&= ~UCSWRST;// limpia SW
//	configure SRAM/EEPROM pins		//pines para memoria
//	SRAM_CS_OUT 	|= SRAM_CS_PIN
//	SRAM_CS_DIR 	|= SRAM_CS_PIN
//	SRAM_HOLD_OUT 	|= SRAM_HOLD_PIN;
//	SRAM_HOLD_DIR 	|= SRAM_HOLD_PIN;
//	EEPROM_CS_OUT 	|= EEPROM_CS_PIN;
//	EEPROM_CS_DIR 	|= EEPROM_CS_PIN;
//	EEPROM_HOLD_OUT |= EEPROM_HOLD_PIN;
//	EEPROM_HOLD_DIR |= EEPROM_HOLD_PIN;
///////////////////////////
}

//------------------------------------------------//
//--------------- configuracion XT ---------------//


void init_Reloj() {
	BCSCTL1 = CALBC1_16MHZ; // 16MHz clock
	DCOCTL = CALDCO_16MHZ;
}

void init_TimerA()
{
	TACTL=0x210;
}

//--------------------------------------------//
//-------------Escritura y Retardo------------//

void escribirDato(u_char dato) {
	ACTIVAR_CS_LCD; //activa el chip select
	ALTO_DC_LCD;	//Indica que es dato
	UCBxTXBUF = dato;
	while (UCBxSTAT & UCBUSY);
	DESACTIVAR_CS_LCD;
}

void escribirComando(u_char comando) {
	ACTIVAR_CS_LCD;	//activa el chi select
	BAJO_DC_LCD;	//Indica que es comando
	UCBxTXBUF = comando;
	while (UCBxSTAT & UCBUSY);
	DESACTIVAR_CS_LCD;
}

void leerDatos(u_char comando, u_char Datos, u_char* Arreglo)
{
	u_char i=0;
	escribirComando(comando);
	for(i=0;i<Datos;i++)
	{

		*(Arreglo+i)= leerDato();
	}

}

void empezarLeerDato(u_char comando) {
	ACTIVAR_CS_LCD;
	BAJO_DC_LCD;
	UCBxBR0 = 0x03;
	UCBxTXBUF = comando;
	while (UCBxSTAT & UCBUSY);
}

u_char leerDato() {
	ACTIVAR_CS_LCD;
	ALTO_DC_LCD;
	u_char dato = 0;
	UCBxTXBUF = 0;
	while (UCBxSTAT & UCBUSY);
	dato = UCBxRXBUF;
	UCBxBR0 = 0x01;
	DESACTIVAR_CS_LCD;
	return dato;
}




void retardo(u_long x1ms) {
	long i=x1ms;
	for(i=x1ms; i>=0;i--)
	{
		TACCR0=16000;
		while ((TACTL&1)==0);
		TACTL&=~1;
	}
}

