/*
 * File:   ili9341.c
 * Author: http://pic18fxx.blogspot.com 
 * 
 * Graphical display TFT 240x320. 
 * Driver ILI9341.
 * Interface: SPI.
 * Version 2.0
 */
#include <xc.h>
#include "spi_pic.h"
#include "ili9341.h"

//==============================================================================
// Declaration of global variables.
//==============================================================================
CUchar *font, *font2;
Uchar width, height, letter_spacing, dot_size = 0, frame_memory = TFT_VERTICAL; 
Uint tft_x = TFT_W - 1;
//==============================================================================
// This function initializes the driver ILI9341.
//==============================================================================
void TFT_Init(void){
TRIS_CS = 0; TRIS_DC = 0; TRIS_RES = 0;
TFT_CS = 1; TFT_DC = 0; TFT_RES = 0;
TFT_Reset();
TFT_WriteCommand(0xCB);   // Power control A (CBh)
TFT_WriteParameter(0x39); 
TFT_WriteParameter(0x2C); 
TFT_WriteParameter(0x00); 
TFT_WriteParameter(0x34); 
TFT_WriteParameter(0x02); 

TFT_WriteCommand(0xCF);   // Power control B (CFh)
TFT_WriteParameter(0x00); 
TFT_WriteParameter(0XC1); 
TFT_WriteParameter(0X30); 

TFT_WriteCommand(0xE8);   // Driver timing control A (E8h)  
TFT_WriteParameter(0x85); 
TFT_WriteParameter(0x00); 
TFT_WriteParameter(0x78); 

TFT_WriteCommand(0xEA);   // Driver timing control B (EAh)  
TFT_WriteParameter(0x00); 
TFT_WriteParameter(0x00); 

TFT_WriteCommand(0xED);   // Power on sequence control (EDh) 
TFT_WriteParameter(0x64); 
TFT_WriteParameter(0x03); 
TFT_WriteParameter(0X12); 
TFT_WriteParameter(0X81); 

TFT_WriteCommand(0xF7);   // Pump ratio control (F7h)
TFT_WriteParameter(0x20); 

TFT_WriteCommand(0xC0);   // Power Control 1 (C0h) 
TFT_WriteParameter(0x23); // VRH[5:0] 

TFT_WriteCommand(0xC1);   // Power Control 2 (C1h)
TFT_WriteParameter(0x10); // SAP[2:0]; BT[3:0] 

TFT_WriteCommand(0xC5);   // Set the VCOMH voltage. 
TFT_WriteParameter(0x3E);
TFT_WriteParameter(0x28); 

TFT_WriteCommand(0xC7);   // VCOM Control 2(C7h)
TFT_WriteParameter(0x86);  

TFT_WriteCommand(0x36);   // Memory Access Control (36h)
TFT_WriteParameter(TFT_VERTICAL);

TFT_WriteCommand(0x3A);   // COLMOD: Pixel Format Set (3Ah)    
TFT_WriteParameter(0x55); 

TFT_WriteCommand(0xB1);   // Frame Rate Control (In Normal Mode/Full Colors) (B1h)  
TFT_WriteParameter(0x00);  
TFT_WriteParameter(0x18); 

TFT_WriteCommand(0xB6);   // Display Function Control (B6h) 
TFT_WriteParameter(0x08); 
TFT_WriteParameter(0x82);
TFT_WriteParameter(0x27);  

TFT_WriteCommand(0xF2);   // Enable 3G (F2h)
TFT_WriteParameter(0x00); 

TFT_WriteCommand(0x26);   // Gamma Set (26h)
TFT_WriteParameter(0x01); 

TFT_WriteCommand(0xE0);   //Positive Gamma Correction (E0h)
TFT_WriteParameter(0x0F); 
TFT_WriteParameter(0x31); 
TFT_WriteParameter(0x2B); 
TFT_WriteParameter(0x0C); 
TFT_WriteParameter(0x0E); 
TFT_WriteParameter(0x08); 
TFT_WriteParameter(0x4E); 
TFT_WriteParameter(0xF1); 
TFT_WriteParameter(0x37); 
TFT_WriteParameter(0x07); 
TFT_WriteParameter(0x10); 
TFT_WriteParameter(0x03); 
TFT_WriteParameter(0x0E); 
TFT_WriteParameter(0x09); 
TFT_WriteParameter(0x00); 

TFT_WriteCommand(0XE1);   // Negative Gamma Correction (E1h)
TFT_WriteParameter(0x00); 
TFT_WriteParameter(0x0E); 
TFT_WriteParameter(0x14); 
TFT_WriteParameter(0x03); 
TFT_WriteParameter(0x11); 
TFT_WriteParameter(0x07); 
TFT_WriteParameter(0x31); 
TFT_WriteParameter(0xC1); 
TFT_WriteParameter(0x48); 
TFT_WriteParameter(0x08); 
TFT_WriteParameter(0x0F); 
TFT_WriteParameter(0x0C); 
TFT_WriteParameter(0x31); 
TFT_WriteParameter(0x36); 
TFT_WriteParameter(0x0F); 

TFT_WriteCommand(0x11);   // Exit Sleep
__delay_ms(150);            // Delay of 150ms
TFT_WriteCommand(0x29);   // Display ON (29h)
TFT_FillScreen(WHITE);
}

