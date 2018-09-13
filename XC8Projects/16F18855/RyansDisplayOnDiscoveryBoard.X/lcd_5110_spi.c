#include "lcd_5110_spi.h"

#define LCD_CLK     RC2PPS                      // Clock Pin
#define LCD_DIN     RC5PPS                      // Data Pin
#define LCD_DC      LATBbits.LATB2              // Register Select Pin
#define LCD_CE      LATBbits.LATB1              // Chip Enable Pin
#define LCD_RST     LATBbits.LATB0              // Display Reset Pin

#define LCD_COMMAND         0                           
#define LCD_DATA            1

#define LCD_X               84                  // LCD Width  (Actual Display Width is 29mm)
#define LCD_Y               48                  // LCD Height (Actual Display Height is 19 mm)


                            // <editor-fold defaultstate="collapsed" desc="3 Bit wide Font">
const char fonts [] = {
    0x00, 0x00, 0x00,  // sp
    0x00, 0x4E, 0x00,  // ! *
    0x06, 0x00, 0x06,  // " *
    0xff, 0xff, 0xff,  // #  35
    0x48, 0xd6, 0x24,  // $ *
    0x12, 0x08, 0x24,  // % *
//    0x13, 0x6B, 0x64,  // % *
    0xff, 0xff, 0xff,  // &
    0x00, 0x06, 0x00,  // ' *
    0x38, 0x44, 0x82,  // ( * 40
    0x82, 0x44, 0x38,  // ) *
    0x14, 0x08, 0x3E,  // *
    0x10, 0x38, 0x10,  // + *
    0xa0, 0x60, 0x00,  // , *
    0x10, 0x10, 0x10,  // - * 45
    0x60, 0x60, 0x00,  // . *
    0x60, 0x18, 0x06,  // / *
    0x7c, 0x42, 0x7c,  // 0 *
    0x44, 0x7e, 0x40,  // 1 *
    0x64, 0x52, 0x4c,  // 2 * 50
    0x4a, 0x4a, 0x34,  // 3 *
    0x38, 0x24, 0x7e,  // 4 *
    0x4e, 0x4a, 0x32,  // 5 *
    0x3c, 0x4a, 0x32,  // 6 *
    0x62, 0x1a, 0x06,  // 7 * 55
    0x76, 0x4a, 0x76,  // 8 *
    0x4c, 0x52, 0x3c,  // 9 *
    0x6c, 0x6c, 0x00,  // : *
    0xac, 0x6c, 0x00,  // ; *
    0x10, 0x28, 0x44,  // < * 60
    0x28, 0x28, 0x28,  // = *
    0x44, 0x28, 0x10,  // > *
    0x02, 0x59, 0x06,  // ?
    0xFF, 0xFF, 0xFF,  // @
    0x7c, 0x12, 0x7c,  // A * 65
    0x7E, 0x5A, 0x34,  // B *
    0x3c, 0x42, 0x42,  // C *
    0x7e, 0x42, 0x3c,  // D *
    0x7e, 0x4a, 0x42,  // E *
    0x7e, 0x0a, 0x0a,  // F * 70
    0x3c, 0x52, 0x34,  // G *
    0x7e, 0x08, 0x7e,  // H *
    0x42, 0x7e, 0x42,  // I *
    0x30, 0x40, 0x3e,  // J *
    0x7e, 0x18, 0x66,  // K * 75
    0x7e, 0x40, 0x40,  // L *
    0x7e, 0x1c, 0x7e,  // M *
    0x7e, 0x02, 0x7e,  // N *
    0x3c, 0x42, 0x3c,  // O *
    0x7e, 0x12, 0x0c,  // P * 80
    0x7e, 0x62, 0xfe,  // Q *
    0x7e, 0x32, 0x4e,  // R *
    0x44, 0x4a, 0x32,  // S *
    0x02, 0x7e, 0x02,  // T *
    0x7E, 0x40, 0x7E,  // U * 85
    0x3e, 0x40, 0x3e,  // V *
    0x7E, 0x38, 0x7E,  // W *
    0x66, 0x18, 0x66,  // X *
    0x0e, 0x70, 0x0e,  // Y *
    0x62, 0x5a, 0x46,  // Z * 90
    0x00, 0x7e, 0x42,  // [ *
    0x06, 0x18, 0x60,  // backslash *
    0x42, 0x7e, 0x00,  // ] *
    0x04, 0x02, 0x04,  // ^ *
    0x40, 0x40, 0x40,  // _ * 95
    0x00, 0x02, 0x04,  // ` *
    0x74, 0x54, 0x78,  // a *
    0x7e, 0x48, 0x30,  // b *
    0x30, 0x48, 0x48,  // c *
    0x30, 0x48, 0x7e,  // d * 100
    0x38, 0x54, 0x58,  // e *
    0x7C, 0x0A, 0x02,  // f *
    0x98, 0xa4, 0x7c,  // g *
    0x7e, 0x08, 0x70,  // h *
    0x48, 0x7a, 0x40,  // i * 105
    0x88, 0xfa, 0x00,  // j *
    0x7e, 0x18, 0x64,  // k *
    0x42, 0x7E, 0x40,  // l *
    0x7c, 0x38, 0x7c,  // m *
    0x7C, 0x04, 0x78,  // n * 110
    0x38, 0x44, 0x38,  // o *
    0xFC, 0x24, 0x18,  // p *
    0x18, 0x24, 0xFC,  // q *
    0x78, 0x04, 0x04,  // r *
    0x48, 0x54, 0x24,  // s * 115
    0x04, 0x3e, 0x44,  // t *
    0x7C, 0x40, 0x7C,  // u *
    0x3c, 0x40, 0x3c,  // v *
    0x7c, 0x30, 0x7c,  // w *
    0x6c, 0x10, 0x6c,  // x * 120
    0x9c, 0xa0, 0x7c,  // y *
    0x64, 0x54, 0x4c,  // z *
    0x0C, 0x12, 0x0c,  // degree symbol
    0xFF, 0xFF, 0xFF,  // O
    0xFF, 0xFF, 0xFF,  // U   125
    0xFF, 0xFF, 0xFF,  // a
    0xFF, 0xFF, 0xFF,  // o
    0xFF, 0xFF, 0xFF,  // u
    0xFF, 0xFF, 0xFF,  // 
    0xfc, 0x40, 0x7c,  // µ * 130
    0xFF, 0xFF, 0xFF,  // <
    0xFF, 0xFF, 0xFF,  // 
};
// </editor-fold>


