/*****************************************************************************
Author: Peter J. Vis
First Written: 8 Dec 2004
Last Updated: 12 Dec 2006
Title: Displaying Ancient Sanskrit Symbol OM - Main File

Microcontroller: ATmega32
Crystal: 16Mhz
Platform: Development System

Documentation:
Further information regarding this code is available on my site:
Also check the library file for the Bar graph project. I have
provided a lot of comments on that.
http://petervis.com

PURPOSE:
This is the main file that fires off everything else. You will need the 
accompanying library file and header file.

LIMITATIONS:
No part of this work may be used in commercial
applications without prior written permission. This work cannot be
used by Bloggers, or any kind of on-line publishing.

COPYRIGHT:	
All the material including function names are copyright protected.

CIRCUIT:
My Modular Development System

*******************************************************************************/


// Include files required
#include <avr/io.h>
#include "128x64.c"



int main (void)
{

// Initialise the LCD.
	lcdInit();

// Display the graphic.
	Show(om);

}


