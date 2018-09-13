
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include "system.h"
#include "user.h"


//*****************************************************************************************
// Set ADC conversion clock FOSC/8, See Page 80
//*****************************************************************************************
void ADCInit()
{
    ADCON1 = 0x10;
}
//*****************************************************************************************



//*****************************************************************************************
//Function to Read given ADC channel (0-14)
//*****************************************************************************************
unsigned char ADCRead(unsigned char ch)
{
    ADCON0=0x00;                         // Set ADCON0 to all zero's
    ADCON0=(ch<<2);                      // Select ADC Channel (write the decimal value of ch, Left shifted two places, writing to Bits 5,4,3 and 2)
    ADON=1;                              // Enable the ADC module (on selected channel)
    delay_us(300);                       // Delay 300 us to allow the ADC cap to charge
    GO_nDONE=1;                          // Start conversion
    while(GO_nDONE);                     // Wait for the conversion to finish
    ADON=0;                              // Disable the ADC
    return ADRES;                        // Return the Analog value
}
//*****************************************************************************************



//*****************************************************************************************
// Median Function (Variables are local to function)
//*****************************************************************************************
unsigned char Median(unsigned char a, unsigned char c, unsigned char e)
{
    unsigned char b, d, f;

    if (a > c){
        b = a;
    }
    else{
        b = c;
    }

    if(c > e){
        d = c;
    }
    else{
        d = e;
    }

    if(b < d){
        f = b;
    }
    else{
        f = d;
    }

    return f;
}
//*****************************************************************************************

