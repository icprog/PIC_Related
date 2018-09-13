#include    "system.h"
#include    "buttons.h"

int16_t         readButtons     =   0;
uint8_t         button          =   None;
uint8_t         lastButton      =   None;
int8_t          j               =   0;

uint8_t readButton(void)
{
    readButtons = ADCRead(11);                           // Read AN7 (_RC1) Value to determine which button is pushed Pin 26
    
    if(readButtons >= 365 && readButtons < 405)
    {
        button = Enter;                                 // Enter Button has been pressed
    }
    
    else if(readButtons >= 535 && readButtons < 590)
    {
        button = Down;                                  // Down Button has been pressed
    }
    
    else if(readButtons > 745)
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
                return (lastButton);            // and return the value of that button
            }
                
            if (j >10)                          // If button has been pressed for an additional 50 program cycles,
            {
                __delay_ms(25);                 // return the key every program cycle, with a delay between Key presses if Key is held down
                j = 10;
                return (lastButton);
            }
        }
        goto end;
    }
    
    j = 0;
    
    end:

    return (None);
}