#include            "glcd.h"
#include            "system.h"
#include            "fonts.h"              // fonts and graphics are stored here

#define glcd_lat    LATC
#define glcd_tris   TRISC
#define BSY         PORTC

#define CS1         LATBbits.LATB8
#define CS2         LATBbits.LATB9
#define DI          LATBbits.LATB10
#define RW          LATBbits.LATB11
#define E           LATBbits.LATB12
#define RS          LATBbits.LATB13

// <editor-fold defaultstate="collapsed" desc="Not Used Original Code">


/*
extern uint8_t Yposition;

uint8_t putChar(uint8_t X, uint8_t Y, const uint8_t c)
{
    uint8_t page, position = 0;           // page 0 - 7 are 8 bit tall pages on either side of display (X location of page)
    uint16_t base;
    
    Y *= 4;
    
    position += Y;

    if(position > 0x3F)                      //if we reached 80 thats last pixel 7 + 1 goto
    {
        if(position > 0x7F)
        {
            position = 0;
            CS1 = 1;
            CS2 = 0;
        }
        CS1 = 0;                        //Right Side on
        CS2 = 1;                        //left side off
        Y -= 0X40;
    }
    else
    {
        CS1 = 1;                        //Select Left Side On    
        CS2 = 0;                        // Right side Off
    }

    page = 0xB8 + X;                    // Set X position of page (0 = 0XB8) (+X, +1, +2,... for other pages)
    cmd_write(page);                    // Go to selected page
    Yposition = 0x40 + Y;            // Set Y position on page (0 - 63, 0X40 = 0 position)
    cmd_write(Yposition);                // and Go there
    
    base = c - 32;
    base *= 3;                          // 3 bit Font, so location * 3 will pull up correct font
    data_write(font[base]);             // fonts are written 1 verrtical line of 8 bits at a time
    Y +=1;
    data_write(font[base + 1]);         // so, this is the second vertical line
    Y += 1;
    data_write(font[base + 2]);         // third vertical line of font charachter
    Y += 1;
    data_write(0);                      // write a blank line to space the font
    Y += 1;
    return(Y);
}

void CharStr(uint8_t X, uint8_t Y, uint8_t *string)
{
    GoTo_XY(X, Y);                       // Goto desired screen location
	int i;
	for(i=0;string[i]!='\0';i++)        // parse characters out of our string, until we reach a terminating character
    {
	   LCDWriteChar(string[i]);         // and write the parsed characters to the LCD (as a string))
    }
}


void GoTo_XY(uint8_t X, uint8_t Y)
{
    uint8_t page, position;       // page 0 - 7 are 8 bit tall pages on either side of display (X location of page)
    if((Y) > 0x3F)                  //if we reached 80 thats last pixel 7 + 1 goto
    {                        
        CS1 = 0;                        //Right Side on
        CS2 = 1;                        //left side off
        Y -= 0X40;
    }
    else
    {
        CS1 = 1;                        //Select Left Side On    
        CS2 = 0;                        // Right side Off
    }

    page = 0xB8 + X;                    // Set X position of page (0 = 0XB8) (+X, +1, +2,... for other pages)
    cmd_write(page);                    // Go to selected page
    position = 0x40 + Y;            // Set Y position on page (0 - 63, 0X40 = 0 position)
    cmd_write(position);                // and Go there
}
*/
// </editor-fold>

void GoToXY(uint8_t X, uint8_t Y)
{
    uint8_t page, position;             // page 0 - 7 are 8 bit tall pages on either side of display (X location of page)
    if((Y * 4) > 0x3F)                  //if we reached 80 thats last pixel 7 + 1 goto
    {                        
        CS1 = 0;                        //Right Side on
        CS2 = 1;                        //left side off
        Y -= 0X10;
    }
    else
    {
        CS1 = 1;                        //Select Left Side On    
        CS2 = 0;                        // Right side Off
    }

    page = 0xB8 + X;                    // Set X position of page (0 = 0XB8) (+X, +1, +2,... for other pages)
    cmd_write(page);                    // Go to selected page
    position = 0x40 + (Y*4);            // Set Y position on page (0 - 63, 0X40 = 0 position)
    cmd_write(position);                // and Go there
}

void LCDWriteChar(const uint8_t c)
{
    uint16_t base;
    base = c - 32;
    base *= 3;                          // 3 bit Font, so location * 3 will pull up correct font
    data_write(font[base]);             // fonts are written 1 verrtical line of 8 bits at a time
    data_write(font[base + 1]);         // so, this is the second vertical line
    data_write(font[base + 2]);         // third vertical line of font charachter
    data_write(0);                      // write a blank line to space the font
}

void LCDWriteString(char *string)
{
//    GoToXY(X, Y);                       // Goto desired screen location
	int i;
	for(i=0;string[i]!='\0';i++)        // parse characters out of our string, until we reach a terminating character
    {
	   LCDWriteChar(string[i]);         // and write the parsed characters to the LCD (as a string))
    }
}

