
#include <p18f4620.h>

#define KS0108_SCREEN_WIDTH		128
#define KS0108_SCREEN_HEIGHT	64

#define DISPLAY_SET_Y       0x40
#define DISPLAY_SET_X       0xB8
#define DISPLAY_START_LINE  0xC0
#define DISPLAY_ON_CMD		0x3E

#define DISPLAY_STATUS_BUSY	0x80

void GLCD_Delay(void);
void GLCD_EnableController(unsigned char controller);
void GLCD_DisableController(unsigned char controller);
unsigned char GLCD_ReadStatus(unsigned char controller);
void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller);
unsigned char GLCD_ReadData(void);
void GLCD_InitializePorts(void);
void GLCD_Initalize(void);
void GLCD_WriteData(unsigned char);
void GLCD_ClearScreen(void);
void GLCD_GoTo(unsigned char, unsigned char);
unsigned char GLCD_ReadByteFromROMMemory(char *);
void GLCD_Bitmap(char *, unsigned char, unsigned char, unsigned char, unsigned char);
void strput(char* ch, int x,int y);
void charput(char ch, int x,int y);
void blit (void);
void clr(void);
void line( int x1, int y1, int x2, int y2,int cond);
void box(int x1, int y1, int x2, int y2,int cond);
void pixel(int x,int y,int cond);
