 #ifndef _PWM6_H
 #define _PWM6_H
 
#include <xc.h>
#include <stdint.h>

 #define PWM6_INITIALIZE_DUTY_VALUE    1023

 void PWM6_Initialize(void);

 /**
   @Summary
     Loads 16-bit duty cycle.

   @Description
     This routine loads the 16 bit duty cycle value.

   @Preconditions
     PWM6_Initialize() function should have been called 
         before calling this function.

   @Param
     Pass 16bit duty cycle value.

   @Example
     <code>
     uint16_t dutycycle;

     PWM6_Initialize();
     PWM6_LoadDutyValue(dutycycle);
     </code>
 */
 void PWM6_LoadDutyValue(uint16_t dutyValue);

 #endif