/*
 * lcd.c
 *
 *  Created on: 25/08/2017
 *      Author: Lalo
 */


#include <lcd.h>


const char signos[8][8]= //°¬¡?\¨´ñ
{
 {2,5,2,0,0,0,0,0}, // °
 {0,0,0,0,0xF,1,0,0}, // ¬
 {4,0,0,4,4,4,4,0},// ¡
 {4,0,4,8,0x10,0x11,0xE,0}, //¿
 {0,0x10,8,4,2,1,0,0},// diagonal invertida
 {0xA,0,0,0,0,0,0,0}, //¨
 {0,2,4,8,0,0,0,0},//´
 {0xA,0x05,0,0x16,0x19,0x11,0x11,0}//ñ
// {0xE,0x1B,0x11,0x11,0x13,0x17,0x1F,0x1F},//simbolo bateria
};


void Conf_LCD1602(void)
{
    long Delay=0;
     /*Conf para P1.0=RS P1.1=RW P1.2=E*/
    E_DIR|=E;
    E_OUT&=~E;
    E_REN&=~E;
    E_SEL&=~E;
    E_SEL2&=~E;

    RS_DIR |=RS;
    RS_OUT &=~RS;
    RS_REN &=~RS;
    RS_SEL &=~RS;
    RS_SEL2&=~RS;

    RW_DIR|=RW;
    RW_OUT&=~RW;
    RW_REN&=~RW;
    RW_SEL&=~RW;
    RW_SEL2&=~RW;

    /*Conf para Datos D4-D7*/
    D4_DIR|=D4;
    D4_OUT&=~D4;
    D4_REN&=~D4;
    D4_SEL&=~D4;
    D4_SEL2&=~D4;

    D5_DIR|=D5;
    D5_OUT&=~D5;
    D5_REN&=~D5;
    D5_SEL&=~D5;
    D5_SEL2&=~D5;

    D6_DIR|=D6;
    D6_OUT&=~D6;
    D6_REN&=~D6;
    D6_SEL&=~D6;
    D6_SEL2&=~D6;

    D7_DIR|=D7;
    D7_OUT&=~D7;
    D7_REN&=~D7;
    D7_SEL&=~D7;
    D7_SEL2&=~D7;

    for(Delay=30000; Delay>0; Delay--);//20 ms aprox a 16MHz
    //manda 0x3 en la parte alta de la LCD
    D4_OUT|=D4;
    D5_OUT|=D5;
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=10000; Delay>0; Delay--);//7 ms aprox a 16MHz

    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=500; Delay>0; Delay--);//100 us aprox a 16MHz

    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=10000; Delay>0; Delay--);//7 ms aprox a 16MHz

    //primer comando 0x20 configuracion a 4 bits
    D4_OUT&=~D4; //conf para los pines D4-7 = P1.4-7
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=240; Delay>0; Delay--);//40 us aprox a 16MHz

    /*M8BIT o M4BIT,M2LINE o M1LINE, M5_8_Font o M5_11_Font */
    LCD1602_Com(M4BIT|M2LINE|M5_8_Font);

    /*ONDisp o OFFDisp, ONCursor o OFFCursor,ONBlink o OFFBLink*/
    LCD1602_Com(ONDisp|OFFCursor|OFFBlink );

    LCD1602_Com(CLEAR); //limpia la pantalla

    /*IAdd o DAdd*/
    LCD1602_Com(IncAdd);

    for(Delay=0;Delay<8;Delay++)
    {
        LCD1602_GC(&signos[Delay][0], Delay);
    }


    LCD1602_Com(HOME);//Manda cursor a home
}


