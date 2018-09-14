#include <xc.h>
#include "pwm1.h"


#define PWM1_INITIALIZE_DUTY_VALUE    511


void PWM1_Initialize(void)
{
    // MODE PWM; EN enabled; CCP1FMT right_aligned; 
    CCP1CON = 0x8F;    

    // RH 1; 
    CCPR1H = 0x01;    

    // RL 255; 
    CCPR1L = 0xFF;    

    // Selecting Timer 2
    CCPTMRS0bits.C1TSEL = 0x1;
}

void PWM1_LoadDutyValue(uint16_t dutyValue)
{
    dutyValue &= 0x01FF;
    
    if(CCP1CONbits.CCP1FMT)                                     // Load duty cycle value
    {
        dutyValue <<= 6;
        CCPR1H = dutyValue >> 8;
        CCPR1L = dutyValue;
    }
    else
    {
        CCPR1H = dutyValue >> 8;
        CCPR1L = dutyValue;
    }
}

bool PWM1_OutputStatusGet(void)
{
    // Returns the output status
    return(CCP1CONbits.OUT);
}