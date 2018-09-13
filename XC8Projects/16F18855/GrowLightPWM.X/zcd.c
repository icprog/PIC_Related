#include "zcd.h"

//unsigned int Vsense                     = 0;    // Voltage across Rsense
extern bool readBit;


void ZCD_Initialize (void)
{
    ZCD1CON = 0x82;                             // ZCD1POL not inverted; ZCD1EN enabled; ZCD1INTP enabled; ZCD1INTN disabled; 
    PIR2bits.ZCDIF  = 0;                        // Clear IF flag before enabling the interrupt.
    PIE2bits.ZCDIE  = 1;                        // Enabling ZCD interrupt.
}

void ZCD_ISR(void)
{
    PIR2bits.ZCDIF  = 0;                        // Clear the ZCD interrupt flag
    readBit         = 1;                        // Set readBit to allow another ADCRead
//    Vsense = ADCRead(7);                        // Measure the Voltage across the sense resistor
}

/*bool ZCD_IsLogicLevel(void)
{
    // Return ZCD logic level depending on the output polarity selected.
#if (__XC8_VERSION < 1360)
    return (ZCDCONbits.ZCDOUT);
#else // __XC8_VERSION
    return (ZCD1CONbits.ZCD1OUT);
#endif // __XC8_VERSION
}
*/


