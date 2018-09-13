/*
 * Pool Heater Inlet and Outlet Temperature Indicator Designed for David Moore (Ninole, Hawaii)
 * Built on a Microchip PIC 16F720 SOIC Micro
 * Final Code Friday March 9, 2015 by Dave Zieglgansberger, dziegl@dr.com
 * Inlet temperature connected to AN2 (pin 17)
 * Outlet temperature connected to AN3 (pin 3)
 * Thermistors ranged for -27 degF to 208 degF
 */


#include "system.h"
#include <xc.h>
#include "lcd_hd44780_pic16.h"
#include "configuration_bits.c"
#include "user.h"


void TempCheck();

char sl = 0;                                                    // Time keeping variables(Seconds low)


void main ()
{
    ConfigureOscillator();

    Init();                                                     //  Initialize TRIS,ANSEL,PORT,OSCTUNE, and OSC Frequency

    delay_ms(750);                                              //Startup delay to allow LCD to Power-Up

    LCDInit(LS_NONE);                                           // Initialize the LCD Module
    delay_ms(500);

    LCDClear();
    LCDGotoXY(0,0);
    LCDWriteStringXY(0,0,"Initializing ...");
    LCDWriteStringXY(2,1,"A");
    delay_ms(200);
    LCDWriteStringXY(3,1,"L");
    delay_ms(200);
    LCDWriteStringXY(4,1,"O");
    delay_ms(200);
    LCDWriteStringXY(5,1,"H");
    delay_ms(200);
    LCDWriteStringXY(6,1,"A");
    delay_ms(200);
    LCDWriteStringXY(7,1," ");
    delay_ms(200);
    LCDWriteStringXY(8,1,"D");
    delay_ms(200);
    LCDWriteStringXY(9,1,"A");
    delay_ms(200);
    LCDWriteStringXY(10,1,"V");
    delay_ms(200);
    LCDWriteStringXY(11,1,"I");
    delay_ms(200);
    LCDWriteStringXY(12,1,"D");
    delay_ms(200);
    LCDWriteStringXY(13,1,"!");
    delay_ms(5000);
    LCDClear();

    while (1)                                                   //  Or, while true, so, Run continuously
    {
        TempCheck();
        delay_ms(1000);
    }
}

void TempCheck()
{
    unsigned int tempin,tempout;

    // Following is a look-up Array for converting ADC output to temperature in Degrees F
    const int tempread[] = {0,0,0,0,0,0,0,0,0,0,-27,-24,-22,-20,-18,-16,-14,-12,-10,-9,-7,-5,-4,-2,-1,1,2,3,4,6,7,8,9,10,11,12,13,14,14,15,16,
    17,18,19,20,21,22,23,24,25,25,26,27,28,29,30,31,32,32,33,34,35,36,36,37,37,38,39,40,41,41,42,42,43,44,44,45,46,46,47,48,49,49,50,51,51,52,
    53,53,54,55,55,56,57,57,58,59,59,60,61,61,62,62,63,64,64,65,65,66,67,67,68,68,69,70,70,71,72,72,73,74,74,75,75,76,77,77,78,79,79,80,81,81,
    82,83,83,84,85,85,86,87,87,88,89,89,90,91,91,92,93,93,94,95,95,96,97,98,98,99,100,100,101,102,103,104,104,105,106,106,107,108,109,110,111,
    111,112,113,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,138,139,140,141,142,144,145,146,
    148,150,151,152,153,155,156,157,159,161,163,164,166,168,170,172,174,176,179,181,184,186,188,190,193,197,201,204,208};

    ADCInit();

    tempin = ADCRead(2);
    tempin = tempread[tempin];

    LCDWriteStringXY(0,0,"In Temp:");
    LCDWriteIntXY(10,0,tempin,3);
    LCDWriteStringXY(13,0,"%0F")

    tempout = ADCRead(3);
    tempout = tempread[tempout];

    LCDWriteStringXY(0,1,"Out Temp:");
    LCDWriteIntXY(10,1,tempout,3);
    LCDWriteStringXY(13,1,"%0F")

}      //        E N D   O F   P R O G R A M

// Following should display a float on the LCD, unfortunately, the Code is too big for memory in 16F720
/*
void TempCheck()
{
    unsigned int tempin,tempout;
    const float tempread[] = {0};
//    const float tempread[] = {2825,754,2645,555,2445,355};    // This needs to be a propper look-up table

    ADCInit();

    LCDWriteStringXY(0,0,"T In:");
    LCDWriteStringXY(0,1,"T Out:");

    tempin = ADCRead(2);
    displaynum(100.9);


 //   tempout = ADCRead(3);
//    line = 1;
//    displaynum(tempread[tempout]);
}

void displaynum(float num)
{
    int num1,dn,hn,tn,on;

    num1 = num;
    num = num - num1;
    num = num/0.10;

    dn = num;
    dn+=48;

    hn = num1/100;
    hn+=48;
    num1 = num1%100;
    tn = num1/10;
    tn+=48;
    num1 = num1%10;
    on = num1;
    on+=48;

    LCDWriteIntXY(8,0,hn,1);
    LCDWriteIntXY(9,0,tn,1);
    LCDWriteIntXY(10,0,on,1);
    LCDWriteStringXY(11,0,".");
    LCDWriteIntXY(12,0,dn,2);
    LCDWriteStringXY(13,0,"%0F")  
}
*/