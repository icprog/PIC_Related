#include "system.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif


//#pragma config FOSC = INTOSCIO          // This line enables internal oscillator (Default runs @ 8 MHz) See Page 72
//#pragma config WDTE = OFF               // Sets WatchDog Timer Off See Manual Page 72
#define _XTAL_FREQ 2000000		// Must be defined, or Compiler will error out using __delay_ms()


//*****************************************************************************************
// Startup Oscillator requirements
//*****************************************************************************************
void ConfigureOscillator()
{
    IRCF1 = 0;                          // These 2 parameters set Clock @ 2 MHz
    IRCF0 = 0;                          // These 2 parameters set Clock @ 2 MHz
    OSCTUNE = 0x00;                     // Change default oscilator speed (See page 68)

    TMR0 = 0;                           // TMR0 Pre-set
    T0CS = 0;                           // TMR0 Clock source 0 = internal clock (FOSC/4)
    T0SE = 0;                           // Triggering on Low to High edge
    PSA = 0;                            // Work with a PreScaler
    PS0 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS1 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS2 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
}


//*****************************************************************************************
// Initialization Function
//*****************************************************************************************
void Init()
{
    TRISA = 0b00011111;                 //  0 = output 1 = input
    ANSELA = 0b00010100;                // RA2 and RA4 as Analog (0 = Digital, 1 = Analog)
    PORTA = 0xff;                       // Set all port A register to 1, 1 = off, 0 = on, (if sinking)
//    TRISA = 0x1f;                        //  0 = output 1 = input
//    ANSELA = 0x14;                       // RA2 and RA4 as Analog (0 = Digital, 1 = Analog)
//    PORTA = 0xff;                        // Set all port A register to 1, 1 = off, 0 = on, (if sinking)

    TRISB = 0b00110000;                 // 0 = output, 1 = input
    ANSELB = 0b00110000;                // RB4 and RB5 as Analog (0 = Digital, 1 = Analog)
    PORTB = 0xff;                       // Set all port B register to 1, 1 = off, 0 = on
//    TRISB = 0x30;                        // 0 = output, 1 = input
//    ANSELB = 0x30;                       // RB4 and RB5 as Analog (0 = Digital, 1 = Analog)
//    PORTB = 0xff;                        // Set all port B register to 1, 1 = off, 0 = on

    TRISC = 0b11001011;                 // (0 = Digital, 1 = Analog)
    ANSELC = 0b11001011;                // RC0, RC1, RC3, RC6 and RC7 as Analog (0 = Digital, 1 = Analog)
    PORTC = 0xff;                       // Set all port C register to 1, 1 = off, 0 = on
//    TRISC = 0xcb;                        // (0 = Digital, 1 = Analog)
//    ANSELC = 0xcb;                       // RC0, RC1, RC3, RC6 and RC7 as Analog (0 = Digital, 1 = Analog)
//    PORTC = 0xff;                        // Set all port C register to 1, 1 = off, 0 = on

    IRCF1 = 0;                          // These 2 parameters set Clock @ 2 MHz
    IRCF0 = 0;                          // These 2 parameters set Clock @ 2 MHz
    OSCTUNE = 0x3e;                     // Change default oscilator speed (See page 68)

    FVRCON = 0xc3;                      // Set FRV for 4.096V, disable internal temperature measurement
//    FVRCON = 0xf3;                      // Set FRV for 4.096V, enable internal temperature measurement
}
