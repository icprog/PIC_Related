#include "AnalogKeyInput.h"
// ***************************************************************************************************************************************************************
int MenuKey = 0;
char lastKeyState = KEY_NONE, key = KEY_NONE, i, j;
// ***************************************************************************************************************************************************************
char MenuRead()
{
    for(i=0;i<2;i++)
    {
        MenuKey = ADCRead(1);
    
        if (MenuKey < 500)
        {
            key = KEY_NONE;
            j = 0;
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
            else                                        //Button (key) has been in the pressed state for 2 program cycles, so,
            {
                j += 1;                                 //increment the "button pressed" counter,
                if(j == 1)
                {
                    return (lastKeyState);              //and return the value of that button
                }
                
                if (j >15)                              //If button has been pressed for an additional 15 program cycles,
                {
                    __delay_ms(50);                     //return the key every program cycle, with a delay between Key presses if Key is held down
                    return (lastKeyState);
                }
            }
        }
    }
    return (KEY_NONE);                              // If all else fails ...
    j = 0;
}
