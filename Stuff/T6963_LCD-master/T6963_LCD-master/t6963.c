/*
 ***********************************************************************************************
 *                           Toshiba T6963C Graphical LCD Display Driver
 *
 * File name     : t6963.c
 * Programmer    : John Leung, TechToys, Hong Kong
 * Web presence  : www.TechToys.com.hk
 * Note          : References - picant complier web page, epe magazine Feb 2001
 *                 & Jean J Labrosse's Embedded Systems Building Blocks
 *                 & treitmey's driver on CCS forum
 * Language      : CCS C complier for PIC mid-range MCU, PCM version 3.170, under MPLAB IDE 7.01
 * Hardware      : Prototype board PCB ver 2.5(home-grown), EQS Console, MCU 16F877a, 20MHz Xtal
 * Date          : Version 0.0 (20 April 2005 - 27 April 2005)
 * Date          : 3 May 2005
 *               : Routine void GDispPixFontAt(x, y, textptr, size, color) and font5x7.h added
 ***********************************************************************************************
 *                                       DESCRIPTION
 *
 * This module provides an interface to Toshiba T6963C-0101 Graphical LCD of size 128x64 dots
 * A 128-word character generator ROM (code 0101) T6963C-0101 built-in.
 * Graphics l.c.d. pinout function
 * pin 1 FG  frame ground
 * pin 2 GND signal ground
 * pin 3 +5V Positive supply
 * pin 4 CX  Negative supply (-3.5V approx)
 * pin 5 WR  Data write (active low)
 * pin 6 RD  Data read (active low)
 * pin 7 CE  Chip enable (active low)
 * pin 8 CD  CD=1, WR=0: command write
 *           CD=1, WR=1: command read
 *           CD=0, WR=0: data write
 *           CD=0, WR=1: data read
 * pin 9 RST Module reset (active low)
 * pin 10 - 17   Data bus
 * pin 18 FS Font select: FS=0(8x8 font), FS=1(or open circuit, 6x8 font)
 * On EQS console ver 2.5 PCB, FS is determined by JP23 jumper. FS=0 when shorted
 *
 ***********************************************************************************************
 */
#include "../lib/include/pic24_all.h"
#include "t6963.h"
#include "font5x7.h"        //custom-defined 5x7 font, for GDispPixFontAt(...)
#include <string.h>
#define bit_test(x,n)(x & (0x01<<n))
#define TIME_DELAY 1
/*
 ***********************************************************************************************
 *                                       LOCAL CONSTANTS
 ***********************************************************************************************
 */
#define CURSOR_PTR_SET      0x21    //Cursor Pointer Set
#define OFFSET_REG_SET      0x22    //Set Offset Command
#define ADDR_PTR_SET        0x24    //Set Address Pointer Command

#define TEXT_HOME_SET       0x40    //Text Home Address Set: Data = low, high addr
#define TEXT_AREA_SET       0x41    //Text Area Set: Data = columns, 0
#define GRAPH_HOME_SET      0x42    //Graphics Home address Set: Data = low, high addr
#define GRAPH_AREA_SET      0x43    //Graphics Area Set: Data = columns, 0
#define SCREEN_PEEK         0xE0    //Read data from screen command
#define SCREEN_COPY         0xE8    //Screen Copy

#define AUTO_WR_ON          0xB0
#define DATA_AUTO_RD        0xB1
#define AUTO_WR_OFF         0xB2

#define DATA_WR_INC         0xC0    // Data write and increment addrespointer
#define DATA_RD_INC         0xC1    // Data read and increment  addrespointer
#define DATA_WR_DEC         0xC2    // Data write and decrement addrespointer
#define DATA_RD_DEC         0xC3    // Data read and decrement  addrespointer
#define DATA_WR             0xC4    // Data write - no addr change
#define DATA_RD             0xC5    // Data read  - no addr change

/*
 *********************************************************************************************************
 *                                   LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */
static void GDispCmdAddrSend (uint16_t Addr, UCHAR cmd);

/*
 *********************************************************************************************************
 *                                       SEND ADDRESS COMMAND
 *
 * Description : This function sends screen address with a command to the LCD screen
 * Arguments   : 'Addr'  is the screen address to send
 *               'cmd'   is the command
 * Returns     : none
 * Notes       : Most often a graphic LCD needs a screen address for command setup.
 *               Example, set Graph Home Address is the command GRAPH_HOME_SET (0x42), at the ram address
 *               GRH_HOME_ADDR (0x0200), say.
 *********************************************************************************************************
 */
