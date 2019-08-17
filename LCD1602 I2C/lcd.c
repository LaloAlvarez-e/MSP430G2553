/*
 * lcd.c
 *
 *  Created on: 25/08/2017
 *      Author: Lalo
 */


#include <lcd.h>


uint8_t u8ActualDevice=0x3F;

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
    for(Delay=30000; Delay>0; Delay--);//20 ms aprox a 16MHz
    //manda 0x3 en la parte alta de la LCD

    LCD1602_Com(0x33);
    LCD1602_Com(0x32);

    /*M8BIT o M4BIT,M2LINE o M1LINE, M5_8_Font o M5_11_Font */
    LCD1602_Com(M4BIT|M2LINE|M5_8_Font);

    /*ONDisp o OFFDisp, ONCursor o OFFCursor,ONBlink o OFFBLink*/
    LCD1602_Com(ONDisp|OFFCursor|OFFBlink );

    LCD1602_Com(CLEAR); //limpia la pantalla
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz

    /*IAdd o DAdd*/
    LCD1602_Com(IncAdd);

    for(Delay=0;Delay<8;Delay++)
    {
        LCD1602_GC(&signos[Delay][0], Delay);
    }


    LCD1602_Com(HOME);//Manda cursor a home
    for(Delay=3000; Delay>0; Delay--);//1.60 ms aprox a 16MHz
}


