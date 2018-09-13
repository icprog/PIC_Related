/*
***********************************************************************************************
*                       Use a T6963C 128x64 monochrome LCD for display.
*                 Fully working prototype based on this software and t6963.c driver
*
* File name     : glcdex1.c
*                 IDE: Microchip's MPLAB v7.01
*                 Project name: T6963CCS.mcp
*                 CCS C complier PCM version 3.170
* Programmer    : John Leung at www.TechToys.com.hk
* Note          : In reference to picant complier web page, & epe magazine for reference 
*                 & treitmey on CCS forum
* Date          : Version 0.0 (20 April 2005 - 27 April 2005)
***********************************************************************************************
*                                       DESCRIPTION
*
* This module provides an interface to Toshiba T6963C Graphical LCD of matrix size 128x64 dots
* Schematics: 
*
***********************************************************************************************
*/

//#include <16F877a.h>
//#fuses HS,NOWDT,NOPROTECT,NOLVP
//#use delay(clock=20000000)
//#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#include "../lib/include/pic24_all.h"

#include "t6963.h"
#include "Dog.h"
#include "icons.h"
volatile UCHAR xeeprom[1000];
UCHAR FontSize;
UCHAR CGBuffer[8];

/*
******************************************************************************************
*                                       PROTOTYPES
******************************************************************************************
*/
#if 0
void GDispDefIcon32X32(UCHAR icon_id);
void GDispIcon32X32At(unsigned int row, unsigned int col, unsigned int8 icon_id); 
void GDispSelIcon32X32At(unsigned int16 row, unsigned int16 col, unsigned int8 mode);
void GDispDefCGPat(void);
void GDispCGPat(unsigned int16 row, unsigned int16 col);
#endif
void GDispDefIcon32X32(UCHAR icon_id);
void GDispIcon32X32At(uint16_t row, uint16_t col, UCHAR icon_id); 
void GDispSelIcon32X32At(uint16_t row, uint16_t col, UCHAR mode);
void GDispDefCGPat(void);
void GDispCGPat(uint16_t row, uint16_t col);
void sim_eeprom(void);
void ClearScr(void);

/*
******************************************************************************************
*/