//==============================================================================
// This function resets the display TFT.
//==============================================================================
void TFT_Reset(void){
TFT_CS = 1;        
TFT_RES = 0; 
__delay_ms(50);
TFT_RES = 1; 
__delay_ms(150);
}

//==============================================================================
// This function writes a command.
//==============================================================================
void TFT_WriteCommand(Uchar command){   
TFT_CS = 0;
TFT_DC = 0; // When DCX = �0�, command is selected.
SPI1_Write(command);
TFT_CS = 1;
}

//==============================================================================
// This function writes a Parameter.
//==============================================================================
void TFT_WriteParameter(Uchar parameter){   
TFT_CS = 0;
TFT_DC = 1; // When DCX = �1�, data is selected.
SPI1_Write(parameter);
TFT_CS = 1;
}

//==============================================================================
// This function is used to define area of frame memory where MCU can access.
// x1: Set start column address. 
// x2: Set end column address. 
// y1: Set start page address.
// y2: Set end page address.
//==============================================================================
void TFT_ColumnPage(Uint x1, Uint x2, Uint y1, Uint y2){      
TFT_CS = 0;
TFT_DC = 0; SPI1_Write(0x2A);
TFT_DC = 1; SPI1_Write(x1 >> 8); SPI1_Write(x1 & 0xFF); SPI1_Write(x2 >> 8); SPI1_Write(x2 & 0xFF);
TFT_DC = 0; SPI1_Write(0x2B);
TFT_DC = 1; SPI1_Write(y1 >> 8); SPI1_Write(y1 & 0xFF); SPI1_Write(y2 >> 8); SPI1_Write(y2 & 0xFF);
TFT_DC = 0; SPI1_Write(0x2C);
TFT_CS = 1;
}

//==============================================================================
// This function sets the memory access control. 
//==============================================================================
Uchar TFT_MemoryAccessControl(Uchar frame_memory_){
if(frame_memory_ == 0){return frame_memory;}
TFT_WriteCommand(0x36);
TFT_WriteParameter(frame_memory_);
switch(frame_memory_)
      {
       case TFT_VERTICAL:     tft_x = TFT_W - 1; break;
       case TFT_HORIZONTAL:   tft_x = TFT_H - 1; break;    
       case TFT_VERTICAL_BMP: tft_x = TFT_W - 1; break;
      }
frame_memory = frame_memory_;
return frame_memory;
} 

//==============================================================================
// This function is used to convert 24 bpp color data to 5-6-5 RGB format.
// 16 bit/pixel color order (R:5-bit, G:6-bit, B:5-bit), 65,536 colors.
// 8-8-8 to to 5-6-5 conversion.
//==============================================================================
Uint TFT_RGBConvert(Uint red, Uint green, Uint blue){
Uint color = 0;
red = (red & 0xF8) << 8; 
green = (green & 0xFC) << 3; 
blue = (blue & 0xF8) >> 3;
color = red | green | blue;
return color;
}

//==============================================================================
// This function draws a pixel on TFT.
// x: x position. Valid values: 0..240 
// y: y position. Valid values: 0..320 
// color: color parameter.
//==============================================================================
void TFT_Pixel(Uint x, Uint y, Uint color){
TFT_CS = 0;
TFT_DC = 0; SPI1_Write(0x2A);
TFT_DC = 1; SPI1_Write(x >> 8); SPI1_Write(x & 0xFF); SPI1_Write(x >> 8); SPI1_Write(x & 0xFF);
TFT_DC = 0; SPI1_Write(0x2B);
TFT_DC = 1; SPI1_Write(y >> 8); SPI1_Write(y & 0xFF); SPI1_Write(y >> 8); SPI1_Write(y & 0xFF);
TFT_DC = 0; SPI1_Write(0x2C); 
TFT_DC = 1; SPI1_Write(color >> 8); SPI1_Write(color & 0xFF);
TFT_CS = 1;
}

