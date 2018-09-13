#include <stdio.h>
#include <stdlib.h>
#include <xc.h> /* XC8 General Include File */
#include <stdint.h> /* For uint8_t definition */
#include <stdbool.h> /* For true/false definition */
#include "5110lcd.h"


int main(int argc, char** argv)
{
    LATA    =   0x00;
    LATB    =   0x00;
    LATC    =   0x00;
    
    TRISA   =   0x00;
    TRISB   =   0x00;
    TRISC   =   0x00;
    
    ANSELA  =   0x00;
    ANSELB  =   0x00;
    ANSELC  =   0x00;
    
    
    LCDInit(); //Init the LCD
    
    LCDClear();

    LCDString("Hello World! Not sure what happens if this keeps going on and on and on?Hello World! Not sure what happens if this keeps going on and on and onHello World! Not sure what happens if this keeps going on and on and on");
    
    while(1)
    {
        ;
    }
    return (EXIT_SUCCESS);
}