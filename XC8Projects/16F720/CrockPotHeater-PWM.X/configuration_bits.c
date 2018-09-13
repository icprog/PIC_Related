#if defined(__XC)
    #include <xc.h>         // XC8 General Include File
#elif defined(HI_TECH_C)
    #include <htc.h>        // HiTech General Include File
#endif

// CONFIG1
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/CLKO pin, I/O function on RA5/CLKI)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA3/MCLR/VPP Pin Function Select bit (RA3/MCLR/VPP pin function is MCLR; Weak pull-up enabled.)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled)
//#pragma config PLLEN = ON       // INTOSC PLLEN Enable Bit (INTOSC Frequency is 16 MHz (32x))
#pragma config PLLEN = OFF      // INTOSC PLLEN Enable Bit (INTOSC Frequency is 500 kHz)

// CONFIG2
#pragma config WRTEN = OFF      // Flash memory self-write protection bits (Write protection off)


#include <xc.h>
