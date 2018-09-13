
#include <xc.h>
#include "adcc.h"

#define     numSamples  20                                              // Number of Temperature readings to Average

uint16_t samples[6][numSamples] = {0};

uint16_t sampleIndex            = {0};

int32_t totals[6]               = {0};

static int channels[6]          ={1,3,4,5,9,11};


void ADCC_Initialize(void)
{
    // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL VSS; 
    ADCON1 = 0x00;
    // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS ADFLTR; 
    ADCON2 = 0x00;
    // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 
    ADCON3 = 0x00;
    // ADACT disabled; 
    ADACT = 0x00;
    // ADAOV ACC or ADERR not Overflowed; 
    ADSTAT = 0x00;
    // ADCCS FOSC/2; 
    ADCLK = 0x3F;               //ADC CLK FOSC/128
//    ADCLK = 0x00;               //ADC CLK FOSC/2
     
//    ADREF = 0x03;             // ADNREF VSS; ADPREF FVR;
    ADREF = 0x00;               // ADNREF VSS; ADPREF VDD;

    ADCAP = 0x00; 
//    ADCAP = 0x1F;
    // ADPRE 0; 
    ADPRE = 0x07;
    // ADACQ 0; 
    ADACQ = 0x00;
    // ADPCH ANA0; 
    ADPCH = 0x00;
    // ADRPT 0; 
    ADRPT = 0x00;
    // ADLTHL 0; 
    ADLTHL = 0x00;
    // ADLTHH 0; 
    ADLTHH = 0x00;
    // ADUTHL 0; 
    ADUTHL = 0x00;
    // ADUTHH 0; 
    ADUTHH = 0x00;
    // ADSTPTL 0; 
    ADSTPTL = 0x00;
    // ADSTPTH 0; 
    ADSTPTH = 0x00;
    
    // ADGO stop; ADFM right; ADON enabled; ADCONT disabled; ADCS FOSC/ADCLK; 
    ADCON0 = 0x84;
    

}


adc_result_t ADCRead(adcc_channel_t channel)
{
    // select the A/D channel
    ADPCH = channel;    

    // Turn on the ADC module
    ADCON0bits.ADON = 1;
	
    //Disable the continuous mode.
    ADCON0bits.ADCONT = 0;    

    // Start the conversion
    ADCON0bits.ADGO = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.ADGO)
    {
    }
    
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

int readAnalog(int channel)
{
    int value;
    
    int analog_channel  =   channels[channel];
    
    value = ADCRead(analog_channel);
    
//    temp = value;                           // Assign the just read temperature to the location of the current oldest data
            
        totals[channel] = totals[channel] - samples[channel][sampleIndex];   // Subtract the oldest sample data from the total

        samples[channel][sampleIndex] = value;             // Assign the just read temperature to the location of the current oldest data

        totals[channel] = totals[channel] + samples[channel][sampleIndex];   // Add that new sample to the total
            
        if(channel>4)
        {
            sampleIndex += 1;                                  // and move to the next index location
            
            if(sampleIndex >= numSamples)
            {
                sampleIndex = 0;
            }
        }
            
        value = totals[channel] / numSamples;                          // assign the average value of total to the readTemperature variable
        
     return value;   
}

/*void ADCC_StopConversion(void)
{
	//Reset the ADGO bit.
	ADCON0bits.ADGO = 0;
}

void ADCC_SetStopOnInterrupt(void)
{
	//Set the ADSOI bit.
	ADCON3bits.ADSOI = 1;
}

void ADCC_DischargeSampleCapacitor(void)
{
	//Set the ADC channel to AVss.
	ADPCH = 0x3C;   
}

void ADCC_LoadAcquisitionRegister(uint8_t acquisitionValue)
{
	//Load the ADACQ register.
	ADACQ = acquisitionValue;   
}

void ADCC_SetPrechargeTime(uint8_t prechargeTime)
{
	//Load the ADPRE register.
	ADPRE = prechargeTime;  
}

void ADCC_SetRepeatCount(uint8_t repeatCount)
{
	//Load the ADRPT register.
	ADRPT = repeatCount;   
}

uint8_t ADCC_GetCurrentCountofConversions(void)
{
	//Return the contents of ADCNT register
	return ADCNT;
}

void ADCC_ClearAccumulator(void)
{
	//Reset the ADCON2bits.ADACLR bit.
	ADCON2bits.ADACLR = 1;
}

uint16_t ADCC_GetAccumulatorValue(void)
{
	//Return the contents of ADACCH and ADACCL registers
	return ((ADACCH << 8) + ADACCL);
}

bool ADCC_HasAccumulatorOverflowed(void)
{
	//Return the status of ADSTATbits.ADAOV
	return ADSTATbits.ADAOV;
}

uint16_t ADCC_GetFilterValue(void)
{
	//Return the contents of ADFLTRH and ADFLTRL registers
	return ((ADFLTRH << 8) + ADFLTRL);
}

uint16_t ADCC_GetPreviousResult(void)
{
	//Return the contents of ADPREVH and ADPREVL registers
	return ((ADPREVH << 8) + ADPREVL);
}

void ADCC_DefineSetPoint(uint16_t setPoint)
{
	//Sets the ADSTPTH and ADSTPTL registers
	ADSTPTH = setPoint >> 8;
	ADSTPTL = setPoint;
}

void ADCC_SetUpperThreshold(uint16_t upperThreshold)
{
	//Sets the ADUTHH and ADUTHL registers
	ADUTHH = upperThreshold >> 8;
	ADUTHL = upperThreshold;
}

void ADCC_SetLowerThreshold(uint16_t lowerThreshold)
{
	//Sets the ADLTHH and ADLTHL registers
	ADLTHH = lowerThreshold >> 8;
	ADLTHL = lowerThreshold;
}

uint16_t ADCC_GetErrorCalculation(void)
{
#if (__XC8_VERSION < 1360)
	//Return the contents of ADSTPEH and ADSTPEL registers
	return ((ADSTPEH << 8) + ADSTPEL);
#else // __XC8_VERSION
	//Return the contents of ADERRH and ADERRL registers
	return ((ADERRH << 8) + ADERRL);
#endif // __XC8_VERSION
}

void ADCC_EnableDoubleSampling(void)
{
	//Sets the ADCON1bits.ADDSEN
	ADCON1bits.ADDSEN = 1;
}

void ADCC_EnableContinuousConversion(void)
{
	//Sets the ADCON0bits.ADCONT
	ADCON0bits.ADCONT = 1;
}

void ADCC_DisableContinuousConversion(void)
{
	//Resets the ADCON0bits.ADCONT
	ADCON0bits.ADCONT = 0;
}

bool ADCC_HasErrorCrossedUpperThreshold(void)
{
	//Returns the value of ADSTATbits.ADUTHR bit.
	return ADSTATbits.ADUTHR;
}

bool ADCC_HasErrorCrossedLowerThreshold(void)
{
	//Returns the value of ADSTATbits.ADLTHR bit.
	return ADSTATbits.ADLTHR;
}

uint8_t ADCC_GetConversionStageStatus(void)
{
	//Returns the contents of ADSTATbits.ADSTAT field.
	return ADSTATbits.ADSTAT;
}

*/
/**
 End of File
*/
