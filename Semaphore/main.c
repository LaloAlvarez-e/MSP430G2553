#include <msp430.h> 

/*
 * main.c
 */

//------------------ DEfincion de Puerto de Salida para salidas --------------------//
#define Sem1_Rojo_Puerto P1OUT
#define Sem1_Amarillo_Puerto P1OUT
#define Sem1_Verde_Puerto P1OUT

#define Sem2_Rojo_Puerto P1OUT
#define Sem2_Amarillo_Puerto P1OUT
#define Sem2_Verde_Puerto P1OUT

#define SemP_Rojo_Puerto P1OUT
#define SemP_Verde_Puerto P1OUT

//------------------ DEfincion de Puerto de Direccion para salidas --------------------//
#define Sem1_Rojo_Dir P1DIR
#define Sem1_Amarillo_Dir P1DIR
#define Sem1_Verde_Dir P1DIR

#define Sem2_Rojo_Dir P1DIR
#define Sem2_Amarillo_Dir P1DIR
#define Sem2_Verde_Dir P1DIR

#define SemP_Rojo_Dir P1DIR
#define SemP_Verde_Dir P1DIR

//------------------ DEfincion de Puerto de habilitacion para salidas --------------------//
#define Sem1_Rojo_Ren P1REN
#define Sem1_Amarillo_Ren P1REN
#define Sem1_Verde_Ren P1REN

#define Sem2_Rojo_Ren P1REN
#define Sem2_Amarillo_Ren P1REN
#define Sem2_Verde_Ren P1REN

#define SemP_Rojo_Ren P1REN
#define SemP_Verde_Ren P1REN





//------------------ DEfincion de Puerto de Entrada para salidas --------------------//
#define Carro1_Puerto P2IN
#define Carro2_Puerto P2IN
#define Peaton_Puerto P2IN

//------------------ DEfincion de Puerto de DIR para salidas --------------------//
#define Carro1_Dir P2DIR
#define Carro2_Dir P2DIR
#define Peaton_Dir P2DIR

//------------------ DEfincion de Puerto de REN para salidas --------------------//
#define Carro1_Ren P2REN
#define Carro2_Ren P2REN
#define Peaton_Ren P2REN

//------------------ DEfincion de Puerto de OUT para salidas --------------------//
#define Carro1_Out P2OUT
#define Carro2_Out P2OUT
#define Peaton_Out P2OUT



#define Sem1_Rojo_Pin BIT0
#define Sem1_Amarillo_Pin BIT1
#define Sem1_Verde_Pin BIT2

#define Sem2_Rojo_Pin BIT3
#define Sem2_Amarillo_Pin BIT4
#define Sem2_Verde_Pin BIT5

#define SemP_Rojo_Pin BIT6
#define SemP_Verde_Pin BIT7

#define Carro1_Pin BIT0
#define Carro2_Pin BIT1
#define Peaton_Pin BIT4

#define Sem1_Rojo_Pin_B 0
#define Sem1_Amarillo_Pin_B 1
#define Sem1_Verde_Pin_B 2

#define Sem2_Rojo_Pin_B 3
#define Sem2_Amarillo_Pin_B 4
#define Sem2_Verde_Pin_B 5

#define SemP_Rojo_Pin_B 6
#define SemP_Verde_Pin_B 7

#define Carro1_Pin_B 0
#define Carro2_Pin_B 1
#define Peaton_Pin_B 4
//---------------------------------------------------------
struct Estados
{
	unsigned char Salida[8];
	unsigned int Tiempo;
	const struct Estados *Estado_Siguiente[8];
};

typedef const struct Estados Tipo_Estados;

#define Verde1 &Maquina_Estados[0]
#define Amarillo1 &Maquina_Estados[1]
#define Rojo1 &Maquina_Estados[2]
#define Verde2 &Maquina_Estados[3]
#define Amarillo2 &Maquina_Estados[4]
#define Rojo2 &Maquina_Estados[5]
#define VerdeP &Maquina_Estados[6]
#define RojoP &Maquina_Estados[7]


