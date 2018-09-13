#include "start_stop_timer.h"
#include "menu4.h"

int startHour[]   =   { 8, 6, 6, 6, 6, 6, 8};

int startMinute[] =   {45,45,45,45,45,45,45};

int stopHour[]    =   {11, 7, 7, 7, 7, 7,11};

int stopMinute[]  =   {00,25,25,25,25,25,00};

signed char choice;

extern char *WeekDay[7];

unsigned char TestKey = KEY_NONE;

//char sel = 0;
    
//char done = 0;

extern char call;

//***************************************************************************************************************************************************************

int8_t runTimer(int16_t weekday, int16_t hour, int16_t minute)
{
    static uint8_t run;
    
    if(hour == startHour[weekday] && minute == startMinute[weekday])
    {
        run = 1;
    }
    
    if(hour == stopHour[weekday] && minute == stopMinute[weekday])
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
    
    while(TestKey != KEY_3)
    {
        TestKey = menuRead();
        
        if(timer > 3500)
        {
            goto Exit;                                                 
        }

        switch(TestKey)
        {
             case KEY_1:
             {
                choice -=1;
                            
                if (choice < 0)
                {
                    choice = 0;
                }
            }
            break;
            
            case KEY_2:
            {
                choice += 1;
                            
                if(choice > 6)
                {
                    choice = 6;
                }
            }
            break;
                    
//            case KEY_RESET:
  //          {
    //            cls();
      //          goto Exit;
        //    }
          //  break;
        }

        if(timer < 3)
        {
            cls();
            loadimg(&menu4[0], 1024,0);                  //Draw Menu4
        }

//        loadimg(&menu4[0], 1024,0);                  //Draw Menu4
        
        LCDWriteStringXY(1,3,"Start/Stop fo");
        LCDWriteStringXY(1,16,"r ");
        LCDWriteString(WeekDay[choice]);
        LCDWriteStringXY(2,3,"Up/Dn Keys to");
        LCDWriteStringXY(2,17,"change.");
        LCDWriteStringXY(3,3,"Enter Key for");
        LCDWriteStringXY(3,17,"Yes");
                                                                                // but, also increments mainTimer every second
        timer += 1;
    }
    
    cls();
    loadimg(&menu4[0], 1024,0);                  //Draw Menu4
    startHour[choice] = setStartHour(startHour[choice]);
    startMinute[choice] = setStartMinute(startMinute[choice]);
    stopHour[choice] = setStopHour(stopHour[choice]);
    stopMinute[choice] = setStopMinute(stopMinute[choice]);

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
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_3;
        }
        
        
        LCDWriteStringXY(1,2,"Start Hour =");
        LCDWriteIntXY(1,16,result,2,0);

        switch(TestKey)
        {
            case KEY_1:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case KEY_2:
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
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_3;
        }
        
        
        LCDWriteStringXY(2,2,"Start Minute =");
        LCDWriteIntXY(2,16,result,2,0);


        switch(TestKey)
        {
            case KEY_1:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case KEY_2:
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
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_3;
        }
        
        
        LCDWriteStringXY(3,2,"Stop Hour =");
        LCDWriteIntXY(3,16,result,2,0);

//        heartBeat();
        

        switch(TestKey)
        {
            case KEY_1:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case KEY_2:
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
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_3;
        }
        
        
        LCDWriteStringXY(4,2,"Stop Minute =");
        LCDWriteIntXY(4,16,result,2,0);

//        heartBeat();
        

        switch(TestKey)
        {
            case KEY_1:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case KEY_2:
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