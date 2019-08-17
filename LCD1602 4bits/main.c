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
    P1OUT|=D4|D5;//configurar lapantalla a 8 bits
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=10000; Delay>0; Delay--);//7 ms aprox a 16MHz
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=500; Delay>0; Delay--);//100 us aprox a 16MHz
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=10000; Delay>0; Delay--);//7 ms aprox a 16MHz
    //primer comando 0x20 configuracion a 4 bits
    P1OUT&=~D4; //conf para los pines D4-7 = P1.4-7
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

    /*M8BIT o M4BIT,M2LINE o M1LINE, M5_8_Font o M5_11_Font */
    LCD1602_Com(M4BIT|M2LINE|M5_8_Font);

    /*ONDisp o OFFDisp, ONCursor o OFFCursor,ONBlink o OFFBLink*/
    LCD1602_Com(ONDisp|OFFCursor|OFFBlink );

    LCD1602_Com(CLEAR); //limpia la pantalla
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz

    /*IAdd o DAdd*/
    LCD1602_Com(IncAdd);

    LCD1602_Com(HOME);//Manda cursor a home
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz
}


void LCD1602_Com(char comando)
{
    /*D4-7=P1.4-7*/
    unsigned char Delay=0;
    unsigned char valor=P1IN&0xF0; //guarda el valor anterior de P1OUT
    PRW&=~RW; //RW para escritura 1=lectura 0=escritura
    PRS&=~RS; //RS 1=dato 0=comando

    P1OUT&=~0xF0; //reinicia los pines P1.4-7
    P1OUT|=(comando)&0xF0; //manda la parte alta del comando
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    P1OUT&=~0xF0; //reinicia los pines P1.4-7
    P1OUT|=(comando<<4)&0xF0; //manda la parte baja del comando
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

    P1OUT&=~0xF0; //reinicia los la parte alta
    P1OUT|=valor; //restaura el valor anterior

    /*D4-7=P1.0-3*/
    /*
    unsigned char Delay=0;
    unsigned char valor=P1IN&0xF; //guarda el valor anterior de la parte baja de P1OUT
    PRW&=~RW; //RW para escritura 1=lectura 0=escritura
    PRS&=~RS; //RS 1=dato 0=comando

    P1OUT&=~0xF; //reinicia los pines P1.0-3
    P1OUT|=(comando>>4)&0xF; //manda la parte alta del comando
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    P1OUT&=~0xF; //reinicia los pines P1.0-3
    P1OUT|=(comando)&0xF; //manda la parte baja del comando
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

    P1OUT&=~0xF; //reinicia la parte baja del P1
    P1OUT|=valor; //restaura el valor anterior
    */
}
void LCD1602_Dato(char dato)
{
   /* D4-7=P1.4-7*/
   unsigned char Delay=0;
   unsigned char valor=P1IN&0xF0; //guarda el valor anterior de P1OUT

    PRW&=~RW; //RW para escritura 1=lectura0=escritura
    PRS|=RS; //RS 1=dato 0=comando

    P1OUT&=~0xF0; //reinicia los valores de P1.4-7
    P1OUT|=(dato)&0xF0; //manda la parte alta del dato
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    P1OUT&=~0xF0;//reinicia los valores de P1.4-7
    P1OUT|=(dato<<4)&0xF0;  //manda la parte baja del dato
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

    P1OUT&=~0xF0;//reinicia los valores de P1.4-7
    P1OUT|=valor; //restarua el valor anterior

    /*D4-7 =P1.0-3*/
    /*
    unsigned char Delay=0;
    unsigned char valor=P1IN&0xF; //guarda el valor anterior de P1OUT

     PRW&=~RW; //RW para escritura 1=lectura0=escritura
     PRS|=RS; //RS 1=dato 0=comando

     P1OUT&=~0xF; //reinicia P1.0-3
     P1OUT|=(dato>>4)&0xF; //manda el comando necesario
     LCD1602_E(); //manda un pulso en el pin E (Enable)
     P1OUT&=~0xF; //reinicia P1.0-3
     P1OUT|=(dato)&0xF; //manda el comando necesario
     LCD1602_E(); //manda un pulso en el pin E (Enable)
     for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

     P1OUT&=~0xF; //reinicia P1.0-3
     P1OUT|=valor; //restarua el valor anterior
*/
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

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
    //4 bits , 2 lineas, 5x8 puntos, incr cursor
    Conf_LCD1602();//configuracion de la pantall LCD1602
    LCD1602_Pos(4,1);
    LCD1602_Dato('I'); //escribe H en 0,0. Cursor 0,1
    LCD1602_Dato('n');
    LCD1602_Dato('D'); //escribe H en 0,0. Cursor 0,1
    LCD1602_Dato('e');
    LCD1602_Dato('v');
    LCD1602_Dato('i');
    LCD1602_Dato('c');
    LCD1602_Dato('e');
    while(1)
    {

    }
}
