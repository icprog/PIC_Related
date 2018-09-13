// ***** LCD Display Code to Operate a NOKIA 5110 Serial Display ***************
#ifndef LCD_5110_SPI_H
#define	LCD_5110_SPI_H

#include    "system.h"

// ***** MACROS DEFINITIONS ****************************************************
#define LCDWriteStringXY(x,y,a){\
 gotoXY(x,y);\
 LCDWriteString(a);\
}

#define LCDWriteIntXY(x,y,val,field_length, numPlaces, sign) {\
 gotoXY(x,y);\
 LCDWriteInt(val,field_length, numPlaces, sign);\
}

// ***** goto Screen Location **************************************************
void gotoXY( char x,  char y);

// ***** Display BitMap Image on Display ***************************************
void LCDBitmap(const char bmp_array[],  char startLine, int len);

// ***** Write Single Character to Display using SPI ***************************
//void SPIWrite(const char sentCharacter);

// ***** Write Single Character to Display *************************************
void LCDWriteCharacter(char character);

// ***** Write String of Characters to Display *********************************
void LCDWriteString(char *characters);

// ***** Clear LCD *************************************************************
void LCDClear(void);

// ***** Write an Integer value to the Display *********************************
void LCDWriteInt(int value, signed char fieldLength,  char numPlaces,  char sign);

// ***** Initialize the LCD Display ********************************************
void LCDInit(void);

// ***** Write Serial Data to the Display using SPI ****************************
void SPIWrite( char data_or_command, char data);

// ***** Write Serial Data to the Display **************************************
void LCDWrite( char data_or_command, char data);

// ***** Draw a simple Box to the Display **************************************
void LCDDrawBox(void);

#endif