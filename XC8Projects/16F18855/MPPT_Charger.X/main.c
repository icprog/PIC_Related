// <editor-fold defaultstate="collapsed" desc="Includes & Defines">

// *************** Includes ****************************************************    
#include "system.h"

#define VIn0                voltage[0]
#define VOut0               voltage[1]
#define VIn1                voltage[2]
#define VOut1               voltage[3]    


#define IIn0                current[0]
#define IOut0               current[1]
#define IIn1                current[2]
#define IOut1               current[3]

#define     Fault           !(RB2)
#define     Buck0Output     dutyCycle6
#define     Buck1Output     dutyCycle7
#define     FanOutput       dutyCycle1
#define     NewFanOutput    (uint16_t)IOutTotal/2+10

#define     Power0In        VIn0/100*IIn0/10
#define     Power0Out       VOut0/100*IOut0/10
#define     Power1In        VIn1*IIn1
#define     Power1Out       VOut1*IOut1



// *************** Externally available Variables ******************************    
int16_t         analogs[8]      =   {0,0,0,0,0,0,0,0};
extern int16_t  voltage[4];                    // Store calculated Voltage values
extern int16_t  current[4];                    // Store Calculated Current Values
int16_t         batteryTemp     =   250;


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc=" Variables declared in Main">
// *************** Main Routine ************************************************    


