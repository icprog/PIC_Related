#include <xc.h>
#include "system.h"

void main(void)
{
    SYSTEM_Initialize();                        // Initialize the device
    
    char sec = 0, SEC_COUNT, MIN_COUNT, HOUR_COUNT;
    char DEBOUNCE = 0;                           // Button debouncing
    long int CORRECTION_COUNTER = 0;
    static bit INCREMENT;
    
    while (1)
    {
        if (TMR0IF==1)
        {
            TMR0IF=0;
            sec+=1;                             // one second has elapsed, so count it
        }

        if (sec>0)
        {
            SEC_COUNT+=1;
            CORRECTION_COUNTER+=1;              // Counter to add or subtract counts to account for oscillator error
            if (CORRECTION_COUNTER > 172799)    
            {
                if (SEC_COUNT>0)
                {
                    SEC_COUNT-=1;
                    CORRECTION_COUNTER -= CORRECTION_COUNTER;
                }
            }
            sec=0;
            
            if (SEC_COUNT>59)
            {
                SEC_COUNT=0;
                INCREMENT=1;
            }
            LATB4 = !(SEC_COUNT & 0x01);
            LATB3 = !((SEC_COUNT & 0x02) >> 1);
            LATB2 = !((SEC_COUNT & 0x04) >> 2);
            LATB1 = !((SEC_COUNT & 0x08) >> 3);
            LATB0 = !((SEC_COUNT & 0x10) >> 4);
            LATA7 = !((SEC_COUNT & 0x20) >> 5);

        }
        
        if (INCREMENT>0)
        {
            INCREMENT=0;
            MIN_COUNT+=1;
            if (MIN_COUNT>59)
            {
                INCREMENT=1;
                MIN_COUNT=0;
            }
            LATA6 =  !(MIN_COUNT & 0x01);
            LATA5 = !((MIN_COUNT & 0x02) >> 1);
            LATA3 = !((MIN_COUNT & 0x04) >> 2);
            LATA2 = !((MIN_COUNT & 0x08) >> 3);
            LATA1 = !((MIN_COUNT & 0x10) >> 4);
            LATA0 = !((MIN_COUNT & 0x20) >> 5);
        }
        
        if (INCREMENT>0)
        {
            INCREMENT=0;
            HOUR_COUNT+=1;
            if (HOUR_COUNT>23)
            {
                HOUR_COUNT=0;
            }
            LATC4 = !(HOUR_COUNT & 0x01);
            LATC3 = !((HOUR_COUNT & 0x02) >> 1);
            LATC2 = !((HOUR_COUNT & 0x04) >> 2);
            LATC1 = !((HOUR_COUNT & 0x08) >> 3);
            LATC0 = !((HOUR_COUNT & 0x10) >> 4);
        }
        
        if (RC6==1 && DEBOUNCE==0)
        {
            MIN_COUNT+=1;
            
            if(MIN_COUNT>59)
            {
                MIN_COUNT=0;
            }
            
            SEC_COUNT= -1;
            LATB4 = !(SEC_COUNT & 0x01);
            LATA6 = !(MIN_COUNT & 0x01);
            LATA5 = !((MIN_COUNT & 0x02) >> 1);
            LATA3 = !((MIN_COUNT & 0x04) >> 2);
            LATA2 = !((MIN_COUNT & 0x08) >> 3);
            LATA1 = !((MIN_COUNT & 0x10) >> 4);
            LATA0 = !((MIN_COUNT & 0x20) >> 5);
            DEBOUNCE=1;
        }
        
        if (RC7==1 && DEBOUNCE==0)
        {
            HOUR_COUNT+=1;

            if(HOUR_COUNT>23)
            {
                HOUR_COUNT=0;
            }

            LATC4 = !(HOUR_COUNT & 0x01);
            LATC3 = !((HOUR_COUNT & 0x02) >> 1);
            LATC2 = !((HOUR_COUNT & 0x04) >> 2);
            LATC1 = !((HOUR_COUNT & 0x08) >> 3);
            LATC0 = !((HOUR_COUNT & 0x10) >> 4);
            DEBOUNCE = 1;
        }

        if (DEBOUNCE>0)
        {
            DEBOUNCE+=1;
        }
        
        if (DEBOUNCE>1)
        {
            DEBOUNCE=0;
        }
        
        CLRWDT();
    }
}