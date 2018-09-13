#include "system.h"

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif


//#pragma config FOSC = INTOSCIO          // This line enables internal oscillator (Default runs @ 8 MHz) See Page 72
//#pragma config WDTE = OFF               // Sets WatchDog Timer Off See Manual Page 72
// #define _XTAL_FREQ 2000000		// Must be defined, or Compiler will error out using __delay_ms()


//*****************************************************************************************
// Startup Oscillator requirements
//*****************************************************************************************
void ConfigureOscillator()
{
//    IRCF1 = 0;                          // These 2 parameters set Clock @ 2 MHz
//    IRCF0 = 0;                          // These 2 parameters set Clock @ 2 MHz
//    OSCTUNE = 0x00;                     // Change default oscillator speed (See page 68)

//    TMR0 = 0;                           // TMR0 Pre-set
  //  T0CS = 0;                           // TMR0 Clock source 0 = internal clock (FOSC/4)
    //T0SE = 0;                           // Triggering on Low to High edge
//    PSA = 0;                            // Work with a PreScaler
//    PS0 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
  //  PS1 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
    //PS2 = 1;                            // Set Pre-Scaler for TMR0 to 256 (1:256)
}


//*****************************************************************************************
// Initialization Function
//*****************************************************************************************
void Init()
{
  TRISB = 0b00010000;           //RB4 as Input PIN (ECHO)
  TRISC = 0x00;                 // LCD Pins as Output
  GIE = 1;                      //Global Interrupt Enable
  RABIF = 0;                     //Clear PORTB On-Change Interrupt Flag
  RABIE = 1;                     //Enable PORTB On-Change Interrupt
  IOCA = 0b00010000;
 // FVRCON = 0xc3;                      // Set FRV for 4.096V, disable internal temperature measurement
//    FVRCON = 0xf3;                      // Set FRV for 4.096V, enable internal temperature measurement
}
