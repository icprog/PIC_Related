/*
***********************************************************************************************
*                           Toshiba T6963C Graphical LCD Display Driver
*
* File name     : t6963.h
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
* A 128-word character generator ROM (code 0101) T6963C-0101 is built in as standard.
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
* In EQS console ver 2.5 PCB, FS is determined by JP23 jumper. FS=0 when shorted
* pin 19 VEE
* pin 20 LEDA
* pin 21 LEDK
*
***********************************************************************************************
*/

/*
***********************************************************************************************
*                                       PORT DEFINITION
***********************************************************************************************
*/
//I/O port for data definition
#ifndef T6963_H
#define T6963_H

//Control pin setting
//RA 0->7 LCD Data Bus
//RA 14 C/D
//RA 15 RD
//RC 1 WR
//RC 2 CE
//RC 3 RESET
//RC 4 FS1 ?

//PORTAbits.RA0        // Check command execution capability
//PORTAbits.RA1        // Check data read/write capability
//PORTAbits.RA2        // Check Auto mode data read capability
//PORTAbits.RA3        // Check Auto mode data write capability
//PORTAbits.RA4        // Check controller operation capability
//PORTAbits.RA5        // Error flag. Used for screen peek and screen copy
//PORTAbits.RA6        // Check the blink condition
//PORTAbits.RA7        // Check the blink condition

#define LCD_WR             LATCbits.LATC1        // LCD Write control line pin number
#define LCD_CE             LATCbits.LATC2       // LCD Enable control line pin number
#define LCD_RST            LATCbits.LATC3        // LCD RST_ line
#define LCD_FS             LATCbits.LATC4        // LCD font select
#define LCD_CD             LATAbits.LATA14       // LCD Control/data Select line
#define LCD_RD             LATAbits.LATA15       // LCD Read control line  pin number
#endif

/*
***********************************************************************************************
*                                       GLOBAL CONSTANTS
***********************************************************************************************
*/

/*
***********************************************************************************************
* Note      :   The T6963 controller's RAM address space from $0000 - $FFFF, total 64kbyte RAM.
*               It is just the RAM address set, not the actual RAM amount can be set!
*               However, everything manufacturer may mount different amount of RAM on its
*               module. Example, Powertip's PG12864-F has 4 kbyte RAM only.
*               RAM space to handle 128x64 dots in 8 font = 128x64/8 = 1,024 byte.
*               Thus, the LCD's actual visible screen area is 1 kbyte.
*               For 8-font, 16 COLUMN, 
*               TEXT_HOME_ADDR  starts 0x0000 ending 0x01FF -> 512  bytes (for text use)?
*               GRH_HOME_ADDR   starts 0x0200 ending 0x05FF -> 1,024 bytes ?
*               CG_HOME_ADDR    starts 0x1400 ending 0x147F -> 128  bytes (custom characters) ?
***********************************************************************************************
*/
#define TEXT_HOME_ADDR      0x0000
#define GRH_HOME_ADDR       0x0200
#define CG_HOME_ADDR        0x1400
#define COLUMN              40      //Set column number to be e.g. 32 for 8x8 fonts, 2 pages 
#define MAX_ROW_PIXEL       128      //MAX_ROW_PIXEL the physical matrix length (y direc-tion)                                    
#define MAX_COL_PIXEL       128     //MAX_COL_PIXEL the physical matrix width (x direction)
#define ENABLE              1
#define DISABLE             0
#define BLACK               1
#define WHITE               0

/*
***********************************************************************************************
*                                       DISPLAY MODE
***********************************************************************************************
*/
#define DISPLAY_OFF         0x90    //0b10010000, display off
#define CURSOR_ON_BLINK_OFF 0x92    //0b1001xx10, cursor on without blinking
#define CURSOR_BLINK_ON     0x93    //0b1001xx11, cursor on with blinking
#define TEXT_ON             0x94    //0b100101xx, text on, graphics off
#define GRAPHIC_ON          0x98    //0b100110xx, text off, graphics on
#define TEXT_GRH_ON         0x9C    //0b100111xx, text on, graphics on


/*
***********************************************************************************************
*                                           MODE
***********************************************************************************************
*   Example:    OR_MODE|EXT_CG_MODE     ->  OR mode, external CG ram mode
*               AND_MODE                ->  AND mode, internal CG ROM mode
***********************************************************************************************
*/
/*
***********************************************************************************************
*       In internal CG ROM MODE (INT_CG_MODE), character codes 00h - 7Fh represent the
*       pre-defined "internal" CG ROM characters, and codes 80h - FFh represent the
*       users' own "external" characters. In external CG ROM MODE (EXT_CG_MODE),
*       all 256 codes from 00h - FFh can be used to represent the users' own characters.
***********************************************************************************************
*/

#define INT_CG_MODE         0x80    //0b10000xxx, Internal CG ROM mode
#define EXT_CG_MODE         0x88    //0b10001xxx, External CG RAM mode
#define OR_MODE             0x80    //0b1000x000, OR mode, internal CG ROM mODE
#define XOR_MODE            0x81    //0b1000x001, XOR mode, internal CG ROM mode
#define AND_MODE            0x83    //0b1000x011, AND mode, internal CG ROM mode
#define TEXT_ATTR_MODE      0x84    //0b1000x100, text attribute mode, internal CG ROM mode



