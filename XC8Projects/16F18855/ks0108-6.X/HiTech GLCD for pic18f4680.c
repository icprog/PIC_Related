# include <xc.h>															// For HI-TECH C18 Compiler.
#include "HiTech GLCD for pic18f4680.h"
#include "system.h"

void main(void)
{
unsigned int i;
char Buffer[25];		// Buffer which contains the characters or string.
	
TRISB=0x00;	// Port B like output,
TRISC=0x00;	// Port D like output.
	
	for(i=0;i<=23;i++)		// Let us populate buffer with some characters (I think 24 of them :-) )... P.S. I change this number 
		Buffer[i]=i+32;			// ... starting from ASCII character "!" and following with "#$%... etc.
			Buffer[++i]=0x00;		// At the last place of buffer we put the terminator NULL (0x00) for the function that actually writes the text knows where is the end of text.
	
Reset_GLCD();					// Resetting the GLCD (initialising it)...
Display_ON();					// ... turn it ON...
Clear_Display();				// ... clear it...
	Text_GLCD(0,0,"HiTech GLCD for p18f4680");		// ... and write some text...
	Text_GLCD(1,5,"This is the first line.");
	Text_GLCD(2,0,"Text with Text_GLCD().");
	Text_GLCD(3,0,"");
	Text_GLCD(4,0, "Text with Text_Buff():");	// Header line for next line...
	TextBuff_GLCD(5,0,Buffer);									// ... and this line is written from Buffer[30]
	Text_GLCD(7,20, "GOOD LUCK!");
	
	while(1);		// Do nothing
}	