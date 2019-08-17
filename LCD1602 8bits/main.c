#include <main.h>

void Conf_Reloj(void)
{
    DCOCTL=CALDCO_16MHZ;
    BCSCTL1=CALBC1_16MHZ; //conf para DCO=16MHz aprox 15.62 a 15.72MHz

    /*Seleccion de ACLK*/
    BCSCTL3&=~(LFXT1S_3);
    BCSCTL3|=LFXT1S_2;  //ACLK=VLOCLK
    /*Division de ACLK*/
    BCSCTL1&=~DIVA_3; //Division de ACLK/1;

    /*SEleccion de MCLK*/
    BCSCTL2&=~SELM_3; //MCLK=DCOCLK
    /*Division de MCLK*/
    BCSCTL2&=~DIVM_3; //Division de MCLK/1;

    /*Seleccion de SMCLK*/
    BCSCTL2&=~SELS; // 0=DCOCLK 1=ACLK
    /*Division de SMCLK*/
    BCSCTL2&=~DIVS_3; //Division de SMCLK/1;
}


void Conf_LCD1602(void)
{
    long Delay=0;
     /*Conf para P2.0=RS P2.1=RW P2.2=E*/
    P2DIR|=RS|RW|E;
    P2SEL&=~(RS|RW|E);
    P2SEL2&=~(RS|RW|E);
    P2REN&=~(RS|RW|E);
    P2OUT&=~(RS|RW|E);

    /*Conf para P1=Datos D0-D7*/
    P1DIR=0xFF;
    P1SEL=0;
    P1SEL2=0;
    P1REN=0;
    P1OUT=0;
    for(Delay=30000; Delay>0; Delay--);//20 ms aprox a 16MHz
   // LCD1602_Com(0x30);//algunas pantallas ocupan mandar 0x3X , 0x3X
   // LCD1602_Com(0x30);
   // LCD1602_Com(0x30);
   // LCD1602_Com(0x20);//0x3X y 0x2X al inicializar

    /*M8BIT o M4BIT,M2LINE o M1LINE, M5_8_Font o M5_11_Font */
    LCD1602_Com(M8BIT|M2LINE|M5_8_Font);

    /*ONDisp o OFFDisp, ONCursor o OFFCursor,ONBlink o OFFBLink*/
    LCD1602_Com(ONDisp|ONCursor|OFFBlink );

    LCD1602_Com(CLEAR); //limpia la pantalla
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz

    /*IAdd o DAdd*/
    LCD1602_Com(IncAdd);

    LCD1602_Com(HOME);//Manda cursor a home
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz
}


void LCD1602_Com(char comando)
{
    unsigned char Delay=0, valor=P1IN; //guarda el valor anterior de P1OUT

    PRW&=~RW; //RW para escritura 1=lectura 0=escritura
    PRS&=~RS; //RS 1=dato 0=comando

    P1OUT=comando; //manda el comando necesario
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

    P1OUT=valor; //restarua el valor anterior
}
void LCD1602_Dato(char dato)
{

   unsigned char Delay=0,valor=P1IN; //guarda el valor anterior de P1OUT

    PRW&=~RW; //RW para escritura 1=lectura0=escritura
    PRS|=RS; //RS 1=dato 0=comando

    P1OUT=dato;//manda el dato necesario
    LCD1602_E();//manda un pulso en el pin E (Enable)
    for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

    P1OUT=valor;    //restaura el valor anterior
}
void LCD1602_E(void)
{
    long Delay=0;
    PE|=E; //manda a 1 logico el bit E (Enable)
    /*Aprox 600ns a 16MHz*/
    for(Delay=8; Delay>0; Delay--); //retardo necesario para que la pantalla lea el dato
    PE&=~E;//manda a 0 logico E, completando el pulso
    /*Aprox 600ns a 16MHz*/
    for(Delay=8; Delay>0; Delay--);    //retardo final
}
void LCD1602_Pos(char columna, char fila)
{
    long direccion=0x80;
    direccion|=columna&0xF;
    direccion|=((fila&0x1)<<6);
    LCD1602_Com(direccion);
}

/**
 * main.c
 */
void main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Conf_Reloj();
	Conf_LCD1602();
	LCD1602_Dato('H'); //escribe H en 0,0. Cursor 0,1
    LCD1602_Com(M8BIT|M1LINE|M5_8_Font); //conf 8 bits 1 linea 5x8
	LCD1602_Dato('O');//escribe 'O' en 1,0. Cursor 0,2
	LCD1602_Com(M8BIT|M1LINE|M5_11_Font); //conf 8 bits 1 linea 5x11
	LCD1602_Dato('L'); //escribe 'L' en 2,0. Cursor 0,3
	LCD1602_Com(M8BIT|M2LINE|M5_8_Font);//conf 8 bits 2 lineas 5x8
	LCD1602_Dato('A'); //escribe 'A' en 3,0. Cursor 4,0
	LCD1602_Com(OFFDisp|ONCursor|OFFBlink );//Apaga Disp
	LCD1602_Dato(' ');//escribe ' ' en 4,0 pero no se observa. Cursor 5,0
	LCD1602_Com(ONDisp|OFFCursor|OFFBlink );//Prende Disp y apaga cursor
	LCD1602_Dato('M');//escribe 'M' en 5,0 se observa el cursor en 6,0
	LCD1602_Com(ONDisp|ONCursor|ONBlink );//Parapadea el cursor
	LCD1602_Dato('U');//escribe'U' en 6,0. Cursor en 7,0
	LCD1602_Com(ONDisp|ONCursor|OFFBlink );//deja de parpadear el cursor
	LCD1602_Dato('N');//escribe 'N' en 7,0. Cursor en 8,0
	LCD1602_Com(DecAdd);//cursor disminuirá
	LCD1602_Dato('D');//escribe 'D' en 8,0 , cursor en 7,0
    LCD1602_Dato('O');//escrbe 'O' en 7,0. Cursor en 6,0
	LCD1602_Com(IncAdd);//cursor aumentará
    LCD1602_Dato('I');//escribe 'I' en 6,0. Cursor en 7,0
    LCD1602_Dato('n');//escribe 'n' en 7,0. Cursor en 8,0
	LCD1602_Com(DecAdd|SDisp);//escribe la letra y luego mueve el disp a la derecha. Cursor no cambia
    LCD1602_Dato('D');//escribe 'D' en 8,0. Cursor 8,0. Desplaza disp a la der
    LCD1602_Dato('e');//escribe 'e' en 8,0. Cursor 8,0. Desplaza disp a la der
	LCD1602_Com(IncAdd|SDisp);//escribe la letra y luego mueve el disp a la izquierda. Cursor no cambia
    LCD1602_Dato('v');//escribe 'v' en 8,0. Cursor 8,0. Desplaza disp a la izq
    LCD1602_Dato('i');//escribe 'i' en 8,0. Cursor 8,0. Desplaza disp a la izq
    LCD1602_Com(DecAdd);//cursor disminuira
    LCD1602_Com(CRDisp);//cursor en 9,0
    LCD1602_Com(CRDisp);//cursor en 10,0
    LCD1602_Dato('c');//escribe 'c' en 10,0. cursor en 9,0
    LCD1602_Com(SRDisp);//desplaza disp a la derecha. cursor 10,0
    LCD1602_Com(SRDisp);//desplaza disp a la derecha. cursor 11,0
    LCD1602_Dato('e');//escribe 'e' en 11,0, cursor en 10,0
    LCD1602_Com(IncAdd);//cursor aumentará
    LCD1602_Pos(4,1);//mueve cursor a 4,0
	while(1)
	{

	}
}
