/*****************************************************************************
Author: Peter J. Vis
First Written: 8 Dec 2004
Last Updated: 12 Dec 2006
Title: Displaying a Bar Graph on a 128x64 LCD

Microcontroller: ATmega32
Crystal: 16Mhz
Platform: Development System

LIMITATIONS:
No part of this work may be used in commercial
applications without prior written permission. This work cannot be
used by Bloggers, or any kind of on-line publishing.

COPYRIGHT:	
All the materials including function names are copyright protected.

Documentation:
Further information regarding this code is available on-line:
http://petervis.com

PURPOSE:
To display a Bar Graph.

DEPENDENCIES:
128x64.c and 128x64.h

CIRCUIT:
My Modular Development System

*******************************************************************************/


// My header file.
#include "128x64.h"

// These are built-in header files.
#include <inttypes.h>
#include <util/delay.h>


/*

This bar is not plotted with individual pixels. It is filled page / byte at a time for greater speed.
 
Bar height: Range 0 to 64 when the row starts from 7.

Maximum height = 64 - (7 - row) * 8

The bar is drawn from the base to the top.

The variable xpos is the position of the column where the bar starts from.The range of xpos is from 0 to (128-width).
 
Make sure the bar width does not overlap column 64 as there is no provision for drawing half a bar on both sides of the lcd. The extra code would slow down the bar response, and is not necessary if you know to avoid this place.

If the bar width is 5, the last xpos is 59 on CS1 and first xpos is 65 on CS2.
 
*/

void Bar(uint8_t height, uint8_t width, uint8_t xpos, uint8_t row) {
	
	int dP;
	uint8_t c;
	uint8_t j;
	uint8_t fbytes=0;					// Full bytes contain all ones, all pixels.
	uint8_t pbytes=0;					// Partial bytes contain some ones, some pixels.
	uint8_t cmd; 						// This is the Command holder.
	
	page = row; 						// The bar starts from this specified row.
	
	if(height > 64){					// Limit for the height.
	height=64;
	}
	
	if(width > 128){					// Limit for the width.
	width=128;
	}
	
	
	
	while(height > 8) {	
		height = height - 8;		
		fbytes = fbytes + 1;		
	}		
	pbytes = height;
	
	
	for(j = 0; j <= fbytes; j++){
	
				cmd = SET_PAGE | page;
				WriteCommand(cmd);	
				page = page - 1;
				
				
				cmd = SET_ADDRESS | xpos;		
				WriteCommand(cmd);
				
		cSelect(xpos);								// Select which half of the
													// screen to use.						
		for(c = 1; c <= width ;c++){ 	
								
								
					if (xpos+c > 64){
					cSelect(xpos+c);				
					}
					
					DataMode();
					dPort = 0b11111111; 
					LocknLoad();							
		}

	}
	
	
	
		cmd = SET_ADDRESS | xpos;		
		WriteCommand(cmd);
				
	
		if (pbytes ==1){					// The are bits filled from the MSB side first
 		dP = 0b10000000;					// because the bar is drawn from the
		}									// lower end of the LCD to top.

		if (pbytes ==2){
 		dP = 0b11000000;
		}

		if (pbytes ==3){
 		dP = 0b11100000;
		}

		if (pbytes ==4){
 		dP = 0b11110000;
		}

		if (pbytes ==5){
 		dP = 0b11111000;
		}

		if (pbytes ==6){
 		dP = 0b11111100;
		}

		if (pbytes ==7){
 		dP = 0b11111110;
		}

		if (pbytes ==8){
 		dP = 0b11111111;
		}

		cSelect(xpos);									// Select which half of the screen to use.
		for(c = 1; c <= width ;c++){ 
							
					if (xpos+c > 64){
					cSelect(xpos+c);		
					}
					


					DataMode();
					dPort = dP; 
					LocknLoad();
		}

		
	
}




/* to clear the bar*/



void BarC(uint8_t height, uint8_t width, uint8_t xpos, uint8_t row) {
	

	uint8_t c;
	uint8_t j;
	uint8_t fbytes=0;
	uint8_t pbytes=0;	
	uint8_t cmd; 
	
	page = row; 
	
	if(height > 64){
	height=64;
	}
	
	if(width > 128){
	width=128;
	}

	
	while(height > 8) {	
		height = height - 8;		
		fbytes = fbytes + 1;		
	}		
	pbytes = height;
	
	if (height > 0){
	 fbytes = fbytes + 1;
	}
	
	for(j = 1; j <= fbytes; j++){
	
				cmd = SET_PAGE | page;
				WriteCommand(cmd);	
				page = page - 1;
				
				
													// Set the x position of the bar.
				cmd = SET_ADDRESS | xpos;		
				WriteCommand(cmd);
				
		cSelect(xpos);								
		for(c = 1; c <= width ;c++){ 				// Width of the bar.
							
					if (xpos+c > 64){
					cSelect(xpos+c);				
					}
					
					DataMode();					
					dPort = 0b00000000; 
					LocknLoad();							
		}

	}
	
	
		
	
}




/* ---------------------------------------------------------------
	Initialise the LCD according to the Data sheet. I prefer to 
	go through a reset procedures.
	
	Function clearl() will clear all the 128x64 dots, and reset the
	column and page address to 0. In noisy environments, this 
	function provides a further insurance of starting with a clean 
	screen.
 -----------------------------------------------------------------*/
