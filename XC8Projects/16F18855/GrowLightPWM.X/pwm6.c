#include "pwm6.h"

void PWM6_Initialize(void)
{
    PWM6CON             = 0x80;         // Pg 287, PWM6POL active_hi; PWM6EN enabled;
     
    PWM6DCH             = 0x00;         //0x3C;                     // Pg 288, Duty Cycle High 60; 
     
    PWM6DCL             = 0x00;         //0x40;                     // Pg 288, Duty Cycle Low 1;
     
    CCPTMRS1bits.P6TSEL = 0x1;          //Pg 456, PWM6 Timer Selection 0X1 = TMR2
}

void PWM6_LoadDutyValue(uint16_t dutyCycle)
{
    PWM6DCH = (dutyCycle & 0x03FC)>>2;  // Writing to 8 MSBs of PWM duty cycle in PWMDCH register (Duty Cycle High))
    
    PWM6DCL = (dutyCycle & 0x0003)<<6;  // Writing to 2 LSBs of PWM duty cycle in PWMDCL register (Duty Cycle Low))
}
