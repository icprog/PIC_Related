#ifndef LCD_H
#define LCD_H

#include <xc.h>
#include "system.h"
#include <stdint.h>

// ***********************************************
// LCD Type Selection
// Uncomment Just one of them
// ************************************************
#define LCD_TYPE_2_LINE	//For 16 or 20 Chars by 2 lines
//#define LCD_TYPE_4_LINE     //For 16 or 20 Chars by 4 lines
// ************************************************
#define RS  RA0             // Define REGISTER SELECT Bit
//      RW  Tied to Vss
#define EN  RA2             // Define ENABLE Bit
#define D4  RA7             // Define LCD Data Port D4
#define D5  RA6             // Define LCD Data Port D5
#define D6  RC0             // Define LCD Data Port D6
#define D7  RC1             // Define LCD Data Port D7
// ***************************************************************************************************************************************************************
#define NONE     0X00
#define BLINK    0X01
#define ULINE    0X02
#define BLUL     0X03 
// ****MACROS*****************************************************************************************************************************************************
#define LCDWriteStringXY(x,y,a) {\
 LCD_Set_Cursor(x,y);\
 LCD_Write_String(a);\
}
// ***************************************************************************************************************************************************************
#define LCDWriteIntXY(x,y,val,field_length, numPlaces, sign) {\
 LCD_Set_Cursor(x,y);\
 LCD_Write_Int(val,field_length, numPlaces, sign);\
}
// ***************************************************************************************************************************************************************
void InitCustomChars();
// ***************************************************************************************************************************************************************
void LCD_Port(uint8_t a);
// ***************************************************************************************************************************************************************
void LCD_Cmd(uint8_t a);
// ***************************************************************************************************************************************************************
void LCD_Clear();
// ***************************************************************************************************************************************************************
void LCD_Set_Cursor(uint8_t x, uint8_t y);
// ***************************************************************************************************************************************************************
void LCD_Init(char style);
// ***************************************************************************************************************************************************************
void LCD_Write_Char(const char a);
// ***************************************************************************************************************************************************************
void LCD_Write_String(const char *a);
// ***************************************************************************************************************************************************************
void LCD_Write_Int(int16_t value,int8_t fieldLength, uint8_t numPlaces, uint8_t sign);
// ***************************************************************************************************************************************************************
//void LCD_Shift_Right();
// ***************************************************************************************************************************************************************
//void LCD_Shift_Left();
#endif
