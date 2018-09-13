#ifndef GLCD_H
#define	GLCD_H

#include <xc.h>     // include processor files - each processor file is guarded. 
#include "system.h"
#include <stdint.h>
//#include "menu.h"

//Macro Definitions
#define LCDWriteStringXY(X,Y,str){\
 GoToXY(X,Y);\
 LCDWriteString(str);\
}

#define LCDWriteIntXY(X,Y,value,fieldLength,numPlaces) {\
 GoToXY(X,Y);\
 LCDWriteInt(value,fieldLength,numPlaces);\
}

//Function Definitions

//uint8_t putChar(uint8_t X, uint8_t Y, const uint8_t c);

//void CharStr(uint8_t X, uint8_t Y, uint8_t *string);

//void GoTo_XY(uint8_t X, uint8_t Y);

void GoToXY(unsigned char X, unsigned char Y);

void LCDWriteChar(const unsigned char c);

void LCDWriteString(char *string);

void LCDWriteInt(int value,signed char fieldLength, signed char numPlaces);

//unsigned char lcd_putchar(unsigned char X, unsigned char Y, char c);

void e_togg(void);

void busy(void);

void cmd_write(unsigned char x);

void data_write(unsigned char x);

void init_lcd(void);

void cls(void);

void loadimg(const unsigned char *image, unsigned int len, char startPage);

void displayOn(int controlCode);

//char printChar(char const *image, char number, char x, int y);

#endif