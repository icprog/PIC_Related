#ifndef ADC_H
#define	ADC_H

#include "system.h"                     // Needed to calculate __delay_() Functions

// This routine defines the channels that are available for the module to use.
typedef enum {
    ADC_CHANNEL_CTMU_TEMPERATURE_SENSOR_INPUT =  0x18,
    ADC_CHANNEL_CTMU =  0x19,
    ADC_CHANNEL_VBG =  0x1C,
    ADC_CHANNEL_AVSS =  0x1D,
    ADC_CHANNEL_AVDD =  0x1E,
    ADC_MAX_CHANNEL_COUNT = 5

//    ADC1_CHANNEL_VBG = 0X1C,
  //  ADC_CHANNEL_AVDD = 0x1E,
    //ADC_CHANNEL_AVSS = 0x1D,
//    ADC_CHANNEL_UPPER_GUARDBAND_RAIL = 0x1C,
//    ADC_CHANNEL_LOWER_GUARDBAND_RAIL = 0x1B,
  //  ADC_CHANNEL_INTERNAL_BAND_GAP_REFERENCE = 0x1A,
    //ADC_CHANNEL_CTMU = 0x17,
//    ADC_CHANNEL_CTMU_TEMPERATURE_SENSOR_INPUT = 0x16,
  //  ADC_MAX_CHANNEL_COUNT = 0
} ADC_CHANNEL;
//***************************************************************************************************************************************************************
void ADCInit(void);
//***************************************************************************************************************************************************************
int ADCRead(ADC_CHANNEL channel);

#endif