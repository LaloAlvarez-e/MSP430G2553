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
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz

    /*IAdd o DAdd*/
    LCD1602_Com(IncAdd);

    LCD1602_Com(HOME);//Manda cursor a home
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz
}


void LCD1602_Com(char comando)
{
    unsigned char Delay=0;
    unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;

    RW_OUT&=~RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT&=~RS; //RS 1=dato 0=comando


    //D7_OUT&=~D7;
    //D7_OUT|=((comando&0x80)&&1)<<D7_POS;
    //D6_OUT&=~D6;
    //D6_OUT|=((comando&0x40)&&1)<<D6_POS;
    //D5_OUT&=~D5;
    //D5_OUT|=((comando&0x20)&&1)<<D5_POS;
    //D4_OUT&=~D4;
    //D4_OUT|=((comando&0x10)&&1)<<D4_POS;
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
    LCD1602_E(); //manda un pulso en el pin E (Enable)

    //D7_OUT&=~D7;
    //D7_OUT|=((comando&0x8)&&1)<<D7_POS;
    //D6_OUT&=~D6;
    //D6_OUT|=((comando&0x4)&&1)<<D6_POS;
    //D5_OUT&=~D5;
    //D5_OUT|=((comando&0x2)&&1)<<D5_POS;
    //D4_OUT&=~D4;
    //D4_OUT|=((comando&0x1)&&1)<<D4_POS;

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
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=150; Delay>0; Delay--);//40 us aprox a 16MHz


    D4_OUT&=~D4;//reinicia los bits
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;
    RS_OUT&=~RS;
    RW_OUT&=~RW;
    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;
}
void LCD1602_Dato(char dato)
{
    unsigned char Delay=0;
    unsigned char valorD4=0,valorD5=0,valorD6=0,valorD7=0;
    unsigned char valorRW=0, valorRS=0;
    //guarda los valores anterior de los pines, en caso que se compartan con otras cosas
    valorD4=D4_IN & D4;
    valorD5=D5_IN & D5;
    valorD6=D6_IN & D6;
    valorD7=D7_IN & D7;
    valorRW=RW_IN & RW;
    valorRS=RS_IN & RS;

    RW_OUT&=~RW; //RW para escritura 1=lectura 0=escritura
    RS_OUT|=RS; //RS 1=dato 0=comando


    //D7_OUT&=~D7;
    //D7_OUT|=((dato&0x80)&&1)<<D7_POS;
    //D6_OUT&=~D6;
    //D6_OUT|=((dato&0x40)&&1)<<D6_POS;
    //D5_OUT&=~D5;
    //D5_OUT|=((dato&0x20)&&1)<<D5_POS;
    //D4_OUT&=~D4;
    //D4_OUT|=((dato&0x10)&&1)<<D4_POS;
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
    LCD1602_E(); //manda un pulso en el pin E (Enable)

    //D7_OUT&=~D7;
    //D7_OUT|=((dato&0x8)&&1)<<D7_POS;
    //D6_OUT&=~D6;
    //D6_OUT|=((dato&0x4)&&1)<<D6_POS;
    //D5_OUT&=~D5;
    //D5_OUT|=((dato&0x2)&&1)<<D5_POS;
    //D4_OUT&=~D4;
    //D4_OUT|=((dato&0x1)&&1)<<D4_POS;

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
    LCD1602_E(); //manda un pulso en el pin E (Enable)
    for(Delay=150; Delay>0; Delay--);//40 us aprox a 16MHz


    D4_OUT&=~D4;//reinicia los bits
    D5_OUT&=~D5;
    D6_OUT&=~D6;
    D7_OUT&=~D7;
    RS_OUT&=~RS;
    RW_OUT&=~RW;
    D4_OUT|=valorD4; //restaura el valor anterior
    D5_OUT|=valorD5;
    D6_OUT|=valorD6;
    D7_OUT|=valorD7;
    RS_OUT|=valorRS;
    RW_OUT|=valorRW;
}
void LCD1602_E(void)
{
    E_OUT|=E; //manda a 1 logico el bit E (Enable)
    E_OUT&=~E;//manda a 0 logico E, completando el pulso
}

void LCD1602_Pos(char columna, char fila)
{
    long direccion=0x80;
    direccion|=columna&0xF;
    direccion|=((fila&0x1)<<6);
    LCD1602_Com(direccion);
}



int LCD1602_Cadena(unsigned char* cadena,unsigned char* columna, unsigned char* fila)
{
    int conteo=0;//variable usada para saber cuentos caracteres se imprimieron

    //punteros
    // cadena = contiene una direccion
    //*cadena = apunta al valor de la direccion guardada en cadena
    //cadena++ o cadena+=1 o cadena= cadena + 1, apunta a la sig direccion

    //variables
    //conteo= tiene guardado un valor
    //&conteo = se obtiene la direccion donde se tiene guardado conteo


    LCD1602_Pos(*columna,*fila); //indica la posicion inicial del cursor
    while(*cadena)// realiza el ciclo minetras la cadena tenga algun valor
        //el valor 0 o '\0' es fin de cadena
    {
        LCD1602_Dato(*(cadena)); //envia el caracter correspondiente
        (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
        if((*columna&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
        {
            *fila^=1; //invierte el valor e fila para que se reinciie
            LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
        }

        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
    }
    return conteo;
}

/**
 * main.c
 */
void main(void)
{
    unsigned char fila=0,columna=0;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    Conf_Reloj(); //conf de reloj 16 MHz, SMCLK y MCLK
    //4 bits , 2 lineas, 5x8 puntos, incr cursor
    Conf_LCD1602();//configuracion de la pantalla LCD1602
    //LCD1602_Print(" Funcion  Print     InDevice",0,0);
    LCD1602_Cadena("Funcion M.Cadena    InDevice",&columna,&fila);
    while(1);
}

