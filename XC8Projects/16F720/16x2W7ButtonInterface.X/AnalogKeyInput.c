#include "AnalogKeyInput.h"

int MenuKey;

char MenuRead()                     // Saved 114 bytes writing like this, rather than what is commented out below
{
    MenuKey = ADCRead(1);
    
    if (MenuKey < 500)
    {
        return(KEY_NONE);
    }
    
    else if(MenuKey < 1100)
    {
        return(KEY_RIGHT);
    }
    
    else if(MenuKey < 1450)
    {
        return(KEY_LEFT);
    }
            
    else if(MenuKey < 1880)
    {
        return(KEY_ENTER);
    }
        
    else if(MenuKey < 2375)
    {
        return(KEY_UP);
    }
        
    else if(MenuKey < 3115)
    {
        return(KEY_DOWN);
    }
        
    else if(MenuKey < 3835)
    {
        return(KEY_MENU);
    }
/*        
    else if(MenuKey >= 3835)
    {
        return(KEY_CANCEL);
    }
*/    
    else
    {
    return (KEY_NONE);              // If all else fails ...
    }
}
    
/*    if (MenuKey >= 0 && MenuKey < 500)
    {
        result = KEY_NONE;
    }
    else
        if(MenuKey >= 500 && MenuKey < 1100)
        {
            result = KEY_RIGHT;
        }
    
        else
        if(MenuKey >= 1100 && MenuKey < 1450)
        {
            result = KEY_LEFT;
        }
            
        else
        if(MenuKey >= 1450 && MenuKey < 1880)
        {
            result = KEY_ENTER;
        }
        
        else
        if(MenuKey >= 1880 && MenuKey < 2375)
        {
            result = KEY_UP;
        }
        
        else
        if(MenuKey >= 2375 && MenuKey < 3115)
        {
            result = KEY_DOWN;
        }
        
        else
        if(MenuKey >= 3115 && MenuKey < 3835)
        {
            result = KEY_MENU;
        }
        
        else
        if(MenuKey >= 3835 && MenuKey < 4095)
        {
            result = KEY_CANCEL;
        }
   
    return (result);
}*/


