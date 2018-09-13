#ifndef HD44780_H
#define	HD44780_H

#include <xc.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

//******************************************************************************
//      L C D   T y p e   S e l e c t i o n    (Uncomment Just one of them)
//******************************************************************************

//#define LCD_TYPE_202	//For 20 Chars by 2 lines

//#define LCD_TYPE_204	//For 20 Chars by 4 lines

#define LCD_TYPE_162	//For 16 Chars by 2 lines

//#define LCD_TYPE_164	//For 16 Chars by 4 lines


//******************************************************************************
//         L C D   C O N N E C T I O N S
//******************************************************************************

#define LCD_DATA        C   //Port RC0-RC3 are connected to D4-D7
#define LCD_DATA_POS    0

#define LCD_RS_PORT     C   //Register Select (RS)
#define LCD_RS_POS      4   //RS is connected to Port D bit 4

#define LCD_RW_PORT     C   //Read/Write (RW)
#define LCD_RW_POS      7   //RW is connected to Port D bit 5

#define LCD_E_PORT      C   //Enable signal (E)
#define LCD_E_POS       6   //E is connected to Port D bit 6

    
//******************************************************************************
//     D E F I N E S
//******************************************************************************
#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010
#define LS_NONE	 0B00000000

#define _CONCAT(a,b) a##b
#define _CONCAT2(port,pos)  TRIS##port##bits.TRIS##port##pos
#define _CONCAT3(port,pos)  R##port##pos
#define PORT(x) _CONCAT(PORT,x)
#define TRIS(x) _CONCAT(TRIS,x)
#define TRISBIT(__port,__pos) _CONCAT2(__port,__pos)
#define PORTBIT(__port,__pos) _CONCAT3(__port,__pos)
    


//******************************************************************************
//			F U N C T I O N   P R O T O T Y P E S
//******************************************************************************
void LCDReset(uint8_t style);
void LCDInit(uint8_t style);
void LCDWriteString(const char *msg);
void LCDWriteInt(int val,int8_t field_length);
void LCDGotoXY(uint8_t x,uint8_t y);
unsigned char __cgram[];

//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();


//******************************************************************************
//	M A C R O S
//******************************************************************************

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

#ifdef	__cplusplus
}
#endif

#endif