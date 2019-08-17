/*
 * lcd.h
 * configuracion para msp
 * Febrero 19, 2015
 *
 * RobG modificado porEduardo Alvarez Lopez
 */
#ifndef LCD_H_
	#define LCD_H_

	#include "definicionesvar.h"
	#include "configuracion.h"
	//----------------------------------------------------------------------------------------//
	//--------------------------------- Definicion de Longitudes ------------------------------//
	//----------------------------------------------------------------------------------------//

	#define PIXEL_LARGO 320
	#define PIXEL_ANCHO 240
	#define OFFSET_LARGO 0
	#define OFFSET_ANCHO 0

	#define COMANDO 0
	#define DATO 1

	//----------------------------------------------------------------------------------------//
	//--------------------------------- Prototipo de Funciones - ------------------------------//
	//----------------------------------------------------------------------------------------//
	void init_LCD();
	void establecer_Area(u_int xInicio, u_int yInicio, u_int xTermino, u_int yTermino);
	u_int obtener_Ancho();
	u_int obtener_Largo();
	void establecer_Orientacion(u_char orientacion);

	//----------------------------	Orientacion ----------------------//
	//----------------------------------------------------------------//
	#define ORIENTACION_VERTICAL 0
	#define ORIENTACION_HORIZONTAL 1
	#define ORIENTACION_VERTICAL_INVERTIDO 2
	#define ORIENTACION_HORIZONTAL_INVERTIDO 3

	//----------------------------	Comandos ----------------------//
	//-------------------------------------------------------------//
	#define NOP		    0x00 //no operacion (no regresa, no recibe comandos,recomendado usar despues de RAMWR o RAMRD)
	#define SWRESET		0x01 //Sofware reset (no regresa, no recibe comandos , esperar 5ms, 120ms si se quiere despertar, cuando se despierta no mandar el comando)
	#define	BSTRON		0x03
	#define RDIDIF		0x04 //Read display identification Informaction (regresa 4 parametros, dummy, fabricante,driver version, driver)
	#define RDDST		0x09 //Read Display Status (regresa 6 parametros, en ellos existen la informacnon de 32 configuraciones)
		#define RDDPM	0x0A //Read Display Power Mode(regresa 2 parametros, dummy, informacion de la alimentacion)
		#define RDDMADCTL	0x0B //Read Display MADCTL( regresa 2 parametros, dummy, informacion de control)
		#define RDDCOLMOD	0x0C //Read Display Pixel Format (regresa 2 parametros, dummy, el formato de bits)
		#define RDDIM		0x0D //Read Display Image Format (regresa 2 parametros, dummy, curva de gamma)
		#define RDDSM		0x0E //Read Display Signal Mode (regresa 2 parametros, dummy, Estado de la señal)
	#define SPLIN     	0x10 //Enter Sleep Mode (entra en modo de bajo consumo)
	#define	SLPOUT		0x11 // Sleep Out (sale del modo de bajo consumo esperar 129ms)
	#define PTLON		0x12 //Partial Mode ON (ventana definida por el comando 0x30, para salir entrar en el comando 0x13)
	#define	NORON		0x13 //Normal Display Mode ON
	#define	DINVOFF		0x20 //Display Inversion OFF
	#define DINVON     	0x21 //Display Inversion ON
	#define	SETCON		0x25
	#define DISPOFF     0x28 //Display OFF (no manda caracteres)
	#define DISPON      0x29 //Display ON (deshabilita Display OFF)
	#define CASET		0x2A //Column Address Set (recibe 4 comandos, el primero y segundo el inicio de X, el tercero y cuarto el inicio de X)
	#define PASET		0x2B //Page Address Set (recibe 4 comandos, el primero y segundo el inicio de Y, el tercero y cuarto el inicio de Y)
	#define RAMWR		0x2C //Memory Write (se puede escribir en memoria los datos necesarios)
	#define RGBSET	    0x2D //Color Set (recibe 128 parametros cada tercio es apra cada color)
	#define RAMRD		0x2E //Memory Read (transfiere datos del contorlador al MCU
	#define PLTAR		0x30 //Partial Area (define en la fila que inicia y termina  el area parcial)
	#define VSCRDE      0x33 //Vertical Scrolling Definition
	#define TEOFF		0x34 //earing Effect Line OFF
	#define TEON		0x35 //earing Effect Line ON

	#define VSCRSADD	0x37 //Vertical Scrolling Start Address (recibe 2 parametros)
	#define IDMOFF		0x38 //Idle Mode OFF
	#define IDMON		0x39 //Idle Mode ON

	#define Write_Memory_Continue 0x3C //Write_Memory_Continue
	#define Read_Memory_Continue  0x3D //Read_Memory_Continue

	#define WRDISBV		0x51 //Write Display Brightness
	#define WRCTRLD		0x53 //Write CTRL Display

	#define DISCTR      0xB9
	#define DOR			0xBA
	#define	EC			0xC0
	#define RDID1		0xDA
	#define RDID2		0xDB
	#define RDID3		0xDC
