// Wyœwietlacz graficzny ze sterownikiem Toshiba T6963C
// (c) Rados³aw Kwiecieñ, 2007
// Kompilator : arm-elf-gcc
//
#include "build/board.h"
#include "T6963C.h"

__inline void outByte(unsigned char byte)
{
AT91F_PIO_CfgOutput(AT91C_BASE_PIOA,(0xFF << T6963_D0));
AT91F_PIO_ForceOutput(AT91C_BASE_PIOA, (unsigned int)(byte << T6963_D0));
}

__inline unsigned char inByte(void)
{
AT91F_PIO_CfgInput(AT91C_BASE_PIOA,(0xFF << T6963_D0));
return ((AT91F_PIO_GetInput(AT91C_BASE_PIOA) >> T6963_D0) & 0xFF);
}


// funkcja wprowadzaj¹ca opóŸnienie zapewniaj¹ce 
// spe³nienie wymagañ czasowych sterownika T6963C

void delay(void)
{
volatile int i;
for(i = 0; i < 4; i++);
}



// funkcja odczytuj¹ca bajt statusu wyœwietlacza
int GLCD_Chceck_Status(void)
{
int tmp;

AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, T6963_CE | T6963_RD);
delay();

tmp = inByte();

AT91F_PIO_SetOutput(AT91C_BASE_PIOA, T6963_CE | T6963_RD);

return tmp;
}

// funkcja zapisu rozkazu do sterownika
void GLCD_Write_Command(int command)
{
while(!(GLCD_Chceck_Status()&0x03));

outByte(command);

AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, T6963_CE | T6963_WR);
delay();
AT91F_PIO_SetOutput(AT91C_BASE_PIOA, T6963_CE | T6963_WR);
}


void GLCD_Write_Data(int data)
{
while(!(GLCD_Chceck_Status()&0x03));

outByte(data);

AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, T6963_CE | T6963_WR | T6963_CD);
delay();
AT91F_PIO_SetOutput(AT91C_BASE_PIOA, T6963_CE | T6963_WR | T6963_CD);
}

int GLCD_Read_Data(void)
{
int tmp;
while(!(GLCD_Chceck_Status()&0x03));

AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, T6963_CE | T6963_RD | T6963_CD);
delay();
tmp = inByte();
AT91F_PIO_SetOutput(AT91C_BASE_PIOA, T6963_CE | T6963_RD | T6963_CD);
return tmp;
}

void GLCD_Clear_Text(void)
{
int i;
GLCD_Write_Data(GLCD_TEXT_HOME);
GLCD_Write_Data(GLCD_TEXT_HOME >> 8);
GLCD_Write_Command(T6963_SET_ADDRESS_POINTER);

for(i = 0; i < GLCD_TEXT_SIZE; i++)
  {
  GLCD_Write_Data(0);
  GLCD_Write_Command(T6963_DATA_WRITE_AND_INCREMENT);
  }
}

void GLCD_Clear_CG(void)
{
int i;
GLCD_Write_Data(GLCD_EXTERNAL_CG_HOME & 0xFF);
GLCD_Write_Data(GLCD_EXTERNAL_CG_HOME >> 8);
GLCD_Write_Command(T6963_SET_ADDRESS_POINTER);

for(i = 0; i < 256 * 8; i++)
  {
  GLCD_Write_Data(0);
  GLCD_Write_Command(T6963_DATA_WRITE_AND_INCREMENT);
  }
}


void GLCD_Clear_Graphic(void)
{
int i;
GLCD_Write_Data(GLCD_GRAPHIC_HOME & 0xFF);
GLCD_Write_Data(GLCD_GRAPHIC_HOME >> 8);
GLCD_Write_Command(T6963_SET_ADDRESS_POINTER);

for(i = 0; i < GLCD_GRAPHIC_SIZE; i++)
  {
  GLCD_Write_Data(0x00);
  GLCD_Write_Command(T6963_DATA_WRITE_AND_INCREMENT);
  }
}

void GLCD_Write_Char(char ch)
{
GLCD_Write_Data(ch - 32);
GLCD_Write_Command(T6963_DATA_WRITE_AND_INCREMENT);
}

void GLCD_Write_String(char * str)
{
while(*str)
  {
  GLCD_Write_Char(*str++);
  }
}

