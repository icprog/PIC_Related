#include <xc.h>
#include "pin_manager.h"
#include <stdbool.h>

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    WPUA = 0x02;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUE = 0x8;

    TRISA = 0x02;                       // RA1 as Input
    TRISA = 0x3A;                       // RA1, 3, 4, & 5 as Inputs
    TRISB = 0x0A;                       // RB1 & 3 as Inputs
    TRISC = 0x10;

    ANSELA = 0x3A;                      // RA1, 3, 4 & 5 as Analog inputs
    ANSELB = 0x0A;                      // RB1 & 3 as analogs
    ANSELC = 0x00;
    
    PIE0bits.IOCIE = 0;                 // interrupts-on-change are globally disabled
    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

//    T2AINPPSbits.T2AINPPS = 0x0013;   //RC3->TMR2:T2IN; RC3 as hardware input pin to timer 2???
    RC2PPS = 0x000E;                    //RA1->PWM6:PWM6OUT;
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