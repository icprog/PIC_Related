#include "AnalogKeyInput.h"
#include "user.h"                   // Included to use ADC functionality
#include "adc.h"
// ***************************************************************************************************************************************************************
int keyState = 0;
char lastSwitchState = SWITCH_NONE, inputSwitch = SWITCH_NONE, i;
// ***************************************************************************************************************************************************************
char switchStateRead()
{
    for(i=0;i<2;i++)
    {
        keyState = ADCRead(4);
    
        if (keyState < 1000)
        {
            inputSwitch = SWITCH_NONE;
        }
    
        else if(keyState < 1500)
        {
            inputSwitch = SWITCH_STEAM_SWITCH;
        }
    
        else if(keyState < 1850)
        {
            inputSwitch = SWITCH_BREW_SWITCH;
        }
            
        else if(keyState < 2200)
        {
            inputSwitch = SWITCH_WATER_SWITCH;
        }
        
/*        else if(keyState < 2375)
        {
            inputSwitch = KEY_UP;
        }
        
        else if(keyState < 3115)
        {
            inputSwitch = KEY_DOWN;
        }
        
        else if(keyState < 3835)
        {
            inputSwitch = KEY_MENU;
        }
        
        else if(keyState < 4093)
        {
            inputSwitch = KEY_CANCEL;
        }
*/    
        if (inputSwitch != SWITCH_NONE)
        {
            if (inputSwitch != lastSwitchState)
            {
                lastSwitchState = inputSwitch;
            }
            else
            {
//                __delay_ms(15);                     // Delay between Key presses if Key is held down (remove if using to read switches, only use if reading menu Keys)
                return (lastSwitchState);
            }
        }
    }
    return (SWITCH_NONE);                              // If all else fails ...
}