static void
GDispCmdAddrSend (uint16_t Addr, UCHAR cmd)
{
  UCHAR c;

  c = Addr & 0x00FF;
  GDispDataWr (c); //Send LSB of 'Addr' first
  c = Addr >> 8;
  GDispDataWr (c); //Send MSB of 'Addr' afterwards
  GDispCmdSend (cmd);
}

/*
 *********************************************************************************************************
 *                                       DISPLAY DRIVER INITIALIZATION
 *
 * Description : This function initializes the display driver
 * Arguments   : none
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispInit (void)
{
  //Reset the LCD module and perform a hardware port init
  GDispInitPort ();
  //Set Text Home address to TEXT_HOME_ADDR
  GDispCmdAddrSend (TEXT_HOME_ADDR, TEXT_HOME_SET);
  //Set Graph Home address to GRH_HOME_ADDR
  GDispCmdAddrSend (GRH_HOME_ADDR, GRAPH_HOME_SET);
  //Set Text Area to COLUMN column mode
  GDispCmdAddrSend (COLUMN, TEXT_AREA_SET);
  //Set Graph Area to COLUMN column mode
  GDispCmdAddrSend (COLUMN, GRAPH_AREA_SET);
  //Set Offset register to 0x0002, CG Ram start address = $1400 (CG_HOME_ADDR)
  //first character code $80 for CG Ram
  GDispCmdAddrSend (0x0002, OFFSET_REG_SET);
  LCD_FS = 0;  // set font select to 8x8
}

/*
 *********************************************************************************************************
 *                               SET MODE FOR DISPLAY/MODE/CURSOR/TEXT_ATTRIBUTE
 *
 * Description : This function sets mode
 * Arguments   : 'mode'  , refer to mode available in t6963.h, MODE Section, CURSOR MODE, TEXT ATTRI
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispSetMode (UCHAR mode)
{
  GDispCmdSend (mode);
}

/*
 *********************************************************************************************************
 *                                           CLEAR TEXT SCREEN
 *
 * Description : This function clears the text clear in font mode
 * Arguments   : none
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispClrTxt (void)
{
  uint16_t row;
  uint16_t col;
  int i;

  //Set address pointer to address (TEXT_HOME_ADDR)
  GDispCmdAddrSend (TEXT_HOME_ADDR, ADDR_PTR_SET);
  //Set Auto Write ON
  GDispCmdSend (AUTO_WR_ON);

  //row runs from 0 ... (MAX_ROW_PIXEL/8 -1), in form of a cell of (FontSize x 8) bits
  for (row = 0; row < MAX_ROW_PIXEL / 8; row++)
    { //write blank to clear screen the first page only, col = 0...(COLUMN-1)
      for (col = 0; col < COLUMN; col++)
      {
         GDispAutoDataWr (0x00);
      }
    }
  //Set Auto Write OFF
  GDispCmdSend (AUTO_WR_OFF);
}

/*
 *********************************************************************************************************
 *                                       CLEAR THE GRAPHIC AREA
 *
 * Description : This function clears the graphic area pixel by pixel
 * Arguments   : none
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispClrGrh (void)
{
  uint16_t row;
  uint16_t col;

  //Set address pointer to address (GRH_HOME_ADDR)
  GDispCmdAddrSend (GRH_HOME_ADDR, ADDR_PTR_SET);
  GDispCmdSend (AUTO_WR_ON);
  //row runs from 0 ... (MAX_ROW_PIXEL-1), in form of a byte size of (FontSize x 1) bits
  for (row = 0; row < MAX_ROW_PIXEL; row++)
    { //write blank to clear screen the first page only, col = 0...(COLUMN-1)
      for (col = 0; col < COLUMN; col++)
    {
      GDispAutoDataWr (0x00);
    }
    }
  GDispCmdSend (AUTO_WR_OFF); //Set Auto Write OFF
}

/*
 *********************************************************************************************************
 *                                       GOTO A POSITION (row, col)
 *
 * Description : This function sets the screen address pointer to a position row, col
 * Arguments   : 'row'   row = 0...(MAX_ROW_PIXEL/8 - 1), the cell number in 8 bits height
 *               'col'   col = 0...(COLUMN-1), is the column position in font width (6/8 font)
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispGoto (uint16_t row, uint16_t col)
{
  uint16_t addr;

  addr = row * COLUMN + col + TEXT_HOME_ADDR;
  GDispCmdAddrSend (addr, ADDR_PTR_SET); //Set address pointer
}

/*
 *********************************************************************************************************
 *                     DISPLAY A CHARACTER AT THE CURRENT SCREEN ADDRESS POINTER
 *
 * Description : This function is used to display a single character on the display device at row, col
 *               col, row should have been set by GDispGoto(row, col) before. AUTO ADDRESS POINTER INC!
 * Arguments   : 'c'     is the ASCII character to write
 * Returns     : none
 * Notes       : This function gets around the problem that pointers cannot be created to constant string
 *               in PCM. Referring to CCS Reference Manual (page 67), a function that has one CHAR
 *               parameter will accept a constant string where it is called. PCM will generate a loop
 *               that will call the function once for each character in the string.
 *               Example :
 *                   GDispGoto(5,5);
 *                   GDispChar("Hello there!");
 *********************************************************************************************************
 */
