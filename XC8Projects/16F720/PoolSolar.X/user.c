
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include "system.h"
#include "user.h"


void Init()
 {                           // Initialization Function

    TRISA = 0b00010100;                 // 0 = output 1 = input
    ANSELA = 0b00010100;                // RA2 and RA4 as Analog (0 = Digital, 1 = Analog)
    PORTA = 0b00000000;                 // Set all port A register to 1, 1 = off, 0 = on, (if sinking)

    TRISB = 0b00000000;                 // 0 = output, 1 = input
    ANSELB = 0b00000000;                // No Analogs (0 = Digital, 1 = Analog)
    PORTB = 0x00;                       // Set all port B register to 0, 1 = off, 0 = on

    TRISC = 0x00;                       // 0 = output 1 = input
    ANSELC = 0x00;                      // 0 = Digital, 1 = Analog
    PORTC = 0xff;                       // Set all port C register to 1, 1 = off, 0 = on


    FVRCON = 0xf3;

}

void ADCInit(){
        ADCON1 = 0x10;                   // Set ADC conversion clock FOSC/8 See Page 80
}
unsigned char ADCRead(unsigned char ch)  //Function to Read given ADC channel (0-14)

{
    ADCON0=0x00;                         // Set ADCON0 to all zero's
    ADCON0=(ch<<2);                      // Select ADC Channel (write the decimal value of ch, Left shifted two places, writing to Bits 5,4,3 and 2)
    ADON=1;                              // Enable the ADC module (on selected channel)
    delay_us(1500);                      // Delay 1500 us to allow the ADC cap to charge
    GO_nDONE=1;                          // Start conversion
    while(GO_nDONE);                     // Wait for the conversion to finish
    ADON=0;                              // Disable the ADC
    return ADRES;                        // Return the Analog value
}
