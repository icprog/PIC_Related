unsigned char Matrix[98][8]=	{
															{0x20, 2, 0x00, 0x00},													// Espace
															{0x21, 2, 0x4f, 0x00},													// !
															{0x22, 4, 0x07, 0x00, 0x07, 0x00},							// "
															{0x23, 6, 0x14, 0x7f, 0x14, 0x7f, 0x14, 0x00},	// #
															{0x24, 6, 0x24, 0x2a, 0x7f, 0x2a, 0x12, 0x00},	// $
															{0x25, 6, 0x23, 0x13, 0x08, 0x64, 0x62, 0x00},	// %
															{0x26, 6, 0x36, 0x49, 0x55, 0x22, 0x20, 0x00},	// &
															{0x27, 3, 0x05, 0x03, 0x00},										// '
															{0x28, 4, 0x1c, 0x22, 0x41, 0x00},							// (
															{0x29, 4, 0x41, 0x22, 0x1c, 0x00},							// )10
															{0x2A, 6, 0x14, 0x08, 0x3e, 0x08, 0x14, 0x00},	// * 
															{0x2B, 6, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x00},	// +
															{0x2C, 2, 0xc0, 0x00},													// , 
															{0x2D, 6, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00},	// -
															{0x2E, 2, 0x40, 0x00},													// .
															{0x2F, 6, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00},	// /
															{0x30, 6, 0x3e, 0x51, 0x49, 0x45, 0x3e, 0x00},	// 0
															{0x31, 4, 0x42, 0x7f, 0x40, 0x00}, 							// 1
															{0x32, 6, 0x42, 0x61, 0x51, 0x49, 0x46, 0x00},	// 2
															{0x33, 6, 0x21, 0x41, 0x45, 0x4b, 0x31, 0x00},	// 320
															{0x34, 6, 0x18, 0x14, 0x12, 0x7f, 0x10, 0x00},	// 4 
															{0x35, 6, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00},	// 5
															{0x36, 6, 0x3c, 0x4a, 0x49, 0x49, 0x30, 0x00},	// 6
															{0x37, 6, 0x01, 0x71, 0x09, 0x05, 0x03, 0x00},	// 7
															{0x38, 6, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00},	// 8
															{0x39, 6, 0x06, 0x49, 0x49, 0x29, 0x1e, 0x00},	// 9
															{0x3A, 3, 0x36, 0x36, 0x00},										// :
															{0x3B, 3, 0x56, 0x36, 0x00},										// ;
															{0x3C, 5, 0x08, 0x14, 0x22, 0x41, 0x00}, 			// <
															{0x3D, 6, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00},	// =30
															{0x3E, 5, 0x41, 0x22, 0x14, 0x08, 0x00}, 			// > 
															{0x3F, 6, 0x02, 0x01, 0x51, 0x09, 0x06, 0x00},	// ?
															{0x40, 6, 0x3e, 0x41, 0x5d, 0x55, 0x1e, 0x00},	// @ 0x40
															{0x41, 6, 0x7e, 0x11, 0x11, 0x11, 0x7e, 0x00},	// A
															{0x42, 6, 0x7f, 0x49, 0x49, 0x49, 0x36, 0x00},	// B
															{0x43, 6, 0x3e, 0x41, 0x41, 0x41, 0x22, 0x00},	// C
															{0x44, 6, 0x7f, 0x41, 0x41, 0x41, 0x3e, 0x00},	// D
															{0x45, 6, 0x7f, 0x49, 0x49, 0x49, 0x41, 0x00},	// E
															{0x46, 6, 0x7f, 0x09, 0x09, 0x09, 0x01, 0x00},	// F
															{0x47, 6, 0x3e, 0x41, 0x49, 0x49, 0x7a, 0x00},	// G40
															{0x48, 6, 0x7f, 0x08, 0x08, 0x08, 0x7f, 0x00},  // H 
															{0x49, 4, 0x41, 0x7f, 0x41, 0x00},  						// I
															{0x4A, 6, 0x20, 0x40, 0x41, 0x3f, 0x01, 0x00},	// J
															{0x4B, 6, 0x7f, 0x08, 0x14, 0x22, 0x41, 0x00},	// K
															{0x4C, 6, 0x7f, 0x40, 0x40, 0x40, 0x40, 0x00},	// L
															{0x4D, 6, 0x7f, 0x02, 0x0c, 0x02, 0x7f, 0x00},	// M
															{0x4E, 6, 0x7f, 0x04, 0x08, 0x10, 0x7f, 0x00},	// N
															{0x4F, 6, 0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00},	// O
															{0x50, 6, 0x7f, 0x11, 0x11, 0x11, 0x0E, 0x00},	// P 0x50
															{0x51, 6, 0x3e, 0x41, 0x51, 0x21, 0x5e, 0x00},	// Q50
															{0x52, 6, 0x7f, 0x09, 0x19, 0x29, 0x46, 0x00},	// R 
															{0x53, 6, 0x26, 0x49, 0x49, 0x49, 0x32, 0x00},	// S
															{0x54, 6, 0x01, 0x01, 0x7f, 0x01, 0x01, 0x00},	// T
															{0x55, 6, 0x3f, 0x40, 0x40, 0x40, 0x3f, 0x00},	// U
															{0x56, 6, 0x1f, 0x20, 0x40, 0x20, 0x1f, 0x00},	// V
															{0x57, 6, 0x3f, 0x40, 0x38, 0x40, 0x3f, 0x00},	// W
															{0x58, 6, 0x63, 0x14, 0x08, 0x14, 0x63, 0x00},	// X
															{0X59, 6, 0x07, 0x08, 0x70, 0x08, 0x07, 0x00},	// Y
															{0X5A, 6, 0x61, 0x51, 0x49, 0x45, 0x43, 0x00},	// Z
															{0x5B, 4, 0x7f, 0x41, 0x41, 0x00},  						// [60
															{0x5C, 6, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00},	// \ 
															{0x5D, 4, 0x41, 0x41, 0x7f, 0x00},  						// ]
															{0x5E, 6, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00},	// ^
															{0x5F, 6, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00},	// _
															{0x60, 3, 0x03, 0x05, 0x00},										// ` 0x60
															{0x61, 6, 0x20, 0x54, 0x54, 0x54, 0x78, 0x00},	// a
															{0x62, 6, 0x7F, 0x44, 0x44, 0x44, 0x38, 0x00},	// b
															{0x63, 6, 0x38, 0x44, 0x44, 0x44, 0x44, 0x00},	// c
															{0x64, 6, 0x38, 0x44, 0x44, 0x44, 0x7f, 0x00},	// d
															{0x65, 6, 0x38, 0x54, 0x54, 0x54, 0x18, 0x00},	// e70
															{0x66, 6, 0x04, 0x04, 0x7e, 0x05, 0x05, 0x00},	// f 
															{0x67, 6, 0x08, 0x54, 0x54, 0x54, 0x3c, 0x00},	// g
															{0x68, 6, 0x7f, 0x08, 0x04, 0x04, 0x78, 0x00},	// h
															{0x69, 4, 0x44, 0x7d, 0x40, 0x00},  						// i
															{0x6A, 5, 0x20, 0x40, 0x44, 0x3d, 0x00}, 			// j
															{0x6B, 5, 0x7f, 0x10, 0x28, 0x44, 0x00}, 				// k
															{0x6C, 4, 0x41, 0x7f, 0x40, 0x00},  						// l
															{0x6D, 6, 0x7c, 0x04, 0x7c, 0x04, 0x78, 0x00},	// m
															{0x6E, 6, 0x7c, 0x08, 0x04, 0x04, 0x78, 0x00},	// n
															{0x6F, 6, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00},	// o80
															{0x70, 6, 0x7c, 0x14, 0x14, 0x14, 0x08, 0x00},	// p 0x70 
															{0x71, 6, 0x08, 0x14, 0x14, 0x14, 0x7c, 0x00},	// q
															{0x72, 5, 0x7c, 0x08, 0x04, 0x04, 0x00}, 			// r
															{0x73, 6, 0x48, 0x54, 0x54, 0x54, 0x24, 0x00},	// s
															{0x74, 6, 0x04, 0x04, 0x3f, 0x44, 0x44, 0x00},	// t
															{0x75, 6, 0x3c, 0x40, 0x40, 0x20, 0x7c, 0x00},	// u
															{0x76, 6, 0x1c, 0x20, 0x40, 0x20, 0x1c, 0x00},	// v
															{0x77, 6, 0x3c, 0x40, 0x30, 0x40, 0x3c, 0x00},	// w
															{0x78, 6, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00},	// x
															{0x79, 6, 0x0c, 0x50, 0x50, 0x50, 0x3c, 0x00},	// y90
															{0x7A, 6, 0x44, 0x64, 0x54, 0x4c, 0x44, 0x00},	// z 
															{0x7B, 5, 0x08, 0x36, 0x41, 0x41, 0x00}, 			// {
															{0x7C, 2, 0x77, 0x00},													// |
															{0x7D, 5, 0x41, 0x41, 0x36, 0x08, 0x00}, 			// }
															{0x7E, 6, 0x08, 0x08, 0x2a, 0x1c, 0x08, 0x00},	// <-
															{0x7F, 6, 0x08, 0x1c, 0x2a, 0x08, 0x08, 0x00},	// ->
															{0x80, 6, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00},			//  0x80 - might be used like curor
															{0xe6, 6, 0x1c, 0x22, 0x62, 0xa2, 0x22, 0x00}
															};


