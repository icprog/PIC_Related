#ifndef GLCD_H
#define	GLCD_H

#include <xc.h>     // include processor files - each processor file is guarded. 

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

void GoToXY(unsigned char X, unsigned char Y);

void LCDWriteChar(const unsigned char c);

void LCDWriteString(char *string);

void LCDWriteInt(int value,signed char fieldLength, signed char numPlaces);

//void lcd_putchar(unsigned char X, unsigned char Y, char c);

void e_togg(void);

void busy(void);

void cmd_write(unsigned char x);

void data_write(unsigned char x);

void init_lcd(void);

void cls(void);

void loadimg(const unsigned char *image, unsigned int len, char startPage);

//char load_num(char const *image, char number, int y, char x);

#endif