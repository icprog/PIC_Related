///////////////////////////////////////////////////////////////////////
//
//     PIC16F877 - LCD03 example
//     Written using HITECH PIC16 compiler
//
//     This code is Freeware - Use it for any purpose you like.
//
///////////////////////////////////////////////////////////////////////


#include <xc.h>
#include <stdio.h>

//__CONFIG(0x3b32);

void clrscn(void);				// prototypes
void cursor(char pos);
void print(char *p);
void setup(void);

char s[21];						// buffer used to hold text to print

void main(void)
{
	setup();					// sets up the PIC16F877 I2C port
	clrscn();					// clears the LCD03 disply
	cursor(26);					// sets cursor to center the text on 2nd row of LCD03
	sprintf(s,"Hello World");	// Traditional welcome text, printed into our buffer
	print(s);					// send it to the LCD03

	while(1);					// just stops
}


void clrscn(void)
{
	SEN = 1;					// send start bit
	while(SEN);					// and wait for it to clear

	SSPIF = 0;
	SSPBUF = 0xc6;				// LCD02 I2C address
	while(!SSPIF);				// wait for interrupt
	SSPIF = 0;					// then clear it.

	SSPBUF = 0;					// address of register to write to
	while(!SSPIF);				//
	SSPIF = 0;					//

	SSPBUF = 12;				// clear screen
	while(!SSPIF);				//
	SSPIF = 0;					//

	SSPBUF = 4;					// cursor off
	while(!SSPIF);				//
	SSPIF = 0;					//

	PEN = 1;					// send stop bit
	while(PEN);					//
}


void cursor(char pos)
{
	SEN = 1;					// send start bit
	while(SEN);					// and wait for it to clear

	SSPIF = 0;
	SSPBUF = 0xc6;				// LCD02 I2C address
	while(!SSPIF);				// wait for interrupt
	SSPIF = 0;					// then clear it.

	SSPBUF = 0;					// address of register to write to
	while(!SSPIF);				//
	SSPIF = 0;					//

	SSPBUF = 2;					// set cursor
	while(!SSPIF);				//
	SSPIF = 0;					//
	SSPBUF = pos;				//
	while(!SSPIF);				//
	SSPIF = 0;					//

	PEN = 1;					// send stop bit
	while(PEN);					//
}


void print(char *p)
{
	SEN = 1;					// send start bit
	while(SEN);					// and wait for it to clear

	SSPIF = 0;
	SSPBUF = 0xc6;				// LCD02 I2C address
	while(!SSPIF);				// wait for interrupt
	SSPIF = 0;					// then clear it.

	SSPBUF = 0;					// address of register to write to
	while(!SSPIF);				//
	SSPIF = 0;					//

	while(*p) {
		SSPBUF = *p++;			// write the data
		while(!SSPIF);			//
		SSPIF = 0;				//
	}

	PEN = 1;					// send stop bit
	while(PEN);					//
}


void setup(void)
{
unsigned long x;

	TRISC = 0xff;
	PORTC = 0xff;

	SSPSTAT = 0x80;
	SSPCON = 0x38;
	SSPCON2 = 0x00;
	SSPADD = 10;				// SCL = 91khz with 4Mhz Osc

	for(x=0; x<60000; x++);		// wait for LCD03 to initialise

}

