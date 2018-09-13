#include    "system.h"
#include    "coffee.h"
// *****************************************************************************
RTCTime time;                                   // declare the type of the time object

int powerFail           =   0;                  //Setting powerFail to 1, instructs the user to set the time

extern int run;

// *************** Main Routine ************************************************
int main(void)
{                       
    InitApp();
    
 //   unsigned char testKey     = 0;              // Variable used for Storing Which Menu Key is Pressed
    
// ******************************************************************************

    while(1)
    {
        time = getRTCTime();                    // get the time
        
                if(powerFail == 1)
                {
                    LCDWriteStringXY(4,0,"Press \"Time\" to Set");
                    LCDWriteStringXY(4,1,"the Current Time");
                }
                else
                {
                    displayTime();

                }
//                LCDBitmap(&coffee[0], 0,504);   //Draw Splash Screen
  //              gotoXY(1,4);
    //            LCDWriteCharacter(' ');         // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
        ClrWdt();                               // Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************
