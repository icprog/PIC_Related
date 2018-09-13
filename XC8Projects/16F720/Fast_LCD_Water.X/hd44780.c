#include "system.h"
#include <xc.h>
#include "hd44780.h"


#define LCD_DATA_PORT 	PORT(LCD_DATA)
#define LCD_DATA_TRIS 	TRIS(LCD_DATA)

#define LCD_E           PORTBIT(LCD_E_PORT,LCD_E_POS)
#define LCD_E_TRIS      TRISBIT(LCD_E_PORT,LCD_E_POS)

#define LCD_RS          PORTBIT(LCD_RS_PORT,LCD_RS_POS)
#define LCD_RS_TRIS     TRISBIT(LCD_RS_PORT,LCD_RS_POS)

#define LCD_RW          PORTBIT(LCD_RW_PORT,LCD_RW_POS)
#define LCD_RW_TRIS     TRISBIT(LCD_RW_PORT,LCD_RW_POS)


#define SET_E() (LCD_E=1)
#define SET_RS() (LCD_RS=1)
#define SET_RW() (LCD_RW=1)

#define CLEAR_E() (LCD_E=0)
#define CLEAR_RS() (LCD_RS=0)
#define CLEAR_RW() (LCD_RW=0)

//******************************************************************************
// Function to Re-set LCD (As it powers up in 8 Bit Mode, then you switch it
// to 4 bit mode, you need to Re-set it in 4 Bit mode, not Re-initialize it!)
//******************************************************************************
void LCDReset(uint8_t style)
{
    LCDCmd(0b00101000);         //function set 4-bit,2 line 5x7 dot format
    LCDCmd(0b00001100|style);	//Display On

}
//******************************************************************************
// Create your Custom Character symbols here
// Their are 8 custom char in the LCD they can be defined using 
// "LCD Custom Character Builder" PC Software.
// You can print custom character using the % symbol. For example to print custom 
// char number 0 (which is a degree symbol), you need to write:
// LCDWriteString("Temp is 30%0C"); (%0 will be replaced by custom char 0.)
// So it will be printed like: Temp is 30�C
//******************************************************************************
unsigned char __cgram[]=
{
	0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00, //Char0 dergee symbol
/*	0x00, 0x04, 0x0E, 0x1F, 0x0E, 0x04, 0x00, 0x00, //Char1
	0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04, 0x00, //Char2
	0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00, 0x00, //Char3
	0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00, 0x00, //Char4
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //Char5
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //Char6
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //Char7   */
};


//******************************************************************************
// Sends a byte to the LCD in 4bit mode (cmd=0 for data, cmd=1 for command)
// NOTE: THIS FUNCTION RETURS ONLY WHEN LCD HAS PROCESSED THE COMMAND
//******************************************************************************
void LCDByte(uint8_t c,uint8_t isdata)
{
uint8_t hn,ln;			//Nibbles
uint8_t temp;

hn=c>>4;
ln=(c & 0x0F);

if(isdata==0)
	CLEAR_RS();
else
	SET_RS();

delay_us(1);

SET_E();

//Send high nibble

temp=(LCD_DATA_PORT & (~(0X0F<<LCD_DATA_POS)))|((hn<<LCD_DATA_POS));
LCD_DATA_PORT=temp;

delay_us(1);			//tEH

//Now data lines are stable pull E low for transmission

CLEAR_E();

delay_us(1);

//Send the lower nibble
SET_E();

temp=(LCD_DATA_PORT & (~(0X0F<<LCD_DATA_POS)))|((ln<<LCD_DATA_POS));

LCD_DATA_PORT=temp;

delay_us(1);			//tEH

//SEND

CLEAR_E();

delay_us(1);			//tEL

LCDBusyLoop();
}

void LCDBusyLoop()
{
	//This function waits till lcd is BUSY

	uint8_t busy,status=0x00,temp;

	//Change Port to input type because we are reading data
	LCD_DATA_TRIS|=(0x0f<<LCD_DATA_POS);

	//change LCD mode
	SET_RW();		//Read mode
	CLEAR_RS();		//Read status

	//Let the RW/RS lines stabilize

	delay_us(1);

	do
	{

		SET_E();

		//Wait tDA for data to become available
		delay_us(1);

		status=(LCD_DATA_PORT>>LCD_DATA_POS);
		status=status<<4;

		delay_us(1);

		//Pull E low
		CLEAR_E();
		delay_us(1);	//tEL

		SET_E();
		delay_us(1);

		temp=(LCD_DATA_PORT>>LCD_DATA_POS);
		temp&=0x0F;

		status=status|temp;

		busy=status & 0b10000000;

		delay_us(1);

                CLEAR_E();
		delay_us(1);	//tEL
	}while(busy);

	CLEAR_RW();		//write mode

        //Change Port to output
	LCD_DATA_TRIS&=(~(0x0F<<LCD_DATA_POS));

}