/*
***********************************************************************************************
*                                       CURSOR MODE
***********************************************************************************************
*/
#define LINE_8_CURSOR       0xA7    //8-line cursor mode
#define LINE_7_CURSOR       0xA6    //7-line cursor mode
#define LINE_6_CURSOR       0xA5    //6-line cursor mode
#define LINE_5_CURSOR       0xA4    //5-line cursor mode
#define LINE_4_CURSOR       0xA3    //4-line cursor mode
#define LINE_3_CURSOR       0xA2    //3-Line cursor mode
#define LINE_2_CURSOR       0xA1    //2-Line cursor mode
#define LINE_1_CURSOR       0xA0    //1-Line cursor mode

/*
***********************************************************************************************
*                                   TEXT ATTRIBUTE MODE
***********************************************************************************************
*/
#define ATTR_NORMAL         0x00    //Normal Display
#define ATTR_REVERSE        0x05    //Reverse Di../t6963.h:189:33: error: expected ';', ',' or ')' before 'mode'splay
#define ATTR_INHIBIT        0x03    //Inhibit Display
#define ATTR_BLINK          0x08    //Blinking of Normal Display
#define ATTR_BLINK_REVERSE  0x0D    //Blinking of Reverse Display
#define ATTR_BLINK_INHIBIT  0x0B    //Blinking of Inhibit Display


/*
***********************************************************************************************
*                                     GLOBAL VARIABLES
***********************************************************************************************
*/
extern UCHAR    DisplayMode;    /* Keeps state of the display mode (DISPLAY MODE)   */
extern UCHAR    Mode;           /* Keeps state of the MODE                          */
extern UCHAR    FontSize;       /* 6 font or 8 font                                 */
extern UCHAR    CGBuffer[8];    /* Buffer for custom pattern                        */

/*
***********************************************************************************************
*                                   FUNCTION PROTOTYPES
***********************************************************************************************
*/
void GDispInit(void);
void GDispSetMode(UCHAR mode);
void GDispClrTxt(void);
void GDispGoto(uint16_t row, uint16_t col);
void GDispChar(UCHAR c);
void GDispCharAt(uint16_t row, uint16_t col, UCHAR c);
void GDispSetCursor(UCHAR mode, uint16_t row, uint16_t col, UCHAR type);
void GDispSetAttrb(uint16_t row, uint16_t col, UCHAR mode);
void GDispCGCharAt(uint16_t row, uint16_t col, UCHAR id);
void GDispDatRd(void);
void GDispDatWr(void);
void GDispCmdRd(void);
void GDispCmdWr(void);
void GDispStringAt(uint16_t row, uint16_t col, char *c);
/*
***********************************************************************************************
*                                   FUNCTION PROTOTYPES
*                                    HARDWARE SPECIFIC
***********************************************************************************************
*/
#define GDispChipEn     LCD_CE = 0                  /* Low level Chip Enable macro          */
#define GDispChipDi     LCD_CE = 1                  /* Low level Chip Disable macro         */
#if 0
#define GDispCmdWr    CONFIG_RA0_AS_OUTPUT(); \
                      CONFIG_RA1_AS_OUTPUT(); \
                      CONFIG_RA2_AS_OUTPUT(); \
                      CONFIG_RA3_AS_OUTPUT(); \
                      CONFIG_RA4_AS_OUTPUT(); \
                      CONFIG_RA5_AS_OUTPUT(); \
                      CONFIG_RA6_AS_OUTPUT(); \
                      CONFIG_RA7_AS_OUTPUT(); \
                      LCD_RD = 1; LCD_CD = 1; \
                      LCD_WR = 0

#define GDispCmdRd    CONFIG_RA0_AS_INPUT(); \
                      CONFIG_RA1_AS_INPUT(); \
                      CONFIG_RA2_AS_INPUT(); \
                      CONFIG_RA3_AS_INPUT(); \
                      CONFIG_RA4_AS_INPUT(); \
                      CONFIG_RA5_AS_INPUT(); \
                      CONFIG_RA6_AS_INPUT(); \
                      CONFIG_RA7_AS_INPUT(); \
                      LCD_RD = 0; LCD_CD = 1; \
                      LCD_WR = 1  

#define GDispDatWr    CONFIG_RA0_AS_OUTPUT(); \
                      CONFIG_RA1_AS_OUTPUT(); \
                      CONFIG_RA2_AS_OUTPUT(); \
                      CONFIG_RA3_AS_OUTPUT(); \
                      CONFIG_RA4_AS_OUTPUT(); \
                      CONFIG_RA5_AS_OUTPUT(); \
                      CONFIG_RA6_AS_OUTPUT(); \
                      CONFIG_RA7_AS_OUTPUT(); \
                      LCD_RD = 1; LCD_CD = 0; \
                      LCD_WR = 0  

#define GDispDatRd    LCD_CD = 0; LCD_WR = 1; LCD_RD = 0
#endif
void GDispInitPort(void);
void GDispBusyChk(void);
void GDispAutoWrChk(void);
void GDispDataWr(UCHAR data);
void GDispAutoDataWr(UCHAR data);
void GDispCmdSend(UCHAR cmd);
void Data_Out(UCHAR data);
void DisplayDisclaimer(void);
void DisplayTieDown(void);
void DisplayFuelMillion(void);
void DisplayShutDown(void);
