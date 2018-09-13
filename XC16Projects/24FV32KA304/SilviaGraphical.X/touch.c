
#include "touch.h"
#include "adc.h"                                    // Included to use ADC functionality

#define cycleDelay          50

#define xPos_In             TRISAbits.TRISA2        // pin 1 on connector Note, Either xPos or xNeg must be an Analog in as well
#define xNeg_In             TRISAbits.TRISA9        // pin 2 on connector
#define yPos_In             TRISAbits.TRISA3        // pin 3 on connector Note, Either yPos or yNeg must be an Analog in as well
#define yNeg_In             TRISAbits.TRISA11       // pin 4 on connector
#define xPos_Out            LATAbits.LATA2
#define xNeg_Out            LATAbits.LATA9
#define yPos_Out            LATAbits.LATA3
#define yNeg_Out            LATAbits.LATA11
#define colume1             1250
#define colume2             2100


// ***************************************************************************************************************************************************************

char menuRead()
{
    static uint8_t KeyState, key, j;
    char col = 0;                            
    int x;                                               

    _CN34PDE = 1;       //Enable Weak-Pull-Downs on Analog port pin, as Pull downs can't be enabled when pin is switched to a OP
    xPos_In = 1;        //Set x+ to an Input
    xNeg_In = 1;        //Set x- to an Input
    yPos_In = 0;        //Set y+ to an Output
    yNeg_In = 0;        //Set y- to an output
    yPos_Out = 1;       //Set y+ to +5V
    yNeg_Out = 0;       //Set y- to 0V
    x = ADCRead(13);    //Read ADC value of x+
    yPos_Out = 0;       //Set y+ to 0V
    _CN34PDE = 0;       //Disable Weak-Pull-Downs on Analog port pin, Enable Weak-Pull-Downs on Analog port pin _CN30PDE is Change Notification 21, Weak Pull Down Enable

    // ***************************************************************************************************************************************************************
       
    if(x < 220)     // || y < 220)
    {
        key = KEY_NONE;
        j = 0;
    }
    
    if(x >= 220 && x <colume1)
    {
        col = 1;
    }
    else if(x >= colume1 && x < colume2)
    {
        col = 2;
    }
    else if(x >= colume2)
    {
        col = 3;
    }
    else
    {
        col = 0;
    }
// ***************************************************************************************************************************************************************
    
    if(col == 1)
    {
        key = KEY_1;
    }
    else if(col == 2)
    {
        key = KEY_2;
    }
    else if(col == 3)
    {
        key = KEY_3;
    }
    else
    {
        key = KEY_NONE;
        j = 0;
    }

// ***************************************************************************************************************************************************************

    if (key != KEY_NONE)
    {
        __delay_us(2);
        
        KeyState = key;

        j += 1;                                             //increment the "button pressed" counter,
            
        if(j == 1)
        {
            return (KeyState);                              //and return the value of that button
            goto end;
        }
            
        else if(j >1 && j <= cycleDelay)
        {
            return (4);
            __delay_ms(20);
            goto end;
        }
             
        else if(j > cycleDelay)                             //If button has been pressed for an additional 30 program cycles,
        {
            __delay_ms(50);                                //return the key every program cycle, with a delay between Key presses if Key is held down
            return (KeyState);
            goto end;
        }
            
        else
        {
            return(KEY_NONE);
        }
    }

//    j = 0;
    return (KEY_NONE);                                      // If all else fails ...
    end:;
}
