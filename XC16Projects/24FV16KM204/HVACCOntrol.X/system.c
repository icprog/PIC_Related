/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include <stdint.h>          /* For uint32_t definition */
#include <stdbool.h>         /* For true/false definition */

#include "system.h"          /* variables/params used by system.c */



void ConfigureOscillator(void)
{
    CLKDIV = 0x3100;                // DOZEN disabled; DOZE 1:8; RCDIV FRC/2; ROI disabled;

    OSCCONbits.SOSCEN = 1;          // Set the secondary oscillator

//    _RTCCLK1 = 0;       // Set RTCC Clock Source to Internal 32kHz RC
//    _RTCCLK0 = 0;

#if 0

        /* Disable Watch Dog Timer */
//        RCONbits.SWDTEN = 0;

        /* When clock switch occurs switch to Prim Osc (HS, XT, EC)with PLL */
//        __builtin_write_OSCCONH(0x03);  /* Set OSCCONH for clock switch */
//        __builtin_write_OSCCONL(0x01);  /* Start clock switching */
//        while(OSCCONbits.COSC != 0b011);

        /* Wait for Clock switch to occur */
        /* Wait for PLL to lock, if PLL is used */
        /* while(OSCCONbits.LOCK != 1); */

#endif
        
}

void InitApp(void)
{
    TRISA = 0x0003;                 // Data Direction 1 = input, 0 = Output
    TRISB = 0x0000;                 // Data Direction 1 = input, 0 = Output
    TRISC = 0x0000;                 // Data Direction 1 = input, 0 = Output
    
    ANSA =  0x0003;                 // Analog or Digital 1 = Analog, 0 = Digital
    ANSB =  0x0000;                 // Analog or Digital 1 = Analog, 0 = Digital
    ANSC =  0x0000;                 // Analog or Digital 1 = Analog, 0 = Digital
    
    PORTA = 0x0000;
    PORTB = 0x0000;
    PORTC = 0x0000;
   
    /* Setup analog functionality and port direction */


    /* Initialize peripherals */
}