void main(void)
{
    int16_t         MPPT0           =   3144;
    int16_t         MPPT1           =   3144;
    
    uint16_t        dutyCycle6      =   1023;                   // 1023 is as Low as can go
    uint16_t        dutyCycle7      =   256;                    // 126 is midpoint, allow adjusting up or down
    uint16_t        dutyCycle1      =   60;                     // 30 is required for minimum speed
    int16_t         IOutTotal       =   0;

    uint8_t         j               =   0;

    uint8_t         fastLoop        =   0;
    uint8_t         slowLoop        =   200;
    uint8_t         displayRefresh  =   0;
    float           efficiency      =   0;
    extern int8_t   Imode0;
    extern int16_t  Vref;                                       // setpoint for voltage output
    extern int16_t  Iref;
    uint8_t         menuButton      =   0;                      // Holds value of which button is pressed
    uint16_t        faultCount      =   0;                      // Keep Count of Current Fault latches/Resets
    uint16_t        faultNotReset   =   0;
    extern int8_t   VHoldMode;
//    uint8_t         tempFanOutput   =   0;
    
    SYSTEM_Initialize();
    
    LCDClear();
    
    void calculateCurrent0(void);
    void calculateCurrent1(void);
  //  void calculateCurrent2(void);
//    void calculateCurrent3(void);
    
    // </editor-fold>
/*    
//    volatile unsigned char value = 0x09;
  //  unsigned char address = 0xE5;
    //eeprom_write(address, value);     // Writing value 0x9 to EEPROM address 0xE5        
    //value = eeprom_read (address);    // Reading the value from address 0xE5
    
//    eeprom_write(Kp_offset,10);
  //  eeprom_write(Ki_offset,4);
    //eeprom_write(Kd_offset,2);
  */  

    while (1)
    {
        if(Fault)
        {
            LATA5=0;
            __delay_us(400);
            faultCount+=1;
            LATA5=1;
        }
        for(j=0;j<8;j++) analogs[j]=readAnalog(j);              // Read analogs
        
        if(Fault)faultNotReset+=1;
        
        voltage[0]=(int16_t)(analogs[0]/.20885);                // Calculate VIn0
        
        voltage[1]=(int16_t)(analogs[1]/.54503);                // Calculate VOut0

//        voltage[2]=(int16_t)(analogs[2]/.20885);                // Calculate VIn1
        
  //      voltage[3]=(int16_t)(analogs[3]/.666);                  // Calculate VOut1
        
        calculateCurrent0();
//        current[0]=(analogs[4]-589)/1.3165;
        
        calculateCurrent1();
//        current[1]=(analogs[5]-578)/3.232;

        
        if(fastLoop>11)
        {
            if(Imode0)
            {
                if(VIn0<MPPT0)                             // 3164 is actual MPPT of Panel
                {
                    if(Buck0Output<1023)
                    {
                        Buck0Output+=1;
                    }
                }
                else if(Buck0Output>0)
                {
                    Buck0Output-=1;
                }
                
                if(VIn1<MPPT1)                             // 3164 is actual MPPT of Panel
                {
                    if(Buck1Output<252)
                    {
//                        Buck1Output+=1;
                    }
                }
                else if(Buck1Output>0)
                {
  //                  Buck1Output-=1;
                }
           }
            else
            {
                if(VOut0>(int16_t)Vref)
                {
                    if(Buck0Output<1023) Buck0Output+=1;
                }
                else
                {
                    if(Buck0Output>0) Buck0Output-=1;;
                }
 
                if(VOut1>(int16_t)Vref)
                {
//                    if(Buck1Output<1023) Buck1Output+=1;
                }
                else
                {
  //                  if(Buck1Output>0) Buck1Output-=1;;
                }

            }
            fastLoop=0;
            slowLoop+=1;
   
            PWM1_LoadDutyValue(FanOutput);
            PWM6_LoadDutyValue(Buck0Output);
            PWM7_LoadDutyValue(Buck1Output);

            menuButton = readButton();
            if(menuButton == Down) if(MPPT0>2800)MPPT0-=10;
            if(menuButton == Up)if(MPPT0<3400)MPPT0+=10;
            if(menuButton == Enter)LCDInit();
        }
        fastLoop+=1;
        
        if(slowLoop>20)
        {
            
            IOutTotal=IOut0+IOut1;
            
            if(IOutTotal>20)
            {
                if(NewFanOutput>FanOutput)FanOutput+=1;else FanOutput-=1;
    //            if(NewFanOutput>tempFanOutput)if(tempFanOutput<75)tempFanOutput+=1;else if(tempFanOutput>0)tempFanOutput-=1;
  //              FanOutput=tempFanOutput;
//                if(FanOutput<19)FanOutput=0;
            }
            else
            {
                FanOutput=0;
            }
            if(Fault)
            {
                FanOutput=55;
                battery_state=CHARGE;
            }
            
            displayRefresh+=1;
            if(displayRefresh>80)
            {
                LCDClear();
                displayRefresh=0;
                batteryTemp=tempCalc(ADCRead(9));                           // Read Thermistor on RB2
            }
            Battery_State_Machine();
            efficiency=(float)Power0Out;
            efficiency/=(float)Power0In;
            efficiency*=100;

            //            LCDWriteIntXY(0,0,ADCRead(23),4,0,0);
  //          LCDWriteIntXY(20,0,ADCRead(22),4,0,0);
    //        LCDWriteIntXY(0,1,ADCRead(21),4,0,0);
      //      LCDWriteIntXY(20,1,ADCRead(20),4,0,0);
        //    LCDWriteIntXY(0,3,ADCRead(19),4,0,0);
          //  LCDWriteIntXY(20,3,ADCRead(18),4,0,0);
            //LCDWriteIntXY(0,4,ADCRead(17),4,0,0);
            //LCDWriteIntXY(20,4,ADCRead(16),4,0,0);

//            LCDWriteIntXY(0,2,ADCRead(22),4,0,0);
  //          LCDWriteIntXY(20,2,ADCRead(15),4,0,0);
            
//            LCDWriteIntXY(0,0,batteryTemp,4,1,0);
            LCDWriteIntXY(0,0,faultCount,5,0,0);
            LCDWriteIntXY(24,0,faultNotReset,5,0,0);
            LCDWriteIntXY(48,0,VHoldMode,3,0,0);
//            LCDWriteStringXY(48,0,"Eff:");
//            LCDWriteInt((int16_t)efficiency,3,0,0);
            LCDWriteCharacter(' ');

//            LCDWriteIntXY(32,0,analogs[4],4,0,0);
  //          LCDWriteIntXY(52,0,analogs[5],4,0,0);
            LCDWriteIntXY(0,1,VIn0,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,1,IIn0,3,1,0);
            LCDWriteCharacter('A');
//            LCDWriteIntXY(56,1,ADCRead(11),4,0,0);                              // Read Buttons
            LCDWriteIntXY(0,2,VOut0,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,2,IOut0,3,1,0);
            LCDWriteCharacter('A');
            LCDWriteIntXY(56,2,Vref,4,2,0);
            LCDWriteCharacter('V');
            
            LCDWriteIntXY(0,3,Power0In,3,0,0);
            LCDWriteCharacter('W');
            LCDWriteIntXY(28,3,battery_state,1,0,0);
            LCDWriteIntXY(36,3,Imode0,1,0,0);
            LCDWriteIntXY(48,3,Iref,3,1,0);
            LCDWriteCharacter('A');
            
            LCDWriteIntXY(0,4,Power0Out,3,0,0);
            LCDWriteCharacter('W');
//            LCDWriteIntXY(24,4,power0OutOld,3,0,0);
  //          LCDWriteCharacter('W');
            LCDWriteIntXY(48,4,MPPT0,4,0,0);
            
//            LCDWriteIntXY(0,3,VIn1,4,2,0);
  //          LCDWriteCharacter('V');
    //        LCDWriteIntXY(28,3,IIn1,4,0,0);
      //      LCDWriteIntXY(0,4,VOut1,4,2,0);
        //    LCDWriteCharacter('V');
          //  LCDWriteIntXY(28,4,IOut1,4,0,0);
            LCDWriteIntXY(0,5,Buck0Output,4,0,0);
            LCDWriteIntXY(24,5,Buck1Output,4,0,0);
            LCDWriteIntXY(48,5,FanOutput,4,0,0);
            LCDWriteIntXY(74,5,Fault,1,0,0);

            if(battery_state > FINISHED)
            {
            	cc_cv_mode();
            }
            slowLoop=0;
        }
    }
}

void calculateCurrent0(void)
{
    if(analogs[4]-589<=0)
    {
        current[0]=0;
    }
    else
    {
        current[0]=(int16_t)((analogs[4]-589)/1.3165);
    }
}

void calculateCurrent1(void)
{
    if(analogs[5]-578<=0)
    {
        current[1]=0;
    }
    else
    {
        current[1]=(int16_t)((analogs[5]-578)/3.2323);
    }
}

/*void calculateCurrent2(void)
{
    if(analogs[6]-589<=0)
    {
        current[2]=0;
    }
    else
    {
        current[0]=(int16_t)((analogs[4]-589)/1.3165);
    }
}

void calculateCurrent3(void)
{
    if(analogs[7]-578<=0)
    {
        current[3]=0;
    }
    else
    {
        current[1]=(int16_t)((analogs[5]-578)/3.2323);
    }
}*/