unsigned char volatile* Puerto_Salida[8]={&Sem1_Verde_Puerto,&Sem1_Amarillo_Puerto,&Sem1_Rojo_Puerto,&Sem2_Verde_Puerto,
										  &Sem2_Amarillo_Puerto,&Sem2_Rojo_Puerto,&SemP_Verde_Puerto,&SemP_Rojo_Puerto};
unsigned char volatile* Dir_Salida[8]={&Sem1_Verde_Dir,&Sem1_Amarillo_Dir,&Sem1_Rojo_Dir,&Sem2_Verde_Dir,
										  &Sem2_Amarillo_Dir,&Sem2_Rojo_Dir,&SemP_Verde_Dir,&SemP_Rojo_Dir};
unsigned char volatile* Ren_Salida[8]={&Sem1_Verde_Ren,&Sem1_Amarillo_Ren,&Sem1_Rojo_Ren,&Sem2_Verde_Ren,
										  &Sem2_Amarillo_Ren,&Sem2_Rojo_Ren,&SemP_Verde_Ren,&SemP_Rojo_Ren};

unsigned char volatile Pin_Salida[8]={Sem1_Verde_Pin,Sem1_Amarillo_Pin,Sem1_Rojo_Pin,Sem2_Verde_Pin,
									  Sem2_Amarillo_Pin,Sem2_Rojo_Pin,SemP_Verde_Pin,SemP_Rojo_Pin};
unsigned char volatile Dir_Salidas[8]={Sem1_Verde_Pin,Sem1_Amarillo_Pin,Sem1_Rojo_Pin,Sem2_Verde_Pin,
									  Sem2_Amarillo_Pin,Sem2_Rojo_Pin,SemP_Verde_Pin,SemP_Rojo_Pin};
unsigned char volatile Ren_Salidas[8]={Sem1_Verde_Pin&0,Sem1_Amarillo_Pin&0,Sem1_Rojo_Pin&0,Sem2_Verde_Pin&0,
									  Sem2_Amarillo_Pin&0,Sem2_Rojo_Pin&0,SemP_Verde_Pin&0,SemP_Rojo_Pin&0};

unsigned char volatile* Puerto_Entrada[3]={&Carro1_Puerto,&Carro2_Puerto,&Peaton_Puerto};
unsigned char volatile* Dir_Entrada[3]={&Carro1_Dir,&Carro2_Dir,&Peaton_Dir};
unsigned char volatile* Ren_Entrada[3]={&Carro1_Ren,&Carro2_Ren,&Peaton_Ren};
unsigned char volatile* Out_Entrada[3]={&Carro1_Out,&Carro2_Out,&Peaton_Out};

unsigned char volatile Pin_Entradas[3]={Carro1_Pin,Carro2_Pin,Peaton_Pin};
unsigned char volatile Pin_B_Entradas[3]={Carro1_Pin_B,Carro2_Pin_B,Peaton_Pin_B};
unsigned char volatile Dir_Entradas[3]={Carro1_Pin&0,Carro2_Pin&0,Peaton_Pin&0};
unsigned char volatile Ren_Entradas[3]={Carro1_Pin,Carro2_Pin,Peaton_Pin};
unsigned char volatile Out_Entradas[3]={Carro1_Pin&0,Carro2_Pin&0,Peaton_Pin&0};

