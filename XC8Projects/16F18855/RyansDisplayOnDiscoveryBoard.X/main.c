// *************** Includes ****************************************************    
#include "system.h"
#include <math.h>
#include "coffee.h"

#define backlightIntensity      dutyCycle7

// *************** Main Routine ************************************************    
void main(void)
{
    int count               =   0;
    
    int dutyCycle7          =   1023;
    
    int potValue            =   1023;
    
    int previousPotValue    =   1023;
    
    char x                  =   0;
    
    SYSTEM_Initialize();
   
    LCDBitmap(&coffee[0], 0,504);           //Draw Splash Screen
    gotoXY(1,4);
    LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
   
   __delay_ms(2500);
   

    while (1)
    {
        potValue = readAnalog(0);
        
        if(count<120)
        {
            if (potValue>previousPotValue+5 || potValue<previousPotValue-5)
            {
                LCDWriteStringXY(0,3,"Brightness:");
            
                LCDWriteIntXY(46,3,(potValue)/10,-1,0,0);
            
                LCDWriteCharacter('%');
                LCDWriteCharacter(' ');
                previousPotValue=potValue;
            }
        }
        
        
        potValue=1023-potValue;
        
        backlightIntensity = potValue;

        while(x<1)
        {
            TRISC    =   0x00;
            x+=1;  
        }
        
        PWM7_LoadDutyValue(backlightIntensity);

        if(count<1)LCDClear();
        
        
        if(!RA5) RESET();
        
        if(count==1)LCDWriteStringXY(0,0," Nokia 5110 Display  ");
       
        if(count==35)LCDWriteStringXY(0,1,"Some Minor Bug Fixes and all will be Good!");

//        if(count==36)LCDWriteIntXY(0,3,potValue,-1,0,0);

        if(count==70)LCDWriteStringXY(35,5,"5... ");

        if(count==80)LCDWriteStringXY(35,5,"4... ");

        if(count==90)LCDWriteStringXY(35,5,"3... ");

        if(count==100)LCDWriteStringXY(35,5,"2... ");
        
        if(count==110)LCDWriteStringXY(35,5,"1... ");

        if(count==120)LCDClear();
        
        if(count==121)
        {
            LCDDrawBox();
        }
        
        if(count>121&&count<133)
        {
//            LCDDrawBox();
            LCDWriteStringXY(8,1,"LAYNE SUCKS COCK!!");
            LCDWriteStringXY(8,2,"A LOT!! of COCK");
            
            LCDWriteStringXY(4,3,"Number of Cocks");
            
            LCDWriteStringXY(4,4,"Sucked:")

            LCDWriteIntXY(34,4,count-122,-1,0,0);
    
            __delay_ms(500);
        }
        
        __delay_ms(50);
        
        if(count>=133)
        {
            count=0;
            LCDClear();
        }
        
        count+=1;
    }
}