void GLCD_Text_GoTo(int x, int y)
{
int address;

address = GLCD_TEXT_HOME +  x + (GLCD_TEXT_AREA * y);

GLCD_Write_Data(address);
GLCD_Write_Data(address >> 8);
GLCD_Write_Command(T6963_SET_ADDRESS_POINTER);
}

void GLCD_Define_Character(int charCode, int * defChar)
{
int address;
int i; 

address = GLCD_EXTERNAL_CG_HOME + (8 * charCode);

GLCD_Write_Data(address);
GLCD_Write_Data(address >> 8);
GLCD_Write_Command(T6963_SET_ADDRESS_POINTER);

for(i = 0; i < 8 ; i++)
  {
  GLCD_Write_Data(*(defChar + i));
  GLCD_Write_Command(T6963_DATA_WRITE_AND_INCREMENT);
  }
}

void GLCD_Initalize(void)
{
volatile int i;
//GLCD_CTRL_PORT &= ~(1 << GLCD_RESET);
//_delay_ms(1);
//GLCD_CTRL_PORT |= (1 << GLCD_RESET);
AT91F_PMC_EnablePeriphClock(AT91C_BASE_PMC, (1 << AT91C_ID_PIOA));

AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, (T6963_RD | T6963_WR | T6963_CD| T6963_CE|T6963_FS | T6963_RESET));
AT91F_PIO_SetOutput(AT91C_BASE_PIOA, (T6963_RD | T6963_WR | T6963_CD| T6963_CE|T6963_FS | T6963_RESET));

AT91F_PIO_OutputWriteEnable(AT91C_BASE_PIOA,(0xFF << T6963_D0));

AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, T6963_RESET);
for(i = 0; i < 1000; i++);
AT91F_PIO_SetOutput(AT91C_BASE_PIOA, T6963_RESET);

#if (GLCD_FONT_WIDTH == 8)
AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, T6963_FS);
#endif

GLCD_Write_Data(GLCD_GRAPHIC_HOME & 0xFF);
GLCD_Write_Data(GLCD_GRAPHIC_HOME >> 8);
GLCD_Write_Command(T6963_SET_GRAPHIC_HOME_ADDRESS);


GLCD_Write_Data(GLCD_GRAPHIC_AREA);
GLCD_Write_Data(0x00);
GLCD_Write_Command(T6963_SET_GRAPHIC_AREA);


GLCD_Write_Data(GLCD_TEXT_HOME);
GLCD_Write_Data(GLCD_TEXT_HOME >> 8);
GLCD_Write_Command(T6963_SET_TEXT_HOME_ADDRESS);

GLCD_Write_Data(GLCD_TEXT_AREA);
GLCD_Write_Data(0x00);
GLCD_Write_Command(T6963_SET_TEXT_AREA);

GLCD_Write_Data(GLCD_OFFSET_REGISTER);
GLCD_Write_Data(0x00);
GLCD_Write_Command(T6963_SET_OFFSET_REGISTER);


GLCD_Write_Data(0);
GLCD_Write_Data(0);
GLCD_Write_Command(T6963_SET_ADDRESS_POINTER);

GLCD_Write_Command(T6963_DISPLAY_MODE  | T6963_GRAPHIC_DISPLAY_ON   | T6963_TEXT_DISPLAY_ON /*| T6963_CURSOR_DISPLAY_ON*/);

GLCD_Write_Command(T6963_MODE_SET | 0);

}

void GLCD_SetPixel(int x, int y, int color)
{
int tmp;
int address;

address = GLCD_GRAPHIC_HOME + (x / GLCD_FONT_WIDTH) + (GLCD_GRAPHIC_AREA * y);

GLCD_Write_Data(address & 0xFF);
GLCD_Write_Data(address >> 8);
GLCD_Write_Command(T6963_SET_ADDRESS_POINTER);

GLCD_Write_Command(T6963_DATA_READ_AND_NONVARIABLE);
tmp = GLCD_Read_Data();

if(color)
  tmp |= (1 <<  (GLCD_FONT_WIDTH - 1 - (x % GLCD_FONT_WIDTH)));
else
 tmp &= ~(1 <<  (GLCD_FONT_WIDTH - 1 - (x % GLCD_FONT_WIDTH)));

GLCD_Write_Data(tmp);
GLCD_Write_Command(T6963_DATA_WRITE_AND_INCREMENT);
}

