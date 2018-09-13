#include    "user.h"
#include    "system.h"                      // Needed to calculate __delay_() Functions
#include    "touch.h"
#include    "glcd.h"

//uint8_t  halfSec, lastState, toggle = 2;

//extern char call;

int timer = 0;              // level = 0;

// ***************************************************************************************************************************************************************
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
// ***************************************************************************************************************************************************************
int setParameter(unsigned char x, unsigned char y,unsigned int min, unsigned int max, int b)
{
//    call = 1;
    
    int result = b;
    
    char TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(20);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            cls();
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteIntXY(x,y,result,4,1);
        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= min)
                    {
                        result = min;
                    }
                }
            break;
                        
            case KEY_UP:
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
        
//        call = 0;
    
    return (result);
}
// ***************************************************************************************************************************************************************
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