void gotoXY(char x, char y)
{
    LCDWrite(0, 0x80 | x);                      // goto Column position "x".
    LCDWrite(0, 0x40 | y);                      // goto Row position "y".
}


void LCDBitmap(const char bmp_array[], uint8_t startLine, uint16_t len)   // len is 84 x number of lines to display
{
    uint16_t index;
    gotoXY(0,startLine);                        // X is always 0, Y is line number tostart on
    for (index = 0 ; index < len ; index++)     // loop through the bmp_array,
    {
        LCDWrite(LCD_DATA, bmp_array[index]);   // & write it byte by byte.     
    } 
}


/*void SPIWrite(const char sentCharacter)
{
    char receivedCharacter  =   0;  
    receivedCharacter       = SSP1BUF;                // dummy read in case unread value might be in register from start up or something 
    
    SSP1BUF = sentCharacter;
    __delay_us(5);
    
    while (SSP1CON1bits.WCOL)      //Check for write collision
    {
        SSP1CON1bits.WCOL = 0;          //Reset collision bit
        __delay_us(5);
        SSP1BUF = receivedCharacter;
        __delay_us(5);
    }
    
    SSP1STATbits.BF = 0;                    // Reset Data arrived flag. This is probably reset automatically on an SSPBUF read
}*/

void LCDWriteCharacter(const char character)
{
/*    uint16_t base;
    base = character - 32;
    base *= 3;                                  // 3 bit Font, so location * 3 will pull up correct font
    LCDWrite(LCD_DATA,fonts[base]);             // fonts are written 1 vertical line of 8 bits at a time
    LCDWrite(LCD_DATA,fonts[base + 1]);         // so, this is the second vertical line
    LCDWrite(LCD_DATA,fonts[base + 2]);         // third vertical line of font character
    LCDWrite(LCD_DATA, 0x00);                   // write a blank line to space the font
}*/

    uint16_t base,x,z;                          // somehow, adding the z variable (instead of using just x) saves 6 bytes)
    base = character - 32;
    base *= 3;                                  // 3 bit Font, so location * 3 will pull up correct font
    z = base;
    for(x=base;base<(z+3);base++)
    {
        SPIWrite(LCD_DATA,fonts[base]);         // fonts are written 1 vertical line of 8 bits at a time
  //        LCDWrite(LCD_DATA,fonts[base]);         // fonts are written 1 vertical line of 8 bits at a time
    }
    SPIWrite(LCD_DATA, 0x00);                   // write a blank line to space the font
}
  // above saves 10 bytes vs previous code


void LCDWriteString(const char *characters) 
{
    while (*characters)
    LCDWriteCharacter(*characters++);
}

void LCDClear(void)                             //Clears the LCD by writing zeros to the entire screen
{
    int index;
    for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, 0x00);
    gotoXY(0, 0);                               //After we clear the display, return to the home position
}

void LCDWriteInt(int value,signed char fieldLength, signed char numPlaces, signed char sign)
{
	char str[5]={0,0,0,0,0};                    // Integer can be up to 5 characters long
	int i=4,j=0;

    if(value<0)                                 // Handle negative integers
    {
        LCDWriteCharacter('-');                 // Write Negative sign to the LCD
        value=value*-1;                         // convert negative value to a positive value
    }
    
    else
    {
        if(sign == 1)
        {
            LCDWriteCharacter('+');
        }
    }

	while(value)
	{
            str[i]=value%10;
            value=value/10;
            i--;
	}
	if(fieldLength==-1)                         // if fieldLength is -1, the field length is # of digits in the value
    {
		while(str[j]==0)
        {
            j++;
        }
    }
	else
    {
		j=5-fieldLength;                        // fieldLength must be between 1 and 5
    }

	for(i=j;i<(5-numPlaces);i++)
	{
        LCDWriteCharacter(48+str[i]);           // Write out Integer value to the screen as characters
	}

    if(numPlaces == 1)
    {
        LCDWriteCharacter(46);                  // A decimal period!
        LCDWriteCharacter(48+str[4]);
    }

    if(numPlaces == 2)
    {
        LCDWriteCharacter(46);                  // A decimal period!
        LCDWriteCharacter(48+str[3]);
        LCDWriteCharacter(48+str[4]);
    }
}


