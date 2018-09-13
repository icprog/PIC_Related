/*****************************************************************************
Author: Peter J. Vis
First Written: 8 Dec 2004
Last Updated: 12 Dec 2006
Title: Displaying a Bar Graph on a 128x64 LCD

Microcontroller: ATmega32
Crystal: 16Mhz
Platform: Development System

Documentation:
Further information regarding this code is available on-line:
http://petervis.com

PURPOSE:
To display a Bar Graph.

LIMITATIONS:
No part of this work may be used in commercial
applications without prior written permission. This work cannot be
used by Bloggers, or any kind of on-line publishing.

COPYRIGHT:	
All the material including function names are copyright protected.

CIRCUIT:
My Modular Development System

*******************************************************************************/

#include <avr/pgmspace.h>
#include <avr/io.h>


// Clock Oscillator Type.
#define F_CPU 16000000UL

// Control Port Used.
#define	cPort	 	PORTB
#define	cPort_ddr	DDRB
#define	cPort_pins	PINB

// Data Port Used.
#define	dPort		PORTD
#define	dPort_ddr	DDRD
#define	dPort_pins	PIND


						// Control Port Bits Involved
						// Function ------------- LCD ------ PortB
#define	lcdrs	0 		// RS ALSO CALLED D/I --- pin4 ----- Pin0 
#define	lcdrw	1 		// R/W ------------------ pin5 ----- Pin1 
#define	lcde	2       // e -------------------- pin6 ----- Pin2 
#define	lcdcs1	5       // CS1 ------------------ pin15 ---- Pin5 
#define	lcdcs2	4       // CS2 ------------------ pin16 ---- Pin4 
#define	lcdrst	3       // RST ------------------ pin17 ---- Pin3 


// LCD Commands.
#define START_LINE		0b11000000
#define SET_ADDRESS		0b01000000
#define SET_PAGE		0b10111000
#define DISP_ON			0b00111111
#define DISP_OFF		0b00111110


// Global variables.
unsigned char column = 0;
unsigned char page = 0;



// Fuction prototypes.
void cSelect(uint8_t col);				// Select the controller chip depending on column number.

// Command pair.
void CommandMode (void);				// This sets the Data bus to accept commands.
void WriteCommand(uint8_t cmd);			// This sends the command to the controllers.

// Data pair.
void DataMode (void);					// This sets the bus to accept data.
void LocknLoad (void);					// Load the Data Buffer and latch for the next byte.


void lcdInit (void);					// Initialise the LCD.
void clearl (void);						// Clear the LCD.						

// Page change.
void setNewPage (unsigned char data);	

// Set cursor position.
void setXY(uint8_t x, uint8_t y);


// Draw Bar.
void Bar(uint8_t height, uint8_t width, uint8_t xpos, uint8_t row);

// Clear Bar.
void BarC(uint8_t height, uint8_t width, uint8_t xpos, uint8_t row);
