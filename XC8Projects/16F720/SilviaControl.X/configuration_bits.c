#if defined(__XC)
    #include <xc.h>                     // XC8 General Include File

#elif defined(HI_TECH_C)
    #include <htc.h>                    // HiTech General Include File
#endif

#pragma config FOSC = INTOSCIO          // Oscillator Selection bits
#pragma config WDTE = OFF               // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON               // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON               // Brown-out Reset Enable bit (BOR enabled)

