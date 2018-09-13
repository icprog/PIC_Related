// ***** LCD Display Code to Operate a NOKIA 5110 Serial Display ***************
#ifndef LCD_H
#define	LCD_H

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
void gotoXY(char x, char y);

// ***** Display BitMap Image on Display ***************************************
void LCDBitmap(const char bmp_array[], uint8_t startLine, uint16_t len);

// ***** Write Single Character to Display *************************************
void LCDWriteCharacter(const char character);

// ***** Write String of Characters to Display *********************************
void LCDWriteString(const char *characters);

// ***** Clear LCD *************************************************************
void LCDClear(void);

// ***** Write an Integer value to the Display *********************************
void LCDWriteInt(int value,signed char fieldLength, signed char numPlaces, signed char sign);

// ***** Initialize the LCD Display ********************************************
void LCDInit(void);

// ***** Write Serial Data to the Display **************************************
void LCDWrite(uint8_t data_or_command, uint8_t data);

// ***** Draw a simple Box to the Display **************************************
void LCDDrawBox(void);

#endif