void
GDispChar (UCHAR c)
{
  GDispDataWr (c - 0x20); //Adjust standard ASCII to T6963 ASCII
  GDispCmdSend (DATA_WR_INC); //Address pointer increment ON
}

/*
 *********************************************************************************************************
 *                             DISPLAY A CHARACTER AT A POSITION (row, col)
 *
 * Description : This function is used to display a single character on the display device, address
 *               auto increment OFF!
 * Arguments   : 'row'   row = 0...(MAX_ROW_PIXEL/8 - 1), the row pos of the cursor (MAX_ROW_PIXEL/8-1) 
 *               'col'   col = 0...(COLUMN-1), is the column position in font width (6/8 font)
 *               'c'     is the ASCII character to write
 * Returns     : none
 * Notes       : COLUMN constant determines the number of page, can be > physical size of the LCD
 *********************************************************************************************************
 */
void
GDispCharAt (uint16_t row, uint16_t col, UCHAR c)
{
  GDispGoto (row, col);
  GDispDataWr (c - 0x20);
  GDispCmdSend (DATA_WR);
}

void
GDispStringAt(uint16_t row, uint16_t col, char *c)
{
  char *str;
  int i;

  str = c;
  i = 0;
  while(*(str+i) != 0)
  {
     GDispCharAt(row,col+i,*(str+i));
     i++;
     if(i > 100)
       return;
  }
}

/*
 *********************************************************************************************************
 *                                       SET CURSOR AT A POSITION
 *
 * Description : This function sets cursor at a position (row, col), of certain mode & type
 * Arguments   : 'mode' is the mode of cursor. It should be bitwise OR with a TEXT / GRAPH mode to work
 *                      mode =   TEXT_GRH_ON|CURSOR_BLINK_ON
 *                               TEXT_ON|CURSOR_ON_BLINK_OFF....
 *                               TEXT_ON, without bitwise OR any cursor mode only will clear cursor
 *               'row'  is the MSB of screen address, the row position of the cursor
 *               'col'  is the LSB of the screen address, the column position of the cursor
 *               'type' is cursor type 
 *                      type = LINE_1_CURSOR / LINE_8_CURSOR
 * Returns     : none
 * Notes       : Cursor address is not like text address pointer. Cannot use GDispGoto(row,col).
 *********************************************************************************************************
 */
void
GDispSetCursor (UCHAR mode, uint16_t row, uint16_t col, UCHAR type)
{
  uint16_t addr;

  addr = row << 8;
  addr = addr | (col & 0x00FF);
  GDispCmdAddrSend (addr, ADDR_PTR_SET);
  GDispCmdSend (CURSOR_PTR_SET); //Set cursor position
  GDispCmdSend (mode);
  GDispCmdSend (type); //cursor mode
}

