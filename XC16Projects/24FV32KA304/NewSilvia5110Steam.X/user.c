#include    "system.h"  
#include    "user.h"

int timer = 0;              // level = 0;

// ***************************************************************************************************************************************************************
int16_t setParameter(int8_t X, int8_t Y, int16_t min, int16_t max, int16_t b)
{
    int16_t result = b;
    
    int8_t testKey;
    
    testKey = readButton();
    
    while(testKey != Enter)
        {
        testKey = readButton();
        
        timer += 1;
        
        __delay_ms(10);                     // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 1000)                    // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
           LCDClear();
            timer = 0;
            testKey = None;
        }
        
        LCDWriteIntXY(X,Y,result,-1,1,0);
        
        switch(testKey)
        {
            case Down:
            {
                result -=1;
                            
                if (result <= min)
                    {
                        result = min;
                    }
                }
            break;
                        
            case Up:
            {
                result += 1;
                            
                if(result >= max)
                    {
                        result = max;
                    }
                }
            break;
            }
//        ClrWdt();                               // Clear (Re-Set) the WatchDog Timer
        }
        
        timer = 0;
    
    return (result);
}

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
            gotoXY(3,19);
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
            gotoXY(3,0);
            LCD_Write_Char(3);
            gotoXY(2,0);
            LCD_Write_Char(3);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 5:
        {
            gotoXY(3,0);
            LCD_Write_Char(4);
            gotoXY(2,0);
            LCD_Write_Char(3);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;

        case 6:
        {
            gotoXY(3,0);
            LCD_Write_Char(5);
            gotoXY(2,0);
            LCD_Write_Char(3);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 7:
        {
            gotoXY(3,0);
            LCD_Write_Char(6);
            gotoXY(2,0);
            LCD_Write_Char(3);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 8:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(3);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 9:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(4);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 10:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(5);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 11:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(6);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 12:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 13:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(4);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 14:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(5);
             gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 15:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(6);
             gotoXY(0,0);
            LCD_Write_Char(3);
        }
        break;
        
        case 16:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(7);
             gotoXY(0,0);
            LCD_Write_Char(3);
       }
        break;
        
        case 17:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(7);
            gotoXY(0,0);
            LCD_Write_Char(4);
        }
        break;
        
        case 18:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(7);
            gotoXY(0,0);
            LCD_Write_Char(5);
        }
        break;
        
        case 19:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(7);
            gotoXY(0,0);
            LCD_Write_Char(6);
        }
        break;
        
        case 20:
        {
            gotoXY(3,0);
            LCD_Write_Char(7);
            gotoXY(2,0);
            LCD_Write_Char(7);
            gotoXY(1,0);
            LCD_Write_Char(7);
            gotoXY(0,0);
            LCD_Write_Char(7);
        }
        break;
        
        default:
        {
            gotoXY(3,0);
            LCD_Write_Char(3);
            gotoXY(2,0);
            LCD_Write_Char(3);
            gotoXY(1,0);
            LCD_Write_Char(3);
            gotoXY(0,0);
            LCD_Write_Char(3);
        }
    }
}
*/
// </editor-fold>

// ***************************************************************************************************************************************************************