//==============================================================================
// This function sets the size of dot.
// size_: Size of dot. Valid values: 0, 1, 2, 3, 4, 5.
//==============================================================================
void TFT_SetDotSize(Uchar size_){
dot_size = size_;
}

//==============================================================================
// This function draws a dot on TFT.
// x: x position. Valid values: 0..240 
// y: y position. Valid values: 0..320 
// color: color parameter.
//==============================================================================
void TFT_Dot(Uint x, Uint y, Uint color){
Uchar i;
switch(dot_size)
      {
       case 0:  i = 1;   break;
       case 1:  i = 9;   break;
       case 2:  i = 25;  break;
       case 3:  i = 49;  break;
       case 4:  i = 81;  break;
       case 5:  i = 121; break;
       default: i = 121; break;
      }
TFT_ColumnPage(x - dot_size, x + dot_size, y - dot_size, y + dot_size);
TFT_CS = 0; TFT_DC = 1;
while(i)
     {
      SPI1_Write(color >> 8);
      SPI1_Write(color & 0xFF);      
      i--;
     }
TFT_CS = 1;
}

//==============================================================================
// This function sets the type of font.
// letterspacing: Letter spacing. Valid values: 1, 2, 3...
//==============================================================================
void TFT_SetFont(CUchar *font_, Uchar letterspacing){
font2 = font_;
letter_spacing = letterspacing;
height = TFT_CharHeight();
}

//==============================================================================
// This function returns the height of character. The size is determined in pixels.
//==============================================================================
Uchar TFT_CharHeight(void){
font = font2;
font += 6;
return *font;
}

//==============================================================================
// This function returns the width of text. The size is determined in pixels.
//==============================================================================
Uint TFT_TextWidth(Schar *buffer){
Uint p, text_width = 0;
while(*buffer)
     {
      p = *buffer - 32; p = p * 4; p = p + 8;       
      font = font2;                
      font += p;                                   
      text_width += *font;
      text_width += letter_spacing;
      buffer++;
     }    
return text_width;
}

//==============================================================================
// This function draws a character on the TFT.
// c: character to be written. 
// x: x position. Valid values: 0..240 
// y: y position. Valid values: 0..320 
// color1: Top color.
// color2: Bottom color.
//==============================================================================
void TFT_WriteChar(Uchar c, Uint x, Uint y, Uint color1, Uint color2)
{
    Uchar i, j, k;
    Uint p;
    p = c - 32;
    p = p * 4;
    p = p + 8;       
    font = font2;                
    font += p;                  
    width = *font;
    font += 2;
    p = *font;
    font -= 1; 
    p = (p << 8) | *font;
    font = font2;
    font += p;
    i = height;
    TFT_ColumnPage(x, x + width + letter_spacing - 1, y, y + height);
    TFT_CS = 0; TFT_DC = 1; 

    while(i)
    {
        j = width;
        while(j)
        {
            if(j>0){if(*font&0x01){SPI1_Write(color1>>8);SPI1_Write(color1&0xFF);}else{SPI1_Write(color2>>8);SPI1_Write(color2&0xFF);}j--;}else{font++;break;}
            if(j>0){if(*font&0x02){SPI1_Write(color1>>8);SPI1_Write(color1&0xFF);}else{SPI1_Write(color2>>8);SPI1_Write(color2&0xFF);}j--;}else{font++;break;}
            if(j>0){if(*font&0x04){SPI1_Write(color1>>8);SPI1_Write(color1&0xFF);}else{SPI1_Write(color2>>8);SPI1_Write(color2&0xFF);}j--;}else{font++;break;}
            if(j>0){if(*font&0x08){SPI1_Write(color1>>8);SPI1_Write(color1&0xFF);}else{SPI1_Write(color2>>8);SPI1_Write(color2&0xFF);}j--;}else{font++;break;}
            if(j>0){if(*font&0x10){SPI1_Write(color1>>8);SPI1_Write(color1&0xFF);}else{SPI1_Write(color2>>8);SPI1_Write(color2&0xFF);}j--;}else{font++;break;}
            if(j>0){if(*font&0x20){SPI1_Write(color1>>8);SPI1_Write(color1&0xFF);}else{SPI1_Write(color2>>8);SPI1_Write(color2&0xFF);}j--;}else{font++;break;}
            if(j>0){if(*font&0x40){SPI1_Write(color1>>8);SPI1_Write(color1&0xFF);}else{SPI1_Write(color2>>8);SPI1_Write(color2&0xFF);}j--;}else{font++;break;}
            if(j>0){if(*font&0x80){SPI1_Write(color1>>8);SPI1_Write(color1&0xFF);}else{SPI1_Write(color2>>8);SPI1_Write(color2&0xFF);}j--;}else{font++;break;}
            font++;
        }
        for(k = 0; k < letter_spacing; k++)
        {
            SPI1_Write(color2 >> 8);
            SPI1_Write(color2 & 0xFF);
        }
        i--;
    }
    TFT_CS = 1;
}

