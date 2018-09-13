#include    "system.h"                                                          // System funct/params, like osc/peripheral config
#include    "menu.h"
// *************** Outputs ***************************************************************************************************************************************
#define piezoOutput             _LATF1                                          // Piezo Alarm Output           G
#define backLightOn             _LATD4                                          // Backlight On/Off             G
#define airPump                 _LATD5                                          // Air pump (for level sensing) G

// *************** Inputs ****************************************************************************************************************************************
// ADC Input to read Button press (User Input Keys) on _RB6 (AN6)                                               G
// ***************************************************************************************************************************************************************

//*************************** Timer1 and Timer2 set in pwm.c *****************************************************************************************************
//*************************** All times are in 1/100th's of a second, so 100 = 1 seconds, 300 = 3 seconds, 150 = 1.5 seconds, etc ********************************

#define max                     1023                                // This needs to move to EEPROM
#define min                     400                                 // Also needs to move to EEPROM & have User interface coded
#define preInfusionDutyCycle    500                                 // This needs to move to EEPROM & have a User Interface set up so user can change it
#define preInfusionTime         (25)                                // length of time to run pump to preInfuse puck
#define soakTime                (preInfusionTime + 15)              // Length of time for wetted puck to soak
#define startRamp               (soakTime + 25)                     // StartRamp starts pump and Ramps up to Max Pressure
#define continuePull            (800 + 1)                           // Shot duration, 60 seconds from Start of Cycle(601)
#define warning                 (850 + 1)                           // Turn on Warning Piezo, reminder to turn off switch (651)


#define PIDDuration             2499
#define WaterPID                PIDValue[0]
#define SteamPID                PIDValue[1]
#define GroupHeadPID            PIDValue[2]

#define waterPIDPeriodCounter   counter[0]
#define steamPIDPeriodCounter   counter[1]
#define groupPIDPeriodCounter   counter[2]
#define shotProgressCounter     counter[3]
#define shotTimer               counter[4]
#define warningTimer            counter[5]


#define waterSetpoint           setpoint[0]
#define steamSetpoint           setpoint[1]
#define groupHeadSetpoint       setpoint[2]

#define waterDeadband           deadband[0]
#define steamDeadband           deadband[1]
#define GroupHeadDeadband       deadband[2]

#define boilerTemperature       temp[0]
#define steamTemperature        temp[1]
#define GroupHeadTemp           temp[2]
#define waterLevel              level                                           //ADCRead(14) is Water Tank level signal
#define numSamples              60                                              //Number of samples to average for temp[] readings (Do not set higher than 20, or keep Max temp below 325F)
                                                                                //You have 65535/(max temp * 10) samples available Changed to float, 300 no worries!! Should be able to get 
// *************** Global Variables ********************************************
extern struct tm currentTime;

extern float Kp[];
extern float Ki[];
extern float Kd[];

uint16_t setpoint[]    =   {1940, 2750, 1970};                                  //setpoint values

uint16_t deadband[]    =   {  50,   10,   50};                                  //dead band values

char *desc[] = {"Water Temp:","Steam Temp:","Group Temp:"};

uint16_t dutyCycle[]    =   {0,0,0};

int8_t powerFail = 1;

