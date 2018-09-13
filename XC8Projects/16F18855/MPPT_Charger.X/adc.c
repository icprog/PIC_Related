#include <xc.h>
#include "adc.h"

#define     numSamples                      12                                              // Number of Temperature readings to Average
#define     numChannels                     8                                               // Number of Analog channels to read

int16_t samples[numChannels][numSamples]    =   {{0},{0}};                                  // Was left initialized like this, but following is correct?

static uint16_t sampleIndex                 =   {0};

static int32_t totals[numChannels]          =   {0};

static uint16_t channels[numChannels]       =   {23, 21, 19, 17, 22, 20, 18, 16};           // List all the Analog channel numbers here, must be same number listed as numChannels
//static uint16_t channels[numChannels]       =   {16, 17, 18, 19, 20, 21, 22, 23};           // List all the Analog channel numbers here, must be same number listed as numChannels

//int16_t voltage[4]                           =   {0};

// *************** ADC Read Individual Channel ****************************************************************************************************
int16_t ADCRead(adcc_channel_t channel)
{
    ADPCH                                   =   channel_VSS;                                  // select the A/D channel_VSS

    ADCON0bits.ADON                         =   1;                                            // Turn on the ADC module

    ADCON0bits.ADCONT                       =   0;                                            //Disable the continuous mode.

    ADCON0bits.ADGO                         =   1;                                            // Start the conversion

    while(ADCON0bits.ADGO)                                              // Wait for the conversion to finish
    {
    }                       

    ADPCH                                   =   channel;                                      // select the A/D channel

    ADCON0bits.ADON                         =   1;                                            // Turn on the ADC module

    ADCON0bits.ADCONT                       =   0;                                            //Disable the continuous mode.

    ADCON0bits.ADGO                         =   1;                                            // Start the conversion

    while(ADCON0bits.ADGO)                                              // Wait for the conversion to finish
    {
    }                       

    return ((ADRESH<<8)+ADRESL);                                        // Conversion finished, return the result
}

// *************** Read Analogs from Analog channel Array ****************************************************************************************
int16_t readAnalog(uint16_t channel)
{
    int16_t value;
    
    uint16_t analog_channel = channels[channel];
    
    value = ADCRead(analog_channel);
            
    totals[channel] = totals[channel]-samples[channel][sampleIndex];    // Subtract the oldest sample data from the total

    samples[channel][sampleIndex] = value;                              // Assign the just read temperature to the location of the current oldest data

    totals[channel] = totals[channel]+samples[channel][sampleIndex];    // Add that new sample to the total
            
    if(channel>=(numChannels-1))
    {
        sampleIndex+=1;                                                 // and move to the next index location
        if(sampleIndex >= numSamples)sampleIndex = 0;
    }
            
    value = totals[channel]/numSamples;                                 // assign the average value of total to the readTemperature variable
        
    return value;   
}

/* // *************** Read Analogs from Analog channel Array ****************************************************************************************
int16_t calculateVoltage(uint8_t j)
{
    float voltage;
    voltage=analogs[j]/.20885;
    
    return (int16_t)voltage;
}*/
// *************** ADC Initialization Routine *****************************************************************************************************
void ADC_Initialize(void)
{
    ADCON1 = 0x00;  // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL VSS; 

    ADCON2 = 0x00;  // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS ADFLTR; 

    ADCON3 = 0x00;  // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 

    ADACT = 0x00;   // ADACT disabled; 

    ADSTAT = 0x00;  // ADAOV ACC or ADERR not Overflowed; 

    FVRCON = 0b11000011;    // FVREN = 1, FVRRDY = 1, Buffer Gain is 4X (4.096V)
    ADCLK = 0x3F;   //ADC CLK FOSC/128
//    ADCLK = 0x00;   //ADC CLK FOSC/2
//    ADCLK = 0X09;   // ADC Clock FOSC/20    
//    FVREN = 1;
    
//    ADFVR = 0x01;
    
    ADREF = 0x03;   // ADNREF VSS; ADPREF FVR;
//    ADREF = 0x00;   // ADNREF VSS; ADPREF VDD;

    ADCAP = 0x00; 
//    ADCAP = 0x1F;

    ADPRE = 0x07;

    ADACQ = 0x00;

    ADPCH = 0x00;

    ADRPT = 0x00;

    ADLTHL = 0x00;

    ADLTHH = 0x00;

    ADUTHL = 0x00;

    ADUTHH = 0x00;

    ADSTPTL = 0x00;

    ADSTPTH = 0x00;
    
    ADCON0 = 0x84;  // ADGO stop; ADFM right; ADON enabled; ADCONT disabled; ADCS FOSC/ADCLK; 
}