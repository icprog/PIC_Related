#include <xc.h>
#include "system.h"
#include "GLCD.h"
//#include "Arial14.h"
#include "GLCD_Pins.h"
#include "SystemFont5x7.h"

void main(void)
{
    Init();
        RA3 = 1;
        __delay_ms(5000);
        RA3 = 0;
        __delay_ms(5000);
    GLCD_Init(INVERTED);                        // initialise the library
        RA3 = 1;
        __delay_ms(5000);
        RA3 = 0;
//        __delay_ms(5000);
//    GLCD_ClearScreen(BLACK);  
  //      RA3 = 1;
    //    __delay_ms(5000);
      //  RA3 = 0;
//    GLCD_DrawBitmap(ArduinoIcon, 32,0, BLACK);    //draw the bitmap at the given x,y position
    //GLCD_ClearScreen(WHITE);
   // GLCD_SelectFont(System5x7);                     // select fixed width system font 

    while(1)
    {
        RA3 = 1;
        __delay_ms(1000);
        RA3 = 0;
        __delay_ms(1000);
        GLCD_DrawRect(0, 0, 64, 61, BLACK);         // rectangle in left side of screen
    }    
}