// Some declarations of functions
#include <xc.h>
#include "system.h"

#define CS1         LATBbits.LATB0
#define CS2         LATBbits.LATB1
#define DI          LATBbits.LATB2
#define RW          LATBbits.LATB3
#define E           LATBbits.LATB4
#define RS          LATBbits.LATB5


extern void Reset_GLCD(void);
extern void Enable(void);
extern void Active_Left(void);
extern void Active_Right(void);
extern void Starting_Address(unsigned int S);
extern unsigned int Y_Address(unsigned int Y);
extern unsigned int X_Address(unsigned int X);
extern void Display_ON(void);
extern void Display_OFF(void);
extern void Clear_Display(void);
extern void Write_Byte(unsigned char B);
extern void Text_GLCD(unsigned int Row, unsigned int Column, const char *String);
extern void TextBuff_GLCD(unsigned int Row, unsigned int Column, unsigned char Buff_String[]);


//	Temporary buffer for GLCD row.

unsigned char Buffer[128];


/*

Function: void Text_GLCD(unsigned char Row,  unsigned char Column,  unsigned char *String)

		Link for the explanation of how GLCD with KS0108 works: http://www.geocities.com/dinceraydin/lcd/gfxintro.htm.

		Idea is to fill the buffer 128 bytes long with the bit-maps of characters. The buffer represents one row for both controllers: 0-63 bytes for the left one and 64-127 bytes for the right.
		When buffer is completed transfer all 128 bytes to controllers: first in the left and than in the right.
		The way to transfer bytes is: first enable left controller and disable right, fill the first 64 bytes from buffer, disable left and enable right controller and fill the rest 64 bytes from buffer.
		If the text starts at some offset from the beginning of row (column that is not the zero-column), than first the buffer will be filled with NULL (0x00), than will be filled with the bit-maps of characters of text and the remaning space (if there is some) will be filled with NULL again. NULL´s are necessary if there is some previous text on the desired row. 
		Why to do this? Because author concluded that this is the fastest way the controller shows the text: prepare the whole row and than fill the controllers.
*/

