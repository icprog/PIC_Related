#ifndef _PWM2_H
#define _PWM2_H


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

void PWM2_Initialize(void);

/**
  @Summary
    Loads 16-bit duty cycle.

  @Description
    This routine loads the 16 bit duty cycle value.

  @Preconditions
    PWM2_Initialize() function should have been called
    before calling this function.

  @Param
    Pass 16bit duty cycle value.

  @Returns
    None

  @Example
    <code>
    uint16_t dutycycle;

    PWM2_Initialize();
    PWM2_LoadDutyValue(dutycycle);
    </code>
*/
void PWM2_LoadDutyValue(uint16_t dutyValue);

/**
  @Summary
    Read pwm output status.

  @Description
    This routine returns the pwm output status.

  @Preconditions
    PWM2_Initialize() function should have been
    called before calling this function.

  @Param
    None

  @Returns
    true : output high
    false: output low

  @Example
    <code>
    uint16_t dutyCycle;
    bool status;
    PWM2_Initialize();
    PWM2_LoadDutyValue(dutyCycle);
    while(1)
    {
            status = PWM2_OutputStatusGet();
    }
    </code>
*/
bool PWM2_OutputStatusGet(void);
        

#endif