#include "interrupt_manager.h"

void interrupt INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.PEIE == 1 && PIE2bits.ZCDIE == 1 && PIR2bits.ZCDIF == 1)
    {
        ZCD_ISR();
    }
    else
    {
        ;
    }
}