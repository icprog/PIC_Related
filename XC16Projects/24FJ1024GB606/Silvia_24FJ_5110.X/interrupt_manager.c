#include "interrupt_manager.h"

void INTERRUPT_Initialize (void)
{
    INTCON2bits.GIE = 1;
    
    IFS2bits.OC5IF = 0;
    IEC2bits.OC5IE = 1;
    
    IFS2bits.OC6IF = 0;
    IEC2bits.OC6IE = 1;
}


void __attribute__((__interrupt__,no_auto_psv)) _OC6Interrupt(void)
{
//    OC6CON2bits.OCTRIG =    1;                      
  //  OC6CON2bits.TRIGSTAT = 0;
    
    IFS2bits.OC6IF = 0;
}