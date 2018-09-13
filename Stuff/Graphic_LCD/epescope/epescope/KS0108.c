//-------------------------------------------------------------------------------------------------
// Universal KS0108 driver library
// (c) Rados³aw Kwiecieñ, radek@dxp.pl
//-------------------------------------------------------------------------------------------------
#include "KS0108.h"

#define KS0108_DATA_PORT	PORTD
#define KS0108_DATA_DIR		TRISD
#define KS0108_DATA_PIN		PORTD
#define KS0108_CTRL_PORT	PORTC
#define KS0108_CTRL_DIR		TRISC

#define KS0108_RS			(1 << 0)
#define KS0108_RW			(1 << 1)
#define KS0108_EN			(1 << 2)

#define KS0108_CS1			(1 << 5)
#define KS0108_CS2			(1 << 4)
#define KS0108_CS3			(1 << 5)

#define DISPLAY_STATUS_BUSY 0x80

extern const rom char font5x8[];

#pragma udata buffer_scn
static char buffer[2048];
#pragma udata

char * backbuffer = &buffer[0];

extern unsigned char screen_x, screen_y;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
unsigned char screen_x = 0, screen_y = 0;
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_Initalize(void)
{
unsigned char i;
GLCD_InitializePorts();
for(i = 0; i < 3; i++)
  GLCD_WriteCommand((DISPLAY_ON_CMD | 1), i);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_GoTo(unsigned char x, unsigned char y)
{
unsigned char i;
screen_x = x;
screen_y = y;

for(i = 0; i < KS0108_SCREEN_WIDTH/64; i++)
  {
  GLCD_WriteCommand(DISPLAY_SET_Y | 0,i);
  GLCD_WriteCommand(DISPLAY_SET_X | y,i);
  GLCD_WriteCommand(DISPLAY_START_LINE | 0,i);
  }
GLCD_WriteCommand(DISPLAY_SET_Y | (x % 64), (x / 64));
GLCD_WriteCommand(DISPLAY_SET_X | y, (x / 64));
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_ClearScreen(void)
{
unsigned char i, j;
for(j = 0; j < KS0108_SCREEN_HEIGHT/8; j++)
  {
  GLCD_GoTo(0,j);
  for(i = 0; i < KS0108_SCREEN_WIDTH; i++)
    GLCD_WriteData(0x00);
  }
}

void GLCD_Bitmap(char * bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy)
{
unsigned char i, j;
for(j = 0; j < dy / 8; j++)
  {
  GLCD_GoTo(x,y + j);
  for(i = 0; i < dx; i++) 
    GLCD_WriteData(GLCD_ReadByteFromROMMemory(bmp++));
  }
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

void GLCD_Delay(void)
	{
	char x = 0;
	}

void GLCD_InitializePorts(void)
	{
	KS0108_CTRL_PORT |= (KS0108_CS1 | KS0108_CS2 | KS0108_CS3);
	KS0108_CTRL_DIR &= ~(KS0108_CS1 | KS0108_CS2 | KS0108_CS3 | KS0108_RS | KS0108_RW | KS0108_EN);
	}

void GLCD_EnableController(unsigned char controller)
	{
	switch(controller)
		{
		case 0 : KS0108_CTRL_PORT &= ~KS0108_CS1; break;
		case 1 : KS0108_CTRL_PORT &= ~KS0108_CS2; break;
		case 2 : KS0108_CTRL_PORT &= ~KS0108_CS3; break;
		}
	}

void GLCD_DisableController(unsigned char controller)
	{
	switch(controller)
		{
		case 0 : KS0108_CTRL_PORT |= KS0108_CS1; break;
		case 1 : KS0108_CTRL_PORT |= KS0108_CS2; break;
		case 2 : KS0108_CTRL_PORT |= KS0108_CS3; break;
		}
}

unsigned char GLCD_ReadStatus(unsigned char controller)
	{
	unsigned char status;
	KS0108_DATA_DIR = 0xFF;
	KS0108_CTRL_PORT |= KS0108_RW;
	KS0108_CTRL_PORT &= ~KS0108_RS;
	GLCD_EnableController(controller);
	KS0108_CTRL_PORT |= KS0108_EN;
	GLCD_Delay();
	status = KS0108_DATA_PIN;
	KS0108_CTRL_PORT &= ~KS0108_EN;
	GLCD_DisableController(controller);
	return status;
	}

void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller)
	{
	while(GLCD_ReadStatus(controller)&DISPLAY_STATUS_BUSY);
	KS0108_DATA_DIR = 0x00;
	KS0108_CTRL_PORT &= ~KS0108_RW;
	KS0108_CTRL_PORT &= ~KS0108_RS;
	GLCD_EnableController(controller);
	KS0108_DATA_PORT = commandToWrite;
	KS0108_CTRL_PORT |= KS0108_EN;
	GLCD_Delay();
	KS0108_CTRL_PORT &= ~KS0108_EN;
	GLCD_DisableController(controller);
	}

unsigned char GLCD_ReadData(void)
	{
	unsigned char data;
	while(GLCD_ReadStatus(screen_x / 64)&DISPLAY_STATUS_BUSY);
	KS0108_DATA_DIR = 0xFF;
	KS0108_CTRL_PORT |= (KS0108_RW | KS0108_RS);
	GLCD_EnableController(screen_x / 64);
	//GLCD_Delay();
	KS0108_CTRL_PORT |= KS0108_EN;
	GLCD_Delay();
	data = KS0108_DATA_PIN;
	KS0108_CTRL_PORT &= ~KS0108_EN;
	GLCD_DisableController(screen_x / 64);
	screen_x++;
	return data;
	}

void GLCD_WriteData(unsigned char dataToWrite)
	{
	while(GLCD_ReadStatus(screen_x / 64)&DISPLAY_STATUS_BUSY);
	KS0108_DATA_DIR = 0x00;
	KS0108_CTRL_PORT &= ~KS0108_RW;
	KS0108_CTRL_PORT |= KS0108_RS;
	KS0108_DATA_PORT = dataToWrite;
	GLCD_EnableController(screen_x / 64);
	KS0108_CTRL_PORT |= KS0108_EN;
	GLCD_Delay();
	KS0108_CTRL_PORT &= ~KS0108_EN;
	GLCD_DisableController(screen_x / 64);
	screen_x++;
	}


unsigned char GLCD_ReadByteFromROMMemory(char * ptr)
	{
 	return *(ptr);
	}

void clr(void)
	{
	int x=0;
	while(x<2048)
		backbuffer[x++] = 0;
	}

void pixel(int x,int y,int cond)
	{
	int tmp;
	char pix,msk;
	char pow[8]={1,2,4,8,16,32,64,128};
	tmp = y  >> 3;
	pix = y - (tmp << 3);
	tmp <<=  7;
	tmp += x;
	pix = pow[ pix];
	msk = backbuffer[tmp];
	if(cond == 2)
		pix ^= msk;
	if (cond == 1)
		{
		pix = ~pix;
		pix &= msk;
		}
	if(cond == 0)
		pix |= msk;
	backbuffer[tmp] = pix;
	}

void box(int x1, int y1, int x2, int y2,int cond)
	{
	line( x1,  y1,  x2,  y1, cond);
	line( x1,  y1,  x1,  y2, cond);
	line( x1,  y2,  x2,  y2, cond);
	line( x2,  y1,  x2,  y2, cond);
	}

void line( int x1, int y1, int x2, int y2,int cond) 
	{
	int		x, y;
	int		dx, dy;
	int		incx, incy;
	int		balance;

	if (x2 >= x1)
		{
		dx = x2 - x1;
		incx = 1;
		}
	else
		{
		dx = x1 - x2;
		incx = -1;
		}
	if (y2 >= y1)
		{
		dy = y2 - y1;
		incy = 1;
		}
	else
		{
		dy = y1 - y2;
		incy = -1;
		}
	x = x1;
	y = y1;

	if (dx >= dy)
		{
		dy <<= 1;
		balance = dy - dx;
		dx <<= 1;
		while (x != x2)
			{
			pixel(x, y, cond);
			if (balance >= 0)
				{
				y += incy;
				balance -= dx;
				}
			balance += dy;
			x += incx;
			}
		 pixel(x, y, cond);
		}
	else
		{
		dx <<= 1;
		balance = dx - dy;
		dy <<= 1;
		while (y != y2)
			{
			pixel(x, y, cond);
			if (balance >= 0)
				{
				x += incx;
				balance -= dy;
				}
			balance += dx;
			y += incy;
			}
		 pixel(x, y, cond);
		}
	}

void blit (void)
	{
	int i, j;
	int t = 0;
	for(j = 0; j < 8; j++)
  		{
		GLCD_GoTo(0,0 + j);
  		for(i = 0; i < 128; i++) 
    		GLCD_WriteData(backbuffer[t++]);
  		}
	}

void charput(char ch, int x,int y)
	{
	int loop, addr;
	char mask, shift;
	rom char* addr2;
	addr = y >> 3;	
	shift = y - (addr << 3);
	addr <<= 7;
	addr += x;
	ch -= 0x20;
	addr2 = &font5x8[0];
	addr2 = addr2 + ((int)ch * 5);
	for( loop = 0; loop< 5;loop++)
		{
		backbuffer[loop + addr] =  (*addr2 << shift);
		backbuffer[loop + addr + 128] = (*addr2++ >> (8-shift));
		}	
	}

void strput(char* str, int x,int y)
	{
	int addr;
	
	while(*str)
		{
		charput(*str++,x,y);
		x+=6;
		}		
	}