void Text_GLCD(unsigned int Row, unsigned int Column, const char *String)
{
	unsigned char Char_In_String=0, Char_In_Matrix=0;
	unsigned int k=0, Place_In_Buffer=0, Index=0, Counter=0;

	while(Place_In_Buffer<=Column)			// First, fill NULL's from the beginning of row to the starting column of text. If Column==0 this while-loop will be skipped.
	{
		Buffer[Place_In_Buffer]=0x00;		// The pointer Place_In_Buffer is the pointer for the buffer. It always increments untill it reaches the end of the buffer (127).
		Place_In_Buffer++;					// Increment pointer.
	}

//Searching the text string to find the match of the character.

	while(String[Char_In_String]!=0x00)			// Untill reach the end of the text string 0x00...
	{
		for(Char_In_Matrix=0;Char_In_Matrix<=96;Char_In_Matrix++)	// ... iterate across the matrix Matrix[97][8] incremening the indeks Char_In_Matrix untill we find the match: the character.
		{
			if(String[Char_In_String]==Matrix[Char_In_Matrix][0])		// When we find the character (it`s code is at place Matrix[Char_In_Matrix][0] – column zero)...
			{
				Counter=2;			// ... and initialize the Counter to point to the first byte of the character`s bit-map: Matrix[Char_In_Matrix][Counter]	and that is the column two.
				for(k=1;k<=Matrix[Char_In_Matrix][1];k++)	// From the place that pointer Char_In_Matrix points to Matrix[][] and from the column one from matrix Matrix[][], take the number that represents the WIDTH (IN	BYTES) OF CHARACTER. THIS IS THE UPPER LIMIT FOR THIS FOR-LOOP. THIS NUMBER CAN BE MAXIMUM 5 (FIVE - LOOK AT THE TOP IN THE MATRIX!).		
				{
					Buffer[Place_In_Buffer]=Matrix[Char_In_Matrix][Counter];	// Now we are writting bytes at buffer pointer Place_In_Buffer, one by one into buffer from the index Matrix[Char_In_Matrix][Counter]...
					Counter++;				// ... move to the next byte of character`s bit-map in the matrix...
					Place_In_Buffer++;	// ... and increment buffer pointer to point to next place in buffer untill we fill the desired bytes of the character.
				}
			}
		}
	if(Place_In_Buffer>=127) break;	// But, if the number of bytes overflow the right limit of the GLCD in one row (128) we quit flling the buffer! Go to the next character in string.
	Char_In_String++;										
	}								

	while(Place_In_Buffer<128)			// But, if the number of bytes is less than the right limit of the GLCD and there is no characters in string...
	{
		Buffer[Place_In_Buffer]=0x00;	//... fill the remainig text buffer space with NULL`s up to the right limit (128).
		Place_In_Buffer++;
	}
	
//After we finished with the buffer, we start to write in to the controllers. First, in the left controller.

	DI=0;		// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0xC0;						// Instruction for the starting address: 0b11000000 - it is the top of the display...
		Enable();						//... and, of course, rise ENABLE.
		CS1=1;	// Pin RB3 (CS1) is going on logical 1 to switch ON left controller... 			Pogledaj napomenu na dnu strane!
		CS2=0;	// ... and RB2 (CS2) is going on logical 0 to switch OFF right controller...
			Enable();					// ... and, of course, rise ENABLE for starting address to be written.

	LATC=0xB8;			// Now, we are writting byte of the instruction for the row in which we are going to write: 0b10111000...
	LATC+=Row;		// ... whom we add the starting row from the top of display...
		Enable();			// ... and, of course, rise ENABLE for X-address to be written.

	LATC=0x40;			// After that, we are writting the instruction for the Y-address – the starting column in which we are going to write: 0b01000000 – the column zero...
		Enable();			// ... and, of course, rise ENABLE for Y-address to be written.

	DI=1;		// Now, we are going to write bytes in GLCD, so pin D/I (data/instruction) is going on logical 1: data.

	for(Index=0;Index<=63;Index++)
	{
		LATC=Buffer[Index];		// We are taking one by one byte from buffer Buffer[] from place Buffer[Index] and write it in port D...
		Enable();							// ... and, of course, rise ENABLE for data to be written in GLCD.
// NOTE: everytime the byte is written, controller by himself increments the Y-address by one so we don`t need to increment the Y-address!
	}

//Continuing to write, but now in the right controller.

	DI=0;			// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;			// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0xC0;							// Again, instruction for the starting address: 0b11000000 - it is the top of the display...
		Enable();							//... and, of course, rise ENABLE.
	 		CS1=0;	// Pin RB3 (CS1) is going on logical 0 to switch OFF left controller...
			CS2=1;	// ... and RB2 (CS2) is going on logical 1 to switch ON right controller...
			Enable();						// ... and, of course, rise ENABLE for starting address to be written.

	LATC=0xB8;					// Again, we are writting byte of the instruction for the row in which we are going to write: 0b10111000...
	LATC+=Row;				// ... whom we add the starting row from the top of display...
		Enable();					// ... and, of course, rise ENABLE for X-address to be written.

	LATC=0x40;				// After that, we are writting the instruction for the Y-address – the sarting column in which we are going to 	write: 0b01000000 – the column zero...
		Enable();				// ... and, of course, rise ENABLE for Y-address to be written.

	DI=1;		// Now, we are going to write bytes in GLCD, so pin D/I (data/instruction) is going on logical 1: data.
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting (just in case).

	  for(Index=64;Index<128;Index++)
	  {
		LATC=Buffer[Index];		// Again, we are taking one by one byte from buffer Buffer[] from place Buffer[Index] and write it in port D...
		Enable();							// ... and, of course, rise ENABLE for data to be written in GLCD.
	  }
	  LATB=0b10000000;		// This line is specially for my EasyPIC3 for port B. It prevents the corresponding diodes not to light, but the 	GLCD is still showing the data (remember: bit 8 must be ON during the whole time the GLCD is used).
	  LATC=0;							// Like the line before, for port D to stay OFF.
}
//******************************End of function void Text_GLCD(unsigned char Row,  unsigned char Column,  unsigned char *String)




