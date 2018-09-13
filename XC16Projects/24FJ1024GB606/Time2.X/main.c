#include    "system.h"

int main(void)
{
    SYSTEM_Initialize();
 
    int month, hour, second, test, count = 0;
    
    struct tm currentTime;
    struct tm initialTime;

    RTCC_Initialize();
    

    while(1)
    {
        RTCC_TimeGet(&currentTime); 
        if(count>1000)
        {
            initialTime.tm_sec =10;
            RTCC_TimeSet(&initialTime);
            count = 0;
        }

        month = currentTime.tm_mon; 
        hour = currentTime.tm_hour;
        second = currentTime.tm_sec;

        LCDWriteIntXY(0,0,month,5,0);
        LCDWriteIntXY(1,0,second,5,0);
        test = RTCC_Task();
        LCDWriteIntXY(2,0,test,5,0);
        LCDWriteIntXY(3,0,count,5,0);
        LCDWriteIntXY(4,0,hour,5,0);
        count+=1;
    }


    return -1;
}