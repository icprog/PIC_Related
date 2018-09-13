
#include "xc.h"
#include "lcd.h"
#include "system.h"                     // System funct/params, like osc/peripheral config

int main(void)
{
 
    InitApp();
    
    __delay_ms(5000);
    
 //   LCDInit(LS_NONE);
    LCD_Initialize();
   
    while(1)
    {
        _RC8 = 0;
        
//        LCDWriteStringXY(0,0,"HELLO WORLD!");
        __delay_ms(2000);
        LCDGoto(0,0);
        LCDPutStr("Hello World, this is a really long ");
        LCDGoto(0,1);
        
        LCDPutStr("Hello World!, This should be Line 2!");
        
        _RC8 = 1;
//        LCDClear();
  //      LCDWriteStringXY(0,0,"Now Hear This");
        __delay_ms(2000);
        DisplayClr();
 //       LCDClear();
        ClrWdt();                                                               //Clr (Re-Set) the WatchDog Timer
    }
    return(0);
}
//***************************************************************************************************************************************************************