void LCD1602_Com(char comando)
{
   unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    unsigned char d4_DIR,d5_DIR,d6_DIR,d7_DIR;
    unsigned char d4_REN,d5_REN,d6_REN,d7_REN;
    unsigned char f0_IE,f1_IE,f2_IE,f3_IE;
    unsigned char f0_IFG,f1_IFG,f2_IFG,f3_IFG;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    int i=0;

    f0_IFG=F0_IFG&F0;
    f1_IFG=F1_IFG&F1;
    f2_IFG=F2_IFG&F2;
    f3_IFG=F3_IFG&F3;

    f0_IE=F0_IE&F0;
    f1_IE=F1_IE&F1;
    f2_IE=F2_IE&F2;
    f3_IE=F3_IE&F3;

    F0_IE&=~F0;
    F1_IE&=~F1;
    F2_IE&=~F2;
    F3_IE&=~F3;

    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;

    RW_OUT&=~RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT&=~RS; //RS 1=dato 0=comando

    E_OUT|=E; //manda a 1 logico el bit E (Enable)

    d4_DIR=D4_DIR & D4;
    d5_DIR=D5_DIR & D5;
    d6_DIR=D6_DIR & D6;
    d7_DIR=D7_DIR & D7;

    d4_REN=D4_REN & D4;
    d5_REN=D5_REN & D5;
    d6_REN=D6_REN & D6;
    d7_REN=D7_REN & D7;


    D4_DIR|=D4;
    D5_DIR|=D5;
    D6_DIR|=D6;
    D7_DIR|=D7;

    D4_REN&=~D4;
    D5_REN&=~D5;
    D6_REN&=~D6;
    D7_REN&=~D7;

    if(comando&0x80)
        D7_OUT|=D7;
    else
        D7_OUT&=~D7;

    if(comando&0x40)
        D6_OUT|=D6;
    else
        D6_OUT&=~D6;

    if(comando&0x20)
        D5_OUT|=D5;
    else
        D5_OUT&=~D5;

    if(comando&0x10)
        D4_OUT|=D4;
    else
        D4_OUT&=~D4;


    E_OUT&=~E;//manda a 0 logico E, completando el pulso
    E_OUT|=E;
    if(comando&0x8)
        D7_OUT|=D7;
    else
        D7_OUT&=~D7;

    if(comando&0x4)
        D6_OUT|=D6;
    else
        D6_OUT&=~D6;

    if(comando&0x2)
        D5_OUT|=D5;
    else
        D5_OUT&=~D5;

    if(comando&0x1)
        D4_OUT|=D4;
    else
        D4_OUT&=~D4;


    E_OUT&=~E;//manda a 0 logico E, completando el pulso

    LCD1602_Busy();

    D4_REN|=d4_REN;
    D5_REN|=d5_REN;
    D6_REN|=d6_REN;
    D7_REN|=d7_REN;


    D4_OUT&=~D4;//reinicia los bits
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;
    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;

    D4_DIR&=~D4;
    D5_DIR&=~D5;
    D6_DIR&=~D6;
    D7_DIR&=~D7;

    D4_DIR|=d4_DIR;
    D5_DIR|=d5_DIR;
    D6_DIR|=d6_DIR;
    D7_DIR|=d7_DIR;



    for(i=0;i<RETARDO;i++);
    F0_IFG&=~F0;
    F1_IFG&=~F1;
    F2_IFG&=~F2;
    F3_IFG&=~F3;


    F0_IFG|=f0_IFG;
    F1_IFG|=f1_IFG;
    F2_IFG|=f2_IFG;
    F3_IFG|=f3_IFG;

    F0_IE|=f0_IE;
    F1_IE|=f1_IE;
    F2_IE|=f2_IE;
    F3_IE|=f3_IE;

}
void LCD1602_Dato(char dato)
{

    unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    unsigned char d4_DIR,d5_DIR,d6_DIR,d7_DIR;
    unsigned char d4_REN,d5_REN,d6_REN,d7_REN;

    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    unsigned char f0_IE,f1_IE,f2_IE,f3_IE;
    unsigned char f0_IFG,f1_IFG,f2_IFG,f3_IFG;
    int i=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas


    f0_IFG=F0_IFG&F0;
    f1_IFG=F1_IFG&F1;
    f2_IFG=F2_IFG&F2;
    f3_IFG=F3_IFG&F3;

    f0_IE=F0_IE&F0;
    f1_IE=F1_IE&F1;
    f2_IE=F2_IE&F2;
    f3_IE=F3_IE&F3;

    F0_IE&=~F0;
    F1_IE&=~F1;
    F2_IE&=~F2;
    F3_IE&=~F3;

    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;


    RW_OUT&=~RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT|=RS; //RS 1=dato 0=comando
    E_OUT|=E; //manda a 1 logico el bit E (Enable)

    d4_DIR=D4_DIR & D4;
    d5_DIR=D5_DIR & D5;
    d6_DIR=D6_DIR & D6;
    d7_DIR=D7_DIR & D7;

    d4_REN=D4_REN & D4;
    d5_REN=D5_REN & D5;
    d6_REN=D6_REN & D6;
    d7_REN=D7_REN & D7;


    D4_DIR|=D4;
    D5_DIR|=D5;
    D6_DIR|=D6;
    D7_DIR|=D7;

    D4_REN&=~D4;
    D5_REN&=~D5;
    D6_REN&=~D6;
    D7_REN&=~D7;

    if(dato&0x80)
        D7_OUT|=D7;
    else
        D7_OUT&=~D7;

    if(dato&0x40)
        D6_OUT|=D6;
    else
        D6_OUT&=~D6;

    if(dato&0x20)
        D5_OUT|=D5;
    else
        D5_OUT&=~D5;

    if(dato&0x10)
        D4_OUT|=D4;
    else
        D4_OUT&=~D4;

    E_OUT&=~E; //manda a 1 logico el bit E (Enable)
    E_OUT|=E; //manda a 1 logico el bit E (Enable)


    if(dato&0x8)
        D7_OUT|=D7;
    else
        D7_OUT&=~D7;

    if(dato&0x4)
        D6_OUT|=D6;
    else
        D6_OUT&=~D6;

    if(dato&0x2)
        D5_OUT|=D5;
    else
        D5_OUT&=~D5;

    if(dato&0x1)
        D4_OUT|=D4;
    else
        D4_OUT&=~D4;
    E_OUT&=~E; //manda a 1 logico el bit E (Enable)
    LCD1602_Busy();


    D4_REN|=d4_REN;
    D5_REN|=d5_REN;
    D6_REN|=d6_REN;
    D7_REN|=d7_REN;

    D4_OUT&=~D4;//reinicia los bits
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;
    RS_OUT&=~RS;

    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;

    D4_DIR&=~D4;
    D5_DIR&=~D5;
    D6_DIR&=~D6;
    D7_DIR&=~D7;

    D4_DIR|=d4_DIR;
    D5_DIR|=d5_DIR;
    D6_DIR|=d6_DIR;
    D7_DIR|=d7_DIR;


    for(i=0;i<RETARDO;i++);

    F0_IFG&=~F0;
     F1_IFG&=~F1;
     F2_IFG&=~F2;
     F3_IFG&=~F3;


     F0_IFG|=f0_IFG;
     F1_IFG|=f1_IFG;
     F2_IFG|=f2_IFG;
     F3_IFG|=f3_IFG;

     F0_IE|=f0_IE;
     F1_IE|=f1_IE;
     F2_IE|=f2_IE;
     F3_IE|=f3_IE;
}