/*
******************************************************************************
Function: void Enable (void)

		This function manage the ENABLE signal for GLCD ("action" ?). Input on my board (EasyPIC3) is connected to pin RB6 of port B (see the picture in the addenum). The action is achieved in the sequence 0-1-0. Falling edge is taking action.
*/
void Enable(void)
{
    E=1;				// Rise RB6 at logical 1...
	__delay_us(2);			// ... wait some time...
    E=0;			// ... than put down RB6 at logical 0 for the action to be taken.
}


/*
*******************************************************************************
Function: void Reset_GLCD (void)

		This function do two things: initialises GLCD by reseting it by it`s pin RS and switch ON both sides of display.
		On my EasyPIC3 this pins are connected on pins RB2, RB3 and RB7 of port B (see picture in addenum). Reset is achieved by sequence 1-0-1 on pin RB7. Swtching controllers is achieved by using pins RB2 and RB3.
Attention: From this moment (or after reset) pin RB7 MUST ALWAYS stay on logical 1 (one) during the whole time the GLCD is used!
*/

void Reset_GLCD(void)
{
// Part ONE: resetting the display.

LATB=0b10000000;			// Rise RB7 to logical 1 for GLCD to evntually do something...
LATC=0x00;							// ...and then clear port D.
	RS=0;		// Set down RB7 to prepare it for action...
	__delay_us(2);		// ... wait some time...	
	RS=1;		//... and action! GLCD is resetted.
	
// Part TWO: Activating both controllers.

TRISC=0xFF;							// Put port D to be input port.
	RW=1;			// Rise RB5 at logical 1 – this is the instruction for reading the status of GLCD...
	Enable();								// ...and ENABLE GLCD to get the status on port D.
	while(E)	// Checking: untill LATC4 is high there is internall operation in GLCD an it does not receive data.
		CS1=1;		// ... and rise pins CS1 i CS2 to high because we want to activate both controllers...
		CS2=1;
		Enable();							// ... and ENABLE to say it to GLCD.
TRISC=0x00;							// Than, put port D to be out port.
}
//******************* End of function Reset_GLCD()



