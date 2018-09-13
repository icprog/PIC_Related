#include "pwm.h"
//#include <p24F16KA102.h>

void InitializeTimer2For_PWM(void)
{
    T2CONbits.TON = 0;      /*  Timer2 is used for generating PWM frequency */
    T2CONbits.TCS = 0;
    T2CONbits.TGATE = 0;
    T2CONbits.TCKPS = 0b00;
    TMR2 = 0x00;
    PR2 = 0x0FFF;           // FOR 488 Hz
    T2CONbits.TON = 1;      // TIMER 2 ON

}

/******************************************************************************/

void Initialize_PWM(void)
{
    // ENFLT0 disabled; ENFLT1 disabled; OCFLT2 disabled; ENFLT2 disabled; OCSIDL disabled; OCM Single Compare Continuous Pulse mode; OCFLT1 disabled; OCFLT0 disabled; OCTSEL TMR2; TRIGMODE Only Software; 
//    OC3CON1 = 0x0003;
    // SYNCSEL TMR2; TRIGSTAT disabled; DCB Start of instruction cycle; OCMPINV disabled; OCTRIG Sync; OC32 disabled; FLTOUT disabled; OCTRIS disabled; FLTMD Cycle; FLTTRIEN disabled; 
//    OC3CON2 = 0x000C;
    // OC3RS 0; 
    OC3R = 0x000F;
    OC3RS = 0x0FFF;
    // OC3R 255; 
//    OC3R = 0x00FF;
    OC3CON2bits.SYNCSEL = 0X1F;
    
    OC3CON2bits.OCTRIG = 0;
    OC3CON1bits.OCTSEL = 0;
    // OC3TMR 0; 
    OC3TMR = 0x0000;
    OC3CON1bits.OCM = 0b110;


//    OC3CON1bits.OCM = 0b000; /*  clearing OCM bits   */
  //  OC3R = 0x0F;
    //OC3RS = 0x0F;           /*  starting module with min PWM    */
//    OC3CON1bits.OCTSEL = 0;
  //  OC3R = 0x0F;
    //OC3CON1bits.OCM = 0b110;

}

/******************************************************************************/

void SetDutyCycle_PWM(unsigned int DutyCycle)
{
    OC3R = DutyCycle;  /*  with 488Hz frequency we have 15bits resolution   */
    
}

/******************************************************************************/
