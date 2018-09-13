#include "user.h"
#include "lcd.h"

//#define HeartBeatLED        _LATA1

uint8_t  halfSec, lastState, toggle = 2;

extern uint8_t mainTimer;

extern char call;

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
            LCD_Write_Char(toggle);                                                  //Display HeartBeat Symbol Open Heart
//            HeartBeatLED = 1 - HeartBeatLED;
            mainTimer += 1;;                                                    //Increment the OutState Counter
        }
    }
    lastState = halfSec;                //And set them equal to each other, so, it doesn't count again next time through
}
// ***************************************************************************************************************************************************************
int TempCalc(int a)
{
    if(a < 819)
    {
        return 499;
    }
    else
    {
//    return ((a - 819)/3.276 - 500);       // - 500 for -50.0 to 50.0 Range
    return ((a - 819)/6.552);               // Range of 0.0 to 50.0 C
    }
}
// ***************************************************************************************************************************************************************
int TempSetpoint(int b)
{
    call = 1;
    
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
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteStringXY(1,0,"Setpoint = ");
        LCDWriteDecIntXY(1,11,result,3);

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
unsigned char SetDeadband(unsigned char b)
{
    call = 1;
    
    unsigned char result = b, TestKey = 9;

    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        
        LCDWriteStringXY(3,0,"DeadBand = ");
        LCDWriteDecIntXY(3,11,result,2);

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
signed char SetBiasNeg15(signed char b)
{
    call = 1;
    
    signed char result = b;
    
    char TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 500)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }

        LCDWriteStringXY(1,0,"-15 Bias = ");
        LCDWriteDecIntXY(1,11,result,2);

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
signed char SetBiasNeg25(signed char b)
{
    call = 1;
    
    signed char result = b;
    
    char TestKey;
    
    TestKey = menuRead();
    
    while(TestKey != KEY_ENTER)
    {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 500)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteStringXY(3,0,"-25 Bias = ");
        LCDWriteDecIntXY(3,11,result,2);

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
bool SetOutput(bool Out, int SetPoint, signed char Bias, int ProcessVariable, unsigned char Deadband)
{
    if (ProcessVariable <= SetPoint + Bias)                                     //Turn on Output if PV < SP + Bias.
        return 1;
    else
    if (ProcessVariable >= SetPoint + Bias + Deadband)                          //Turn off Output if PV >= SP + Bias + Deadband
        return 0;
    else
        return Out;                                                             //All other cases, leave it as it was.
    
}
//***************************************************************************************************************************************************************