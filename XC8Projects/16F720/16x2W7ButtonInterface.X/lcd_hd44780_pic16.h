/* 
 * File:   lcd_hd44780_pic16.h
 * Created on 6 June, 2013, 11:51 AM
 */

#ifndef LCD_HD44780_PIC16_H
#define	LCD_HD44780_PIC16_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif


//LCD Data Port
//Port RC0-RC3 are connected to D4-D7
#define LCD_DATA        C   //Port RC0-RC3 are connected to D4-D7, RC0 is Pin 16 on 16F720,
#define LCD_DATA_POS    0   // RC1 is Pin 15 on 16F720, RC2 is Pin 14, RC3 is Pin 7

//Register Select (RS)
//RS is connected to Port RC bit 4
#define LCD_RS_PORT     C
#define LCD_RS_POS      4       // Pin 6 on 16F720

//Read/Write (RW)
//RW is connected to Port RC bit 5
#define LCD_RW_PORT     C
#define LCD_RW_POS      5       // Pin 5 on 16F720

//Enable signal (E)
//E is connected to Port RC bit 6
#define LCD_E_PORT      C
#define LCD_E_POS       6       // Pin 8 on 16F720

/***********************************************

LCD Type Selection
Uncomment Just one of them

************************************************/

//#define LCD_TYPE_202	//For 20 Chars by 2 lines

//#define LCD_TYPE_204	//For 20 Chars by 4 lines

#define LCD_TYPE_162	//For 16 Chars by 2 lines

//#define LCD_TYPE_164	//For 16 Chars by 4 lines


#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010
#define LS_NONE	 0B00000000


void LCDInit(uint8_t style);
void LCDWriteString(const char *msg);
void LCDWriteInt(int val,int8_t field_length);
void LCDGotoXY(uint8_t x,uint8_t y);

//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();


#define LCDClear() LCDCmd(0b00000001)
#define LCDHome()  LCDCmd(0b00000010)

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}

//#ifdef	__cplusplus
//}
//#endif

#endif	// LCD_HD44780_PIC16_H

