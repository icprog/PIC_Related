#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    

//    TRISA = 0xFE;
  //  TRISB = 0xFF;                               // RB0 is Analog Input for Zero Cross Detector
    //TRISC = 0xFF;

//    ANSELA = 0x00;
  //  ANSELB = 0x01;
    //ANSELC = 0x00;
    
    TRISA = 0x00;
    TRISB = 0x00;                               // RB0 is Analog Input for Zero Cross Detector
    TRISC = 0x00;

    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;

    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
}       

//void PIN_MANAGER_IOC(void)
//{   

//}