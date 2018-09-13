#include "start_stop_timer.h"
#include "glcd.h"


int const startHour[]   =   {40,42,44,46,48,50,52};

int const startMinute[] =   {54,56,58,60,62,64,66};

int const stopHour[]    =   {68,70,72,74,76,78,80};

int const stopMinute[]  =   {82,84,86,88,90,92,94};

signed char choice;

//unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!

char *dayOfWeek[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

unsigned char TestKey = KEY_NONE;

char sel = 0;
    
char done = 0;

extern char call;

//***************************************************************************************************************************************************************
char runTimer(int weekday, int hour, int minute)
{
    static char run;
    
    if(hour == eepromGetData(startHour[weekday]) && minute == eepromGetData(startMinute[weekday]))
    {
        run = 1;
    }
    
    if(hour == eepromGetData(stopHour[weekday]) && minute == eepromGetData(stopMinute[weekday]))
    {
        run = 0;
    }
    return run;
}
//***************************************************************************************************************************************************************
void writeStartStopTimes(void)
{
    unsigned int timer = 0;                                                     // Used to return to operation if user does not finish!
    
    TestKey = KEY_NONE;
    
    while(TestKey != KEY_ENTER)
    {
        TestKey = menuRead();
        
        if(timer > 500)
        {
            goto Exit;                                                 
        }

        switch(TestKey)
        {
             case KEY_UP:
             {
                choice -=1;
                            
                if (choice < 0)
                {
                    choice = 0;
                }
            }
            break;
            
            case KEY_DOWN:
            {
                choice += 1;
                            
                if(choice > 6)
                {
                    choice = 6;
                }
            }
            break;
                    
            case KEY_RESET:
            {
                cls();
                goto Exit;
            }
            break;
        }

        if(timer < 3)
        {
            cls();
        }

        GoToXY(0,1);
        LCDWriteString("Start/Stop for ");
        LCDWriteString(dayOfWeek[choice]);
        LCDWriteStringXY(2,0,"Up/Dn Keys to change");
        LCDWriteStringXY(3,0,"Enter Key for Yes   ");
                
        heartBeat();                                                            // HeartBeat displays the HeartBeat on the LCD,
                                                                                // but, also increments mainTimer every second
        timer += 1;
    }
    
    cls();
    eepromPutData(startHour[choice], setStartHour(eepromGetData(startHour[choice])));
    eepromPutData(startMinute[choice], setStartMinute(eepromGetData(startMinute[choice])));
    eepromPutData(stopHour[choice], setStopHour(eepromGetData(stopHour[choice])));
    eepromPutData(stopMinute[choice], setStopMinute(eepromGetData(stopMinute[choice])));

    Exit:
    cls();
    timer = 0;
}

//***************************************************************************************************************************************************************
char setStartHour(char b)
{
    call = 1;
    
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = KEY_NONE;

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
        
        
        LCDWriteStringXY(0,1,"Start Hour = ");
        LCDWriteIntXY(0,16,result,2);

        heartBeat();
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result > 23)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
        
    call = 0;
    
    return (result);
}


//***************************************************************************************************************************************************************
char setStartMinute(char b)
{
    call = 1;
    
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = KEY_NONE;

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
        
        
        LCDWriteStringXY(1,1,"Start Minute = ");
        LCDWriteIntXY(1,16,result,2);

        heartBeat();
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 5;
                            
                if(result > 55)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
        
    call = 0;
    
    return (result);
}

//***************************************************************************************************************************************************************
char setStopHour(char b)
{
    call = 1;
    
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = KEY_NONE;

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
        
        
        LCDWriteStringXY(2,1,"Stop Hour = ");
        LCDWriteIntXY(2,16,result,2);

        heartBeat();
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result > 23)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
        
    call = 0;
    
    return (result);
}


//***************************************************************************************************************************************************************
char setStopMinute(char b)
{
    call = 1;
    
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = KEY_NONE;

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
        
        
        LCDWriteStringXY(3,1,"Stop Minute = ");
        LCDWriteIntXY(3,16,result,2);

        heartBeat();
        

        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case KEY_UP:
            {
                result += 5;
                            
                if(result > 55)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
        
    call = 0;
    
    return (result);
}
//***************************************************************************************************************************************************************