char LCD1602_LDato()
{
    unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    unsigned char d4_DIR,d5_DIR,d6_DIR,d7_DIR;
    unsigned char d4_REN,d5_REN,d6_REN,d7_REN;
    char dato=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    unsigned char f0_IE,f1_IE,f2_IE,f3_IE;
    unsigned char f0_IFG,f1_IFG,f2_IFG,f3_IFG;
    int i=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas


    f0_IFG=F0_IFG&F0;
    f1_IFG=F1_IFG&F1;
    f2_IFG=F2_IFG&F2;
    f3_IFG=F3_IFG&F3;

    f0_IE=F0_IE&F0;
    f1_IE=F1_IE&F1;
    f2_IE=F2_IE&F2;
    f3_IE=F3_IE&F3;

    F0_IE&=~F0;
    F1_IE&=~F1;
    F2_IE&=~F2;
    F3_IE&=~F3;

    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;

    RW_OUT|=RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT|=RS; //RS 1=dato 0=comando

    E_OUT|=E; //manda a 1 logico el bit E (Enable)


    d4_DIR=D4_DIR & D4;
    d5_DIR=D5_DIR & D5;
    d6_DIR=D6_DIR & D6;
    d7_DIR=D7_DIR & D7;

    d4_REN=D4_REN & D4;
    d5_REN=D5_REN & D5;
    d6_REN=D6_REN & D6;
    d7_REN=D7_REN & D7;


    D4_DIR&=~D4;
    D5_DIR&=~D5;
    D6_DIR&=~D6;
    D7_DIR&=~D7;

    D4_REN|=D4;
    D5_REN|=D5;
    D6_REN|=D6;
    D7_REN|=D7;

    D4_OUT&=~D4;
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;

    if(D7_IN&D7)
        dato|=0x80;
    else
        dato&=~0x80;


    if(D6_IN&D6)
        dato|=0x40;
    else
        dato&=~0x40;


    if(D5_IN&D5)
        dato|=0x20;
    else
        dato&=~0x20;

    if(D4_IN&D4)
        dato|=0x10;
    else
        dato&=~0x10;

    E_OUT&=~E;//manda a 0 logico E, completando el pulso
    E_OUT|=E; //manda a 1 logico el bit E (Enable)

    if(D7_IN&D7)
        dato|=0x8;
    else
        dato&=~0x8;

    if(D6_IN&D6)
        dato|=0x4;
    else
        dato&=~0x4;

    if(D5_IN&D5)
        dato|=0x2;
    else
        dato&=~0x2;

    if(D4_IN&D4)
        dato|=0x1;
    else
        dato&=~0x1;
    E_OUT&=~E;//manda a 0 logico E, completando el pulso

    LCD1602_Busy();

    D4_REN&=~D4;
    D5_REN&=~D5;
    D6_REN&=~D6;
    D7_REN&=~D7;

    D4_REN|=d4_REN;
    D5_REN|=d5_REN;
    D6_REN|=d6_REN;
    D7_REN|=d7_REN;

    RS_OUT&=~RS;
    RW_OUT&=~RW;

    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;

    D4_DIR|=d4_DIR;
    D5_DIR|=d5_DIR;
    D6_DIR|=d6_DIR;
    D7_DIR|=d7_DIR;



    for(i=0;i<RETARDO;i++);

     F0_IFG&=~F0;
     F1_IFG&=~F1;
     F2_IFG&=~F2;
     F3_IFG&=~F3;


     F0_IFG|=f0_IFG;
     F1_IFG|=f1_IFG;
     F2_IFG|=f2_IFG;
     F3_IFG|=f3_IFG;

     F0_IE|=f0_IE;
     F1_IE|=f1_IE;
     F2_IE|=f2_IE;
     F3_IE|=f3_IE;

    return dato;
}



