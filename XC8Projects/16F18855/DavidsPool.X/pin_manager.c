#include <xc.h>
#include "pin_manager.h"
#include <stdbool.h>

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;
    LATB = 0x0;
    LATC = 0x0;

    WPUA = 0x00;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUE = 0x8;

    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x10;

    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    
    PIE0bits.IOCIE = 0;                 // interrupts-on-change are globally disabled
    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

//    T2AINPPSbits.T2AINPPS = 0x0013;   //RC3->TMR2:T2IN; RC3 as hardware input pin to timer 2???
    RA1PPS = 0x000E;                    //RA1->PWM6:PWM6OUT;
//    RA2PPS = 0x000E;   //RA2->PWM6:PWM6OUT;
//    RA3PPS = 0x000E;                    //RA3->PWM6:PWM6OUT;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}


//void PIN_MANAGER_IOC(void)
//{    
//}