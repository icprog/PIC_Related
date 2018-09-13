#include <xc.h>
#include "system.h"
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x20;                    // LATA5 MUST be set to a 1 on an Output for LCD to get power
    LATB = 0x04;                    // LATB2 needs to be 1, to provide + Supply V for Thermistor measurement    
    LATC = 0x80;                    // LATC7 needs to be 1, to provide + Supply V for Thermistor measurement

    WPUA = 0x00;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUE = 0x8;

    TRISA = 0x00;
    TRISB = 0x02;                   // RB1 as Input
    TRISC = 0x40;                   // RC6 as Input

    ANSELA = 0x00;
    ANSELB = 0x02;                  // RB1 as Analog Input(AN9))
    ANSELC = 0x40;                  // RC6 as Analog Input(AN22))
    
    
/*    LATA = 0x00;
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
*/    
    PIE0bits.IOCIE = 0;                 // interrupts-on-change are globally disabled
    signed char state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

//    T2AINPPSbits.T2AINPPS = 0x0013;   //RC3->TMR2:T2IN; RC3 as hardware input pin to timer 2???
    RC4PPS = 0x000F;                    //RC4->PWM7:PWM7OUT;
//    RA2PPS = 0x000E;   //RA2->PWM6:PWM6OUT;
//    RA3PPS = 0x000E;                    //RA3->PWM6:PWM6OUT;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}