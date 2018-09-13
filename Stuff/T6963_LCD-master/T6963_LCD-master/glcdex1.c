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

#include "../lib/include/pic24_all.h"
#include "t6963.h"
UCHAR FontSize;

/********************************************************************************************/

int main()
{
    int i,j,x,y,a,b;
    UCHAR k;
    configClock();
    configHeartbeat();
    configDefaultUART(DEFAULT_BAUDRATE);
    outString("\nstarting...\n");

    GDispInit();                        //T6963C display initialization
    outString("past init...\n");

    FontSize = 8;                       //8 font mode
    GDispSetMode(XOR_MODE);
    GDispSetMode(TEXT_ON);
    GDispClrTxt();
    k = 0x20;
    DisplayDisclaimer();
    DELAY_MS(8000);

    for(a = 0;a < 10;a++)
    {
    outChar(0x30 + a);
    outChar(0x20);
    k = 0x20;
    DELAY_MS(20);
    for(i = 0;i < 20;i++)
    {
       for(j = 0;j < 40;j++)
       {
          GDispCharAt(i,j,k);
          if(++k > 0x7e)
             k = 0x20;
       }
    }
    DELAY_MS(20);
    k = 0x20;
    for(i = 19;i >= 0;i--)
    {
       for(j = 39;j >= 0;j--)
       {
          GDispCharAt(i,j,k);
          if(++k > 0x7e)
             k = 0x20;
       }
    }
    DELAY_MS(20);
    for(i = 0;i < 20;i++)
    {
       for(j = 0;j < 40;j++)
       {
          GDispCharAt(i,j,k);
          if(++k > 0x7e)
             k = 0x20;
       }
    }
    DELAY_MS(20);
    for(y = 0;y < 16;y++)
    {
        k = 0x20;
        for(x = 0;x < 20;x++)
        {
            k = x+0x20;
            i = y;
            for(j = 0;j< 40;j++)
            {
                GDispCharAt(i,j,k++);
                DELAY_MS(1);
            }
            GDispCharAt(0,0,a+0x30);
        }
//        DELAY_MS(2);
    }
    }
    GDispClrTxt();
    GDispStringAt(8,6,"Exiting...");
    DELAY_MS(2000);
    GDispSetMode(DISPLAY_OFF);
    return 0;

}//end of main()

void DisplayDisclaimer(void)
{
    outString("disclaimer\n");
    GDispStringAt(1,15,"CAUTION\0");
    GDispStringAt(3,2,"Use of this system does not replace\0");
    GDispStringAt(4,2,"basic safety precautions and pro-\0");
    GDispStringAt(5,2,"cedures for operating the machine.\0");
    GDispStringAt(6,2,"Do not operate the machine while\0");
    GDispStringAt(7,2,"system communication are being\0");
    GDispStringAt(8,2,"established or diagnostic codes are\0");
    GDispStringAt(9,2,"present. Refer to the Operation and\0");
    GDispStringAt(10,2,"Maintenance Manual of the machine\0");
    GDispStringAt(11,2,"for additional information.\0");
}