//==============================================================================
// This function writes text constant on TFT.
// buffer: Pointer to read all the array.
// x: x position. Valid values: 0..240 
// y: y position. Valid values: 0..320 
// color1: Top color.
// color2: Bottom color.
//==============================================================================
void TFT_ConstText(CSchar *buffer, Uint x, Uint y, Uint color1, Uint color2){
while(*buffer)                
     {
      TFT_WriteChar(*buffer, x, y, color1, color2);
      x += width + letter_spacing;
      buffer++;               
     } 
}

//==============================================================================
// This function writes text variable on TFT.
// buffer: Pointer to read all the array.
// x: x position. Valid values: 0..240 
// y: y position. Valid values: 0..320 
// color1: Top color.
// color2: Bottom color.
//==============================================================================
void TFT_Text(Schar *buffer, Uint x, Uint y, Uint color1, Uint color2){
while(*buffer)                
     {
      TFT_WriteChar(*buffer, x, y, color1, color2);
      x += width + letter_spacing;
      buffer++;               
     } 
}

//==============================================================================
// These functions write text with alignment. 
// buffer: Pointer to read all the array.
// y: y position. Valid values: 0..320 
// color1: Top color.
// color2: Bottom color.
//==============================================================================
void TFT_TextLEFT(Schar *buffer, Uint y, Uint color1, Uint color2){
Uint x = 0;
while(*buffer)                
     {
      TFT_WriteChar(*buffer, x, y, color1, color2);
      x += width + letter_spacing;
      buffer++;               
     }
TFT_Box(x, y, tft_x, y + height - 1, color2);
}

void TFT_TextCENTER(Schar *buffer, Uint y, Uint color1, Uint color2){
Uint x;
x = TFT_TextWidth(buffer);
x = tft_x - x;
x = x / 2;
TFT_Box(0, y, x, y + height - 1, color2);
x++;
while(*buffer)                
     {
      TFT_WriteChar(*buffer, x, y, color1, color2);
      x += width + letter_spacing;
      buffer++;               
     }
TFT_Box(x, y, tft_x, y + height - 1, color2);
}

void TFT_TextRIGHT(Schar *buffer, Uint y, Uint color1, Uint color2){
Uint x;
x = TFT_TextWidth(buffer);
x = tft_x - x;
TFT_Box(0, y, x, y + height - 1, color2);
x++;
while(*buffer)                
     {
      TFT_WriteChar(*buffer, x, y, color1, color2);
      x += width + letter_spacing;
      buffer++;               
     }
}

//==============================================================================
// This function fills screen with given color.  
// color: color parameter.
//==============================================================================
void TFT_FillScreen(Uint color){    
Uchar DH, DL;
Uint i, j;
DH = color >> 8;
DL = color & 0xFF;
switch(frame_memory)
      {
       case TFT_VERTICAL:   TFT_ColumnPage(0, TFT_W - 1, 0, TFT_H - 1); break;
       case TFT_HORIZONTAL: TFT_ColumnPage(0, TFT_H - 1, 0, TFT_W - 1); break;    
      }
TFT_CS = 0; TFT_DC = 1;
for(i = 0; i < TFT_H; i++)
   {
    for (j = 0; j < TFT_W; j++)
        {
         SPI1_Write(DH);
         SPI1_Write(DL);
        }
   }
TFT_CS = 1;
}

