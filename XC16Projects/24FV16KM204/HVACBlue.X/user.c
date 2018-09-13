#include "user.h"
#include "lcd.h"

uint8_t  halfSec, lastState, toggle = 2;

extern int8_t call;

unsigned int timer = 0;

// ***************************************************************************************************************************************************************
void heartBeat(void)
{
    halfSec = RCFGCALbits.HALFSEC;
    
    
    if (halfSec == 0)                                                           //If halfSec is 0
    {
        if (halfSec != lastState)                                               //If halfSec changed since last read
        {
            toggle = 3 - toggle;        //toggle = (a + b) - toggle, set toggle to either a or b, and it toggles between them
            LCD_Set_Cursor(3,19);
            LCD_Write_Char(toggle);                                             //Display HeartBeat Symbol Open Heart
        }
    }
    lastState = halfSec;                //And set them equal to each other, so, it doesn't count again next time through
}
// ***************************************************************************************************************************************************************
int TempCalc(int a)
{
    if(a < 800)
    {
        return 511;
    }
    else
    {
    return ((a - 819)/6.552);               // Range of 0.0 to 50.0 C for Second production board, Blue LED's
    }
}
// ***************************************************************************************************************************************************************
uint8_t SetStartEndMonth(int8_t b)
{
    call = 1;
    
    int8_t result = b, TestKey = 9;

    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 800)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        
        LCDWriteIntXY(1,10,result,2,0,0);

        heartBeat();
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 1;
                            
                if (result <= 1)
                {
                    result = 1;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 12)
                {
                    result = 12;
                }
            }
            break;
        }
    }
        
    TestKey = 9;                            // Ensure TestKey is set to KEY_NONE before exiting
        
    timer = 0;
        
    call = 0;
    
    return (result);
}
// ***************************************************************************************************************************************************************
uint8_t SetStartEndDay(int8_t b)
{
    call = 1;
    
    int8_t result = b, TestKey = 9;

    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 800)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        
        LCDWriteIntXY(3,10,result,2,0,0);

        heartBeat();
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 1;
                            
                if (result <= 1)
                {
                    result = 1;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 28)
                {
                    result = 28;
                }
            }
            break;
        }
    }
        
    TestKey = 9;                            // Ensure TestKey is set to KEY_NONE before exiting
        
    timer = 0;
        
    call = 0;
    
    return (result);
}
// ***************************************************************************************************************************************************************

int TempSetpoint(int b)
{
    call = 1;
    
    int result = b;
    
    int8_t TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(25);            // 25 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteStringXY(1,0,"Setpoint = ");
        LCDWriteIntXY(1,11,result,3,1,0);

        heartBeat();
        
        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 50)
                    {
                        result = 50;
                    }
                }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 350)
                    {
                        result = 350;
                    }
                }
            break;
            }
        }
        
        TestKey = 9;            // Ensure TestKey is set to KEY_NONE before exiting
        
        timer = 0;
        
        call = 0;
    
    return (result);
}
//***************************************************************************************************************************************************************
uint8_t SetDeadband(uint8_t b)
{
    call = 1;
    
    uint8_t result = b, TestKey = 9;

    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 800)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        
        LCDWriteStringXY(3,0,"DeadBand = ");
        LCDWriteIntXY(3,11,result,2,1,0);

        heartBeat();
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 1;
                            
                if (result <= 2)
                {
                    result = 2;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 50)
                {
                    result = 50;
                }
            }
            break;
        }
    }
        
    TestKey = 9;                            // Ensure TestKey is set to KEY_NONE before exiting
        
    timer = 0;
        
    call = 0;
    
    return (result);
}
//***************************************************************************************************************************************************************
int8_t SetBiasWarm(int8_t b)
{
    call = 1;
    
    int8_t result = b;
    
    int8_t TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 800)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }

        LCDWriteStringXY(1,0,"WarmBias= ");
        LCDWriteIntXY(1,11,result,2,1,1);
        
        heartBeat();

        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= -99)
                {
                    result = -99;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 0)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    TestKey = 9;            // Ensure TestKey is set to KEY_NONE before exiting
    
    timer = 0;
        
    call = 0;
    
    return (result);
}
//***************************************************************************************************************************************************************

int8_t SetBiasNeg5(int8_t b)
{
    call = 1;
    
    int8_t result = b;
    
    int8_t TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 800)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }

        LCDWriteStringXY(3,0,"-5 Bias = ");
        LCDWriteIntXY(3,11,result,2,1,0);

        heartBeat();

        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 0)
                {
                    result = 0;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 50)
                {
                    result = 50;
                }
            }
            break;
        }
    }
        
    TestKey = 9;            // Ensure TestKey is set to KEY_NONE before exiting
    
    timer = 0;
        
    call = 0;
    
    return (result);
}
//***************************************************************************************************************************************************************
int8_t SetBiasNeg15(int8_t b)
{
    call = 1;
    
    int8_t result = b;
    
    int8_t TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 800)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }

        LCDWriteStringXY(1,0,"-15 Bias = ");
        LCDWriteIntXY(1,11,result,2,1,0);

        heartBeat();

        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 0)
                {
                    result = 0;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 50)
                {
                    result = 50;
                }
            }
            break;
        }
    }
        
    TestKey = 9;            // Ensure TestKey is set to KEY_NONE before exiting
    
    timer = 0;
        
    call = 0;
    
    return (result);
}
//***************************************************************************************************************************************************************
int8_t SetBiasNeg25(int8_t b)
{
    call = 1;
    
    int8_t result = b;
    
    int8_t TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
    {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 800)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteStringXY(3,0,"-25 Bias = ");
        LCDWriteIntXY(3,11,result,2,1,0);

        heartBeat();

        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 0)
                {
                    result = 0;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 70)
                {
                    result = 70;
                }
            }
            break;
        }
    }
        
    TestKey = 9;                                                            // Ensure TestKey is set to KEY_NONE before exiting
    
    timer = 0;
    
    call = 0;
        
    return (result);
}
//***************************************************************************************************************************************************************
int8_t SetExtendedRunBit(int8_t b)
{
    call = 1;
    
    int8_t result = b;
    
    int8_t TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
    {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(30);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 800)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteStringXY(1,0,"Extended Run Bit");
        LCDWriteIntXY(1,18,result,1,0,0);

        heartBeat();

        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 0)
                {
                    result = 0;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 1)
                {
                    result = 1;
                }
            }
            break;
        }
    }
        
    TestKey = 9;                                                            // Ensure TestKey is set to KEY_NONE before exiting
    
    timer = 0;
    
    call = 0;
        
    return (result);
}
//***************************************************************************************************************************************************************
bool SetOutput(bool Out, int SetPoint, signed int Bias, int ProcessVariable, uint8_t Deadband)
{
    if (ProcessVariable <= SetPoint + Bias)                                     //Turn on Output if PV < SP + Bias.
        return 1;
    else if (ProcessVariable >= SetPoint + Bias + Deadband)                     //Turn off Output if PV >= SP + Bias + Deadband
        return 0;
    else
        return Out;                                                             //All other cases, leave it as it was.
    
}
