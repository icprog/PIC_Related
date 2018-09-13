#ifndef GLCD_H
#define	GLCD_H

#include <xc.h>                 // include processor files - each processor file is guarded. 

#define LCDWriteStringXY(X,Y,str){\
 GoToXY(X,Y);\
 LCDWriteString(str);\
}

#define LCDWriteIntXY(X,Y,value,fieldLength) {\
 GoToXY(X,Y);\
 LCDWriteInt(value,fieldLength);\
}



void GoToXY(unsigned char X, unsigned char Y);

void LCDWriteChar(const unsigned char c);

void LCDWriteString(char *string);

void LCDWriteInt(int value,signed char fieldLength);

void LCDWriteDecIntXY(unsigned char X, unsigned char Y, int value,signed char fieldLength);

void lcd_putchar(unsigned char X, unsigned char Y, char c);

void e_togg(void);

void busy(void);

void cmd_write(unsigned char x);

void data_write(unsigned char x);

void init_lcd(void);

void cls(void);

void loadimg(char const *image, unsigned int len);

//char load_num(char const *image, char number, int y, char x);
#endif