//==============================================================================
// This function draws a box on TFT.
// x1: x coordinate of the upper left rectangle corner. Valid values: 0..240  
// y1: y coordinate of the upper left rectangle corner. Valid values: 0..320 
// x2: x coordinate of the lower right rectangle corner. Valid values: 0..240 
// y2: y coordinate of the lower right rectangle corner. Valid values: 0..320 
// color: color parameter. 
//==============================================================================
void TFT_Box(Uint x1, Uint y1, Uint x2, Uint y2, Uint color){
Uchar DH, DL;
Uint i, j;
DH = color >> 8;
DL = color & 0xFF;
TFT_ColumnPage(x1, x2, y1, y2);
TFT_CS = 0; TFT_DC = 1;
for(i = y1; i <= y2; i++)
   {
    for (j = x1; j <= x2; j++)
        {
         SPI1_Write(DH);
         SPI1_Write(DL);        
        }
   }
TFT_CS = 1;
}

//==============================================================================
// This function draws a line on TFT (Bresenham algorithm). 
// x1: x coordinate of the line start. Valid values: 0..240
// y1: y coordinate of the line start. Valid values: 0..320 
// x2: x coordinate of the line end. Valid values: 0..240 
// y2: y coordinate of the line end. Valid values: 0..320 
// color: color parameter.
//==============================================================================
void TFT_Line(Uint x1, Uint y1, Uint x2, Uint y2, Uint color){
Sint i;
Sint longest, shortest; 
Sint numerator;
Sint w = x2 - x1;
Sint h = y2 - y1;
Sint dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;

if(w < 0) dx1 = -1; else if(w > 0) dx1 = 1;
if(h < 0) dy1 = -1; else if(h > 0) dy1 = 1;
if(w < 0) dx2 = -1; else if(w > 0) dx2 = 1;
if(w < 0) w *= -1;
if(h < 0) h *= -1;
longest = w; 
shortest = h;
if(!(longest > shortest)) 
  {//if(w < 0) w *= -1; //if(h < 0) h *= -1; 
   longest = h; 
   shortest = w;
   if(h < 0) dy2 = -1; else if(h > 0) dy2 = 1;
   dx2 = 0;         
  }
numerator = longest >> 1;
for (i = 0; i <= longest; i++)
    {
     TFT_Dot(x1, y1, color);
     numerator += shortest;
     if(!(numerator < longest)) 
       {
        numerator -= longest;
        x1 += dx1;
        y1 += dy1;
       }else
       {
        x1 += dx2;
        y1 += dy2;
       }
    }
}

//==============================================================================
// This function draws a rectangle on TFT.
// x1: x coordinate of the upper left rectangle corner. Valid values: 0..240  
// y1: y coordinate of the upper left rectangle corner. Valid values: 0..320 
// x2: x coordinate of the lower right rectangle corner. Valid values: 0..240 
// y2: y coordinate of the lower right rectangle corner. Valid values: 0..320 
// color: color parameter.
//==============================================================================
void TFT_Rectangle(Uint x1, Uint y1, Uint x2, Uint y2, Uint color){
TFT_Line(x1, y1, x2, y1, color);
TFT_Line(x1, y2, x2, y2, color);
TFT_Line(x1, y1, x1, y2, color);
TFT_Line(x2, y1, x2, y2, color);
}

//==============================================================================
// This function draws a rounded edge rectangle on TFT.
// radius: radius of the rounded edge.
//==============================================================================
void TFT_RectangleRound(Uint x1, Uint y1, Uint x2, Uint y2, Uint radius, Uint color){
TFT_Line(x1 + radius, y1, x2 - radius, y1, color);
TFT_Line(x1 + radius, y2, x2 - radius, y2, color);
TFT_Line(x1, y1 + radius, x1, y2 - radius, color);
TFT_Line(x2, y1 + radius, x2, y2 - radius, color);
TFT_RoundEdge(x1 + radius, y1 + radius, 3, radius, color); 
TFT_RoundEdge(x2 - radius, y1 + radius, 4, radius, color); 
TFT_RoundEdge(x1 + radius, y2 - radius, 2, radius, color); 
TFT_RoundEdge(x2 - radius, y2 - radius, 1, radius, color); 
}

//==============================================================================
// This function draws a filled rounded edge rectangle on TFT.
//==============================================================================
void TFT_RectangleRoundFill(Uint x1, Uint y1, Uint x2, Uint y2, Uint radius, Uint color){ 
TFT_Box(x1 + radius, y1, x2 - radius, y2, color);
TFT_Box(x1, y1 + radius, x2, y2 - radius, color);
TFT_CircleFill(x1 + radius, y1 + radius, radius, color); 
TFT_CircleFill(x2 - radius, y1 + radius, radius, color); 
TFT_CircleFill(x1 + radius, y2 - radius, radius, color); 
TFT_CircleFill(x2 - radius, y2 - radius, radius, color);
}

