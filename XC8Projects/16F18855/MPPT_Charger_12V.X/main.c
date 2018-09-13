// <editor-fold defaultstate="collapsed" desc="Includes & Defines">

// *************** Includes ****************************************************    
#include "system.h"

#define VOut0               voltage[0]
#define VOut1               voltage[1]    
#define VIn0                voltage[2]
#define VIn1                voltage[3]

#define IOut0               current[0]
#define IOut1               current[1]
#define IIn0                current[2]
#define IIn1                current[3]

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
int16_t         Vanalogs[4]         =   {0,0,0,0};
int16_t         Ianalogs[4]         =   {0,0,0,0};
extern int16_t  voltage[4];                    // Store calculated Voltage values
extern int16_t  current[4];                    // Store Calculated Current Values
int16_t         batteryTemp         =   300;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc=" Variables declared in Main">
// *************** Main Routine ************************************************    


void main(void)
{
    int16_t         MPPT0           =   1525;                   // Need to tune to correct value      Maybe 1700? 
    int16_t         MPPT1           =   1525;                   // Change one vs the other, to see where MPPT is at.
    
    uint16_t        dutyCycle6      =   1023;                   // 1023 is as Low as can go
    uint16_t        dutyCycle7      =   1023;                    // 126 is midpoint, allow adjusting up or down
//    uint16_t        dutyCycle1      =   60;                     // 30 is required for minimum speed
    int16_t         IOutTotal       =   0;
    uint8_t         j               =   0;
    uint8_t         slowLoop        =   200;
    uint8_t         displayRefresh  =   0;
    float           efficiency      =   0;
    extern int8_t   Imode[2];
    extern int16_t  Vref[2];                                       // setpoint for voltage output
    extern int16_t  Iref[2];
    uint8_t         menuButton      =   0;                      // Holds value of which button is pressed
    uint16_t        faultCount      =   0;                      // Keep Count of Current Fault latches/Resets
    uint16_t        faultNotReset   =   0;
    extern int8_t   VHoldMode[2];
    extern uint8_t  batteryState[2];
//    uint8_t         tempFanOutput   =   0;
    extern uint16_t IminCount[2];

    
    SYSTEM_Initialize();
    
    LCDClear();
    
    void calculateCurrent0(void);
    void calculateCurrent1(void);
    void calculateCurrent2(void);
    void calculateCurrent3(void);
    
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
        for(j=0;j<4;j++) Ianalogs[j]=readIAnalog(j);                // Read analogs
        
        Vanalogs[0]=ADCRead(21);                                    // Read VOut0
        
        Vanalogs[1]=ADCRead(17);                                    // Read VOut1

        Vanalogs[2]=ADCRead(23);                                    // Read VIn0

        Vanalogs[3]=ADCRead(19);                                    // Read VIn1    

        if(Fault)faultNotReset+=1;
        
        voltage[0]=(int16_t)(Vanalogs[0]/.5448);                    // Calculate VOut0
        
//        voltage[1]=(int16_t)(Vanalogs[1]/.540757);                   // Calculate VOut1
        voltage[1]=(int16_t)(Vanalogs[1]/.5448);                    // Calculate VOut1

        voltage[2]=(int16_t)(Vanalogs[2]/.405775);                  // Calculate VIn0
        
        voltage[3]=(int16_t)(Vanalogs[3]/.406788);                   // Calculate VIn1
        
        calculateCurrent0();

        calculateCurrent1();
        
        calculateCurrent2();

        calculateCurrent3();
        
        if(Imode[0])
        {
            if(VIn0<MPPT0)                             // actual MPPT of Panel
            {
                if(Buck0Output<1023)
                {
                    Buck0Output+=1;
                }
            }
            else if(VIn0>MPPT0)                             // actual MPPT of Panel
            {
                if(Buck0Output>0)
                {
                    Buck0Output-=1;
                }
            }
            else Buck0Output=Buck0Output;
        }
        else
        {
            if(VOut0>(int16_t)Vref[0])
            {
                if(Buck0Output<1023) Buck0Output+=1;
            }
            else if(VOut0<(int16_t)Vref[0])
            {
                if(Buck0Output>0) Buck0Output-=1;;
            }
            else Buck0Output=Buck0Output;
        }
 
        if(Imode[1])
        {
            if(VIn1<MPPT1)                             // 3164 is actual MPPT of Panel
            {
                if(Buck1Output<1023)
                {
                    Buck1Output+=1;
                }
            }
            else if(Buck1Output>0)
            {
                Buck1Output-=1;
            }
        }
        else
        {
            if(VOut1>(int16_t)Vref[1])
            {
                if(Buck1Output<1023) Buck1Output+=1;
            }
            else if(VOut1<(int16_t)Vref[1])
            {
                if(Buck1Output>0) Buck1Output-=1;;
            }
            else Buck1Output=Buck1Output;
        }

        slowLoop+=1;
   
//            PWM1_LoadDutyValue(FanOutput);
            PWM6_LoadDutyValue(Buck0Output);
            PWM7_LoadDutyValue(Buck1Output);

            menuButton = readButton();
            if(menuButton == Down) if(MPPT1>1375)MPPT1-=1;
            if(menuButton == Up)if(MPPT1<2200)MPPT1+=1;
            if(menuButton == Enter)LCDInit();
//        }
  //      fastLoop+=1;
        
        if(slowLoop>250)
        {
            
            IOutTotal=IOut0+IOut1;
            
//            if(IOutTotal>20)
  //          {
    //            if(NewFanOutput>FanOutput)FanOutput+=1;else FanOutput-=1;
    //            if(NewFanOutput>tempFanOutput)if(tempFanOutput<75)tempFanOutput+=1;else if(tempFanOutput>0)tempFanOutput-=1;
  //              FanOutput=tempFanOutput;
//                if(FanOutput<19)FanOutput=0;
      //      }
        //    else
//            {
  //              FanOutput=0;
    //        }
      //      if(Fault)
        //    {
          //      FanOutput=55;
            //    batteryState[0]=CHARGE;
              //  batteryState[1]=CHARGE;
            //}
            
            ADREF = 0x00;                                               // ADNREF VSS; ADPREF VDD;
            batteryTemp=tempCalc(ADCRead(9));                           // Read Thermistor on RB2
            ADREF = 0x03;                                               // ADNREF VSS; ADPREF FVR;
            
            displayRefresh+=1;
            if(displayRefresh>80)
            {
                LCDClear();
                displayRefresh=0;
//                batteryTemp=tempCalc(ADCRead(9));                           // Read Thermistor on RB2
            }
            Battery_State_Machine(0);
            Battery_State_Machine(1);
            
            
            LCDWriteStringXY(0,0,"In:");
            LCDWriteStringXY(26,0,"Out:");
            LCDWriteStringXY(52,0,"Ref:");
            
            LCDWriteIntXY(0,1,VIn0,4,2,0);
            LCDWriteCharacter('V');
      //      LCDWriteCharacter(' ');
            LCDWriteIntXY(26,1,VOut0,4,2,0);
            LCDWriteCharacter('V');
    //        LCDWriteCharacter(' ');
            LCDWriteIntXY(52,1,Vref[0],4,2,0);
            LCDWriteCharacter('V');
  //          LCDWriteCharacter(' ');
            LCDWriteIntXY(80,1,Imode[0],1,0,0);

            LCDWriteIntXY(0,2,IIn0,3,1,0);
//            LCDWriteIntXY(0,2,Ianalogs[2],3,1,0);
            LCDWriteCharacter('A');
//            LCDWriteCharacter(' ');
            LCDWriteIntXY(26,2,IOut0,3,1,0);
//            LCDWriteIntXY(26,2,Ianalogs[0],3,1,0);
            LCDWriteCharacter('A');
//            LCDWriteCharacter(' ');
            LCDWriteIntXY(52,2,Iref[0],3,1,0);
            LCDWriteCharacter('A');
            //LCDWriteCharacter(' ');
            LCDWriteIntXY(80,2,batteryState[0],1,0,0);

            LCDWriteIntXY(0,3,VIn1,4,2,0);
            LCDWriteCharacter('V');
          //  LCDWriteCharacter(' ');
            LCDWriteIntXY(26,3,VOut1,4,2,0);
//            LCDWriteIntXY(26,3,voltage[1],4,2,0);
            LCDWriteCharacter('V');
        //    LCDWriteCharacter(' ');
            LCDWriteIntXY(52,3,Vref[1],4,2,0);
            LCDWriteCharacter('V');
      //      LCDWriteCharacter(' ');
            LCDWriteIntXY(80,3,Imode[1],1,0,0);
            
            LCDWriteIntXY(0,4,IIn1,3,1,0);
//            LCDWriteIntXY(0,4,Ianalogs[3],3,1,0);
            LCDWriteCharacter('A');
    //        LCDWriteCharacter(' ');
            LCDWriteIntXY(26,4,IOut1,3,1,0);
//            LCDWriteIntXY(26,4,Ianalogs[1],3,1,0);
            LCDWriteCharacter('A');
  //          LCDWriteCharacter(' ');
            LCDWriteIntXY(52,4,Iref[1],3,1,0);
            LCDWriteCharacter('A');
//            LCDWriteCharacter(' ');
            LCDWriteIntXY(80,4,batteryState[1],1,0,0);
            
//           LCDWriteIntXY(0,5,Ianalogs[0],4,0,0);

            LCDWriteIntXY(0,5,Buck0Output,4,0,0);
            LCDWriteIntXY(18,5,VHoldMode[0],1,0,0);
            LCDWriteCharacter(' ');
            LCDWriteIntXY(28,5,Buck1Output,4,0,0);
            LCDWriteIntXY(46,5,VHoldMode[1],1,0,0);    
            LCDWriteCharacter(' ');
            LCDWriteIntXY(56,5,batteryTemp,3,1,0);
            LCDWriteCharacter(123);
            LCDWriteCharacter('C');

/*            efficiency=(float)Power0Out;
            efficiency/=(float)Power0In;
            efficiency*=100;

            LCDWriteIntXY(0,0,ADCRead(19),4,0,0);
            LCDWriteIntXY(22,0,ADCRead(17),4,0,0);
//            LCDWriteIntXY(24,0,IminCount[1],4,0,0);
            LCDWriteIntXY(44,0,Ianalogs[1],4,0,0);
  //          LCDWriteIntXY(28,0,ADCRead(21),4,0,0);
    //        LCDWriteIntXY(40,0,ADCRead(20),4,0,0);
            LCDWriteIntXY(66,0,Ianalogs[3],4,0,0);
//            LCDWriteIntXY(0,0,batteryTemp,4,1,0);
//            LCDWriteIntXY(0,0,faultCount,5,0,0);
  //          LCDWriteIntXY(24,0,faultNotReset,5,0,0);
//            LCDWriteIntXY(58,0,VHoldMode[1],2,0,0);
//            LCDWriteCharacter(' ');
//            LCDWriteStringXY(48,0,"Eff:");
//            LCDWriteIntXY(64,0,(int16_t)efficiency,3,0,0);
//            LCDWriteCharacter(' ');



            
            LCDWriteIntXY(0,1,VIn1,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,1,IIn1,3,1,0);
            LCDWriteCharacter('A');
            LCDWriteIntXY(56,1,ADCRead(11),4,0,0);                              // Read Buttons

            
            //            LCDWriteIntXY(0,2,ADCRead(22),4,0,0);
  //          LCDWriteIntXY(20,2,ADCRead(15),4,0,0);
            LCDWriteIntXY(0,2,VOut1,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,2,IOut1,3,1,0);
            LCDWriteCharacter('A');
            LCDWriteIntXY(56,2,Vref[1],4,2,0);
            LCDWriteCharacter('V');
            

            LCDWriteIntXY(0,3,Power1In,3,0,0);
            LCDWriteCharacter('W');
            LCDWriteIntXY(28,3,batteryState[1],1,0,0);
            LCDWriteIntXY(36,3,Imode[1],1,0,0);
            LCDWriteIntXY(48,3,Iref[1],3,1,0);
            LCDWriteCharacter('A');
        //    LCDWriteIntXY(0,3,ADCRead(19),4,0,0);
          //  LCDWriteIntXY(20,3,ADCRead(18),4,0,0);
//            LCDWriteIntXY(0,3,VIn1,4,2,0);
  //          LCDWriteCharacter('V');
    //        LCDWriteIntXY(28,3,IIn1,4,0,0);


            //LCDWriteIntXY(0,4,ADCRead(17),4,0,0);
            //LCDWriteIntXY(20,4,ADCRead(16),4,0,0);
            LCDWriteIntXY(0,4,Power1Out,3,0,0);
            LCDWriteCharacter('W');
//            LCDWriteIntXY(24,4,power0OutOld,3,0,0);
  //          LCDWriteCharacter('W');
            LCDWriteIntXY(48,4,MPPT1,4,0,0);
      //      LCDWriteIntXY(0,4,VOut1,4,2,0);
        //    LCDWriteCharacter('V');
          //  LCDWriteIntXY(28,4,IOut1,4,0,0);
            LCDWriteIntXY(0,5,Buck0Output,4,0,0);
            LCDWriteIntXY(24,5,Buck1Output,4,0,0);
            LCDWriteIntXY(48,5,FanOutput,4,0,0);
            LCDWriteIntXY(74,5,Fault,1,0,0);
*/
            if(batteryState[0] > FINISHED)
            {
            	cc_cv_mode(0);
            }
            if(batteryState[1] > FINISHED)
            {
            	cc_cv_mode(1);
            }
            slowLoop=0;
        }
    }
}


void calculateCurrent0(void)                                                    // I0 Out
{
    if(Ianalogs[0]-545<=0)
    {
        current[0]=0;
    }
    else
    {
        current[0]=(int16_t)((Ianalogs[0]-545)/2.92);
//        current[0]=(int16_t)((Ianalogs[0]-559)/3.09);
    }
}

void calculateCurrent1(void)                                                    // I1 Out
{
    if(Ianalogs[1]-545<=0)
    {
        current[1]=0;
    }
    else
    {
//        current[1]=(int16_t)((Ianalogs[1]-538)/1.55);                        
        current[1]=(int16_t)((Ianalogs[1]-545)/1.2);                        
    }
}

void calculateCurrent2(void)                                                    // I0 In
{
    if(Ianalogs[2]-535<=0)
    {
        current[2]=0;
    }
    else
    {
//        current[2]=(int16_t)((Ianalogs[2]-565)/3.12);
        current[2]=(int16_t)((Ianalogs[2]-535)/2.82);
    }
}

void calculateCurrent3(void)                                                    // I1 In
{
    if(Ianalogs[3]-545<=0)
    {
        current[3]=0;
    }
    else
    {
        current[3]=(int16_t)((Ianalogs[3]-545)/2.4);
    }
}