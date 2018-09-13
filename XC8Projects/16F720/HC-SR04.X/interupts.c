#include "interupts.h"

#if defined(__XC)
    #include <xc.h>                         // XC8 General Include File
#elif defined(HI_TECH_C)
    #include <htc.h>                        // HiTech General Include File
#endif

// Interrupt Service Routine (keyword "interrupt" tells the compiler it's an ISR)

void interrupt echo()
{
    extern unsigned int Value;
    
    if(RABIF == 1)                          //Makes sure that it is PORTB On-Change Interrupt
    {
        RABIE = 0;                          //Disable On-Change Interrupt

        if(RB4 == 1)                        //If ECHO is HIGH
        {
            TMR1ON = 1;                     //Start Timer
        }
    
        if(RB4 == 0)                        //If ECHO is LOW
        {
            TMR1ON = 0;                     //Stop Timer
            Value = (TMR1L | (TMR1H<<8))/59;    //Calculate Distance
//            a = (TMR1L | (TMR1H<<8))/58.82; //Calculate Distance
        }
    }
    RABIF = 0;                              //Clear PORTB On-Change Interrupt flag
    RABIE = 1;                              //Enable PORTB On-Change Interrupt
}