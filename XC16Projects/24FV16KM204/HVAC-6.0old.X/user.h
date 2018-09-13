#ifndef USER_H
#define	USER_H

#include <xc.h>                         // include processor files - each processor file is guarded.  
//#include <stdio.h>                      // Needs to be here to use sprintf in this source file
#include "stdint.h"                     // Includes uint16_t definition
#include <stdbool.h>                    // Includes true/false definition
#include <stdlib.h>
#include "system.h"                     // Neede to calculate __delay_ Functions
#include "AnalogKeyInput.h"             // Include to check menu buttons

// ***************************************************************************************************************************************************************
void heartBeat(void);

//***************************************************************************************************************************************************************

// This routine defines the channels that are available for the module to use.

typedef enum {
    ADC_CHANNEL_AVDD = 0x1E,
    ADC_CHANNEL_AVSS = 0x1D,
    ADC_CHANNEL_UPPER_GUARDBAND_RAIL = 0x1C,
    ADC_CHANNEL_LOWER_GUARDBAND_RAIL = 0x1B,
    ADC_CHANNEL_INTERNAL_BAND_GAP_REFERENCE = 0x1A,
    ADC_CHANNEL_CTMU = 0x17,
    ADC_CHANNEL_CTMU_TEMPERATURE_SENSOR_INPUT = 0x16,
    ADC_MAX_CHANNEL_COUNT = 0
} ADC_CHANNEL;
//***************************************************************************************************************************************************************
    
void ADCInit(void);
//***************************************************************************************************************************************************************
    
int ADCRead(ADC_CHANNEL channel);
//***************************************************************************************************************************************************************

int TempCalc(int a);
//***************************************************************************************************************************************************************
    
int TempSetpoint(int);
//***************************************************************************************************************************************************************

unsigned char SetDeadband(unsigned char b);
//***************************************************************************************************************************************************************

signed char SetBiasNeg15(signed char b);
//***************************************************************************************************************************************************************

signed char SetBiasNeg25(signed char b);
//***************************************************************************************************************************************************************

bool SetOutput(bool Out, int SetPoint, signed char Bias, int ProcessVariable, unsigned char Deadband);
//***************************************************************************************************************************************************************

#endif