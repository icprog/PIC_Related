#include    "system.h"                                                          // System funct/params, like osc/peripheral config
//#include    "menu.h"

int main(void)
{
    
    int dutyCycle = 1000;
    
    SYSTEM_Initialize();

    uint16_t count, count3;
    
    InitializeTimers();
    
    Initialize_PWM();
    
    setDutyCycle(2192);
    
    while(1)
    {
        
//        T1CONbits.TON = 1;
  //      T2CONbits.TON = 1;
//        xxx +=1;
        if(IFS0bits.T2IF)
        {
            IFS0bits.T2IF = 0;
            count+=1;
        }
        if(IFS0bits.T1IF)
        {
            IFS0bits.T1IF = 0;
            count3+=1;
        }
        
        LCDWriteIntXY(0,0,count,5,0,0);
        LCDWriteIntXY(42,0,count3,5,0,0);
        
        

        
// ******************************************************************************
        ClrWdt();                                                               //Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************