char LCD1602_LCom(unsigned char* columna,unsigned char* fila)
{
    unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    unsigned char d4_DIR,d5_DIR,d6_DIR,d7_DIR;
    unsigned char d4_REN,d5_REN,d6_REN,d7_REN;
    char dato=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    unsigned char f0_IE,f1_IE,f2_IE,f3_IE;
    unsigned char f0_IFG,f1_IFG,f2_IFG,f3_IFG;
    int i=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas


    f0_IFG=F0_IFG&F0;
    f1_IFG=F1_IFG&F1;
    f2_IFG=F2_IFG&F2;
    f3_IFG=F3_IFG&F3;

    f0_IE=F0_IE&F0;
    f1_IE=F1_IE&F1;
    f2_IE=F2_IE&F2;
    f3_IE=F3_IE&F3;

    F0_IE&=~F0;
    F1_IE&=~F1;
    F2_IE&=~F2;
    F3_IE&=~F3;


    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;

    RW_OUT|=RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT&=~RS; //RS 1=dato 0=comando

    E_OUT|=E; //manda a 1 logico el bit E (Enable)


    d4_DIR=D4_DIR & D4;
    d5_DIR=D5_DIR & D5;
    d6_DIR=D6_DIR & D6;
    d7_DIR=D7_DIR & D7;

    d4_REN=D4_REN & D4;
    d5_REN=D5_REN & D5;
    d6_REN=D6_REN & D6;
    d7_REN=D7_REN & D7;


    D4_DIR&=~D4;
    D5_DIR&=~D5;
    D6_DIR&=~D6;
    D7_DIR&=~D7;

    D4_REN|=D4;
    D5_REN|=D5;
    D6_REN|=D6;
    D7_REN|=D7;

    D4_OUT&=~D4;
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;

    if(D7_IN&D7)
        dato=1;
    else
        dato=0;


    if(D6_IN&D6)
        *fila=1;
    else
        *fila=0;


    E_OUT&=~E;//manda a 0 logico E, completando el pulso
    E_OUT|=E; //manda a 1 logico el bit E (Enable)

    if(D7_IN&D7)
        *columna|=0x8;
    else
        *columna&=~0x8;

    if(D6_IN&D6)
        *columna|=0x4;
    else
        *columna&=~0x4;

    if(D5_IN&D5)
        *columna|=0x2;
    else
        *columna&=~0x2;

    if(D4_IN&D4)
        *columna|=0x1;
    else
        *columna&=~0x1;
    E_OUT&=~E;//manda a 0 logico E, completando el pulso

    D4_REN&=~D4;
    D5_REN&=~D5;
    D6_REN&=~D6;
    D7_REN&=~D7;

    D4_REN|=d4_REN;
    D5_REN|=d5_REN;
    D6_REN|=d6_REN;
    D7_REN|=d7_REN;


    RS_OUT&=~RS;
    RW_OUT&=~RW;

    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;

    D4_DIR|=d4_DIR;
    D5_DIR|=d5_DIR;
    D6_DIR|=d6_DIR;
    D7_DIR|=d7_DIR;


    for(i=0;i<RETARDO;i++);
    F0_IFG&=~F0;
     F1_IFG&=~F1;
     F2_IFG&=~F2;
     F3_IFG&=~F3;


     F0_IFG|=f0_IFG;
     F1_IFG|=f1_IFG;
     F2_IFG|=f2_IFG;
     F3_IFG|=f3_IFG;

     F0_IE|=f0_IE;
     F1_IE|=f1_IE;
     F2_IE|=f2_IE;
     F3_IE|=f3_IE;

    return dato;
}