/*
********************************************************************
Function: void Active_Left(void)

		This function activates the left side of GLCD. Actually, it only activates the left controller and enable it to receive characters.
*/

void Active_Left(void)
{
	DI=0;			// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;			// ... and R/W pin (read/write) at logical 0: writting.
		CS1=1;		// Pin RB3 (CS1) is going on logical 1 to switch ON left controller......
		CS2=0;		// ... and pin RB2 (CS2) is going on logical 0 to switch OFF right controller...
		Enable();							// ... and, of course, rise ENABLE.
}
//******************* End of function Active_Left()



/*
******************************************************************
Function: void Active_Right(void)

		This function activates the right side of GLCD. Actually, it only activates the right controller and enable it to receive characters.
*/
void Active_Right(void)
{
	DI=0;			//Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;			// ... and R/W pin (read/write) at logical 0: writting.
		CS1=0;		// Pin RB3 (CS1) is going on logical 0 to switch OFF left controller......
		CS2=1;		// ... and pin RB2 (CS2) is going on logical 1 to switch ON right controller...
		Enable();							// ... and, of course, rise ENABLE.
}
//******************* End of function Aktive_Right()



/*
******************************************************************
Function: void Starting_Address(unsigned int S)

		This function is mostly like SHIFT function. Works in that way that the given line of GLCD controller (not the given row) is shifted to the line zero or to the top of display. Or, much closer: if we want for ex. line 35 to move to the top of display we put the parameter S to be 35. Then, the line will "slide" to top of display. The lines that are dissapeared above this line are not lost: they will appear at the bottom of display.

		Note: This function will perform only on active controller! So, if we want the hole line to be moved we must activate the both controllers.
*/
void Starting_Address(unsigned int S)
{
	DI=0;		// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0xC0;						// Instruction for the starting address: 0b11000000 - it is the top of the display...
		LATC+=S;						// ... and add the offset from the top of display...
		Enable();						// ... and, of course, rise ENABLE for starting address to be written.
}
//********************End of function void Starting_Address(usigned char S)



