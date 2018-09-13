#include "system.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

void ConfigureOscillator(void)
{
    FVRCON = 0xD3;
    IRCF1 = 0;                          // These 2 parameters set Clock @ 2 MHz
    IRCF0 = 0;                          // These 2 parameters set Clock @ 2 MHz
}

// Initialisation routine
void Init()
{
    TRISA =  0x14;                       // RA2 and RA4 as inputs, 0 = output 1 = input Not used in this configuration
    ANSELA = 0x14;                       // RA2 and RA4 as Analog (0 = Digital, 1 = Analog) Not used in this project
    PORTA =  0x00;                       // Set all port A register to 1, 1 = off, 0 = on, (if sinking)

    TRISB = 0xdf;                 // 0 = output, 1 = input   RB5 connected to Trigger RB4 to Echo
    ANSELB = 0x00;                // No Analogs (0 = Digital, 1 = Analog)
    PORTB = 0x00;                       // Set all port B register to 0, 1 = off, 0 = on
    IOCB = 0x10;                        // Interupt on change RB4

    TRISC = 0b00000000;                       // 0 = output 1 = input
    ANSELC = 0x00;                      // 0 = Digital, 1 = Analog
//    PORTC = 0xff;                       // Set all port C register to 1, 1 = off, 0 = on
    GIE = 1;                            //Global Interrupt Enable
    RABIF = 0;                           //Clear PORTB On-Change Interrupt Flag
    RABIE = 1;                           //Enable PORTB On-Change Interrupt

}