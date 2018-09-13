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

// The include files required for this project.
#include <avr/io.h>
#include <avr/interrupt.h>
#include "128x64.c"
#include <util/delay.h>  



int main (void)
{

	lcdInit();

_delay_ms(500);	
Bar(5,5,0,7);
_delay_ms(500);
Bar(10,5,10,7);
_delay_ms(500);
Bar(15,5,20,7);
_delay_ms(500);
Bar(20,5,30,7);
_delay_ms(500);
Bar(25,5,40,7);
_delay_ms(500);
Bar(30,5,50,7);
_delay_ms(500);
Bar(35,5,59,7);
_delay_ms(500);
Bar(40,5,70,7);
_delay_ms(500);
Bar(45,5,80,7);
_delay_ms(500);
Bar(50,5,90,7);
_delay_ms(500);
Bar(55,5,100,7);
_delay_ms(500);
Bar(60,5,110,7);
_delay_ms(500);
Bar(64,5,120,7);


_delay_ms(1000);
BarC(64,5,120,7);
_delay_ms(500);
BarC(60,5,110,7);
_delay_ms(500);
BarC(55,5,100,7);
_delay_ms(500);
BarC(50,5,90,7);
_delay_ms(500);
BarC(45,5,80,7);
_delay_ms(500);
BarC(40,5,70,7);
_delay_ms(500);
BarC(35,5,59,7);
_delay_ms(500);
BarC(30,5,50,7);
_delay_ms(500);
BarC(25,5,40,7);
_delay_ms(500);
BarC(20,5,30,7);
_delay_ms(500);
BarC(15,5,20,7);
_delay_ms(500);
BarC(10,5,10,7);
_delay_ms(500);
BarC(5,5,0,7);



}


