#include "system.h"

void main(void)
{
    SYSTEM_Initialize();                        // initialize the device

    INTERRUPT_GlobalInterruptEnable();          // Enable the Global Interrupts

    INTERRUPT_PeripheralInterruptEnable();      // Enable the Peripheral Interrupts

    while (1)
    {
        LCD_Write_String("FUCK!!");
        CLRWDT();
    }
}