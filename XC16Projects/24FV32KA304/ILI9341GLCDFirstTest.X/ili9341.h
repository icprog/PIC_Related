#ifndef __ILI9341_H
#define __ILI9341_H
//==============================================================================
// Connection of module TFT.
//
// VCC      <<<>>> 3.3 V.
// GND      <<<>>> GND.
// TFT_CS   <<<>>> You can change this pin.
// TFT_REST <<<>>> You can change this pin.
// TFT_D/C  <<<>>> You can change this pin.
// TFT_SDI  <<<>>> Connect to SDO MCU.
// TFT_SCK  <<<>>> Connect to SCK MCU.
// TFT_SDO  <<<>>> Connect to SDI MCU.
// LED      <<<>>> 3.3 V (Use a 10-ohm resistor).
//==============================================================================
#include    "system.h"

#define TFT_CS             LATBbits.LATB15
#define TRIS_CS            LATBbits.LATB15

//#define TFT_CS             LATDbits.LATD0
//#define TRIS_CS            TRISDbits.TRISD0

#define TFT_RES            LATCbits.LATC6
#define TRIS_RES           TRISCbits.TRISC6
//#define TFT_RES            LATDbits.LATD1
//#define TRIS_RES           TRISDbits.TRISD1

#define TFT_DC             LATCbits.LATC7
#define TRIS_DC            TRISCbits.TRISC7
//#define TFT_DC             LATDbits.LATD2
//#define TRIS_DC            TRISDbits.TRISD2

//==============================================================================
// These are some colors that you can use for fonts and graphics.
//==============================================================================
#define BLACK              0b0000000000000000
#define BRIGHTBLUE         0b0000000000011111
#define BRIGHTGREEN        0b0000011111100000
#define BRIGHTCYAN         0b0000011111111111
#define BRIGHTRED          0b1111100000000000
#define BRIGHTMAGENTA      0b1111100000011111
#define BRIGHTYELLOW       0b1111111111100000
#define BLUE               0b0000000000010000
#define GREEN              0b0000010000000000
#define CYAN               0b0000010000010000
#define RED                0b1000000000000000
#define MAGENTA            0b1000000000010000
#define BROWN              0b1111110000000000
#define LIGHTGRAY          0b1000010000010000
#define DARKGRAY           0b0100001000001000
#define LIGHTBLUE          0b1000010000011111
#define LIGHTGREEN         0b1000011111110000
#define LIGHTCYAN          0b1000011111111111
#define LIGHTRED           0b1111110000010000
#define LIGHTMAGENTA       0b1111110000011111
#define YELLOW             0b1111111111110000
#define WHITE              0b1111111111111111

#define GRAY0       	   0b1110011100011100
#define GRAY1         	   0b1100011000011000   
#define GRAY2              0b1010010100010100   
#define GRAY3              0b1000010000010000
#define GRAY4              0b0110001100001100
#define GRAY5              0b0100001000001000
#define GRAY6	           0b0010000100000100

//==============================================================================
// These are the defines to select the memory access control.
//==============================================================================
#define TFT_VERTICAL       0x88
#define TFT_HORIZONTAL     0xE8
#define TFT_VERTICAL_BMP   0x08

//==============================================================================
// Define number of pixels in width and height.
// New name for data types.
//==============================================================================
#define TFT_W 240
#define TFT_H 320

typedef char                     Schar;
typedef unsigned char            Uchar;
typedef const char               CSchar;
typedef const unsigned char      CUchar;
typedef int                      Sint; 
typedef unsigned int             Uint;
typedef const unsigned int       CUint;

//==============================================================================
// Function Prototypes.
//==============================================================================
void TFT_Init(void);
void TFT_Reset(void);
void TFT_WriteCommand(Uchar command);
void TFT_WriteParameter(Uchar parameter);
void TFT_ColumnPage(Uint x1, Uint x2, Uint y1, Uint y2);
Uchar TFT_MemoryAccessControl(Uchar frame_memory_);
Uint TFT_RGBConvert(Uint red, Uint green, Uint blue);
//==============================================================================
void TFT_Pixel(Uint x, Uint y, Uint color);
void TFT_SetDotSize(Uchar size_);
void TFT_Dot(Uint x, Uint y, Uint color);
void TFT_SetFont(CUchar *font_, Uchar letterspacing);
Uchar TFT_CharHeight(void);
Uint TFT_TextWidth(Schar *buffer);
void TFT_WriteChar(Uchar c, Uint x, Uint y, Uint color1, Uint color2);
void TFT_ConstText(CSchar *buffer, Uint x, Uint y, Uint color1, Uint color2);
void TFT_Text(Schar *buffer, Uint x, Uint y, Uint color1, Uint color2);
void TFT_TextLEFT(Schar *buffer, Uint y, Uint color1, Uint color2);
void TFT_TextCENTER(Schar *buffer, Uint y, Uint color1, Uint color2);
void TFT_TextRIGHT(Schar *buffer, Uint y, Uint color1, Uint color2);
void TFT_FillScreen(Uint color);
void TFT_Box(Uint x1, Uint y1, Uint x2, Uint y2, Uint color);
void TFT_Line(Uint x1, Uint y1, Uint x2, Uint y2, Uint color);
void TFT_Rectangle(Uint x1, Uint y1, Uint x2, Uint y2, Uint color);
void TFT_RectangleRound(Uint x1, Uint y1, Uint x2, Uint y2, Uint radius, Uint color);
void TFT_RectangleRoundFill(Uint x1, Uint y1, Uint x2, Uint y2, Uint radius, Uint color);
void TFT_Circle(Uint x1, Uint y1, Uint radius, Uint color);
void TFT_CircleFill(Uint x1, Uint y1, Uint radius, Uint color);
void TFT_RoundEdge(Uint x1, Uint y1, Uint alignment, Uint radius, Uint color);
void TFT_Icon(CUint *buffer, Uint x, Uint y, Uchar width_, Uchar height_);

#endif