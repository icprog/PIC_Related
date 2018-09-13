#include    "system.h"
#include    "buttons.h"

uint16_t    readButtons =   0;
int8_t      button      =   0;

char readButton(void)
{
    readButtons = ADC_Read(0);
    
    if(readButtons > 400 && readButtons < 500)
    {
        button = 1;
    }
    
    else if(readButtons > 500 && readButtons < 600)
    {
        button = 2;
    }
    
    else if(readButtons > 700 && readButtons < 800)
    {
        button = 3;
    }
    
    else if(readButtons > 900)
    {
        button = 4;
    }
    
    else
    {
        button = 0;
    }
    return (button);
}