//==============================================================================
// This function draws a circle on TFT (Midpoint circle algorithm).
// x1: x coordinate of the circle center. Valid values: 0..240
// y1: y coordinate of the circle center. Valid values: 0..320
// radius: radius size
// color: color parameter.
//==============================================================================
void TFT_Circle(Uint x1, Uint y1, Uint radius, Uint color){  
Sint x = radius, y = 0;
Sint radiusError = 1 - x;
while(x >= y)
     {
      TFT_Dot(x + x1, y + y1, color);
      TFT_Dot(y + x1, x + y1, color);
      TFT_Dot(-x + x1, y + y1, color);
      TFT_Dot(-y + x1, x + y1, color);
      TFT_Dot(-x + x1, -y + y1, color);
      TFT_Dot(-y + x1, -x + y1, color);
      TFT_Dot(x + x1, -y + y1, color);
      TFT_Dot(y + x1, -x + y1, color);
      y++;
      if(radiusError<0)
        {
         radiusError += 2 * y + 1;
        }else
        {
         x--;
         radiusError += 2 * (y - x + 1);
        }
     }
}

//==============================================================================
// This function draws a filled circle on TFT.
//==============================================================================
void TFT_CircleFill(Uint x1, Uint y1, Uint radius, Uint color){
Uchar i = dot_size;    
Sint x = radius, y = 0;
Sint radiusError = 1 - x;
dot_size = 0; 
while(x >= y)
     {
      TFT_Line(x1-x, y1+y, x1+x, y1+y, color);
      TFT_Line(x1-x, y1-y, x1+x, y1-y, color);
      TFT_Line(x1-y, y1+x, x1+y, y1+x, color);
      TFT_Line(x1-y, y1-x, x1+y, y1-x, color);
      TFT_Dot(x + x1, y + y1, color);
      TFT_Dot(y + x1, x + y1, color);
      TFT_Dot(-x + x1, y + y1, color);
      TFT_Dot(-y + x1, x + y1, color);
      TFT_Dot(-x + x1, -y + y1, color);
      TFT_Dot(-y + x1, -x + y1, color);
      TFT_Dot(x + x1, -y + y1, color);
      TFT_Dot(y + x1, -x + y1, color);
      y++;
      if(radiusError<0)
        {
         radiusError += 2 * y + 1;
        }else
        {
         x--;
         radiusError += 2 * (y - x + 1);
        }
     }
dot_size = i;
}

//==============================================================================
// This function is used to draw a round edge.
//==============================================================================
void TFT_RoundEdge(Uint x1, Uint y1, Uint alignment, Uint radius, Uint color){
Sint x = radius, y = 0;
Sint radiusError = 1 - x;
while(x >= y)
     {
      switch(alignment)
        {
         case 1: 
                TFT_Dot(x + x1, y + y1, color);
                TFT_Dot(y + x1, x + y1, color);
         break;
         case 2:
                TFT_Dot(-x + x1, y + y1, color);
                TFT_Dot(-y + x1, x + y1, color); 
         break;
         case 3:
                 TFT_Dot(-x + x1, -y + y1, color);
                 TFT_Dot(-y + x1, -x + y1, color); 
         break;
         case 4:
                TFT_Dot(x + x1, -y + y1, color);
                TFT_Dot(y + x1, -x + y1, color);
         break;
        }      
      y++;
      if(radiusError<0)
        {
         radiusError += 2 * y + 1;
        }else
        {
         x--;
         radiusError += 2 * (y - x + 1);
        }
     }
}

//==============================================================================
// This function draws a image on a desired location.
// x: x position. 
// y: y position. 
// width: width of the image in pixels.
// height: height of the image in pixels.
//==============================================================================
void TFT_Icon(CUint *buffer, Uint x, Uint y, Uchar width_, Uchar height_){
Uint i, j;    
TFT_ColumnPage(x, x + (width_ - 1), y, y + (height_ - 1));
TFT_CS = 0; TFT_DC = 1;
for(i = 0; i < height_; i++)
   {
    for(j = 0; j < width_; j++)
       {
        SPI1_Write(*buffer >> 8);
        SPI1_Write(*buffer & 0xFF);    
        buffer++;
       }
   }
TFT_CS = 1;
}