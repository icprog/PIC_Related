/* 
 * File:   user.h
 * Author: DAVE
 *
 * Created on May 18, 2015, 10:30 PM
 */

#ifndef USER_H
#define	USER_H

#include "system.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

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

    
    void ADCInit(void);
    
    int ADCRead(ADC_CHANNEL channel);
    
    void TimerInit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* USER_H */

