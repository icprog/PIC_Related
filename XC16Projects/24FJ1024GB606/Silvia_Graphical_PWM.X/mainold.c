#include "system.h"
#include "menu.h"

int main(void)
{
    SYSTEM_Initialize();                        // initialize the device
    
    uint8_t loopCount = 0;
    
//    extern uint16_t x,y;  
  //  extern uint8_t col, row;
    uint8_t testKey = 0;


    while (1)
    {
        if(loopCount<2)
        {
        loadimg(&menu2[0], 1024,0);                     //Draw Menu2
        }

        LCDWriteStringXY(3,6,"Please Set");
        LCDWriteStringXY(3,17,"the Time!");
        _RF3 = 1;
        __delay_ms(100);
        char s = 0;
        testKey = menuRead();
//        LCDWriteIntXY(4,0,x,5,0);
  //      LCDWriteIntXY(5,0,y,5,0);
    //    LCDWriteIntXY(4,17,col,5,0);
      //  LCDWriteIntXY(5,17,row,5,0);
        
        if (testKey == KEY_RIGHT)
        {
            
            cls();
            loadimg(&menu3[0], 1024,0);                         //Draw Menu3
            LCDWriteStringXY(3,2,"Press 'ENTER' ");
            LCDWriteStringXY(3,16,"to Set the Time");

        }
        

        
        LCDWriteIntXY(4,17,s,0,0)
        LCDWriteIntXY(1,1,loopCount,5,0);
        LCDWriteIntXY(2,1,ADCRead(ADC_CHANNEL_CTMU_TEMPERATURE_SENSOR_INPUT),5,0);
        _RF3 = 0;
//        __delay_ms(1000);
        
//        _RB15 = 1;
  //      __delay_ms(500);
    //    _RB15 = 0;
//        __delay_ms(5000);
/*        
        if(loopCount >253)
        {
            displayOn(0);
            loopCount = 0;
            __delay_ms(10);
            displayOn(1);
        }
        
*/
        if(loopCount<10)
        {
            loopCount+=1;
        }
    }
    return -1;
}