//******************************************************************************
// This function Initializes the lcd module, must be called before calling lcd 
// related functions
// Arguments:
// style = LS_BLINK,LS_ULINE(can be "OR"ed for combination)
// LS_BLINK : The cursor is blinking type
// LS_ULINE : Cursor is "underline" type else "block" type
// LS_NONE : No visible cursor
//******************************************************************************
void LCDInit(uint8_t style)
{
    delay_ms(750);              //After power on Wait for LCD to Initialize
                                //Set IO Ports
	LCD_DATA_TRIS&=(~(0x0F<<LCD_DATA_POS)); //Output
    LCD_E_TRIS=0;               //Output
    LCD_RS_TRIS=0;              //Output
    LCD_RW_TRIS=0;              //Output

	LCD_DATA_PORT&=(~(0x0F<<LCD_DATA_POS));//Clear data port

    CLEAR_E();
	CLEAR_RW();
	CLEAR_RS();

                                //Set 4-bit mode
	delay_us(8);

	SET_E();
	LCD_DATA_PORT|=((0b00000010)<<LCD_DATA_POS); //[B] To transfer 0b00100000 i was using LCD_DATA_PORT|=0b00100000
	delay_us(8);
	CLEAR_E();
	delay_us(8);

	//Wait for LCD to execute the Functionset Command
	LCDBusyLoop();

	//Now the LCD is in 4-bit mode

	
	LCDCmd(0b00101000);             //function set 4-bit,2 line 5x7 dot format
    LCDCmd(0b00001100|style);   	//Display On

	/* Custom Char */
    LCDCmd(0b01000000);

	uint8_t __i;
	for(__i=0;__i<sizeof(__cgram);__i++)
		LCDData(__cgram[__i]);
}

//******************************************************************************
// This function Writes a given string to lcd at the current cursor location.
// Arguments:
// msg: a null terminated C style string to print
// Custom Char Support
//******************************************************************************
void LCDWriteString(const char *msg)
{
    while(*msg!='\0')
    {
        if(*msg=='%')
        {
            msg++;
            int8_t cc=*msg-'0';

            if(cc>=0 && cc<=7)
            {
                LCDData(cc);
            }
            else
            {
                LCDData('%');
                LCDData(*msg);
            }
        }
        else
        {
            LCDData(*msg);
        }
        msg++;
    }
}

//******************************************************************************
// This function writes a integer type value to LCD module 
// Arguments:
// 1)int val	: Value to print
// 2)unsigned int field_length :total length of field in which the value is printed
//	must be between 1-5 if it is -1 the field length is no of digits in the val
//******************************************************************************
void LCDWriteInt(int val,int8_t field_length)
{
	char str[5]={0,0,0,0,0};
	int i=4,j=0;
   
    if(val<0)           //Handle negative integers
    {
        LCDData('-');   //Write Negative sign
        val=val*-1;     //convert to positive
    }

	while(val)
	{
        str[i]=val%10;
        val=val/10;
        i--;
	}

	if(field_length==-1)
    {
        while(str[j]==0) j++;
    }
	else
    {
		j=5-field_length;
    }
	
	for(i=j;i<5;i++)
	{
	LCDData(48+str[i]);
	}
}

//******************************************************************************
//      Position the cursor to specific part of the screen
//******************************************************************************
void LCDGotoXY(uint8_t x,uint8_t y)
{
    #ifdef LCD_TYPE_162

    if(x>=16) return;

    switch(y)
    {
	case 0:
        break;
    
    case 1:
        x|=0b01000000;
        break;
    }

    #endif


	#ifdef LCD_TYPE_164

        if(x>=16) return;

	switch(y)
	{
		case 0:
			break;
            
		case 1:
			x|=0b01000000;
			break;
            
		case 2:
			x+=0x10;
			break;
            
		case 3:
			x+=0x50;
			break;
	}

	#endif

        

	#ifdef LCD_TYPE_202

    if(x>=20) return;

	switch(y)
	{
		case 0:
			break;
            
		case 1:
			x|=0b01000000;
			break;
	}

	#endif


    #ifdef LCD_TYPE_204

    if(x>=20) return;

	switch(y)
	{
		case 0:
			break;
            
		case 1:
			x|=0b01000000;
			break;
            
		case 2:
			x+=0x14;
			break;
            
		case 3:
			x+=0x54;
			break;
	}

	#endif

	x|=0b10000000;
  	LCDCmd(x);
}