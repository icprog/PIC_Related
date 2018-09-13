#include "pwm.h"

void PWM_Initialize(void)
{
    PWM6CON                 = 0x80;         // Pg 287, PWM6POL active_hi; PWM6EN enabled;
     
    PWM6DCH                 = 0x00;         //0x3C;                     // Pg 288, Duty Cycle High 60; 
     
    PWM6DCL                 = 0x00;         //0x40;                     // Pg 288, Duty Cycle Low 1;
         
    CCPTMRS1bits.P6TSEL     = 0x01;          //Pg 456, PWM6 Timer Selection 0X1 = TMR2


    PWM7CON                 = 0x80;         // Pg 287, PWM7POL active_hi; PWM7EN enabled;
     
    PWM7DCH                 = 0x00;         //0x3C;                     // Pg 288, Duty Cycle High 60; 
     
    PWM7DCL                 = 0x00;         //0x40;                     // Pg 288, Duty Cycle Low 1;
     
    CCPTMRS1bits.P7TSEL     = 0x02;         //Pg 456, PWM7 Timer Selection 0X2 = TMR4

    
//    CCP1CONbits.CCP1EN      = 1;            // Enable CCP1 Module
  //  CCP1CONbits.CCP1FMT     = 1;            // Left handed Alignment(8 bits in CCPR1H and 2 bits in CCPR1L, to match up with PWM6 & PWM7) 
    //CCP1CONbits.CCP1MODE    = 0xF;          // PWM Mode
//    CCPTMRS0bits.C1TSEL     = 0x1;          // PWM Based on Timer2
}


void PWM6_LoadDutyValue(uint16_t dutyCycle6)
{
    PWM6DCH = (dutyCycle6 & 0x03FC)>>2;  // Writing to 8 MSBs of PWM duty cycle in PWMDCH register (Duty Cycle High))
    
    PWM6DCL = (dutyCycle6 & 0x0003)<<6;  // Writing to 2 LSBs of PWM duty cycle in PWMDCL register (Duty Cycle Low))
}

void PWM7_LoadDutyValue(uint16_t dutyCycle7)
{
    PWM7DCH = (dutyCycle7 & 0x03FC)>>2;  // Writing to 8 MSBs of PWM duty cycle in PWMDCH register (Duty Cycle High))
    
    PWM7DCL = (dutyCycle7 & 0x0003)<<6;  // Writing to 2 LSBs of PWM duty cycle in PWMDCL register (Duty Cycle Low))
}

/*void PWM1_LoadDutyValue(uint16_t dutyCycle1)
{
    CCPR1H = (dutyCycle1& 0x03FC)>>2;
    CCPR1L = (dutyCycle1 & 0x0003)<<6;  // Writing to 2 LSBs of PWM duty cycle in CCPR1L register (Duty Cycle Low))
}
*/