#include "AnalogKeyInput.h"

int MenuKey = 0;
char lastKeyState = KEY_NONE, key = KEY_NONE, i;

char MenuRead()
{
    for(i=0;i<2;i++)
    {
        MenuKey = ADCRead(1);
    
        if (MenuKey < 500)
        {
            key = KEY_NONE;
        }
    
        else if(MenuKey < 1100)
        {
            key = KEY_RIGHT;
        }
    
        else if(MenuKey < 1450)
        {
            key = KEY_LEFT;
        }
            
        else if(MenuKey < 1880)
        {
            key = KEY_ENTER;
        }
        
        else if(MenuKey < 2375)
        {
            key = KEY_UP;
        }
        
        else if(MenuKey < 3115)
        {
            key = KEY_DOWN;
        }
        
        else if(MenuKey < 3835)
        {
            key = KEY_MENU;
        }
    
        if (key != KEY_NONE)
        {
            if (key != lastKeyState)
            {
                lastKeyState = key;
            }
            else
            {
                __delay_ms(100);                     // Delay between Key presses if Key is held down
                return (lastKeyState);
            }
        }
    }
    return (KEY_NONE);                              // If all else fails ...
}