void LCD1602_Com(char comando)
{
    uint8_t u8Dato[4];
    uint16_t u16Delay;

    u8Dato[0]=BL|EN|(comando&0xF0);
    u8Dato[1]=BL|(comando&0xF0);
    u8Dato[2]=BL|EN|((comando<<4)&0xF0);
    u8Dato[3]=BL|((comando<<4)&0xF0);
    I2C_u16SendMultiByteMaster(u8ActualDevice,u8Dato,4);
    while(I2C_u16Busy());
    for(u16Delay=0; u16Delay<400; u16Delay++);


}
void LCD1602_ChangeDevice(uint8_t u8Address)
{
    u8ActualDevice=u8Address;
}
void LCD1602_Dato(char dato)
{
    unsigned char dato1[4];
    uint16_t u16Delay;

    dato1[0]=BL|EN|RS|(dato&0xF0);
    dato1[1]=BL|RS|(dato&0xF0);
    dato1[2]=BL|EN|RS|((dato<<4)&0xF0);
    dato1[3]=BL|RS|((dato<<4)&0xF0);
    I2C_u16SendMultiByteMaster(u8ActualDevice,dato1,4);
    while(I2C_u16Busy());
    for(u16Delay=0; u16Delay<400; u16Delay++);
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




void LCD1602_Pos(char columna, char fila)
{
    register long direccion=0x80;
    direccion|=columna&0xF;
    direccion|=((fila&0x1)<<6);
    LCD1602_Com(direccion);
}



int LCD1602_Cadena(char* cadena,unsigned char* columna, unsigned char* fila)
{
    register int conteo=0;//variable usada para saber cuentos caracteres se imprimieron

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
        //toma como base para copiar el ultimo digito utilizado
        //ejemplo
       // convTemp="xxxxxxx-156\0"
       // punteroActual = "-156\0"
        //conv="-156\0"
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
    register int delay; //utilizada para los comandos como clear y home
    (*columna)&=0xF;//delimita el valor inicial de columna de 0 a 15
    LCD1602_Pos(*columna,*fila); //indica la posicion inicial del cursor
    while(*cadena)// realiza el ciclo mientras la cadena tenga algun valor
           //el valor 0 o '\0' es fin de cadena
    {
        switch (*cadena) //detecta si existe un caracter especial
        {
        case '\n': //salto de linea
            (*fila)++; //aumenta la fila
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\r': //retorno de carro
            *columna=0; //actualiza el valor de la columna a la primera posicion
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\t': //tabulacion
            if(((*columna)&0xF)<13)
                *columna+=3; //aumenta 3 espacios vacios
            else
            {
                *columna=0; // pasa a la siguiente fila si no cabe la tabulacion
                *fila++;
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
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
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\a'://borrado (ascii sonido)
            if(((*columna)!=0) || ((*fila)!=0)) //si la columna es diferente a 0 puede retroceder
            {
                if(((*columna)!=0))
                    (*columna)--;
                else
                    if(((*fila)!=0))
                    {
                        (*columna)=0xF;
                        (*fila)--;
                    }
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            LCD1602_Char(' ');//borra el caracter que pudiera haber en la posicion
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\e': //escape
            salir=1;//indica que se necesita salir de la funcion
            break;
        case '\f': //nueva pagina
            *columna=*fila=0;//reinicia los valores
            LCD1602_Com(CLEAR); //limpia la pantalla
            for(delay=3000; delay>0; delay--);//1.60 ms aprox a 16MHz
            LCD1602_Pos(*columna,*fila); //actualiza la posicion a 0,0
            break;
        default :
            LCD1602_Char(*(cadena)); //envia el caracter correspondiente
            (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
            if((*columna&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
            {
                (*columna)=0;
                (*fila)++; //invierte el valor e fila para que se reinciie
                LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
            }
            break;
        }
        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
        if(salir) //si detecto un \e (escape) sale del ciclo while
            break;
    }
     return conteo; //regresa el conteo de caracteres y caracteres especiales
}




unsigned char LCD1602_Printf(char* cadena,unsigned char* columna, unsigned char* fila,...)
{
    register unsigned char conteo=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    register char salir=0; //variable que funciona cuanod encuentra un ESC
    register int delay; //utilizada para los comandos como clear y home

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
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\r': //retorno de carro
            *columna=0; //actualiza el valor de la columna a la primera posicion
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\t': //tabulacion
            if(((*columna)&0xF)<13)
                *columna+=3; //aumenta 3 espacios vacios
            else
            {
                *columna=0; // pasa a la siguiente fila si no cabe la tabulacion
                *fila++;
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
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
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\a'://borrado (ascii sonido)
            if(((*columna)!=0) || ((*fila)!=0)) //si la columna es diferente a 0 puede retroceder
            {
                if(((*columna)!=0))
                    (*columna)--;
                else
                    if(((*fila)!=0))
                    {
                        (*columna)=0xF;
                        (*fila)--;
                    }
            }
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            LCD1602_Char(' ');//borra el caracter que pudiera haber en la posicion
            LCD1602_Pos(*columna,*fila); //actualiza la posicion
            break;
        case '\e': //escape
            salir=1;//indica que se necesita salir de la funcion
            break;
        case '\f': //nueva pagina
            *columna=*fila=0;//reinicia los valores
            LCD1602_Com(CLEAR); //limpia la pantalla
            for(delay=5000; delay>0; delay--);//1.60 ms aprox a 16MHz
            LCD1602_Pos(*columna,*fila); //actualiza la posicion a 0,0
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
                case 'f': //"%f"
                    valorARGd=(double)va_arg(ap, double);
                    Conv_Float((float)valorARGd,3,conversion);
                    conteo+=LCD1602_Cadena(conversion,columna,fila)-1;
                    break;




                case 'c': //"%c"
                    valorARGi=(unsigned char)va_arg(ap, unsigned char);
                    LCD1602_Char(valorARGi);//manda el caracter a la LCD
                    (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
                    if(((*columna)&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
                    {
                        (*columna)=0;
                        (*fila)++; //aumenta en uno la fila
                        LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
                    }
                    break;
                case 's':// "%s"
                    valorARGc=(char*)va_arg(ap,char*);  //el siguiente argumento es un puntero
                    conteo+=LCD1602_Print(valorARGc,columna,fila)-1;//imprime la cadena del puntero
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
                    LCD1602_Dato(*cadena);
                    (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
                    if(((*columna)&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
                    {
                        (*columna)=0;
                        (*fila)++; //invierte el valor e fila para que se reinciie
                        LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
                    }
                    break;

           }
            break;



        default :
            LCD1602_Char(*(cadena)); //envia el caracter correspondiente
            (*columna)++; //suma 1 a la columna indicando que se ha escrito un valor
            if((*columna&0xF)==0) //si la columna es 0 indica que empieza una nueva fila
            {
                (*columna)=0;
                (*fila)++; //invierte el valor e fila para que se reinciie
                LCD1602_Pos(*columna,*fila); //pone el cursor en 0,x
            }
            break;
        }
        cadena++; //el puntero apunta al siguiente caracter
        conteo++; //suma 1 al conteo total de caracter enviados a la LCD
        if(salir) //si detecto un \e (escape) sale del ciclo while
            break;
    }
    va_end(ap); //reinicia el puntero

     return conteo; //regresa el conteo de caracteres y caracteres especiales
}