void LCDWriteInt(int value,signed char fieldLength, signed char numPlaces)     //writes a integer type value to LCD module
{
	char str[5]={0,0,0,0,0};            // Integer can be up to 5 characters long
	int i=4,j=0;

    if(value<0)                         // Handle negative integers
    {
        LCDWriteChar('-');              // Write Negative sign to the LCD
        value=value*-1;                 // convert negative value to a positive value
    }

	while(value)
	{
            str[i]=value%10;
            value=value/10;
            i--;
	}
	if(fieldLength==-1)                 // if fieldLength is -1, the field length is # of digits in the value
    {
		while(str[j]==0)
        {
            j++;
        }
    }
	else
    {
		j=5-fieldLength;                // fieldLength must be between 1 and 5
    }

	for(i=j;i<(5-numPlaces);i++)
	{
        LCDWriteChar(48+str[i]);            // Write out Integer value to the screen as characters
	}

    if(numPlaces == 1)
    {
        LCDWriteChar(46);                   //A decimal period!
        LCDWriteChar(48+str[4]);
    }

    if(numPlaces == 2)
    {
        LCDWriteChar(46);                   //A decimal period!
        LCDWriteChar(48+str[3]);
        LCDWriteChar(48+str[4]);
    }
}

void loadimg(const uint8_t *image, uint16_t len, char startPage)
{
    char i,x,y;

    int z = 0;
    while(z != len)            
    {
        for(i = startPage;i<8;i++)
        {
            CS1 = 1;
            CS2 = 0;
            y = 0xB8 + i;
            cmd_write(y);  
            cmd_write(0x40);

            for(x=0;x<64;x++)
            {
                if(z == len)
                break;
                data_write(*image);
                image++;
                z++;
            }

            CS1 = 0;
            CS2 = 1;
            y = 0xB8 + i;
            cmd_write(y);  
            cmd_write(0x40);

            for(x=0;x<64;x++)
            {
                if(z == len)
                    break;
                data_write(*image);
                image++;
                z++;
            }

            if(z == len)
                break;
        }
        if(z == len)
            break;
    }
}

// <editor-fold defaultstate="collapsed" desc="Also not used">


/*

uint8_t lcd_putchar(uint8_t X, uint8_t Y, char c)
{
    uint8_t page, position;
    uint16_t base;
    base = c - 32;
    base *= 3;
    
    if(Y > 0x3F)                        //if we reached 80 thats last pixel 7 + 1 goto
    {                        
        CS1 = 0;                        //Right Side on
        CS2 = 1;                        //left side off
    }
    else
    {
        CS1 = 1;    
        CS2 = 0;
    }
        page = 0xB8 + X;                               //Select Left Side and page 0 (+1, +2,... for other pages)
        cmd_write(page);  

        position = 0x40 + Y;                            //Goto fist y position
        cmd_write(position);
    
    data_write(font[base]);
    Y+=1;
    data_write(font[base + 1]);
    Y+=1;
    data_write(font[base + 2]);
    Y+=1;
//    data_write(font[base + 3]);
//    Y+=1;
  //  data_write(font[base + 4]);
  //  Y+=1;
    data_write(0);
    Y+=1;
    return Y;
}
*/

/*
char printChar(char const *image, char number, char x, int y)  //number = number , y = Pixel y, x = page
{
//TODO: Add code to determine if we reached last pixel on right site to add 1 to page and 
//jumpt down . And use left side to continue. 

    char i;
    char w = 7 * number;                    //w will be what number to print (7 bytes wide)

    image= image + w;                       //w = image location + w (which is 7* the number)

    for(i=0;i<7;i++){                       //Loop through 7 bytes 0-6

        if(y > 0x7F){                       //if we reached 80 thats last pixel 7 + 1 goto 
            CS1 = 0;                        //Right Side on
            CS2 = 1;                        //left side off
            cmd_write(x);                   //Right the page we are on
            cmd_write(0x40);                //Y pixel 0 on right side
            y = 0x40;                       //Set y = 0x40 (1st pixel)
        }

        data_write(*image);                 //Write to where ever we are at.
        image++;                            //add 1 to pointer position
        y++;                                //Add 1 to y
    }
    return y;                               //Return 1 so we can use it to check if we reached last pixel
}
*/
// </editor-fold>


void busy(void)
{
	uint8_t stat;
	glcd_tris = 0xff;						// PORTC to all inputs
	DI = 0;
	RW = 1;
	if(CS1==1&&CS2==1)
	{
		CS1 = 0;
		do
		{
			E = 1;
			__delay_us(1);
			stat = BSY;
			E = 0;
		}while(stat==0x80);
		CS1 = 1;
		CS2 = 0;
		do
		{
			E = 1;
			__delay_us(1);
			stat = BSY;
			E = 0;
		}while(stat==0x80);
		CS2 = 1;
	}
	else
	{
		do
		{
			E = 1;
			__delay_us(1);
			stat = BSY;
			E = 0;
		}while(stat==0x80);
	}
	glcd_tris = 0;
}

void cmd_write(uint8_t x)
{
	busy();
	DI = RW = 0;
	glcd_lat = x;
	e_togg();
}

void data_write(uint8_t x)
{
	busy();
	DI = 1;
    RW = 0;
	glcd_lat = x;
	e_togg();
}

void init_lcd(void)
{
	RS = 1;
	E = 0;
	CS1 = CS2 = 1;
	cmd_write(0x3F);                        // turn on display
	cmd_write(0x40);                        // go to left side
	cmd_write(0xB8);                        // go to top page
	cls();                                  // clear the screen
}	

void e_togg(void)
{
	E = 1;
	__delay_us(1);
	E = 0;
}

void cls(void)                              // clear screen
{
	char x,y;
	CS1 = CS2 = 1;
	for(y=0;y<8;y++)                        // page loop
	{
		cmd_write(0xb8 + y);
		for(x=0;x<64;x++)                   // y loop
			data_write(0x00);
	}

	cmd_write(0x40);                        // go to left side
	cmd_write(0xb8);                        // go to top page
}
