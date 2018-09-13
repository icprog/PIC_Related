#ifndef ADC_H
#define ADC_H

#include "system.h"

typedef enum
{
    channel_VSS =   0x3C,
    channel_Temp =  0x3D,
    channel_DAC1 =  0x3E,
    channel_FVR =   0x3F
} adcc_channel_t;                                   //   This routine defines the channels that are available for the module to use.


void ADC_Initialize(void);

void ADC_StartConversion(adcc_channel_t channel);

bool ADC_IsConversionDone();

unsigned int ADC_GetConversionResult(void);

unsigned int ADCRead(adcc_channel_t channel);

void ADC_StopConversion(void);

void ADC_SetStopOnInterrupt(void);

void ADC_DischargeSampleCapacitor(void); 

void ADC_LoadAcquisitionRegister(uint8_t);

void ADC_SetPrechargeTime(uint8_t);

void ADC_SetRepeatCount(uint8_t);

uint8_t ADC_GetCurrentCountofConversions(void);

void ADC_ClearAccumulator(void);

uint16_t ADC_GetAccumulatorValue(void);

bool ADC_HasAccumulatorOverflowed(void);

uint16_t ADC_GetFilterValue(void);

/**
  @Summary
   Returns the contents of ADPREVH and ADPREVL registers.

  @Description
    None

  @Preconditions
    None.

  @Returns
    16 bit value obtained from ADPREVH and ADPREVL registers.

  @Param
    None.

  @Example
    <code>
	uint16_t prevResult = ADC_GetPreviousResult();
	
    </code>
*/
uint16_t ADC_GetPreviousResult(void);

/**
  @Summary
   Sets the ADSTPTH and ADSTPTL registers.

  @Description
    None

  @Preconditions
    None

  @Returns
    None

  @Param
    16 bit value for set point.

  @Example
    <code>
	uint16_t setPoint = 90;
	ADC_DefineSetPoint(setPoint);
    </code>
*/
void ADC_DefineSetPoint(uint16_t);

/**
  @Summary
   Sets the ADUTHH and ADUTHL register.

  @Description
    None

  @Preconditions
    None

  @Returns
    None

  @Param
    16 bit value for upper threshold.

  @Example
    <code>
	uint16_t upperThreshold = 90;
	ADC_SetUpperThreshold(upperThreshold);
	
    </code>
*/
void ADC_SetUpperThreshold(uint16_t);

/**
  @Summary
   Sets the ADLTHH and ADLTHL register.

  @Description
    None

  @Preconditions
    None

  @Returns
    None

  @Param
    16 bit value for lower threshold..

  @Example
    <code>
	uint16_t lowerThreshold = 90;
	ADC_SetLowerThreshold(lowerThreshold);
	
    </code>
*/
void ADC_SetLowerThreshold(uint16_t);

/**
  @Summary
   Returns the 16 bit value obtained from ADERRH and ADERRL registers.

  @Description
    None

  @Preconditions
    None

  @Returns
    16 bit value obtained from ADERRH and ADERRL registers.

  @Param
    None.

  @Example
    <code>
	uint16_t error = ADC_GetErrorCalculation(void);
    </code>
*/
uint16_t ADC_GetErrorCalculation(void);

/**
  @Summary
   Sets the ADDSEN bit.

  @Description
    None

  @Preconditions
    None

  @Returns
    None

  @Param
    None.

  @Example
    <code>
    </code>
*/
void ADC_EnableDoubleSampling(void);

/**
  @Summary
   Sets the ADCONT bit.

  @Description
    None

  @Preconditions
    None

  @Returns
    None

  @Param
    None.

  @Example
    <code>
    </code>
*/
void ADC_EnableContinuousConversion(void);

/**
  @Summary
   Resets the ADCONT bit.

  @Description
    None

  @Preconditions
    None

  @Returns
    None

  @Param
    None.

  @Example
    <code>
    </code>
*/
void ADC_DisableContinuousConversion(void);

/**
  @Summary
   Returns the value of ADUTHR bit.

  @Description
    None

  @Preconditions
    None

  @Returns
    Returns the value of ADUTHR bit.

  @Param
    None.

  @Example
    <code>
    </code>
*/
bool ADC_HasErrorCrossedUpperThreshold(void);

/**
  @Summary
   Returns the value of ADLTHR bit.

  @Description
    None

  @Preconditions
    None

  @Returns
    Returns the value of ADLTHR bit.

  @Param
    None.

  @Example
    <code>
    </code>
*/
bool ADC_HasErrorCrossedLowerThreshold(void);

/**
  @Summary
   Returns value of ADSTAT setting.

  @Description
    None

  @Preconditions
    None

  @Returns
    Returns value of ADSTAT setting.

  @Param
    None.

  @Example
    <code>
    </code>
*/
uint8_t ADC_GetConversionStageStatus(void);

#endif
