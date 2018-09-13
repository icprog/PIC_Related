#ifndef _ADCC_H
#define _ADCC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint16_t adc_result_t;


typedef enum
{
//    POT         =   0x4,
    channel_VSS =   0x3C,
    channel_Temp =  0x3D,
    channel_DAC1 =  0x3E,
    channel_FVR =   0x3F
} adcc_channel_t;                                   //   This routine defines the channels that are available for the module to use.


void ADCC_Initialize(void);

void ADCC_StartConversion(adcc_channel_t channel);

bool ADCC_IsConversionDone();

adc_result_t ADCC_GetConversionResult(void);

adc_result_t ADCRead(adcc_channel_t channel);

void ADCC_StopConversion(void);

void ADCC_SetStopOnInterrupt(void);

void ADCC_DischargeSampleCapacitor(void); 

void ADCC_LoadAcquisitionRegister(uint8_t);

void ADCC_SetPrechargeTime(uint8_t);

void ADCC_SetRepeatCount(uint8_t);

uint8_t ADCC_GetCurrentCountofConversions(void);

void ADCC_ClearAccumulator(void);

uint16_t ADCC_GetAccumulatorValue(void);

bool ADCC_HasAccumulatorOverflowed(void);

uint16_t ADCC_GetFilterValue(void);

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
	uint16_t prevResult = ADCC_GetPreviousResult();
	
    </code>
*/
uint16_t ADCC_GetPreviousResult(void);

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
	ADCC_DefineSetPoint(setPoint);
    </code>
*/
void ADCC_DefineSetPoint(uint16_t);

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
	ADCC_SetUpperThreshold(upperThreshold);
	
    </code>
*/
void ADCC_SetUpperThreshold(uint16_t);

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
	ADCC_SetLowerThreshold(lowerThreshold);
	
    </code>
*/
void ADCC_SetLowerThreshold(uint16_t);

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
	uint16_t error = ADCC_GetErrorCalculation(void);
    </code>
*/
uint16_t ADCC_GetErrorCalculation(void);

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
void ADCC_EnableDoubleSampling(void);

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
void ADCC_EnableContinuousConversion(void);

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
void ADCC_DisableContinuousConversion(void);

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
bool ADCC_HasErrorCrossedUpperThreshold(void);

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
bool ADCC_HasErrorCrossedLowerThreshold(void);

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
uint8_t ADCC_GetConversionStageStatus(void);

#endif
