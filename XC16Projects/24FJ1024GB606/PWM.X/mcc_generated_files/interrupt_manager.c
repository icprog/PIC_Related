#include <xc.h>

void INTERRUPT_Initialize (void)
{
    //    TI: T2 - Timer2
    //    Priority: 1
        IPC1bits.T2IP = 1;

}
