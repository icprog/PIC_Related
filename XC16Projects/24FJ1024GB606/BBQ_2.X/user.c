#include    "user.h"

extern uint8_t call;

int timer = 0;              // level = 0;

// ***************************************************************************************************************************************************************
                    
                    // <editor-fold defaultstate="collapsed" desc="Temperature Calculation">

int TempCalc(int a)
{
    if(a < 819)
    {
        return a;
    }
    else
    {
//    return ((a - 819)/3.276 - 500);       // - 500 for -50.0 to 50.0 Range
//    return ((a - 819)/6.552);               // Range of 0.0 to 50.0 C
    return (a);               
    }
}
// </editor-fold>

// ***************************************************************************************************************************************************************
                    
                    // <editor-fold defaultstate="collapsed" desc="PID Parameter Setting">


int16_t setParameter(int8_t X, int8_t Y, int16_t min, int16_t max, int16_t b)
{
    call = 1;
    
    int16_t result = b;
    
    int8_t TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);                 // 30 mS delay to extend dead time to 150mS x number of timer counts below, before auto-exit of function
                    
        if(timer > 1000)                // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            cls();
            timer = 0;
            TestKey = KEY_3;
        }
        
        LCDWriteIntXY(X,Y,result,4,1);
        
        switch(TestKey)
        {
        case KEY_1:
        {
            result -=1;
                           
            if (result <= min)
                {
                    result = min;
                }
            }
        break;
            
                        
        case KEY_2:
        {
            result += 1;
                           
            if(result >= max)
                {
                    result = max;
                }
            }
        break;
        }
    }
        
    timer = 0;
        
    call = 0;
    
    return (result);
}

// </editor-fold>

// ***************************************************************************************************************************************************************

                    // <editor-fold defaultstate="collapsed" desc="Currently Un-Used Junk">

/*void heartBeat(void)
{
    halfSec = RCFGCALbits.HALFSEC;
    
    
    if (halfSec == 0)                                                           //If halfSec is 0
    {
        if (halfSec != lastState)                                               //If halfSec changed since last read
        {
            toggle = 3 - toggle;                                                //toggle = (a + b) - toggle, set toggle to either a or b, and it toggles between them
            GoToXY(3,19);
            LCDWriteChar(toggle);                                             //Display HeartBeat Symbol Open Heart
        }
    }
    lastState = halfSec;                                                        //And set them equal to each other, so, it doesn't count again next time through
}
 * */
// ***************************************************************************************************************************************************************
/*void levelCalc(void)
{
    level = ADCRead(10);
    
    level = level/195;
    
    switch(level)
    {
        case 4:
        {
            GoToXY(3,0);
            LCD_Write_Char(3);
            GoToXY(2,0);
            LCD_Write_Char(3);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 5:
        {
            GoToXY(3,0);
            LCD_Write_Char(4);
            GoToXY(2,0);
            LCD_Write_Char(3);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;

        case 6:
        {
            GoToXY(3,0);
            LCD_Write_Char(5);
            GoToXY(2,0);
            LCD_Write_Char(3);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 7:
        {
            GoToXY(3,0);
            LCD_Write_Char(6);
            GoToXY(2,0);
            LCD_Write_Char(3);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 8:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(3);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 9:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(4);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 10:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(5);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 11:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(6);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 12:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 13:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(4);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 14:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(5);
             GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 15:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(6);
             GoToXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 16:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(7);
             GoToXY(0,0);
            LCD_Write_Char(3);
       }
        break;
        
        case 17:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(7);
            GoToXY(0,0);
            LCD_Write_Char(4);
        }
        break;
        
        case 18:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(7);
            GoToXY(0,0);
            LCD_Write_Char(5);
        }
        break;
        
        case 19:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(7);
            GoToXY(0,0);
            LCD_Write_Char(6);
        }
        break;
        
        case 20:
        {
            GoToXY(3,0);
            LCD_Write_Char(7);
            GoToXY(2,0);
            LCD_Write_Char(7);
            GoToXY(1,0);
            LCD_Write_Char(7);
            GoToXY(0,0);
            LCD_Write_Char(7);
        }
        break;
        
        default:
        {
            GoToXY(3,0);
            LCD_Write_Char(3);
            GoToXY(2,0);
            LCD_Write_Char(3);
            GoToXY(1,0);
            LCD_Write_Char(3);
            GoToXY(0,0);
            LCD_Write_Char(3);
        }
    }
}
*/
// </editor-fold>

// ***************************************************************************************************************************************************************