// *************** Main Function ***********************************************
int main(void)
{
    SYSTEM_Initialize();
        
    InitializeTimers();
    
    Initialize_PWM();
    
// *************** Local Variables *********************************************
    
    uint8_t blink = 1;                          // blink flashes display when water level low
    
    uint8_t errorCount = 0;                     // errorCount disables power, if water level remains low too long
    
    uint8_t count2 = 0;                         // count2 ramps pump pressure
    
    int samples[3][numSamples];                 //Used to average temp[] over "numSamples" of samples
    
    uint16_t temp[3];
    
    uint16_t shortTermTemp[3];                                              
    
    uint8_t sampleIndex = 0;                    // Used to calculate average sample of temp[]
    
    float total[3] = {0,0,0};                   // Running total of temp[] samples 

    uint16_t i = 0;                             // x is used for holding shot timer value for 20 seconds before resetting to zero
    
    uint16_t a = 0;
    
    uint8_t testKey = 0;                        // Variable used for Storing Which Menu Key is Pressed
    
    uint8_t power = 1;                          // Power switch input state     G

    uint8_t brewSwitch = 1;                     // Brew Switch Input            G

    uint8_t steamSwitch = 1;                    // Steam Switch Input           G
    
    uint8_t waterSwitch = 1;                    // Water Switch Input           G
    
//    int internalBGV;
    
    int PIDValue[] = {0,0,0};                   // PID calculated values
    
    int previous_time = 0;                      // Used with time.second to limit some stuff to once a second
            
    int counter[6] = {0,0,0,0,0,0};    // fix   // PID Counter for boiler temp, steam temp, and grouphead temp, as well as shot progress counter, shot timer, and warning timer
    
    uint16_t level = 0;
    
    uint8_t ONTimer = 0;
    
    uint8_t powerSwitch = 0;
    
    uint16_t count = 0;
    
    uint16_t    fuck = 0;
    
// *************** Draw the Main Screen Menu Display ***************************
    LCDBitmap(&menu0[0], 5, 84);                // Draw Menu0


    while(1)
    {
        power = _RG9;                                  // FIX
//        power = !_RG9;                                  // RG9 is pulled high normally, pulled low by turning ON Power switch, so 0 is ON, 1 is OFF
        
        brewSwitch = !_RB4;                             // RB4 is pulled high normally, pulled low by turning ON Brew switch, so 0 is ON, 1 is OFF
        
//        steamSwitch = _RB5;                            // RB5 is pulled high normally, pulled low by turning ON Steam switch, so 0 is ON, 1 is OFF
        steamSwitch = !_RB5;                            // RB5 is pulled high normally, pulled low by turning ON Steam switch, so 0 is ON, 1 is OFF
        
        waterSwitch = !_RB3;                            // RB3 is pulled high normally, pulled low by turning ON Water switch, so 0 is ON, 1 is OFF

        static int timer = 0;                           // Used to count up time in a loop, to auto exit if user in a menu too long

        RTCC_TimeGet(&currentTime);                     // Read the current Time from the RTCC

// *************** Grab Temperatures, & Average over time **********************
        shortTermTemp[0] = ADCRead(13);                 // Assign the ADC(13) (Boiler Temp) to a temporary variable
        
        total[0] = total[0] - samples[0][sampleIndex];  // Subtract the oldest sample data from the total

        samples[0][sampleIndex] = shortTermTemp[0];     // Assign the just read temperature to the location of the current oldest data
        
        total[0] = total[0] + samples[0][sampleIndex];  // Add that new sample to the total

        boilerTemperature = total[0] / numSamples;      // Assign the average value of total to the boilerTemperature variable
        
//        steamTemperature = boilerTemperature;           //This is a single boiler, so Steam & Water temps are the same measurement


        shortTermTemp[1] = ADCRead(12);                 // Assign the ADC(12) (Steam Temp) to a temporary variable
        
        total[1] = total[1] - samples[1][sampleIndex];  // Subtract the oldest sample data from the total

        samples[1][sampleIndex] = shortTermTemp[1];     // Assign the just read temperature to the location of the current oldest data
        
        total[1] = total[1] + samples[1][sampleIndex];  // Add that new sample to the total
        
        sampleIndex += 1;                               // and move to the next index location
        
        if(sampleIndex >= numSamples)                   //If we have reached the max number of samples
        {
            sampleIndex = 0;                            //Reset to zero
        }
        steamTemperature = total[1] / numSamples;       // Assign the average value of total to the GroupHeadTemp variable


        shortTermTemp[2] = ADCRead(11);                 //Assign the ADC(11) (GroupHead Temp) to a temporary variable
        
        total[2] = total[2] - samples[2][sampleIndex];  // Subtract the oldest sample data from the total

        samples[2][sampleIndex] = shortTermTemp[2];     // Assign the just read temperature to the location of the current oldest data
        
        total[2] = total[2] + samples[2][sampleIndex];  // Add that new sample to the total
        
        sampleIndex += 1;                               // and move to the next index location
        
        if(sampleIndex >= numSamples)                   //If we have reached the max number of samples
        {
            sampleIndex = 0;                            //Reset to zero
        }
        GroupHeadTemp = total[2] / numSamples;          // Assign the average value of total to the GroupHeadTemp variable

// *************** Only Update once a Second! **********************************
        if(previous_time != currentTime.tm_sec)         // It is a new Second, lets do some shit!!
        {
            ONTimer = runTimer(currentTime.tm_wday, currentTime.tm_hour, currentTime.tm_min);   // Set ONTimer bit, if AutoStart Times are a match
            
            if(power==1 || ONTimer==1)                  // If Power Switch is on, or we are in an Auto Time Startup Period
            {
                powerSwitch = 1;        
            }
            else
            {
                powerSwitch = 0;
            }
            
            errorCount>9?powerSwitch=0:powerSwitch;     // If we have an error, persisting for 10 seconds, shut it down!
            
//            level = waterTankLevel();                                             // FIX
            level = 35;
 
            level<10?powerSwitch=0:powerSwitch;
            
            if(level < 10)
            {
                errorCount +=1;
                errorCount>20?errorCount=20:errorCount;
                errorCount<20?airPump=1:(airPump=0);
            }
            
            previous_time = currentTime.tm_sec;

           
// ******************************************************************************
//            internalBGV = ADCRead(ADC_CHANNEL_VBG);
      
            for(i = 0;i<2;++i)
            {
                temp[i] = TempCalc(temp[i]);
            }
            
// ******************************************************************************
 
            if(powerFail == 1)
            {
                LCDWriteStringXY(4,0,"Press \"Time\" to Set");
                LCDWriteStringXY(4,1,"the Current Time");
            }
            else
            {
                displayTime();

                gotoXY(2,1);                                //LCD Line 2 Display

                if(steamSwitch)
                {
                    LCDWriteString(desc[1]);
                    LCDWriteIntXY(48,1,steamTemperature,4,1,0);
                    LCDWriteCharacter(123);                 // generate degree symbol in font list
                    LCDWriteCharacter(70);
                }
                else
                {
                    LCDWriteString(desc[0]);
                    LCDWriteIntXY(48,1,boilerTemperature,4,1,0);
                    LCDWriteCharacter(123);                 // generate degree symbol in font list
                    LCDWriteCharacter(70);
                }

                LCDWriteStringXY(2,2,desc[2]);
                LCDWriteIntXY(48,2,GroupHeadTemp,4,1,0);
                LCDWriteCharacter(123);                     // generate degree symbol in font list
                LCDWriteCharacter(70);
                LCDWriteCharacter(' ');
                
                if(shotTimer == 0)
                {
                    LCDWriteStringXY(2,3,"Tank Level:");
                    LCDWriteIntXY(48,3,level,-1,0,0);
                    LCDWriteCharacter('%');
                    LCDWriteCharacter(' ');
                    LCDWriteCharacter(' ');
                    
      //              LCDWriteIntXY(5,4,testKey,5,0,0);
//                    LCDWriteIntXY(5,4,dutyCycle,5,0);
//                    LCDWriteIntXY(5,16,count,5,0);
        //            LCDWriteIntXY(5,22,shotProgressCounter,5,0,0);
                    
                    if(level < 25)
                    {
                        blink = 1 - blink;
                        if(blink)
                        {
                            LCDWriteStringXY(48,3,"LOW");
                            LCDWriteCharacter(' ');
                            LCDWriteCharacter(' ');
                        }
                    }
                }
                else
                {
                    LCDWriteStringXY(2,3,"Shot Timer:");
                    LCDWriteIntXY(48,3,shotTimer,4,1,0);
                }
            }
        }
        
// ******************************************************************************
        if(powerSwitch == 1)
        {
            if(currentTime.tm_min == 0 && currentTime.tm_sec < 5)
            {
                airPump = 1;
            }
            else
            {
                airPump = 0;
            }

// ******************************************************************************
            GroupHeadPID = PID_Calculate(2, setpoint, temp);
            
            if((groupHeadSetpoint - GroupHeadTemp) > GroupHeadDeadband)
            {
                dutyCycle[0] = 8191;            // Turn OC5 on 100%
            }
            else 
            {
                GroupHeadPID = PID_Calculate(2, setpoint, temp);
                
                dutyCycle[0] = GroupHeadPID;    // Drive OC5 with PID PWM
            }
            
// ******************************************************************************
  /*          if(steamSetpoint - steamTemperature > steamDeadband)
            {
                dutyCycle[2] = 8191;
            }
            else
            {
                SteamPID = PID_Calculate(1, setpoint, temp);
                    
                dutyCycle[2] = SteamPID;
            }
                
            if(waterSetpoint - boilerTemperature > waterDeadband)
            {
                dutyCycle[1] = 8191;
            }
            else
            {
                WaterPID = PID_Calculate(0, setpoint, temp);
                   
                dutyCycle[1] = WaterPID;
            }
   
// ******************************************************************************
*/          
            
            dutyCycle[2] = 0x8191;
            
            dutyCycle[1] = 0x8191;
            
            
              
            (dutyCycle[0]==0)?(OC5CON2bits.OCTRIS = 1):(OC5CON2bits.OCTRIS = 0);
            (dutyCycle[1]==0)?(OC4CON2bits.OCTRIS = 1):(OC4CON2bits.OCTRIS = 0);
            (dutyCycle[2]==0)?(OC6CON2bits.OCTRIS = 1):(OC6CON2bits.OCTRIS = 0);
              
            if(steamSwitch == 1)                //Steam setpoint takes priority
            {
                OC6R = 0;                           
            
                OC6RS = dutyCycle[2];           // Steam Boiler Output

                OC4R = OC6RS;

                (OC4R+dutyCycle[1]>=0x2000)?(OC4RS = 0x2000):(OC4RS = OC4R + dutyCycle[1]); //Water Boiler Output
            }

            else                                //Water setpoint takes priority
            {            
                OC4R = 0;                           
            
                OC4RS = dutyCycle[1];           // Water Boiler Output is Shut OFF

                OC6R = OC4RS;

                (OC6R+dutyCycle[2]>=0x2000)?(OC6RS = 0x2000):(OC6RS = OC6R + dutyCycle[2]); //Steam Boiler Output is Shut OFF
            }
            
            OC5R = dutyCycle[0];
 
// ******************************************************************************
            if(brewSwitch == 1)
            {   
                a = 0;
                
                if(shotProgressCounter <= preInfusionTime)
                {
//                    dutyCycle = preInfusionDutyCycle;
                }
                
                if(shotProgressCounter > preInfusionTime && shotProgressCounter <= soakTime)
                {
//                    dutyCycle = 0;
                }

                if (shotProgressCounter > soakTime && shotProgressCounter <= startRamp)               
                {
//                    if(dutyCycle[2] <= max)
                    {
  //                      dutyCycle[2] +=2;
                    }
                }
            
                if(shotProgressCounter > startRamp && shotProgressCounter <= continuePull)
                {
    //                if(dutyCycle[2] >= min)
                    {   
                        count2 +=1;
                        
                        if(count2 > 9)
                        {
      //                      dutyCycle[2] -=1;
                            count2 = 0;
                        }
                    }
                } 
                    
                    if(shotProgressCounter > (250 + preInfusionTime + soakTime))
                    {
//                        dutyCycle = 20;
                    }
                
                if (shotProgressCounter >= warning)         // 90 Seconds has elapsed without Brew Switch being turned off,
                {                  
                    piezoOutput = 1;                        // Activate Piezo Buzzer for 1/2 second
                }

                if(shotProgressCounter >= warning + 50)     // Piezo has been on for 1/2 second
                { 
                    piezoOutput = 0;                        // So, Shut it off! (pulsing alarm)
                    shotProgressCounter = (warning - 50);   // set time back 2 seconds, so it can go again.(in 1.5 seconds)
                    warningTimer++;                         // Increment z every 2 seconds, after 10 counts, alarm will go solid
                }

                if(warningTimer >= 10)                      // After 10 seconds of pulsing alarm being ignored,
                { 
                    piezoOutput = 1;                        // turn Piezo on constantly,
                    shotProgressCounter = (warning - 250);  // and set tenCount to below the pulsing alarm time,
                    warningTimer = 10;                      // so Piezo will not start pulsing alarm again.
                }                                       
                
                
                if(IFS0bits.T1IF)
                {
                    count+=1;

                    if(count == 10)
                    {
                        shotProgressCounter +=1;
    
                        if(shotProgressCounter > soakTime)
                        {
                            shotTimer +=1;
                        }
                        
                        count = 0;
                    }

                    IFS0bits.T1IF = 0;
                }
            }

            else
            {
                piezoOutput =           0;
                warningTimer =          0;
                T1CONbits.TON =         0;
                shotProgressCounter =   0;
//                dutyCycle =             0;
                a += 1;
                if(a >= 12500)                              //Approximately 20 seconds (about 625 counts/second)
                {
                    shotTimer =         0;
                }
            }

// ******************************************************************************
            if(waterSwitch)
            {
//                run the PUMP 100%                                                                         //FIX
            }
        }

// ******************************************************************************
        else                                    // If Power Switch is OFF
        {
            OC5R = 0;                           // This is Edge aligned, so, as long as R is 0, no Output                           
            OC5RS = 0x2000;                     // This is Edge aligned, so, This sets the Period
            OC4R = 0x2000;                      // This is Center aligned, so, as long as R is Higher that RS, no Output
            OC4RS = 0;                          // This is Center aligned, so, as long as R is Higher that RS, no Output
            OC6R = 0x2000;                      // This is Center aligned, so, as long as R is Higher that RS, no Output
            OC6RS = 0;                          // This is Center aligned, so, as long as R is Higher that RS, no Output
            shotTimer           = 0;            // shotTimer reset to 0
            piezoOutput         = 0;            // Piezo is turned OFF
        }

// ******************************************************************************
        if(!brewSwitch && !steamSwitch && !waterSwitch)
        {
//                                       // Turn Water Pump OFF                                                // FIX
        }

// ******************************************************************************
        testKey = readButton();
// ******************************************************************************
//        heartBeat();                                      // HeartBeat displays the HeartBeat on the LCD,
// ******************************************************************************  
        if (testKey == Menu)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto done2;
            }
            
            LCDClear();
            LCDBitmap(&menu2[0], 5, 84);                    //Draw Menu2
            LCDWriteStringXY(4,1,"Press \"ENTER\" Key");
            LCDWriteStringXY(4,2,"to Set the Time");

            while(testKey != Enter)
            {
                testKey = readButton();
                timer +=1;
                __delay_ms(10);
                if (timer > 500)
                {
                    timer = 0;
                    LCDClear();
                    LCDBitmap(&menu2[0], 5, 84);            //Draw Menu2
                    goto done2;
                }
            }

            RTCC_TimeSet(&currentTime);
            
            timer = 0;

//            LCDBitmap(&menu0[0], 5, 84);                    //Draw Menu0
            __delay_ms(500);
            
            done2:;
            LCDBitmap(&menu0[0], 5, 84);                    //Draw Menu0
        }
        