void main()
{
    UCHAR ch = 0x21;
    configClock();
    configHeartbeat();
    configDefaultUART(DEFAULT_BAUDRATE);
    char str[] = "Hey";
    outString("\nstarting...\n");
    GDispInit();                        //T6963C display initialization
    outString("past init...\n");
    FontSize = 8;                       //8 font mode
    GDispSetMode(XOR_MODE|INT_CG_MODE); //Exclusive OR mode, internal CG character RAM
    GDispSetMode(TEXT_GRH_ON);          //Text ON, Graphics ON
    GDispClrTxt();                      //Clear the text area
    GDispClrGrh();                      //Clear the graphics area (dot-by-dot!)
    outString("in loop...\n");
    for (;;)
    {
        outChar(ch);
        if(++ch > 0x7e)
          ch = 0x21;
        GDispDefCGPat();    //read data from eeprom, write to LCD's CG RAM for for DOG picture
        GDispCGPat(0, 2);   //display the Dog picture from LCD's CG RAM

        GDispPixFontAt(85, 20, &str[0], 2, BLACK);  //display a 10x14 font for string "Hey" in pixel    

        DELAY_MS(2000);     //no need to explain!

        GDispClrTxt();      //clear the text area (in this case, clear the dog)
        GDispClrGrh();      //clear the graphic area (in this case, clear the string "Hey")

        GDispDefIcon32X32(0);       //read icon pattern from eeprom, write to LCD's CG RAM, id=0
        GDispDefIcon32X32(1);       //same as above, id=1
        GDispDefIcon32X32(2);       //same asa above, id=2
        GDispIcon32X32At(2,1,0);    //display the icon data stored under CG RAM with id=0
        GDispIcon32X32At(2,6,1);    //id=1
        GDispIcon32X32At(2,11,2);   //id=2
        GDispSelIcon32X32At(2, 1, ATTR_BLINK_REVERSE);  //blink the icon at row,col = 2,1
        DELAY_MS(2000);

        GDispSelIcon32X32At(2,1,ATTR_NORMAL);       //bring back to normal mode
        GDispSetMode(XOR_MODE|INT_CG_MODE);         //some sort of bug here! Try commenting this
                                                    //to see what happen with the string "Hey".
        GDispClrTxt();
    }
    
}//end of main()
/*
*********************************************************************************************************
*/
void sim_eeprom(void)
{
    int i;

    for(i=0; i<128; i++)
        write_ext_eeprom(i, cygwin_icon[i]);        //byte 0-127
    
    for(i=0; i<128; i++)
        write_ext_eeprom(i+128, flash_icon[i]);     //byte 128-255

    for(i=0; i<128; i++)
        write_ext_eeprom(i+256, outlook_icon[i]);   //byte 256-383

    for(i=0; i<72; i++) write_ext_eeprom(i+384, Dog_row1[i]);   //offset = 384, byte 0-71
    for(i=0; i<72; i++) write_ext_eeprom(i+456, Dog_row2[i]);   
    for(i=0; i<72; i++) write_ext_eeprom(i+528, Dog_row3[i]);
    for(i=0; i<72; i++) write_ext_eeprom(i+600, Dog_row4[i]);
    for(i=0; i<72; i++) write_ext_eeprom(i+672, Dog_row5[i]);
    for(i=0; i<72; i++) write_ext_eeprom(i+744, Dog_row6[i]);
    for(i=0; i<72; i++) write_ext_eeprom(i+816, Dog_row7[i]);
    for(i=0; i<72; i++) write_ext_eeprom(i+888, Dog_row8[i]);
}
/*
*********************************************************************************************************
*/
void write_ext_eeprom(int loc, UCHAR put)
{
    xeeprom[loc] = put;
}

/*

*********************************************************************************************************
*/
UCHAR read_ext_eeprom(int location)
{
    return xeeprom[location];
}

/*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                           SET CUSTOM DEFINED ICON OF 32x32 MATRIX FROM EEPROM DATA
*
* Description : This function assigns LCD's CG RAM with a custom icon pattern of 32x32 matrix with
*               an id number from I2C EEPROM data
* Arguments   : 'icon_id'   is the identifier for the icon created.
*               Range of 'icon_id' is 0 to 8 for T6963 in 8 Font mode.
* Returns     : none
* Notes       : icon stored in 24LC256 / 512 eeprom, the first byte from top left, across to down right
*********************************************************************************************************
*/
void GDispDefIcon32X32(UCHAR icon_id)
{
    uint16_t i, col, row;

    for(row=0; row<4; row++)
    {
        for(col=0; col<4; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(32*row + i*4 + col + (uint16_t)icon_id*128);
            }
            GDispDefCGChar(col+4*row+icon_id*16,&CGBuffer[0]);
        }
    }
}


/*
*********************************************************************************************************
*                             DISPLAY AN ICON OF 32x32 MATRIX AT ROW, COL FROM CG RAM
*
* Description : This function shows a pre-defined 32x32 ICON in CG RAM at (row, col) coordinates
* Arguments   : 'icon_id'   is the identifier for the pattern created. Range of 'id' is 0...8 in 8 font
*               'row'   row = 0...(MAX_ROW_PIXEL/8 - 1), the cell number in 8 bits height
*               'col'   col = 0...(COLUMN-1), is the column position in font width (6/8 font)  
* Returns     : none
* Notes       : 
*********************************************************************************************************
*/
void GDispIcon32X32At(uint16_t row, uint16_t col, UCHAR icon_id)
{
    UCHAR id=0;
    uint16_t row_cnt, col_cnt;

    id = id + icon_id*16;

    GDispGoto(row, col);
    for(row_cnt = row; row_cnt < (row+4); row_cnt++)
    {
        for(col_cnt = col; col_cnt < (col+4); col_cnt++)
        {
            GDispCGCharAt(row_cnt, col_cnt, id++);
        }
    }
}