void LCDInit(void)
{
    LCD_RST = 0;                                // Reset is Active Low
    __delay_ms(100);                            // delay needed on Reset    
    LCD_RST = 1;                                // Clear Reset Bit

//    TRISBbits.TRISB0    =   0;
  //  TRISBbits.TRISB1    =   0;
    //TRISBbits.TRISB2    =   0;

//    LCD_DIN = 0;
  //  LCD_CLK = 0;
    //LCD_DC  = 0;

    LCDWrite(LCD_COMMAND, 0x21);                //Tell LCD that extended commands follow

//The code for changing the contrast on the fly is easy. Set the SCE pin to low to enable the serial interface.
//Set the D/C pin to low (which tells the LCD you are sending commands, not pixel data), then send byte 0x21 which enables the extended instruction set,
//then send the contrast byte, then send byte 0x20 which returns to the basic instruction set. You do not need to reset the panel or anything like that.
//The acceptable range is between 0x80 (being a contrast value of 0) and 0xFF (being a contrast value of 127)
    
    LCDWrite(LCD_COMMAND, 0xBE);                //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark

    LCDWrite(LCD_COMMAND, 0x04);                //Set Temp coefficent

    LCDWrite(LCD_COMMAND, 0x13);                //LCD bias mode 1:48: Try 0x13 or 0x14

    LCDWrite(LCD_COMMAND, 0x20);                //We must send 0x20 to tell the display to use standard commands

    LCDWrite(LCD_COMMAND, 0x0C);                //Set display control, normal mode. 0x0D for inverse
}

void SPIWrite(uint8_t data_or_command, uint8_t data)
{
    uint8_t i; //,d;                            // Save 4 bytes by eliminating the d variable

    char receivedCharacter  =   0;  
    
//    d=data;
    
    if(data_or_command == 0)
    {
        LCD_DC  =   0;                          // Set Register Select Low
    }
    else
    {
        LCD_DC  =   1;                          // Set Register Select High
    }   

    LCD_CE  =   0;                              // Set Chip enable Low

    receivedCharacter       = SSP1BUF;                // dummy read in case unread value might be in register from start up or something 

    LCD_DIN = 1;
    
    SSP1BUF = data;
    __delay_us(5);
    
    while (SSP1CON1bits.WCOL)      //Check for write collision
    {
        SSP1CON1bits.WCOL = 0;          //Reset collision bit
        __delay_us(5);
        SSP1BUF = receivedCharacter;
        __delay_us(5);
    }

    LCD_CLK =   1;                          // Set Clock to "1" and Clock in the Bit

    __delay_us(2);
    
    LCD_CLK = 0;
    
    SSP1STATbits.BF = 0;                    // Reset Data arrived flag. This is probably reset automatically on an SSPBUF read

    LCD_CE  =   1;                              // Display is no longer accepting Data                                      
}


void LCDWrite(uint8_t data_or_command, uint8_t data)
{
    uint8_t i; //,d;                            // Save 4 bytes by eliminating the d variable
    
//    d=data;
    
    if(data_or_command == 0)
    {
        LCD_DC  =   0;                          // Set Register Select Low
    }
    else
    {
        LCD_DC  =   1;                          // Set Register Select High
    }   

    LCD_CE  =   0;                              // Set Chip enable Low

    for(i=0;i<8;i++)
    {
        LCD_DIN = 0;

        if(data&0x80)                           // If the Bit is a "1"
        {
            LCD_DIN =   1;                      // Turn On the Bit at this Display Position
        }
        
        LCD_CLK =   1;                          // Set Clock to "1" and Clock in the Bit
        
        data<<=1;                               // Grab the next Bit
        
        LCD_CLK=0;                              // Set Clock to "0"
    }

    LCD_CE  =   1;                              // Display is no longer accepting Data                                      
}


void LCDDrawBox(void)
{
    int j;
    
    for(j = 0; j < 84; j++)                     // top
    {
        gotoXY(j, 0);
        LCDWrite(LCD_DATA,0x01);
    }

    for(j = 0; j < 84; j++)                     //Bottom
    {
        gotoXY(j, 5);
        LCDWrite(LCD_DATA,0x80);
    }
    
    for(j = 0; j < 6; j++)                      // Left
    {
        gotoXY(0, j);
        LCDWrite(LCD_DATA,0xff);
    }
    
    for(j = 0; j < 6; j++)                      // Right
    {
        gotoXY(83, j);
        LCDWrite(LCD_DATA,0xff);
    }
}

