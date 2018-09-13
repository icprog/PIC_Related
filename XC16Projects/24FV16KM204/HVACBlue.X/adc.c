#include "adc.h"

// ***************************************************************************************************************************************************************
void ADCInit(void)
{
    // ADSIDL disabled; ASAM disabled; FORM Absolute decimal result, unsigned, right-justified; MODE12 enabled; ADON enabled; DONE disabled; SAMP disabled; SSRC Clearing sample bit ends sampling and starts conversion; 

    AD1CON1 = 0x8400;

    // OFFCAL disabled; ALTS disabled; PVCFG AVDD; BUFM disabled; BUFREGEN disabled; NVCFG0 AVSS; SMPI 1; CSCNA disabled; 

    AD1CON2 = 0x0000;

    // ADRC FOSC/2; SAMC 0; EXTSAM disabled; ADCS 5; 

    AD1CON3 = 0x0005;

    // CH0SA AN0; CH0SB AN0; CH0NB AVSS; CH0NA AVSS; 

    AD1CHS = 0x0000;

    // CSS3 disabled; CSS4 disabled; CSS5 disabled; CSS6 disabled; CSS7 disabled; CSS8 disabled; CSS9 disabled; CSS10 disabled; CSS11 disabled; CSS0 disabled; CSS12 disabled; CSS13 disabled; CSS2 disabled; CSS14 disabled; CSS1 disabled; CSS15 disabled; 

    AD1CSSL = 0x0000;

    // CSS16 disabled; CSS29 disabled; CSS17 disabled; CSS18 disabled; CSS27 disabled; CSS19 disabled; CSS28 disabled; CSS30 disabled; CSS21 disabled; CSS22 enabled; CSS20 disabled; CSS26 disabled; CSS23 disabled; 

    AD1CSSH = 0x0040;


//    adc_obj.intSample = AD1CON2bits.SMPI;

}
//***************************************************************************************************************************************************************
int ADCRead(ADC_CHANNEL channel)
{
    uint16_t result;
    AD1CHS = channel;
    if(AD1CHS == 0x1A)                                                          //If reading Internal Band Gap Voltage
    {
        _BGREQ = 1;                                                             //Enable Band Gap Reference
        __delay_us(20);                                                 
    }
    AD1CON1bits.SAMP = 1;
    __delay_us(50);
    AD1CON1bits.SAMP = 0;
    while(!AD1CON1bits.DONE)
    {
         IFS0bits.AD1IF = false;
    }
    _BGREQ = 0;                                                                 // Turn off Band Gap Reference
    result = ADC1BUF0;
    return result;
}