/*
**********************************************************************
Function: unsigned int Y_Address(unsigned int Y)

		This function puts the character at the column from the left edge of display (the horizontal address).
*/

unsigned int Y_Address(unsigned int Y)
{
	DI=0;		// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0x40;						// Instruction for the Y-address: 0b0100000- it is the left edge of the controller...
		LATC+=Y;						// ... and add the offset from the left edge of controller...
		Enable();						// ... and, of course, rise ENABLE for Y-address to be written.
	return Y;							// return Y if someone needs it.
}
//********************End of function unsigned char Y_Address(usigned char Y)



/*
*****************************************************************************
Function: unsigned int X_Address(unsigned int X)

		This function puts the character at the row from the top edge of display (the vertical address).
*/

unsigned int X_Address(unsigned int X)
{
	DI=0;		// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0xB8;						// Instruction for the X-address: 0b10111000- it is the left edge of the controller...
		LATC+=X;						// ... and add the offset from the left edge of controller...
		Enable();						// ... and, of course, rise ENABLE for Y-address to be written.
	return X;							// return X if someone needs it.
}
//********************End of function unsigned char X_Address(usigned char X)



/*
******************************************************************
Function: void Display_ON(void)

		Obviosly, this function only swtches the GLCD ON.
*/

void Display_ON(void)
{
	DI=0;		// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0x3F;						// Instruction for the display to turn on: 0b00111111...
		Enable();						// ... and, of course, rise ENABLE to turn display ON.
}
//********************End of function void Display_ON(void)



/*
***************************************************
Function: void Display_OFF(void)

		Obviosly, this function only swtches the GLCD OFF.
*/

void Display_OFF(void)
{
	DI=0;		// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0x3E;						// Instruction for the display to turn off: 0b00111110...
		Enable();						// ... and, of course, rise ENABLE to turn display OFF.
}
//********************End of function void Display_OFF(void)



/*
****************************************************
Function: void Write_Byte(unsigned char B)

		I think that function is self explanatory...
*/

