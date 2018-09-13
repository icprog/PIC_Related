#ifndef LCD_H
#define	LCD_H

#include    "system.h"

// ****MACROS*****************************************************************************************************************************************************
#define LCDWriteStringXY(x,y,a){\
 gotoXY(x,y);\
 LCD_Write_String(a);\
}
// ***************************************************************************************************************************************************************
#define LCDWriteIntXY(x,y,val,field_length, numPlaces, sign) {\
 gotoXY(x,y);\
 LCD_Write_Int(val,field_length, numPlaces, sign);\
}


void gotoXY(int8_t x, int8_t y);

//This takes a large array of bits and sends them to the LCD
void LCDBitmap(const char my_array[]);

//This function takes in a character, looks it up in the font table/array
//And writes it to the screen
//Each character is 8 bits tall and 5 bits wide. We pad one blank column of
//pixels on each side of the character for readability.
void LCD_Write_Character(const char character);


//Given a string of characters, one by one is passed to the LCD
void LCD_Write_String(const char *characters);


//Clears the LCD by writing zeros to the entire screen
void LCD_Clear(void);

void LCD_Write_Int(int value,signed char fieldLength, signed char numPlaces, signed char sign);

//This sends the magical commands to the PCD8544
void LCDInit(void);

//There are two memory banks in the LCD, data/RAM and commands. This
//function sets the DC pin high or low depending, and then sends
//the data byte
void LCDWrite(uint8_t data_or_command, uint8_t data);

void drawBox(void);

#endif