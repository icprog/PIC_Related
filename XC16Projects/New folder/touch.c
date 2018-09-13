#include "touch.h"

// ***************************************************************************************************************************************************************
    char col = 0, row = 0;                                  // these can be moved local to the function once testing is done
    int x, y;                                               // these too, as well as delete all 4 externs in main
    int lastKeyState = KEY_NONE, key = KEY_NONE, j, k, L;
    extern char call;                                       //call is used to set HMI delay time, based on what function you are in 

// ***************************************************************************************************************************************************************

char menuRead()
{
    _CN31PDE = 1;                   //Enable Weak-Pull-Downs on Analog port pin, as Pull downs can't be enabled when pin is switched to a OP
    TRISCbits.TRISC1 = 1;           //Set x+ to an Input
    TRISCbits.TRISC2 = 1;           //Set x- to an Input
    TRISBbits.TRISB9 = 0;           //Set y+ to an Output
    TRISAbits.TRISA8 = 0;           //Set y- to an output
    LATBbits.LATB9 = 1;             //Set y+ to +5V
    LATAbits.LATA8 = 0;             //Set y- to 0V
    x = ADCRead(7);                 //Read ADC value of x+
    LATBbits.LATB9 = 0;             //Set y+ to 0V
    _CN31PDE = 0;                   //Disable Weak-Pull-Downs on Analog port pin
 
    _CN21PDE = 1;                   //Enable Weak-Pull-Downs on Analog port pin
    TRISBbits.TRISB9 = 1;           //Set y+ to an Input
    TRISAbits.TRISA8 = 1;           //Set y- to an Input
    TRISCbits.TRISC1 = 0;           //Set x+ to an Output
    TRISCbits.TRISC2 = 0;           //Set x- to an Output
    LATCbits.LATC1 = 1;             //Set x+ to +5V
    LATCbits.LATC2 = 0;             //Set x- to 0V
    y = ADCRead(21);                //Read ADC value of x+
    LATCbits.LATC1 = 0;             //Set y+ to 0V
    _CN21PDE = 0;                   //Disable Weak-Pull-Downs on Analog port pin, as Pull downs can't be enabled when pin is switched to a OP
 // ***************************************************************************************************************************************************************
       
    if(x < 220 || y < 220)
    {
        key = KEY_NONE;
        j = 0;
    }
    
    if(x >= 220 && x <1075)
    {
        col = 1;
    }
    else if(x >= 1075 && x < 1990)
    {
        col = 2;
    }
    else if(x >= 1990)
    {
        col = 3;
    }
    else
    {
        col = 0;
    }
    
    if(y >= 220 && y <1000)
    {
        row = 1;
    }
    else if(y >= 1000 && y < 2000)
    {
        row = 2;
    }
    else if(y >= 2000)
    {
        row = 3;
    }
    else
    {
        row = 0;
    }
// ***************************************************************************************************************************************************************
    
    if(col == 1)
    {
        if(row == 1)
        {
            key = KEY_START_STOP;
        }
        else if(row == 2)
        {
            key = KEY_LEFT;
        }
        else if(row == 3)
        {
            key = KEY_RESET;
        }
        else 
        {
            key = KEY_NONE;
            j = 0;
        }
    }
    
    else if(col == 2)
    {
        if(row == 1)
        {
            key = KEY_DOWN;
        }
        else if(row == 2)
        {
            key = KEY_ENTER;
        }
        else if(row == 3)
        {
            key = KEY_UP;
        }
        else 
        {
            key = KEY_NONE;
        }
    }

    else if(col == 3)
    {
        if(row == 1)
        {
            key = KEY_MENU;
        }
        else if(row == 2)
        {
            key = KEY_RIGHT;
        }
        else if(row == 3)
        {
            key = KEY_SET_TIME;
        }
        else 
        {
            key = KEY_NONE;
        }
    }
    
    else
    {
        key = KEY_NONE;
    }
// ***************************************************************************************************************************************************************
    if (key != KEY_NONE)
    {
        if (call != 0)
        {
            k = 15;
            L = 25;
        }
        
        else
        {
            k = 250;
            L = 250;
        }
        
        
        if (lastKeyState != key)
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
            
            else if(j >1 && j <= k)
            {
                return (KEY_NONE);
            }
                
            else if(j > k)                                   //If button has been pressed for an additional 30 program cycles,
            {
                __delay_ms(L);                     //return the key every program cycle, with a delay between Key presses if Key is held down
                return (lastKeyState);
            }
            
            else
            {
                return(KEY_NONE);
            }
        }
    }
    j = 0;
    return (KEY_NONE);                                  // If all else fails ...
}