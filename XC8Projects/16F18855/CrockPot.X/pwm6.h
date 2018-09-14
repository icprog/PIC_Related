 #ifndef _PWM6_H
 #define _PWM6_H
 
#include <xc.h>
#include <stdint.h>

 #define PWM6_INITIALIZE_DUTY_VALUE    0            // Set to between 0 and 1023

 void PWM6_Initialize(void);

 void PWM6_LoadDutyValue(uint16_t dutyValue);

 #endif