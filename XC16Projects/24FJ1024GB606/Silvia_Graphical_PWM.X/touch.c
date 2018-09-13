#include "touch.h"
#include "system.h"

#define xPos_TRIS           TRISBbits.TRISB15       // pin 1 on connector Note, Either xPos or xNeg must be an Analog in as well
#define xNeg_TRIS           TRISFbits.TRISF4        // pin 3 on connector
#define yNeg_TRIS           TRISFbits.TRISF5        // pin 2 on connector
#define yPos_TRIS           TRISBbits.TRISB14       // pin 4 on connector Note, Either yPos or yNeg must be an Analog in as well

#define xPos_Out            LATBbits.LATB15
#define xNeg_Out            LATFbits.LATF4
#define yNeg_Out            LATFbits.LATF5
#define yPos_Out            LATBbits.LATB14

#define col_1_min           300                     //minimum value (read on ADC) to define colume 1 boundary
#define col_1_max           1300                    //maximum value (read on ADC) to define colume 1 boundary
#define col_2_min           1400                    //minimum value (read on ADC) to define colume 2 boundary
#define col_2_max           2450                    //maximum value (read on ADC) to define colume 2 boundary
#define col_3_min           2550                    //minimum value (read on ADC) to define colume 3 boundary
#define row_1_min           300                     //minimum value (read on ADC) to define row 1 boundary
#define row_1_max           1400                    //maximum value (read on ADC) to define row 1 boundary
#define row_2_min           1600                    //minimum value (read on ADC) to define row 2 boundary
#define row_2_max           2500                    //maximum value (read on ADC) to define row 2 boundary
#define row_3_min           2600                    //minimum value (read on ADC) to define row 3 boundary
#define row_3_max           3300                    //maximum value (read on ADC) to define row 3 boundary

// ***************************************************************************************************************************************************************
extern uint8_t call;

uint8_t menuRead()
{
    static uint8_t lastKeyState = KEY_NONE, key = KEY_NONE, j, k, L;
    uint8_t col = 0;    //, row = 0;                            
    uint16_t x,y;                                               

    xPos_TRIS           = 1;    //Set x+ to an Input, we are going to read y coordinates
    xNeg_TRIS           = 1;    //Set x- to an Input
    IOCPDFbits.IOCPDF4  = 1;    //Enable Weak-Pull-Downs on Analog port pin, as Pull downs can't be enabled when pin is switched to a OP
    yPos_TRIS           = 0;    //Set y+ to an Output
    yNeg_TRIS           = 0;    //Set y_ to an Output
    yPos_Out = 0;               //Set y+ to 0V
    yNeg_Out = 1;               //Set y_ to +3.3V (changing whether Neg or Pos is higher voltage, changes orientation of touch screen)
    y = ADCRead(15);            //Read ADC value of x+
    yPos_Out = 0;               //Set y+ to 0V
    IOCPDFbits.IOCPDF4  = 0;    //Disable Weak-Pull-Downs on Analog port pin

    yPos_TRIS           = 1;    //Set y+ to an Input
    yNeg_TRIS           = 1;    //Set y- to an Input
    IOCPDFbits.IOCPDF5  = 1;    //Enable Weak-Pull-Downs on Analog port pin (keeps pin from floating, resulting in a center touch reading)
    xPos_TRIS           = 0;    //Set x+ to an Output
    xNeg_TRIS           = 0;    //Set x- to an Output
    xPos_Out            = 1;    //Set x+ to +3.3V
    xNeg_Out            = 0;    //Set x- to 0V
    x = ADCRead(14);            //Read ADC value of y+
    xPos_Out            = 0;    //Set x+ to 0V
    IOCPDFbits.IOCPDF5  = 0;    //Disable Weak-Pull-Downs on Analog port pin, as Pull downs can't be enabled when pin is switched to a OP

    // ***************************************************************************************************************************************************************
       
    if(x < col_1_min)
    {
        key = KEY_NONE;
        j = 0;
    }
    
    if(x >= col_1_min && x < col_1_max && y < row_1_max)
    {
        col = 1;
    }
    else if(x >= col_2_min && x < col_2_max && y < row_1_max)
    {
        col = 2;
    }
    else if(x >= col_3_min && y < row_1_max)
    {
        col = 3;
    }
    else
    {
        col = 0;
    }
    
     
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
    else if(y > row_2_min)
    {
        key = KEY_4;
    }
    else
    {
        key = KEY_NONE;
        j = 0;
    }

// ***************************************************************************************************************************************************************

    if (key != KEY_NONE)
    {
        if (call != 0)
        {
            k = 25;
            L = 250;
        }
        
        else

        k = 250;
        L = 150;
        
        
        if (lastKeyState != key)
        {
            lastKeyState = key;
        }
        else                                        //Button (key) has been in the pressed state for 2 program cycles, so,
        {
            j += 1;                                 //increment the "button pressed" counter,
            
            if(j == 2)
            {
                return (lastKeyState);              //and return the value of that button
            }
            
            else if(j >2 && j <= k)
            {
                return (KEY_NONE);
            }
                
            else if(j > k)                          //If button has is still pressed for an additional "k" program cycles,
            {
                __delay_ms(L);                      //return the key every program cycle, with a delay between Key presses if Key is held down
                return (lastKeyState);
            }
            
            else
            {
                return(KEY_NONE);
            }
        }
    }
    j = 0;
    return (KEY_NONE);                              // If all else fails ...
}