/*
 *********************************************************************************************************
 *                                       SET PIXEL AT X, Y POSITION
 *
 * Description : This function sets a pixel with color = BLACK / WHITE (defined in t6963.h)
 * Arguments   : 'X'    0....MAX_COL_PIXEL is matrix position in horizontal direction
 *               'Y     0....MAX_ROW_PIXEL is matrix position in vertical direction 
 *               'color'  sets BLACK / WHITE standing for pixel ON/OFF
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispSetPixel (uint16_t X, uint16_t Y, UCHAR color)
{
  uint16_t addr;
  uint16_t row, col;
  UCHAR cmd;
 
  row = Y;
  col = X / FontSize;

  addr = row * COLUMN + col + TEXT_HOME_ADDR;
  GDispCmdAddrSend (addr, ADDR_PTR_SET);

  if (color == BLACK)
    cmd = (0b11111000) | (FontSize - 1 - (X % FontSize));
  else
    cmd = (0b11110000) | (FontSize - 1 - (X % FontSize));

   GDispCmdSend (cmd);
}

/*
 *********************************************************************************************************
 *                                        I/O PORT INITIALIZATION
 *
 * Description : This initializes the I/O ports used by the display driver
 * Arguments   : none
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispInitPort (void)
{
  int i;

  DISABLE_RA0_ANALOG ();
  DISABLE_RA1_ANALOG ();
  DISABLE_RA2_ANALOG ();
  DISABLE_RA3_ANALOG ();
  DISABLE_RA4_ANALOG ();
  DISABLE_RA5_ANALOG ();
  DISABLE_RA6_ANALOG ();
  DISABLE_RA7_ANALOG ();

  DISABLE_RA0_OPENDRAIN ();
  DISABLE_RA1_OPENDRAIN ();
  DISABLE_RA2_OPENDRAIN ();
  DISABLE_RA3_OPENDRAIN ();
  DISABLE_RA4_OPENDRAIN ();
  DISABLE_RA5_OPENDRAIN ();
  DISABLE_RA6_OPENDRAIN ();
  DISABLE_RA7_OPENDRAIN ();

  DISABLE_RA0_PULLUP ();
  DISABLE_RA1_PULLUP ();
  DISABLE_RA2_PULLUP ();
  DISABLE_RA3_PULLUP ();
  DISABLE_RA4_PULLUP ();
  DISABLE_RA5_PULLUP ();
  DISABLE_RA6_PULLUP ();
  DISABLE_RA7_PULLUP ();

  DISABLE_RA0_PULLDOWN ();
  DISABLE_RA1_PULLDOWN ();
  DISABLE_RA2_PULLDOWN ();
  DISABLE_RA3_PULLDOWN ();
  DISABLE_RA4_PULLDOWN ();
  DISABLE_RA5_PULLDOWN ();
  DISABLE_RA6_PULLDOWN ();
  DISABLE_RA7_PULLDOWN ();

  //Set all control line as output
  CONFIG_RC2_AS_DIG_OUTPUT (); // CE
  CONFIG_RA15_AS_DIG_OUTPUT (); // RD
  CONFIG_RC1_AS_DIG_OUTPUT (); // WR
  CONFIG_RA14_AS_DIG_OUTPUT (); // CD
  CONFIG_RC3_AS_DIG_OUTPUT (); // RESET
  CONFIG_RC4_AS_DIG_OUTPUT (); // font select

  CONFIG_RA0_AS_DIG_OUTPUT ();
  CONFIG_RA1_AS_DIG_OUTPUT ();
  CONFIG_RA2_AS_DIG_OUTPUT ();
  CONFIG_RA3_AS_DIG_OUTPUT ();
  CONFIG_RA4_AS_DIG_OUTPUT ();
  CONFIG_RA5_AS_DIG_OUTPUT ();
  CONFIG_RA6_AS_DIG_OUTPUT ();
  CONFIG_RA7_AS_DIG_OUTPUT ();

  LCD_RST = 0;
  LCD_CD = 1;
  LCD_CE = 1;
  LCD_RD = 1;
  LCD_WR = 1;
  LCD_FS = 0;
  Data_Out (0x00);

  //Turn on LCD module after reset
  //    #asm
  //        nop
  //    #endasm
  for (i = 0; i < 10; i++)
    DELAY_US (TIME_DELAY);
  LCD_RST = 1;
}

/*
 *********************************************************************************************************
 *                                             BUSY CHECK
 *
 * Description : This function checks command execution capability, & data read/write capability
 * Arguments   : none
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispBusyChk (void)
{
  int i;
  GDispCmdRd ();
  GDispChipEn;
  //    #asm
  //       nop
  //   #endasm
//  outUint8NoLeader((UCHAR)(PORTA & 0x00ff));
  for (i = 0; i < 2; i++)
    DELAY_US (TIME_DELAY);
  while (!PORTAbits.RA0) // Busy Check here
    ;
  while (!PORTAbits.RA1)
    ;
  GDispChipDi; //Chip disable to finish
}

/*
 *********************************************************************************************************
 *                                       AUTO MODE DATA WRITE CHECK
 *
 * Description : This function checks auto mode data write capability
 * Arguments   : none
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispAutoWrChk (void)
{
  int i;
  GDispCmdRd ();
  GDispChipEn;
  //    #asm
  //        nop
  //    #endasm
  for (i = 0; i < 2; i++)
    DELAY_US (TIME_DELAY);
  while (!PORTAbits.RA3);
  //  {
  //    outUint8NoLeader((UCHAR)(PORTA & 0x00ff));
  //    outChar(++i);
  //  }
  GDispChipDi;
}

/*
 *********************************************************************************************************
 *                                           WRITE DATA TO LCD MODULE
 *
 * Description : This function sends a single data byte to the display device
 * Arguments   : 'data' is the BYTE to send to the display device
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispDataWr (UCHAR data)
{
  int i;
  GDispBusyChk (); // Wait for LCD to be ready

  //  LCD_DATA = data;                // Data write
  Data_Out (data);
  //  #asm
  //    nop
  //  #endasm
  for (i = 0; i < 2; i++)
    DELAY_US (TIME_DELAY);
  GDispDatWr ();
  GDispChipEn;
  //  #asm                  
  //    nop                         //delay one cycle for port stablize
  //  #endasm
  for (i = 0; i < 2; i++)
    DELAY_US (TIME_DELAY);

  GDispChipDi;
}

/*
 *********************************************************************************************************
 *                        WRITE DATA TO LCD MODULE, SCREEN ADRESS AUTO-INCREMENTED
 *
 * Description : Send a single data byte to the screen with screen address auto'ly incremented 
 * Arguments   : 'data' is the BYTE to send to the display device
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispAutoDataWr (UCHAR data)
{
  int i;
  GDispAutoWrChk (); // Auto write mode check

  //  LCD_DATA = data;                // Data write
  Data_Out (data);
  //  #asm
  //    nop
  //  #endasm
  for (i = 0; i < 2; i++)
    DELAY_US (TIME_DELAY);

  GDispDatWr ();
  GDispChipEn;
  //  #asm                  
  //    nop                         //delay one cycle for port stablize
  //  #endasm
  for (i = 0; i < 2; i++)
    DELAY_US (TIME_DELAY);

  GDispChipDi;
}

/*
 *********************************************************************************************************
 *                                       WRITE COMMAND TO LCD MODULE
 *
 * Description : This function sends a single byte as command to the display device
 * Arguments   : 'cmd' is the COMMAND BYTE to send to the display device
 * Returns     : none
 * Notes       : 
 *********************************************************************************************************
 */