void Write_Byte(unsigned char B)
{
	DI=1;		// Put pin D/I (data/instruction) at logical 1: data...
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting.
	LATC=B	;							// Put byte (data) on port B to be written to GLCD...
		Enable();						// ... and, of course, rise ENABLE to write byte in GLCD.
}
//********************End of function void Write_Byte(unsigned char B)



/*
****************************************
Function void Clear_Display(void)

		Function clears the GLCD by writting the NULL`s to both sides of display (to both controllers) from top to down (outer for-loop) and from top to the left (the inner for-loop).
*/

void Clear_Display(void)
{
	unsigned char i, j;				// First, we defined a pair of variables for for-loops for incremnts of Y and X addresses.
		CS1=1;			// Pin RB3 (CS1) is going on logical 1 to switch ON left controller......
		CS2=1;			// ... and pin RB2 (CS2) is going on logical 1 to switch ON right controller...
			Enable();							// ... and, of course, rise ENABLE to switch them.
			Starting_Address(0);		// ... and starting address is 0,0.
			for(i=0;i<=7;i++)			// Strat from row zero and go to row 7 of both controllers (outer for-loop)...
			{
				X_Address(i);				// ...and "say" it to GLCD.
				for(j=0;j<=63;j++)		// Start the writting from the left-most column (column zero) to 63. column of both controllers (inner for-loop).
				{
				Write_Byte(0x00);		// Write NULL.
				}
			}
	
}
//*********************** End of function void Clear_Display(void)



/*

Function: void Text_GLCD(unsigned char Row,  unsigned char Column,  unsigned char Buff_String[])

		This function is almost identical with Text_GLCD(). Only difference is that this function writes the text from previous populated buffer Buff_String[] defined in RAM during the run time.

*/

