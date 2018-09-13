#include "zcd.h"

void ZCD_Initialize (void)
{
#if (__XC8_VERSION < 1360)
    ZCDCON = 0x82;
#else                   
    ZCD1CON = 0x82;                             // ZCD1POL not inverted; ZCD1EN enabled; ZCD1INTP enabled; ZCD1INTN disabled; 
#endif                  

    PIR2bits.ZCDIF = 0;                         // Clear IF flag before enabling the interrupt.

    PIE2bits.ZCDIE = 1;                         // Enabling ZCD interrupt.
}

void ZCD_ISR(void)
{
    PIR2bits.ZCDIF = 0;                         // Clear the ZCD interrupt flag
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