void
GDispCmdSend (UCHAR cmd)
{
  int i;
  GDispBusyChk (); // Wait for LCD to be ready
  //      LCD_DATA = cmd;
  Data_Out (cmd);
  GDispCmdWr ();
  GDispChipEn;
  //    #asm
  //        nop
  //    #endasm    
  for (i = 0; i < 2; i++)
    DELAY_US (TIME_DELAY);

  GDispChipDi;
}

/*
 *********************************************************************************************************
 */
void
Data_Out (UCHAR data)
{
  LATA &= 0xff00;
  LATA |= 0x00ff & data;
}

void
GDispCmdWr (void)
{
  CONFIG_RA0_AS_DIG_OUTPUT ();
  CONFIG_RA1_AS_DIG_OUTPUT ();
  CONFIG_RA2_AS_DIG_OUTPUT ();
  CONFIG_RA3_AS_DIG_OUTPUT ();
  CONFIG_RA4_AS_DIG_OUTPUT ();
  CONFIG_RA5_AS_DIG_OUTPUT ();
  CONFIG_RA6_AS_DIG_OUTPUT ();
  CONFIG_RA7_AS_DIG_OUTPUT ();
  LCD_RD = 1;
  LCD_CD = 1;
  LCD_WR = 0;
}

void
GDispCmdRd (void)
{
  CONFIG_RA0_AS_DIG_INPUT ();
  CONFIG_RA1_AS_DIG_INPUT ();
  CONFIG_RA2_AS_DIG_INPUT ();
  CONFIG_RA3_AS_DIG_INPUT ();
  CONFIG_RA4_AS_DIG_INPUT ();
  CONFIG_RA5_AS_DIG_INPUT ();
  CONFIG_RA6_AS_DIG_INPUT ();
  CONFIG_RA7_AS_DIG_INPUT ();
  LCD_RD = 0;
  LCD_CD = 1;
  LCD_WR = 1;
}

void
GDispDatWr (void)
{
  CONFIG_RA0_AS_DIG_OUTPUT ();
  CONFIG_RA1_AS_DIG_OUTPUT ();
  CONFIG_RA2_AS_DIG_OUTPUT ();
  CONFIG_RA3_AS_DIG_OUTPUT ();
  CONFIG_RA4_AS_DIG_OUTPUT ();
  CONFIG_RA5_AS_DIG_OUTPUT ();
  CONFIG_RA6_AS_DIG_OUTPUT ();
  CONFIG_RA7_AS_DIG_OUTPUT ();
  LCD_RD = 1;
  LCD_CD = 0;
  LCD_WR = 0;
}

void
GDispDatRd (void)
{
  LCD_CD = 0;
  LCD_WR = 1;
  LCD_RD = 0;
}
