#include    "system.h"
#include    "buttons.h"

uint16_t    readButtons =   0;
int8_t      button      =   0;
int8_t      lastButton  =   0;
int8_t      j           =   0;

char readButton(void)
{
    readButtons = ADCRead(6);                           // Read AN6 (_RB6) Value to determine which button is pushed
    
    if(readButtons > 1900 && readButtons < 2050)
    {
        button = Menu;                                  // Menu Button has been pressed
    }
    
    else if(readButtons > 2250 && readButtons < 2460)
    {
        button = Enter;                                 // Enter Button has been pressed
    }
    
    else if(readButtons > 2900 && readButtons < 3100)
    {
        button = Down;                                  // Down Button has been pressed
    }
    
    else if(readButtons > 3900)
    {
        button = Up;                                    // Up Button has been pressed
    }
    
    else
    {
        button = None;                                  // No Button has been pressed
    }
    
    if (button != None)
    {
        if (button != lastButton)
        {
            lastButton = button;
            j = 0;
        }
        else                                            // Button (key) has been in the pressed state for 2 program cycles, so,
        {
            j += 1;                                     // increment the "button pressed" counter,
        
            if(j == 1)
            {
                return (lastButton);                    // and return the value of that button
            }
                
            if (j >50)                                 // If button has been pressed for an additional 50 program cycles,
            {
                __delay_ms(250);                        // return the key every program cycle, with a delay between Key presses if Key is held down
                return (lastButton);
                j = 50;
            }
        }
        goto end;
    }
    
    j = 0;
    
    end:

    return (None);
}