/*
*********************************************************************************************************
*                               HIGHLIGHT AN ICON OF 32x32 MATRIX AT ROW, COL
*
* Description : This function highlight an icon at a position row, col.
* Arguments   : 'mode'  =   ATTR_REVERSE, ATTR_INHIBIT, ATTR_BLINK_REVERSE, ATTR_BLINK_INHIBIT,
*                           ATTR_NORMAL,  ATTR_BLINK (all modes defined under t6963.h file)
*               'row'   row = 0...(MAX_ROW_PIXEL/8 - 1), the cell number in 8 bits height
*               'col'   col = 0...(COLUMN-1), is the column position in font width (6/8 font)       
* Returns     : none
* Notes       : 
*********************************************************************************************************
*/
void GDispSelIcon32X32At(uint16_t row, uint16_t col, UCHAR mode)
{
    uint16_t row_cnt, col_cnt;

    for(row_cnt = row; row_cnt < (row+4); row_cnt++)
    {
        for(col_cnt = col; col_cnt < (col+4); col_cnt++)
        {
            GDispSetAttrb(row_cnt, col_cnt, mode);
        }
    }
}

/*
*********************************************************************************************************
*                           SET CUSTOM DEFINED CG RAM CHARACTERS OF SIZE X*Y MATRIX
*
* Description : This function assigns a custom pattern of X*Y matrix. In this case for Dog_rowx[]
*               x = 1 to 8, 9x8 CG RAM characters required
* Arguments   : none
* Returns     : none
* Notes       : 
*********************************************************************************************************
*/
void GDispDefCGPat(void)
{
    uint16_t i,  col;

        for(col=0; col<9; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(i+384+col*8);
            }
            GDispDefCGChar(col,&CGBuffer[0]);
        }

        for(col=0; col<9; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(i+456+col*8);
            }
            GDispDefCGChar(col+9,&CGBuffer[0]);
        }       

        for(col=0; col<9; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(i+528+col*8);
            }
            GDispDefCGChar(col+18,&CGBuffer[0]);
        }

        for(col=0; col<9; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(i+600+col*8);
            }
            GDispDefCGChar(col+27,&CGBuffer[0]);
        }

        for(col=0; col<9; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(i+672+col*8);
            }
            GDispDefCGChar(col+36,&CGBuffer[0]);
        }

        for(col=0; col<9; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(i+744+col*8);
            }
            GDispDefCGChar(col+45,&CGBuffer[0]);
        }

        for(col=0; col<9; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(i+816+col*8);
            }
            GDispDefCGChar(col+54,&CGBuffer[0]);
        }

        for(col=0; col<9; col++)
        {
            for(i=0;i<8;i++)
            {
                CGBuffer[i] = read_ext_eeprom(i+888+col*8);
            }
            GDispDefCGChar(col+63,&CGBuffer[0]);
        }

}

/*
*********************************************************************************************************
*                         DISPLAY CUSTOM DEFINED CG RAM CHARACTERS OF SIZE X*Y MATRIX
*
* Description : This function displays a custom defined pattern of X*Y matrix from CG RAM. 
*               In this case for Dog_rowx[] data that has been stored by previous project
*               x = 1 to 8, 9x8 CG RAM characters required
* Arguments   : none
* Returns     : none
* Notes       : 
*********************************************************************************************************
*/
void GDispCGPat(uint16_t row, uint16_t col)
{
    uint16_t id=0, row_cnt, col_cnt;

    GDispGoto(row, col);
    for(row_cnt = row; row_cnt < (row+8); row_cnt++)
    {
        for(col_cnt = col; col_cnt < (col+9); col_cnt++)
        {
            GDispCGCharAt(row_cnt, col_cnt, id++);
        }
    }
    
}
