/*
 * Flash.c
 *
 *  Created on: 30 sep. 2017
 *      Author: InDev
 */

#include <Flash.h>
void Borrar_Segmento(char segmento)
{
    const register char seg=segmento;
    register char* dirSeg= (char*)0xFE00;
    register short valorWD=_WDTCTL;
    const register short valorIWD=_IE1&WDTIE;
    const register short IntGeneral=__get_SR_register()&0x8;
    if((seg>16) || (seg==0))
        return;
    valorWD&=~0xFF00;
    valorWD|=WDTPW;
    _DINT();
    _IE1&=~WDTIE;
    _WDTCTL= WDT_HOLD;
    dirSeg-=(0x200*seg);

    while(_FCTL3&BUSY);
    _FCTL2=(FWKEY|31|FSSEL_3);
    _FCTL3=FWKEY;
    _FCTL1=ERASE_KEY;
    *dirSeg=0;
    while(_FCTL3&BUSY);
    _FCTL3=LOCK_KEY;

    _WDTCTL=valorWD;
    _IE1|=valorIWD;
    __bis_SR_register(IntGeneral);

}


void Borrar_Flash()
{

    register char* dirSeg=(char*) 0xFE00;
    register short valorWD=_WDTCTL;
    const register short valorIWD=_IE1&WDTIE;
    const register short IntGeneral=__get_SR_register()&0x8;

    valorWD&=~0xFF00;
    valorWD|=WDTPW;
    _DINT();
    _IE1&=~WDTIE;
    _WDTCTL= WDT_HOLD;
    while(_FCTL3&BUSY);
    _FCTL2=(FWKEY|31|FSSEL_3);
    _FCTL3=FWKEY;
    _FCTL1=MERAS_KEY;
    *dirSeg=0;
    while(_FCTL3&BUSY);
    _FCTL3=LOCK_KEY;


    _WDTCTL=valorWD;
    _IE1|=valorIWD;
    __bis_SR_register(IntGeneral);

}

void Escribir_Byte(char dato, char segmento, short pos)
{
    const register char seg=segmento;
    register char* dirSeg= (char*)0xFE00;
    register short valorWD=_WDTCTL;
    const register short valorIWD=_IE1&WDTIE;
    const register short IntGeneral=__get_SR_register()&0x8;
    if((seg>16) || (seg==0))
        return;

    valorWD&=~0xFF00;
    valorWD|=WDTPW;
    _DINT();
    _IE1&=~WDTIE;
    _WDTCTL= WDT_HOLD;
    dirSeg-=(0x200*seg)+pos;

    while(_FCTL3&BUSY);
    _FCTL2=(FWKEY|31|FSSEL_3);
    _FCTL3=FWKEY;
    _FCTL1=WRT_KEY;
    *dirSeg=dato;
    _FCTL1=FWKEY;
    while(_FCTL3&BUSY);
    _FCTL3=LOCK_KEY;

    _WDTCTL=valorWD;
    _IE1|=valorIWD;
    __bis_SR_register(IntGeneral);
}

#pragma CODE_SECTION(modulo, ".TI.ramfunc")
char modulo(short pos)
{
       return pos%2;
}

void Escribir_Word(short dato, char segmento, short pos)
{
    const register char seg=segmento;
    register short* dirSeg= (short*)0xFE00;
    register short valorWD=_WDTCTL;
    const register short valorIWD=_IE1&WDTIE;
    const register short IntGeneral=__get_SR_register()&0x8;
    if((seg>16) || (seg==0) || (modulo(pos)))
           return;

    valorWD&=~0xFF00;
    valorWD|=WDTPW;
    _DINT();
    _IE1&=~WDTIE;
    _WDTCTL= WDT_HOLD;
    dirSeg-=(0x100*seg)+pos;


    while(_FCTL3&BUSY);
    _FCTL2=(FWKEY|31|FSSEL_3);
    _FCTL3=FWKEY;
    _FCTL1=WRT_KEY;
    *dirSeg=dato;
    _FCTL1=FWKEY;
    while(_FCTL3&BUSY);
    _FCTL3=LOCK_KEY;

    _WDTCTL=valorWD;
    _IE1|=valorIWD;
    __bis_SR_register(IntGeneral);
}



#pragma CODE_SECTION(Escribir_BlockByte, ".TI.ramfunc")
void Escribir_BlockByte(char* dato,short cantidad, char segmento, short pos)
{
    const register char seg=segmento;
    register char* dirSeg= (char*)0xFE00;
    register short valorWD=_WDTCTL;
    const register short valorIWD=_IE1&WDTIE;
    const register short IntGeneral=__get_SR_register()&0x8;
    register unsigned short i=0;
    if((seg>16) || (seg==0))
        return;

    valorWD&=~0xFF00;
    valorWD|=WDTPW;
    _DINT();
    _IE1&=~WDTIE;
    _WDTCTL= WDT_HOLD;
    dirSeg-=(0x200*seg)+pos;

    while(_FCTL3&BUSY);
    _FCTL2=(FWKEY|31|FSSEL_3);
    _FCTL3=FWKEY;
    _FCTL1=BLKWRT_KEY;

    while(cantidad)
    {
        dirSeg[i]=dato[i];
        while(!(_FCTL3&WAIT));
        i++;
        cantidad--;
    }
    _FCTL1=FWKEY;
    while(_FCTL3&BUSY);
    _FCTL3=LOCK_KEY;

    _WDTCTL=valorWD;
    _IE1|=valorIWD;
    __bis_SR_register(IntGeneral);
}

#pragma CODE_SECTION(Escribir_BlockWord, ".TI.ramfunc")
 void Escribir_BlockWord(short* dato,short cantidad, char segmento, short pos)
{
     const register char seg=segmento;
     register short* dirSeg= (short*)0xFE00;
     register short valorWD=_WDTCTL;
     const register short valorIWD=_IE1&WDTIE;
     const register short IntGeneral=__get_SR_register()&0x8;
     register unsigned short i=0;
     if((seg>16) || (seg==0)|| (modulo(pos)))
         return;

     valorWD&=~0xFF00;
     valorWD|=WDTPW;
     _DINT();
     _IE1&=~WDTIE;
     _WDTCTL= WDT_HOLD;
     dirSeg-=(0x100*seg)+pos;

     while(_FCTL3&BUSY);
     _FCTL2=(FWKEY|31|FSSEL_3);
     _FCTL3=FWKEY;
     _FCTL1=BLKWRT_KEY;

     while(cantidad)
     {
         dirSeg[i]=dato[i];
         while(!(_FCTL3&WAIT));
         i++;
         cantidad--;
     }
     _FCTL1=FWKEY;
     while(_FCTL3&BUSY);
     _FCTL3=LOCK_KEY;

     _WDTCTL=valorWD;
     _IE1|=valorIWD;
     __bis_SR_register(IntGeneral);
}