// ******************************************************************************
        
        if(testKey == Enter)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit2;
            }

//            testKey = None;
            
            LCDClear();
            LCDBitmap(&menu1[0], 5, 84);                    //Draw Menu1
            LCDWriteStringXY(0,1,"Press \"ENTER\" to Set Start/Stop Times");
//            LCDWriteStringXY(3,16,"art/Stop Times");

            while(testKey != Enter)
            {
                testKey = readButton();
                 timer +=1;
                 __delay_ms(10);
               
                if(timer > 500)
                {
                    timer = 0;
                    LCDClear();
                    LCDBitmap(&menu1[0], 5, 84);            //Draw Menu2
                    goto Exit2;                                                 
                }
            }
            
            timer = 0;
            
            writeStartStopTimes();

            LCDBitmap(&menu0[0], 5, 84);                    //Draw Menu0
            __delay_ms(500);
            
            Exit2:; 
        }
// ******************************************************************************

        if (testKey == Down)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit;
            }

            if(timer < 2)
            {
                LCDClear();
                LCDBitmap(&menu2[0], 5, 84);                //Draw Menu2
                testKey = None;
                __delay_ms(750);
            }
            
            
            int8_t choice = 0;

            while(testKey != Enter)
            {
                testKey = readButton();
                __delay_ms(10);
                
                if(timer > 500)
                {
                    timer = 0;
                    LCDClear();
                    LCDBitmap(&menu0[0], 5, 84);            //Draw Menu0
                    goto Exit;                              //This uses less memory than testKey = Down
//                    testKey = Down;                       // This functions fine, but forces a write to EEProm
                }

                switch(testKey)
                {
                    case Down:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;

                        
                    case Up:
                    {
                        choice += 1;
                            
                        if(choice > 2)
                        {
                            choice = 2;
                        }
                    }
                    break;
                }


//                gotoXY(1,2);
                LCDWriteStringXY(0,0,"PID Settings for");
//                LCDWriteStringXY(1,16,"or ");
                LCDWriteStringXY(0,1,desc[choice]);
                LCDWriteStringXY(0,3,"Up/Dn Keys to Change");
//                LCDWriteStringXY(2,17,"to change");
                LCDWriteStringXY(0,4,"  \"Enter\" to Accept ")
  //              LCDWriteStringXY(3,16,"o Accept")

                timer += 1;
            }
            
            testKey = 0;
            
            LCDClear();
            LCDBitmap(&menu2[0], 5, 84);                    //Draw Menu2
            LCDWriteStringXY(0,0,"SetPoint = ");
            setpoint[choice] = setParameter(44,0,1750,2950,setpoint[choice]);
            
            LCDWriteStringXY(0,1,"DeadBand =");
            deadband[choice] = setParameter(44,1,5,100,deadband[choice]);            

            LCDWriteStringXY(0,2,"Gain =");
            Kp[choice] = setParameter(44,2,0,200,Kp[choice]);

            LCDWriteStringXY(0,3,"Integral =");
            Ki[choice] = setParameter(44,3,0,500,Ki[choice]);

            LCDWriteStringXY(0,4,"Derivative =");
            Kd[choice] = setParameter(44,4,0,100,Kd[choice]);
            
            
            Init_PID(choice,Kp[choice],Ki[choice],Kd[choice]);                

            timer = 0;

            LCDClear();
            LCDBitmap(&menu0[0], 5, 84);                    //Draw Menu0
            __delay_ms(500);
        }
 
        Exit:
                        
// ******************************************************************************
        if (testKey == Up)                                  // Reset the LCD
        {
            LCDInit();
            LCDClear();
            LCDBitmap(&menu0[0], 5,84);                     //Draw Menu0
        }
        
// ******************************************************************************
        ClrWdt();                                                               //Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************
