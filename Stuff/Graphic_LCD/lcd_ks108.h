#include "ioh82138.h"

#define TRUE          0x01
#define FALSE         0x00
#define ON            TRUE
#define OFF           FALSE
#define HIGH          TRUE
#define LOW           FALSE
#define DATA          TRUE
#define INST          FALSE

#define NORMAL        0x00
#define INVERS        0x01

#define OUTPUT        0xFF
#define INPUT         0x00

#define ACTIVE        0xFF
#define INACTIVE      0x00

#define LCD_DATA      P3DR
#define LCD_DATA_DIR  P3DDR //?? Reihenfolge der Leitungen ?
#define LCD_DATA_PULL P3PCR
#define LCD_CTRL      P4DR
#define LCD_CTRL_DIR  P4DDR //?? Reihenfolge der Leitungen ?

void LcdInit(void);
void LcdClear(void);
void LcdDisplayGfx (void);
void LcdWriteString(unsigned char uchPosX,unsigned char uchPosY,unsigned char *uchText,unsigned char uchXMax,unsigned char uchStyle);
void LcdSetPoint(unsigned char uchPosX,unsigned char uchPosY);
void LcdClearPoint(unsigned char uchPosX,unsigned char uchPosY);
void LcdSetLine(unsigned char uchPosStartX,unsigned char uchPosStartY,unsigned char uchPosEndX,unsigned char uchPosEndY);
void LcdClearLine(unsigned char uchPosStartX,unsigned char uchPosStartY,unsigned char uchPosEndX,unsigned char uchPosEndY);
void LcdSetByte(unsigned char uchPosX,unsigned char uchPosY,unsigned char uchData);