void TextBuff_GLCD(unsigned int Row,  unsigned int Column, char Buff_String[])
{
	unsigned char Char_In_String=0, Char_In_Matrix=0;
	unsigned int k=0, Place_In_Buffer=0, Index=0, Counter=0;

	while(Place_In_Buffer<=Column)			// First, fill NULL's from the beginning of row to the starting column of text. If Column== 0 this while-loop will be skipped.
	{
		Buffer[Place_In_Buffer]=0x00;		// The pointer Place_In_Buffer is the pointer for the buffer. It always increments untill it reaches the end of the buffer (127).
		Place_In_Buffer++;					// Increment pointer.
	}

//Searching the text string to find the match of the character.

	while(Buff_String[Char_In_String]!=0x00)			// Untill reach the end of the text string 0x00...
	{
		for(Char_In_Matrix=0;Char_In_Matrix<=96;Char_In_Matrix++)	// ... iterate across the matrix Matrix[97][8] incremening the indeks Char_In_Matrix untill we find the match: the character.
		{
			if(Buff_String[Char_In_String]==Matrix[Char_In_Matrix][0])		// When we find the character (it`s code is at place  Matrix[Char_In_Matrix][0] – column zero)...
			{
				Counter=2;	// ... and initialize the Counter to point to the first byte of the character`s bit-map: Matrix[Char_In_Matrix][Counter]	and that is the column two.
				for(k=1;k<=Matrix[Char_In_Matrix][1];k++)	// From the place that pointer Char_In_Matrix points to Matrix[][] and from the column one from matrix Matrix[][], take the number that represents the WIDTH (IN	BYTES) OF CHARACTER. THIS IS THE UPPER LIMIT FOR THIS FOR-LOOP. THIS NUMBER CAN BE MAXIMUM 5 (FIVE - LOOK AT THE TOP IN THE MATRIX!).		
				{
					Buffer[Place_In_Buffer]=Matrix[Char_In_Matrix][Counter];	// Now we are writting bytes at buffer pointer Place_In_Buffer, one by	one into buffer from the index Matrix[Char_In_Matrix][Counter]...
					Counter++;				// ... move to the next byte of character`s bit-map in the matrix...
					Place_In_Buffer++;	// ... and increment buffer pointer to point to next place in buffer untill we fill the desired bytes of the character.
				}
			}
		}
	if(Place_In_Buffer>=127) break;	// But, if the number of bytes overflow the right limit of the GLCD in one row (128) we quit flling the buffer! Go to the next character in string.
	Char_In_String++;										
	}								

	while(Place_In_Buffer<128)			// But, if the number of bytes is less than the right limit of the GLCD and there is no characters in string...
	{
		Buffer[Place_In_Buffer]=0x00;	//... fill the remainig text buffer space with NULL`s up to the right limit (128).
		Place_In_Buffer++;
	}
	
//After we finished with the buffer, we start to write in to the controllers. First, in the left controller.

	DI=0;		// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0xC0;						// Instruction for the starting address: 0b11000000 - it is the top of the display...
		Enable();						//... and, of course, rise ENABLE.
		CS1=1;	// Pin RB3 (CS1) is going on logical 1 to switch ON left controller... 			Pogledaj napomenu na dnu strane!
		CS2=0;	// ... and RB2 (CS2) is going on logical 0 to switch OFF right controller...
			Enable();					// ... and, of course, rise ENABLE for starting address to be written.

	LATC=0xB8;						// Now, we are writting byte of the instruction for the row in which we are going to write: 0b10111000...
	LATC+=Row;					// ... whom we add the starting row from the top of display...
		Enable();						// ... and, of course, rise ENABLE for X-address to be written.

	LATC=0x40;				// After that, we are writting the instruction for the Y-address – the starting column in which we are going to write: 0b01000000 – the column zero...
		Enable();				// ... and, of course, rise ENABLE for Y-address to be written.

	DI=1;	// Now, we are going to write bytes in GLCD, so pin D/I (data/instruction) is going on logical 1: data.

	for(Index=0;Index<=63;Index++)
	{
		LATC=Buffer[Index];		// We are taking one by one byte from buffer Buffer[] from place Buffer[Index] and write it in port D...
		Enable();							// ... and, of course, rise ENABLE for data to be written in GLCD.
// NOTE: everytime the byte is written, controller by himself increments the Y-address by one so we don`t need to increment the Y-address!
	}

//Continuing to write, but now in the right controller.

	DI=0;			// Put pin D/I (data/instruction) at logical 0: instruction...
	RW=0;			// ... and R/W pin (read/write) at logical 0: writting.
	LATC=0xC0;							// Again, instruction for the starting address: 0b11000000 - it is the top of the display...
		Enable();							//... and, of course, rise ENABLE.
	 		CS1=0;	// Pin RB3 (CS1) is going on logical 0 to switch OFF left controller...
			CS2=1;	// ... and RB2 (CS2) is going on logical 1 to switch ON right controller...
			Enable();						// ... and, of course, rise ENABLE for starting address to be written.

	LATC=0xB8;					// Again, we are writting byte of the instruction for the row in which we are going to write: 0b10111000...
	LATC+=Row;				// ... whom we add the starting row from the top of display...
		Enable();					// ... and, of course, rise ENABLE for X-address to be written.

	LATC=0x40;					// After that, we are writting the instruction for the Y-address – the sarting column in which we are going to	write: 0b01000000 – the column zero...
		Enable();					// ... and, of course, rise ENABLE for Y-address to be written.

	DI=1;		// Now, we are going to write bytes in GLCD, so pin D/I (data/instruction) is going on logical 1: data.
	RW=0;		// ... and R/W pin (read/write) at logical 0: writting (just in case).

	  for(Index=64;Index<128;Index++)
	  {
		LATC=Buffer[Index];		// Again, we are taking one by one byte from buffer Buffer[] from place Buffer[Index] and write it in port D...
		Enable();							// ... and, of course, rise ENABLE for data to be written in GLCD.
	  }
	  LATB=0b10000000;			// This line is specially for my EasyPIC3 for port B. It prevents the corresponding diodes not to light, but the GLCD is still showing the data (remember: bit 8 must be ON during the whole time the GLCD is used).
	  LATC=0;						// Like the line before, for port D to stay OFF.
}
//******************************End of function void TextBuff_GLCD(unsigned char Row,  unsigned char Column,  unsigned char Buff_String)
