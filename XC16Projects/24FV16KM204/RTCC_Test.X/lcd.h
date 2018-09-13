/* 
 * File:   lcd.h
 * Author: DAVE
 *
 * Created on May 16, 2015, 1:26 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

//LCD Functions Developed by electroSome
#include <xc.h>
#include "system.h"
#include "stdint.h"

#define RS _RC4
#define EN _RC6
#define D4 _RC0
#define D5 _RC1
#define D6 _RC2
#define D7 _RC3
    

char s [20];
    

//******************************************************************************
//      L C D   T y p e   S e l e c t i o n    (Uncomment Just one of them)
//******************************************************************************

//#define LCD_TYPE_2_LINE                     //For 2 line LCD's

#define LCD_TYPE_4_LINE                     //For 4 line LCD's


#define LCDWriteStringXY(x,y,a) {\
 LCD_Set_Cursor(x,y);\
 LCD_Write_String(a);\
}


void LCD_Port(char a)
{
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}
void LCD_Cmd(char a)
{
	RS = 0;             // => RS = 0
	LCD_Port(a);
	EN  = 1;             // => E = 1
    __delay_ms(4);
    EN  = 0;             // => E = 0
}

void LCD_Clear()
{
	LCD_Cmd(0);
	LCD_Cmd(1);
}


#ifdef LCD_TYPE_2_LINE                                                          // For 2 Line LCD's

void LCD_Set_Cursor(char a, char b)
{
	char temp,z,y;
    
	if(a == 0)
	{                
        temp = 0x80 + b;
		z = temp>>4;
		y = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(y);
	}

	else if(a == 1)
	{
		temp = 0xC0 + b;
		z = temp>>4;
		y = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(y);
	}

#endif

#ifdef LCD_TYPE_4_LINE                                                          // For 4 line LCD's

void LCD_Set_Cursor(char x, char y)
{
	char temp,z,w;
    
	if(x == 0)
	{                
        temp = 0x80 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

	else if(x == 1)
	{
		temp = 0xC0 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

	else if(x == 2)
	{
        temp = 0x94 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

    else if(x == 3)
	{
	    temp = 0xD4 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}
    #endif
    
}

void LCD_Init()
{
    LCD_Port(0x00);
    __delay_ms(20);
    LCD_Cmd(0x03);
	__delay_ms(5);
    LCD_Cmd(0x03);
	__delay_ms(11);
    LCD_Cmd(0x03);
  /////////////////////////////////////////////////////
    LCD_Cmd(0x02);
    LCD_Cmd(0x02);
    LCD_Cmd(0x08);
    LCD_Cmd(0x00);
    LCD_Cmd(0x0C);
    LCD_Cmd(0x00);
    LCD_Cmd(0x06);
    }

void LCD_Write_Char(char a)
{
    char temp,y;
    temp = a&0x0F;
    y = a&0xF0;
    RS = 1;             // => RS = 1
    LCD_Port(y>>4);             //Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
    LCD_Port(temp);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void LCD_Write_String(const char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_Write_Char(a[i]);
}

void LCD_Shift_Right()
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x0C);
}

void LCD_Shift_Left()
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x08);
}

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

