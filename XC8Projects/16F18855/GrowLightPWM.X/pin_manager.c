#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    

    TRISA = 0xFD;                               // LATA2 as Output for PWM
    TRISB = 0xFF;                               // RB0 is Analog Input for Zero Cross Detector
    TRISC = 0xFF;

    ANSELA = 0x80;                              // RA7, pin 9 Analog in to measure Vsense
    ANSELB = 0x01;
    ANSELC = 0x00;

    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    
    PIE0bits.IOCIE = 0;                         // interrupts-on-change are globally disabled
    INTERRUPT_GlobalInterruptDisable();
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;               // unlock PPS

//    T2AINPPSbits.T2AINPPS = 0x0013;   //RC3->TMR2:T2IN; RC3 as hardware input pin to timer 2???
    RA1PPS = 0x000E;                    //RA1->PWM6:PWM6OUT;
//    RA2PPS = 0x000E;   //RA2->PWM6:PWM6OUT;
//    RA3PPS = 0x000E;                    //RA3->PWM6:PWM6OUT;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;               // lock PPS
    INTERRUPT_GlobalInterruptEnable();
}