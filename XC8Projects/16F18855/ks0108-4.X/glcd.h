
#include <xc.h>
#include "system.h"
#include "font.h"

#define GLCD_Data   PORTC
#define b_GLCD_GCS1 LATBbits.LATB0
#define b_GLCD_GCS2 LATBbits.LATB1
#define b_GLCD_RS   LATBbits.LATB2
#define b_GLCD_RW   LATBbits.LATB3
#define b_GLCD_E    LATBbits.LATB4
#define b_GLCD_On   LATBbits.LATB5

#define TRIS_Data    TRISC
#define b_TRIS_GCS1  TRISBbits.TRISB0 //GCS1
#define b_TRIS_GCS2  TRISBbits.TRISB1 //GCS2 
#define b_TRIS_RS    TRISBbits.TRISB2 //RS 
#define b_TRIS_RW    TRISBbits.TRISB3 //RW 
#define b_TRIS_E     TRISBbits.TRISB4 //E 
#define b_TRIS_On    TRISBbits.TRISB5 //RST

unsigned char GLCD_Read(void);

void Wait_Not_Busy(void);

void GLCD_Write_Cmd(unsigned char data);

void GLCD_Write_Data (unsigned char data);

void ClearScreen(void);

void Init_GLCD(void);

void PutChar(unsigned char data);

unsigned char GLCD_Read_Data(void);

void SetPos(unsigned char x,unsigned char y);

void WritePosition(void);

void plot(unsigned char x,unsigned char y);

void hline(unsigned char x,unsigned char y1,unsigned char y2);

void vline(unsigned char x1,unsigned char x2,unsigned char y);

void box(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);

void PutMessage(unsigned char const *Message);

void PutLogo(unsigned char const *logo);