Tipo_Estados Maquina_Estados[8]=
{
		{{Sem1_Verde_Pin,0,0,0,0,Sem2_Rojo_Pin,0,SemP_Rojo_Pin}, 3000, {Verde1, Verde1, Amarillo1, Amarillo1, Amarillo1, Amarillo1, Amarillo1, Amarillo1}},
		{{0,Sem1_Amarillo_Pin,0,0,0,Sem2_Rojo_Pin,0,SemP_Rojo_Pin}, 500, {Rojo1, Rojo1, Rojo1, Rojo1, Rojo1, Rojo1, Rojo1, Rojo1}},
		{{0,0,Sem1_Rojo_Pin,0,0,Sem2_Rojo_Pin,0,SemP_Rojo_Pin}, 200, {Verde2, Verde2, Verde2, Verde2, VerdeP, VerdeP, VerdeP, VerdeP}},
		{{0,0,Sem1_Rojo_Pin,Sem2_Verde_Pin,0,0,0,SemP_Rojo_Pin}, 3000, {Verde2, Amarillo2, Verde2, Amarillo2, Amarillo2, Amarillo2, Amarillo2, Amarillo2}},
		{{0,0,Sem1_Rojo_Pin,0,Sem2_Amarillo_Pin,0,0,SemP_Rojo_Pin}, 500, {Rojo2, Rojo2, Rojo2, Rojo2, Rojo2, Rojo2, Rojo2, Rojo2}},
		{{0,0,Sem1_Rojo_Pin,0,0,Sem2_Rojo_Pin,0,SemP_Rojo_Pin}, 200, {Verde1, Verde1, Verde1, Verde1, VerdeP, VerdeP, VerdeP, Verde1}},
		{{0,0,Sem1_Rojo_Pin,0,0,Sem2_Rojo_Pin,SemP_Verde_Pin,0}, 3000, {RojoP, RojoP, RojoP, RojoP, VerdeP, RojoP, RojoP, RojoP}},
		{{0,0,Sem1_Rojo_Pin,0,0,Sem2_Rojo_Pin,0,SemP_Rojo_Pin}, 500, {Verde1, Verde1, Verde2, Verde1, Verde1, Verde1, Verde2, Verde2}}
};


void configurar_Puertos(void)
{
	int i;
	//P1DIR=0xFF;
	//P2DIR=0;
	//P2REN=(Carro1_Pin|Carro2_Pin|Peaton_Pin);
	//P2OUT=0;

	for(i=0; i<8;i++)
	{
	    		*Puerto_Salida[i]&=~Pin_Salida[i];
	    		*Dir_Salida[i]&=~Pin_Salida[i];
	    		*Ren_Salida[i]&=~Pin_Salida[i];
	    		*Dir_Salida[i]|=Dir_Salidas[i];
	    		*Ren_Salida[i]|=Ren_Salidas[i];
	}
	for(i=0; i<3;i++)
	{
	    		*Dir_Entrada[i]&=~Pin_Entradas[i];
	    		*Ren_Entrada[i]&=~Pin_Entradas[i];
	    		*Out_Entrada[i]&=~Pin_Entradas[i];
	    		*Dir_Entrada[i]|=Dir_Entradas[i];
	    	    *Ren_Entrada[i]|=Ren_Entradas[i];
	    		*Out_Entrada[i]|=Out_Entradas[i];
	}

	P1SEL=0;
	P1SEL2=0;
	P2SEL=0;
	P2SEL2=0;
}

void configurar_Timer(void)
{
	TACTL=0x210;
}

void retardo_1ms(unsigned long tiempo)
{
	TACCR0=1000; TAR=0; TACTL&=~1;
	int i;
	for(i=0;i<tiempo; i++)
	{
		while(!(TACTL&BIT0));
		TACTL&=~1;
	}
}

void main(void) {
	Tipo_Estados *Estado = Verde1;
	unsigned char Entrada;
	int i=0;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	configurar_Puertos();
	configurar_Timer();
    while(1)
	{
    	for(i=0; i<8;i++)
    	{
    		*Puerto_Salida[i]&=~Pin_Salida[i];
    		*Puerto_Salida[i]|=Estado->Salida[i];
    	}
    	retardo_1ms(Estado->Tiempo);
    	Entrada=0;
    	for(i=0; i<3; i++)
    	{
    		Entrada|=((*Puerto_Entrada[i]&Pin_Entradas[i])>>Pin_B_Entradas[i])<<i;
    	}
		Estado= Estado->Estado_Siguiente[Entrada];
	}
}