void LCD1602_Busy()
{
    unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    unsigned char d4_DIR,d5_DIR,d6_DIR,d7_DIR;
    unsigned char d4_REN,d5_REN,d6_REN,d7_REN;
    char dato=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    unsigned char f0_IE,f1_IE,f2_IE,f3_IE;
    unsigned char f0_IFG,f1_IFG,f2_IFG,f3_IFG;
    int i=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas


    f0_IFG=F0_IFG&F0;
    f1_IFG=F1_IFG&F1;
    f2_IFG=F2_IFG&F2;
    f3_IFG=F3_IFG&F3;

    f0_IE=F0_IE&F0;
    f1_IE=F1_IE&F1;
    f2_IE=F2_IE&F2;
    f3_IE=F3_IE&F3;

    F0_IE&=~F0;
    F1_IE&=~F1;
    F2_IE&=~F2;
    F3_IE&=~F3;

    D4_IE&=~D4;
    D5_IE&=~D5;
    D6_IE&=~D6;
    D7_IE&=~D7;

    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;

    RW_OUT|=RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT&=~RS; //RS 1=dato 0=comando



    d4_DIR=D4_DIR & D4;
    d5_DIR=D5_DIR & D5;
    d6_DIR=D6_DIR & D6;
    d7_DIR=D7_DIR & D7;

    d4_REN=D4_REN & D4;
    d5_REN=D5_REN & D5;
    d6_REN=D6_REN & D6;
    d7_REN=D7_REN & D7;


    D4_DIR&=~D4;
    D5_DIR&=~D5;
    D6_DIR&=~D6;
    D7_DIR&=~D7;

    D4_REN|=D4;
    D5_REN|=D5;
    D6_REN|=D6;
    D7_REN|=D7;

    D4_OUT&=~D4;
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;
    do{
        E_OUT|=E; //manda a 1 logico el bit E (Enable)

        if(D7_IN&D7)
            dato=1;
        else
            dato=0;

        E_OUT&=~E;//manda a 0 logico E, completando el pulso
        E_OUT|=E; //manda a 1 logico el bit E (Enable)

        E_OUT&=~E;//manda a 0 logico E, completando el pulso

    }while(dato);

    D4_REN&=~D4;
    D5_REN&=~D5;
    D6_REN&=~D6;
    D7_REN&=~D7;

    D4_REN|=d4_REN;
    D5_REN|=d5_REN;
    D6_REN|=d6_REN;
    D7_REN|=d7_REN;
    RW_OUT&=~RW;

    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;


    D4_DIR|=d4_DIR;
    D5_DIR|=d5_DIR;
    D6_DIR|=d6_DIR;
    D7_DIR|=d7_DIR;



    for(i=0;i<RETARDO;i++);
    F0_IFG&=~F0;
     F1_IFG&=~F1;
     F2_IFG&=~F2;
     F3_IFG&=~F3;


     F0_IFG|=f0_IFG;
     F1_IFG|=f1_IFG;
     F2_IFG|=f2_IFG;
     F3_IFG|=f3_IFG;

     F0_IE|=f0_IE;
     F1_IE|=f1_IE;
     F2_IE|=f2_IE;
     F3_IE|=f3_IE;
}

void LCD1602_Lectura(unsigned char columna,unsigned char fila,char cantidad,char* conv)
{


    LCD1602_Pos(columna,fila);
    while(cantidad--)
    {
        *conv=LCD1602_LDato();
        conv++;
    }
    *conv=0;
    LCD1602_Pos(columna,fila);


}

void LCD1602_Char(char dato)
{
    //°¬¡?\¨´ñ
    switch(dato)
    {
    case '°':
        dato=0;
        break;
    case '¬':
        dato=1;
        break;
    case '¡':
        dato=2;
        break;
    case '¿':
        dato=3;
        break;
    case '\\':
        dato=4;
        break;
    case '¨':
        dato=5;
        break;
    case '´':
        dato=6;
        break;
    case 'ñ':
    case 'Ñ':
        dato=7;
        break;
    default:
        break;
    }
    LCD1602_Dato(dato);
}




void LCD1602_E(void)
{
    E_OUT|=E; //manda a 1 logico el bit E (Enable)
    E_OUT&=~E;//manda a 0 logico E, completando el pulso
}

void LCD1602_Pos(unsigned char columna,unsigned char fila)
{
    register long direccion=0x80;
    direccion|=columna&0xF;
    direccion|=((fila&0x1)<<6);
    LCD1602_Com(direccion);
}