#define RDID4		0xD3
	#define ST7735_GMCTRP1 0xE0
	#define ST7735_GMCTRN1 0xE1

	#define SETOSC		0xB0
	#define SETPWCTR4	0xB4
	#define SETPWCTR5	0xB5
	#define SETEXTCMD	0xC1
	#define SETGAMMAP	0xC2
	#define SETGAMMAN	0xC3

	#define GAMSET			0x26 //Gamma Set (se envia un parametro, 01,02,04,08 para eleccion de alguna curva)
		#define CURVA_1 1
		#define CURVA_2 2
		#define CURVA_3 4
		#define CURVA_4 8
	#define	MADCTL			0x36 //Memory Access Control (recibe 1 parametro)
	#define PIXSET			0x3A //COLMOD: Pixel Format Set (recibe 1 parametro)

		#define bits16_16	0x55
		#define bits16_18	0x56
		#define bits18_16	0x65
		#define bits18_18	0x66

	#define FRMCTR1			0xB1 //Frame Rate Control (In Normal Mode/Full Colors)

		#define DOSC1 0
		#define DOSC2 1
		#define DOSC4 2
		#define DOSC8 3
		#define FRAME_RATE_119	0x10
		#define FRAME_RATE_112	0x11
		#define FRAME_RATE_106	0x12
		#define FRAME_RATE_100	0x13
		#define FRAME_RATE_95	0x14
		#define FRAME_RATE_90	0x15
		#define FRAME_RATE_86	0x16
		#define FRAME_RATE_83	0x17
		#define FRAME_RATE_79	0x18
		#define FRAME_RATE_76	0x19
		#define FRAME_RATE_73	0x1A
		#define FRAME_RATE_70	0x1B
		#define FRAME_RATE_68	0x1C
		#define FRAME_RATE_65	0x1D
		#define FRAME_RATE_63	0x1E
		#define FRAME_RATE_61	0x1F

	#define ILIFCIM			0xB2
	#define ILIFCPM			0xB3
	#define DISCTRL			0xB6 //Display Function Control (recibe 4 parametros)
	#define PWCTRL1			0xC0 //Power Control 1 (recibe 2 parametros, nivel de VDD y
		#define V460		0x23 //4.6v
		#define V330		0x09 //3.3v
		#define V500		0x2B //5.0V
		#define RV300		0x0E //regulador 3.0v
	#define PWCTRL2			0xC1 //Power Control 2 (recibe un parametro)
	#define PWCTRL3			0xC2 //Power Control 3 (recibe un parametro)
	#define PWCTRL4			0xC3 //Power Control 4 (recibe un parametro)
	#define PWCTRL5			0xC4 //Power Control 5 (recibe un parametro)
		#define OSC1		0x80 //osc/1
		#define OSC2		0x90 //osc/2
		#define OSC4		0xA2 //osc/4
		#define OSC8		0xB3 //osc/8
		#define OSC16		0xC4 //osc/16
		#define OSC32		0xD5 //osc/32
		#define OSC64		0xD6 //osc/64
	#define VMCTRL1			0xC5 //VCOM Control 1
		#define V425		0x3E //4.25v
		#define V450		0x48 //4.5v
		#define V280		0x40 //2.8v
		#define MV150		0x28 //-1.5v
	#define VMCTRL2			0xC7 //VCOM Control 2
		#define OFFSET10	0x86 //offset +-10
	#define PGAMCTRL		0xE0 //Positive Gamma Correction
	#define NGAMCTRL		0xE1 //Negative Gamma Correction
	#define IFCTL			0xF6 //Interface Control

#endif /* LCD_H_ */
