//#ifndef 5110LCD_H

//#define	5110LCD_H

#include <xc.h>
#include <stdint.h>

void gotoXY(int8_t x, int8_t y);

//This takes a large array of bits and sends them to the LCD
void LCDBitmap(char my_array[]);

//This function takes in a character, looks it up in the font table/array
//And writes it to the screen
//Each character is 8 bits tall and 5 bits wide. We pad one blank column of
//pixels on each side of the character for readability.
void LCDCharacter(char character);


//Given a string of characters, one by one is passed to the LCD
void LCDString(char *characters);


//Clears the LCD by writing zeros to the entire screen
void LCDClear(void);

//This sends the magical commands to the PCD8544
void LCDInit(void);

//There are two memory banks in the LCD, data/RAM and commands. This
//function sets the DC pin high or low depending, and then sends
//the data byte
void LCDWrite(unsigned char data_or_command, unsigned char data);


//#endif