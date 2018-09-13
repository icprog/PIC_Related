#include "system.h"
#include "menu.h"

int main(void)
{
    SYSTEM_Initialize();                        // initialize the device

    while (1)
    {
        loadimg(&menu2[0], 1024,0);                     //Draw Menu2
        __delay_ms(750);
       LCDWriteStringXY(3,6,"Please Set");
        LCDWriteStringXY(3,17,"the Time!");
        _RF3 = 1;
        __delay_ms(1000);
        _RF3 = 0;
        __delay_ms(1000);
    }

    return -1;
}