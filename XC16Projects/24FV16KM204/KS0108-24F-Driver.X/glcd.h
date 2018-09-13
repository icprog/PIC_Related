#ifndef GLCD_H
#define	GLCD_H

#include <xc.h>                 // include processor files - each processor file is guarded. 

void GoToXY(unsigned char X, unsigned char Y);

void LCDWriteChar(const unsigned char c);

void LCDWriteStringXY(unsigned char X, unsigned char Y, char *string);

void LCDWriteIntXY(unsigned char X, unsigned char Y, int value,signed char fieldLength);

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