void lcdInit (void)
{  
	// Set the data and control ports for output mode
	// and reset them to 0.	
	cPort_ddr = 0xff; 
	cPort = 0x00; 

	dPort_ddr = 0xff;
	dPort = 0x00;  

	// Reset the LCD using reset pin 17.
	cPort |= (1<<lcdrst); 
  
	 
	WriteCommand(DISP_OFF);	  // According to the data sheet this is needed.
	WriteCommand(START_LINE);	
	WriteCommand(DISP_ON);  
  
	// Clear every pixel and reset the column and page to 0.
	clearl(); 
}





/* ---------------------------------------------------------------
	This function is to clear the LCD screen, and also resets the 
	column and page registers.
	
	Use this function when the whole screen needs clearing to 
	display another text / graphic.
 -----------------------------------------------------------------*/
void clearl (void){
 
 unsigned int i;
 
 // Reset global variables.
 column = 0;
 page = 0;
 
 // Reset LCD registers.  
 WriteCommand(SET_ADDRESS);
 WriteCommand(SET_PAGE);
 
 
 for(i = 0; i < 1024 ;i++)
 {
  
  if (column == 128)
  {
   column = 0;
   page++;
   setNewPage(page);
  }

  cSelect(column);						
										
	DataMode(); 						
	dPort = 0b00000000; 				// This clears the pixels.
	LocknLoad();						

  column++;
 }
 
 // Reset global variables.
 column = 0;
 page = 0;
 
 // Reset LCD registers.
 WriteCommand(SET_ADDRESS);
 WriteCommand(SET_PAGE);
 
}







 
 /* ---------------------------------------------------------------
	set LCD to data mode. The data sent to the data bus will now
	be plotted.
 -----------------------------------------------------------------*/
void DataMode (void)
{   
  // Set hardware pins for data mode
  cPort |= (1<<lcdrs);
  cPort &= ~(1<<lcdrw); 
}








/* ---------------------------------------------------------------
	To send commands to the LCD controllers through the data port.
	
	Use this BEFORE using the cSelect() function.
 -----------------------------------------------------------------*/
void WriteCommand(uint8_t cmd) {

		cPort |= (1<<lcdcs1);   // Enable CS1 & CS2.
        cPort |= (1<<lcdcs2);   
        		
        cPort &= ~(1<<lcdrw);   // Clear RW & RS for Command Mode.   
		cPort &= ~(1<<lcdrs);   
		
    dPort = cmd;   				// Send the command.
    LocknLoad();
}






/* ---------------------------------------------------------------
	This selects the controller chip CS1 or CS2 based on the 
	column number.
 -----------------------------------------------------------------*/
void cSelect(uint8_t col)
{

if (col <= 63){
	cPort |= (1<<lcdcs1);   // Enable CS1.
	cPort &= ~(1<<lcdcs2);  // Disable CS2.
	}
	
	if (col >= 64){
	cPort |= (1<<lcdcs2);   // Enable CS2.
	cPort &= ~(1<<lcdcs1);  // Disable CS1.
	}

}






/* ---------------------------------------------------------------
	This will set the required page 0-7, and reset the column to 
	column 0.
 -----------------------------------------------------------------*/
void setNewPage (unsigned char PageData)
{		
		PageData = PageData + SET_PAGE;
        WriteCommand(PageData);	
		
		WriteCommand(SET_ADDRESS); 		// This line resets the column address to the
}								   		// first column again.





/* ---------------------------------------------------------------
	According to the data sheet the enable pin has to be cleared
	for the data port to be read! Set it to 1 to lock the data
	then clear it to load the data. This lock and load cycle is
	performed in 3us to give a wide margin of safety.
	
	The Enable pin e is set to 1 to output data, and back to 0 to 
	latch data.
				  ____________
        _________|			  |______________    Data DB0-DB7
	             |____________|
				 				 
	             ______________               __ Enable pin e
                |              |             |
        ________|              |_____________|

                |    0.45us    |    0.45us   |
                |                            |
                |<----        1us       ---->|      
 -----------------------------------------------------------------*/
void LocknLoad (void)
{
    cPort |= (1<<lcde);   	// Output - Data Load.
	
   _delay_us(4); 		  	// Small delay.
   
    cPort &= ~(1<<lcde);  	// Latch - Data Lock.

   _delay_us(4);
}



/* ---------------------------------------------------------------
	This function sets the page and column registers of the LCD 
	based on the column and row values given.
	
	Use this prior to printing text on the LCD. This is used when 
	the text is required at a particular point (x,y) on the screen.
	
	The page and column variables are global.
 -----------------------------------------------------------------*/
void setXY(uint8_t x, uint8_t y) {

	uint8_t cmd;
	
	if(x > 127) x = 0;				// Validate the x and y values.
	if(y > 63)  y = 0;								
	
	page = y/8;
	column = x;
	cSelect(column); 				// Select the chip based on the column number.
									// The column variable is global and also used
									// by the ASCII driver function lcd_putch().
	
	
	cmd = SET_ADDRESS | x;	
	WriteCommand(cmd);
	
	cmd = SET_PAGE | page;			// Set the Page (y address) on the selected chip.
	WriteCommand(cmd);

}




