void LCD1602_Limites(unsigned char* columna,unsigned char* fila)
{
    (*columna)++;
    if((*columna&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
    {
        (*columna)=0;
        (*fila)++; //invierte el valor e fila para que se reinciie
        LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
    }
}

int LCD1602_Cadena(char* cadena,unsigned char* columna, unsigned char* fila)
{
    register int conteo=0;//variable usada para saber cuentos caracteres se imprimieron

    LCD1602_Pos(*columna,*fila); //indica la posicion inicial del cursor
    while(*cadena)// realiza el ciclo minetras la cadena tenga algun valor
        //el valor 0 o '\0' es fin de cadena
    {
        LCD1602_Dato(*(cadena)); //envia el caracter correspondiente
        (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
        if((*columna&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
        {
            (*columna)=0;
            (*fila)++; //invierte el valor e fila para que se reinciie
            LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
        }

        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
    }
    return conteo;
}

unsigned char Conv_Entero(long long numero, char* conv)
{
    char           convTemp[21]; //longitud maxima de long 12 digitos con signo
    register char *punteroActual;
    register int num=0;
    register char i=0;
    register long long  numeroReg = numero;//paso el numero a un registro para aumentar rendimiento

    punteroActual = &convTemp[21 - 1]; //empezamos llenando desde la ultima posicion
    *punteroActual = 0; //guarda el fin de cadena en la ultima posicion
    if( numeroReg < 0)
    {
        numeroReg*=-1;
    }

    do {
        punteroActual--;//se decrementa la posicion donse guardara el valor
        num=numeroReg % 10; //obtiene el digito de menor peso
        //num1=abs(num);//un if es mas rapido que una multiplicacion por -1 si es negativo el valor
        *punteroActual = num  + '0'; //convierte el valor en caracter
    }  while((numeroReg /= 10)); //mientras exista un digito sigue el ciclo

    if ( numero < 0)
    {
        punteroActual--;
        *punteroActual = '-';//si el numero es negativo guarda el signo negativo
    }

    numeroReg=convTemp+21-punteroActual;//realiza la resta de cuantos caracteres se utilizaron
    for (i = 0; i< numeroReg; i++) //hace un ciclo burbuja optimizado
    {
       ((unsigned char *)conv)[i] = ((const unsigned char *)punteroActual)[i];
    }

    return numeroReg - 1;
}


const long long dec[16]=
{0,10,100,1000,10000,100000,1000000,10000000,100000000,
 1000000000,10000000000,100000000000,1000000000000,
 10000000000000,100000000000000,1000000000000000
};

unsigned char Conv_Float(double numero,int decimales,char* conv)
{
    register long long deci=0; //contiene los decimales en version entero
    register double decimal=0;//contiene el valor de decimales en version double
    register unsigned char valores=0;//cuantos digitos se imprimen

    decimal=numero-(long long)numero; //obtiene la parte decimal
    decimal*=dec[decimales];//hace la multiplicacion depende de cuantos decimales necesitemos
    deci=(long long)decimal;//castea la parte decimal a un long long (64 bits)
    if(deci<0)//si el numero es negativo elimina el signo
      deci*=-1;

    valores= Conv_Entero((long long)numero, conv); //convierte la parte entera del numero
    conv[valores]='.';//agrega un '.' en la posicion del fin de cadena
    valores++;//aumenta a la siguiente posicion
    valores+=Conv_Entero(deci, &conv[valores]);//convierte la parte decimal despues del punto
    return valores;//regresa la cantidad de digitos convertidos
}


const char HEXA[16]=
{
 '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

const char hexa[16]=
{
 '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'
};

unsigned char Conv_Hex(long long numero, char* conv)
{
    char           convTemp[19]; //longitud maxima de long 16 digitos
    register char *punteroActual;
    register int num=0;
    register char i=0;
    register unsigned long long  numeroReg = (unsigned long long) numero;//paso el numero a un registro para aumentar rendimiento

    punteroActual = &convTemp[19 - 1]; //empezamos llenando desde la ultima posicion
    *punteroActual = 0; //guarda el fin de cadena en la ultima posicion

    do {
        punteroActual--;//se decrementa la posicion donse guardara el valor
        num=numeroReg&0xF; //obtiene el digito de menor peso
        *punteroActual = hexa[num]; //convierte el valor en caracter
        numeroReg>>=1;
        numeroReg>>=1;
        numeroReg>>=1;
        numeroReg>>=1;
       // numeriReg>>=4;
    }  while((numeroReg > 0)); //mientras exista un digito sigue el ciclo

    punteroActual--;
    *punteroActual = 'x';
    punteroActual--;
    *punteroActual = '0';
    numeroReg=convTemp+19-punteroActual;//realiza la resta de cuantos caracteres se utilizaron
    for (i = 0; i< numeroReg; i++) //hace un ciclo burbuja optimizado
    {
        ((unsigned char *)conv)[i] = ((const unsigned char *)punteroActual)[i];
    }

    return numeroReg - 1;
}

unsigned char Conv_HEX(long long numero, char* conv)
{
    char           convTemp[19]; //longitud maxima de long 16 digitos
    register char *punteroActual;
    register int num=0;
    register char i=0;
    register unsigned long long  numeroReg = (unsigned long long)numero;//paso el numero a un registro para aumentar rendimiento

    punteroActual = &convTemp[19 - 1]; //empezamos llenando desde la ultima posicion
    *punteroActual = 0; //guarda el fin de cadena en la ultima posicion

    do {
        punteroActual--;//se decrementa la posicion donse guardara el valor
        num=numeroReg&0xF; //obtiene el digito de menor peso
        *punteroActual = HEXA[num]; //convierte el valor en caracter
        numeroReg>>=1;
        numeroReg>>=1;
        numeroReg>>=1;
        numeroReg>>=1;
    }  while((numeroReg > 0)); //mientras exista un digito sigue el ciclo

    punteroActual--;
    *punteroActual = 'X';
    punteroActual--;
    *punteroActual = '0';
    numeroReg=convTemp+19-punteroActual;//realiza la resta de cuantos caracteres se utilizaron
    for (i = 0; i< numeroReg; i++) //hace un ciclo burbuja optimizado
    {
        ((unsigned char *)conv)[i] = ((const unsigned char *)punteroActual)[i];
    }

    return numeroReg - 1;
}


unsigned char Conv_Oct(long long numero, char* conv)
{
    char           convTemp[24]; //longitud maxima de long 22 digitos
    register char *punteroActual;
    register int num=0;
    register char i=0;
    register unsigned long long  numeroReg = (unsigned long long)numero;//paso el numero a un registro para aumentar rendimiento

    punteroActual = &convTemp[24 - 1]; //empezamos llenando desde la ultima posicion
    *punteroActual = 0; //guarda el fin de cadena en la ultima posicion

    do {
        punteroActual--;//se decrementa la posicion donse guardara el valor
        num=numeroReg&0x7; //obtiene el digito de menor peso
        *punteroActual = num+'0'; //convierte el valor en caracter
        numeroReg>>=1;
        numeroReg>>=1;
        numeroReg>>=1;
    }  while((numeroReg > 0)); //mientras exista un digito sigue el ciclo


    punteroActual--;
    *punteroActual = '0';//si el numero es negativo guarda el signo negativo

    numeroReg=convTemp+24-punteroActual;//realiza la resta de cuantos caracteres se utilizaron
    for (i = 0; i< numeroReg; i++) //hace un ciclo burbuja optimizado
    {
        ((unsigned char *)conv)[i] = ((const unsigned char *)punteroActual)[i];
    }

    return numeroReg - 1;
}



unsigned char Conv_Bin(long numero, char* conv)
{
    char           convTemp[26]; //longitud maxima de long 22 digitos
    register char *punteroActual;
    register int num=0;
    register char i=0;
    register unsigned long  numeroReg = (unsigned long)numero;//paso el numero a un registro para aumentar rendimiento

    punteroActual = &convTemp[26 - 1]; //empezamos llenando desde la ultima posicion
    *punteroActual = 0; //guarda el fin de cadena en la ultima posicion

    do {
        punteroActual--;//se decrementa la posicion donse guardara el valor
        num=numeroReg&0x1; //obtiene el digito de menor peso
        *punteroActual = num+'0'; //convierte el valor en caracter
        numeroReg>>=1;
    }  while((numeroReg > 0)); //mientras exista un digito sigue el ciclo


    punteroActual--;
    *punteroActual = 'b';//si el numero es negativo guarda el signo negativo

    numeroReg=convTemp+26-punteroActual;//realiza la resta de cuantos caracteres se utilizaron
    for (i = 0; i< numeroReg; i++) //hace un ciclo burbuja optimizado
    {
        ((unsigned char *)conv)[i] = ((const unsigned char *)punteroActual)[i];
    }

    return numeroReg - 1;
}

void LCD1602_GC(const char* datos, char dir)
{
  register char i=0;
  if( dir>7) //solo tiene espacio para guardar 8 caracteres
    return;
  LCD1602_Com(GCRAM+(dir<<3)); // 01xx xddd x=caracter d=posicion
  while(i<8)
  {
    LCD1602_Dato(datos[i++]);
  }
}

unsigned char LCD1602_Print(char* cadena,unsigned char* columna, unsigned char* fila)
{
    register unsigned char conteo=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    register char salir=0; //variable que funciona cuanod encuentra un ESC
     (*columna)&=0xF;//delimita el valor inicial de columna de 0 a 15
    LCD1602_Pos(*columna,*fila); //indica la posicion inicial del cursor
    while(*cadena)// realiza el ciclo mientras la cadena tenga algun valor
           //el valor 0 o '\0' es fin de cadena
    {
        switch (*cadena) //detecta si existe un caracter especial
        {
        case '\n': //salto de linea
            (*fila)++; //aumenta la fila
            break;
        case '\r': //retorno de carro
            *columna=0; //actualiza el valor de la columna a la primera posicion
            break;
        case '\t': //tabulacion
            if(((*columna)&0xF)<13)
                *columna+=3; //aumenta 3 espacios vacios
            else
            {
                *columna=0; // pasa a la siguiente fila si no cabe la tabulacion
                *fila++;
            }
            break;
         case '\a':
         case '\b': //retroceso
            if(((*columna)!=0) || ((*fila)!=0)) //si la columna y fila es diferente a 0 puede retroceder
            {
                if(((*columna)!=0)) //si la columna encuentra entre 1 y 15 puede disminuir uno
                    (*columna)--;
                else
                    if(((*fila)!=0)) //si la columna es 0 entonces checa si existen filas que disminuir
                    {
                        (*columna)=0xF;
                        (*fila)--;
                    }
            }
            if((*cadena)=='\a')
            {
                LCD1602_Pos(*columna,*fila); //actualiza la posicion
                LCD1602_Char(' ');//borra el caracter que pudiera haber en la posicion
            }
            break;
        case '\e': //escape
            salir=1;//indica que se necesita salir de la funcion
            break;
        case '\f': //nueva pagina
            *columna=*fila=0;//reinicia los valores
             LCD1602_Com(CLEAR); //limpia la pantalla
            break;
        default :
            LCD1602_Char(*(cadena)); //envia el caracter correspondiente
            LCD1602_Limites(columna,fila);
            break;
        }
        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
        if(salir) //si detecto un \e (escape) sale del ciclo while
            break;
        LCD1602_Pos(*columna,*fila); //actualiza la posicion

    }
     return conteo; //regresa el conteo de caracteres y caracteres especiales
}




unsigned char LCD1602_Printf(char* cadena,unsigned char* columna, unsigned char* fila,...)
{
    register unsigned char conteo=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    register char salir=0; //variable que funciona cuanod encuentra un ESC

    va_list ap; //crea puntero de los argumentos
    double valorARGd; //variable donde guardara el valor del argumento
    char* valorARGc; //variable donde guardara el valor del argumento
    long valorARGi; //variable donde guardara el valor del argumento
    char conversion[30];
    va_start(ap, fila);//maneja la memoria de los argumentos empezando desde el ultimo conocido ingresado

    (*columna)&=0xF;//delimita el valor inicial de columna de 0 a 15
    LCD1602_Pos(*columna,*fila); //indica la posicion inicial del cursor
    while(*cadena)// realiza el ciclo mientras la cadena tenga algun valor
           //el valor 0 o '\0' es fin de cadena
    {
        switch (*cadena) //detecta si existe un caracter especial
        {
        case '\n': //salto de linea
            (*fila)++; //aumenta la fila
            break;
        case '\r': //retorno de carro
            *columna=0; //actualiza el valor de la columna a la primera posicion
            break;
        case '\t': //tabulacion
            if(((*columna)&0xF)<13)
                *columna+=3; //aumenta 3 espacios vacios
            else
            {
                *columna=0; // pasa a la siguiente fila si no cabe la tabulacion
                *fila++;
            }
            break;
         case '\a':
         case '\b': //retroceso
            if(((*columna)!=0) || ((*fila)!=0)) //si la columna y fila es diferente a 0 puede retroceder
            {
                if(((*columna)!=0)) //si la columna encuentra entre 1 y 15 puede disminuir uno
                    (*columna)--;
                else
                    if(((*fila)!=0)) //si la columna es 0 entonces checa si existen filas que disminuir
                    {
                        (*columna)=0xF;
                        (*fila)--;
                    }
            }
            if((*cadena)=='\a')
            {
                LCD1602_Pos(*columna,*fila); //actualiza la posicion
                LCD1602_Dato(' ');//borra el caracter que pudiera haber en la posicion
            }
            break;
        case '\e': //escape
            salir=1;//indica que se necesita salir de la funcion
            break;
        case '\f': //nueva pagina
            *columna=*fila=0;//reinicia los valores
            LCD1602_Com(CLEAR); //limpia la pantalla
            break;
        case '%':
            cadena++;
            switch(*cadena)
            {
                case 'd': //"%d o %i"
                case 'i':
                    valorARGi=(int)va_arg(ap, int);
                    Conv_Entero(valorARGi,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break;
                case 'u':// "%u"
                    valorARGi=(unsigned int)va_arg(ap, unsigned int);
                    Conv_Entero(valorARGi,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break;
                case 'x': //"%x"
                    valorARGi=(unsigned int)va_arg(ap, unsigned int);
                    Conv_Hex(valorARGi,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break;
                case 'X':// "%X"
                    valorARGi=(unsigned int)va_arg(ap, unsigned int);
                    Conv_HEX(valorARGi,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break;
                case 'o': //"%o"
                    valorARGi=(unsigned int)va_arg(ap, unsigned int);
                    Conv_Oct(valorARGi,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break;
              case 'c': //"%c"
                    valorARGi=(unsigned char)va_arg(ap, unsigned char);
                    LCD1602_Char(valorARGi);//manda el caracter a la LCD
                     LCD1602_Limites(columna,fila);
                    break;
                case 'p': //"%p"
                    valorARGi=(unsigned long)va_arg(ap, void*);
                    Conv_Hex(valorARGi,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break;
                case 's':// "%s"
                    valorARGc=(char*)va_arg(ap,char*);  //el siguiente argumento es un puntero
                    conteo+=LCD1602_Print(valorARGc,columna,fila)-1;//imprime la cadena del puntero
                    break;
                case 'F':
                   case 'f': //"%f"
                       valorARGd=(double)va_arg(ap, double);
                       Conv_Float((float)valorARGd,3,conversion);
                       conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                       break;
                case 'l'://"%lf" "%8.4lf" "%5.3f" "%l"
                    cadena++; //aumenta en uno la posicion del string
                    if(*cadena=='f') //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                    valorARGd=(double)va_arg(ap, double);
                    Conv_Float((double)valorARGd,3,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break; //break de este caso
                    }
                    else
                        cadena--; //si no encuentra la 'f' regresa a la 'l'
                default:// "%p"
                    cadena--;//si no es ningun caso anterior regresa al '%'
                case '%':
                     LCD1602_Dato('%');
                     LCD1602_Limites(columna,fila);
                     break;
           }
            break;
        default :
            LCD1602_Char(*(cadena)); //envia el caracter correspondiente
            LCD1602_Limites(columna,fila);
            break;
        }
        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
        if(salir) //si detecto un \e (escape) sale del ciclo while
            break;
        LCD1602_Pos(*columna,*fila); //actualiza la posicion

    }
    va_end(ap); //reinicia el puntero

     return conteo; //regresa el conteo de caracteres y caracteres especiales
}



