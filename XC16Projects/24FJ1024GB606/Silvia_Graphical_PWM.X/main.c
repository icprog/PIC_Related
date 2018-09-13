#include    "system.h"                                                             // System funct/params, like osc/peripheral config
#include    "menu.h"
// *************** Outputs ***************************************************************************************************************************************
#define boilerOutput            _LATD6          //Change
#define groupheadOutput         _LATD7          //Change
#define piezoOutput             _LATF1                                          // Piezo Alarm Output G
#define backLightOn             _LATD4                                          // Backlight On/Off G
#define airPump                 _LATD5                                          // Air pump (for level sensing) G

// *************** Inputs ****************************************************************************************************************************************
#define power                   1                                            // Power Switch Input G             
//#define power                   _RG9                                            // Power Switch Input G             
#define steamSwitch             _RB5                                            // Steam Switch Input G
#define brewSwitch              _RB4                                            // Brew Switch Input G
#define waterSwitch             _RB3                                            // Water Switch Input G
// ***************************************************************************************************************************************************************

//***************************Timer2 set in pwm.c
//***************************All times are in 1/100th's of a second, so 100 = 1 seconds, 300 = 3 seconds, 150 = 1.5 seconds, etc 

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
// ***************************************************************************************************************************************************************
extern struct tm currentTime;

extern float Kp[];
extern float Ki[];
extern float Kd[];

uint16_t setpoint[]    =   {1940, 2750, 1970};                                     //setpoint values

uint16_t deadband[]    =   {  50,   10,   50};                                     //dead band values

char *desc[] = {"Water Temp:","Steam Temp:","Group Temp:"};

uint8_t call = 0;

int8_t powerFail = 1;

uint16_t timeFU = 0;                                                              //Setting powerFail to 1, instructs the user to set the time

// ******************************************************************************
int main(void)
{
    SYSTEM_Initialize();
// ******************************************************************************
    
    uint8_t blink = 1, errorCount = 0, count2 = 0;                              // blink flashes display when level low, errorCount disables
                                                                                // power, if level remains low too long, count2 ramps pump pressure
    uint16_t dutyCycle = 0;                                                     // Water Pump duty cycle?? 

    int samples[3][numSamples];                                                 //Used to average temp[] over "numSamples" of samples
    
    int temp[3], shortTermTemp[3];                                              
    
    unsigned char sampleIndex = 0;                                              //Used to calculate average sample of temp[]
    
    float total[3] = {0,0,0};                                                   //Running total of temp[] samples 

    int i = 0, a = 0;                                                           // x is used for holding shot timer value for 20 seconds before resetting to zero
    
    char TestKey;                                                               // Variable used for Storing Which Menu Key is Pressed

    int internalBGV;
    
    int PIDValue[] = {0,0,0};                                                   // PID calculated values
    
    int previous_time = 0;                                                      //Used with time.second to limit some stuff to once a second
            
    int counter[6] = {0,0,0,0,0,0};                                             //PID Counter for boiler temp, steam temp, and grouphead temp, as well as shot progress counter, shot timer, and warning timer
    
    unsigned int level = 0;
    
    char ONTimer = 0, powerSwitch = 0;
    
    uint16_t count = 0;
    
// ******************************************************************************
    setDutyCycle(dutyCycle);
    
    loadimg(&menu3[0], 1024,0);                 //Draw Menu3

    while(1)
    {
        static int timer = 0;                                                   // Used to count up time in a loop, to auto exit if user in a menu too long

        RTCC_TimeGet(&currentTime); 

        shortTermTemp[0] = ADCRead(13);                                         //Assign the ADC(13) (Boiler Temp) to a temporary variable
        
        total[0] = total[0] - samples[0][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[0][sampleIndex] = shortTermTemp[0];                             // Assign the just read temperature to the location of the current oldest data
        
        total[0] = total[0] + samples[0][sampleIndex];                          // Add that new sample to the total

        boilerTemperature = total[0] / numSamples;                              // Assign the average value of total to the boilerTemperature variable
        
//        steamTemperature = boilerTemperature;                                   //This is a single boiler, so Steam & Water temps are the same measurement

       shortTermTemp[1] = ADCRead(12);                                          //Assign the ADC(12) (Steam Temp) to a temporary variable
        
        total[1] = total[1] - samples[1][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[1][sampleIndex] = shortTermTemp[1];                             // Assign the just read temperature to the location of the current oldest data
        
        total[1] = total[1] + samples[1][sampleIndex];                          // Add that new sample to the total
        
        sampleIndex += 1;                                                       // and move to the next index location
        
        if(sampleIndex >= numSamples)                                           //If we have reached the max number of samples
        {
            sampleIndex = 0;                                                    //Reset to zero
        }
        steamTemperature = total[1] / numSamples;                               // Assign the average value of total to the GroupHeadTemp variable


        shortTermTemp[2] = ADCRead(11);                                         //Assign the ADC(11) (GroupHead Temp) to a temporary variable
        
        total[2] = total[2] - samples[2][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[2][sampleIndex] = shortTermTemp[2];                             // Assign the just read temperature to the location of the current oldest data
        
        total[2] = total[2] + samples[2][sampleIndex];                          // Add that new sample to the total
        
        sampleIndex += 1;                                                       // and move to the next index location
        
        if(sampleIndex >= numSamples)                                           //If we have reached the max number of samples
        {
            sampleIndex = 0;                                                    //Reset to zero
        }
        GroupHeadTemp = total[2] / numSamples;                                  // Assign the average value of total to the GroupHeadTemp variable

// ******************************************************************************
        if(previous_time != currentTime.tm_sec)
        {
            ONTimer = runTimer(currentTime.tm_wday, currentTime.tm_hour, currentTime.tm_min);
            
            if(power==1 || ONTimer==1)
            {
                powerSwitch = 1;
            }
            else
            {
                powerSwitch = 0;
            }
            
            errorCount>9?powerSwitch=0:powerSwitch;
            
//            level = waterTankLevel();
            level = 30;
 
            level<10?powerSwitch=0:powerSwitch;
            
            if(level < 10)
            {
                errorCount +=1;
                errorCount>20?errorCount=20:errorCount;
                errorCount<20?airPump=1:(airPump=0);
            }
            
            previous_time = currentTime.tm_sec;

// ******************************************************************************
            internalBGV = ADCRead(0x1A);
      
            for(i = 0;i<2;++i)
            {
                temp[i] = TempCalc(temp[i]);
            }
            
// ******************************************************************************
//            if (dutyCycle < 0x800)                  // 0x800 = 2048, 100 % output is 2047, but going to 2048 ensures the pin will stay at 100%                            
  //          {
    //            count +=1;
      //          if(count > 15)
        //        {
          //          dutyCycle+=1;
            //    }
            //}
        
            setDutyCycle(dutyCycle);

 
            if(powerFail == 1)
            {
                LCDWriteStringXY(3,6,"Please Set");
                LCDWriteStringXY(3,17,"the Time!");
            }
            else
            {
                displayTime();

                GoToXY(2,1);                                                //LCD Line 2 Display

                if(steamSwitch)
                {
                    LCDWriteString(desc[1]);
                    LCDWriteString("/Set");
                    GoToXY(2,25);
                    LCDWriteChar('/');
                    LCDWriteInt(setpoint[1],4,1);
                }
                else
                {
                    LCDWriteString(desc[0]);
                    LCDWriteString("/Set");
                    GoToXY(2,25);
                    LCDWriteChar('/');
                    LCDWriteInt(setpoint[0],4,1);
                }

                LCDWriteIntXY(2,17,boilerTemperature,4,1);
                LCDWriteChar(129);                                          // generate degree symbol in font list
                LCDWriteChar(70);

                GoToXY(3,1);                                                //LCD Line 3 Display
                LCDWriteString(desc[2]);
                LCDWriteString("/Set");
                LCDWriteIntXY(3,17,GroupHeadTemp,4,1);
                LCDWriteChar(129);                                          // generate degree symbol in font list
                LCDWriteChar(70);
                LCDWriteChar(' ');
                LCDWriteChar('/');
                LCDWriteInt(setpoint[2],4,1);
                
                if(shotTimer == 0)
                {
                    LCDWriteStringXY(4,3,"Tank Level:");
                    LCDWriteIntXY(4,17,level,3,0);
                    LCDWriteChar (' ');
                    LCDWriteChar ('%');
                    
                    LCDWriteIntXY(5,4,TestKey,5,0);
//                    LCDWriteIntXY(5,4,dutyCycle,5,0);
                    LCDWriteIntXY(5,16,timeFU,5,0);
//                    LCDWriteIntXY(5,16,count,5,0);
                    LCDWriteIntXY(5,22,shotProgressCounter,5,0);
                    
                    if(level < 25)
                    {
                        blink = 1 - blink;
                        if(blink)
                        {
                            LCDWriteStringXY(4,17,"LOW");
                            LCDWriteChar (' ');
                            LCDWriteChar (' ');
                        }
                    }
                }
                else
                {
                    LCDWriteStringXY(4,3,"Shot Timer:");
                    LCDWriteIntXY(4,17,shotTimer,4,1);
                }
            }
        }
        
// ******************************************************************************
        if(powerSwitch == 1)
        {
//            if(IFS0bits.T2IF)
  //          {
    //            IFS0bits.T2IF = 0;
      //          count+=1;
        //    }

            if(currentTime.tm_min == 0 && currentTime.tm_sec < 5)
            {
                airPump = 1;
            }
            else
            {
                airPump = 0;
            }

            if(steamSwitch == 1)
            {
//                SteamPID = PID_Calculate(1, setpoint, temp);
            }
            else
            {
  //              WaterPID = PID_Calculate(0, setpoint, temp);
            }

    //        GroupHeadPID = PID_Calculate(2, setpoint, temp);
            
// ******************************************************************************
            if(steamSwitch == 1)                                                //Steam setpoint takes priority
            {
                if(steamSetpoint - boilerTemperature > steamDeadband)
                {
                    boilerOutput = 1;
                }
                else
                {
                    steamPIDPeriodCounter+=1;
        
                    if (steamPIDPeriodCounter > PIDDuration)
                    {
                        steamPIDPeriodCounter = 0;
                    }
        
                    if (SteamPID > steamPIDPeriodCounter)
                    {
                        boilerOutput = 1;
                    }
                    else
                    {
                        boilerOutput = 0;
                    }
                }
            }

            else                                                                //Water setpoint takes priority
            {            
                if(waterSetpoint - boilerTemperature > waterDeadband)
                {
                    boilerOutput = 1;
                }
                else
                {
                    waterPIDPeriodCounter+=1;
       
                    if (waterPIDPeriodCounter > PIDDuration)
                    {
                        waterPIDPeriodCounter = 0;
                    }
        
                    if (WaterPID > waterPIDPeriodCounter)
                    {
                        boilerOutput = 1;
                    }
                    else
                    {
                        boilerOutput = 0;
                    }
                }
            }
            
// ******************************************************************************
            if((groupHeadSetpoint - GroupHeadTemp) > GroupHeadDeadband)
            {
                groupheadOutput = 1;
            }

            else 
            {
                groupPIDPeriodCounter+=1;
        
                if(groupPIDPeriodCounter > PIDDuration)
                {
                    groupPIDPeriodCounter = 0;
                }
        
                if(GroupHeadPID > groupPIDPeriodCounter)
                {
                    groupheadOutput = 1;
                }
                else
                {
                    groupheadOutput = 0;
                }
            }

// ******************************************************************************
            if(brewSwitch == 1)
            {   
                a = 0;
                
                if(shotProgressCounter <= preInfusionTime)
                {
                    dutyCycle = preInfusionDutyCycle;
                }
                
                if(shotProgressCounter > preInfusionTime && shotProgressCounter <= soakTime)
                {
                    dutyCycle = 0;
                }

                if (shotProgressCounter > soakTime && shotProgressCounter <= startRamp)               
                {
                    if(dutyCycle <= max)
                    {
                        dutyCycle +=2;
                    }
                }
            
                if(shotProgressCounter > startRamp && shotProgressCounter <= continuePull)
                {
                    if(dutyCycle >= min)
                    {   
                        count2 +=1;
                        
                        if(count2 > 9)
                        {
                            dutyCycle -=1;
                            count2 = 0;
                        }
                    }
                } 
                    
                    if(shotProgressCounter > (250 + preInfusionTime + soakTime))
                    {
                        dutyCycle = 20;
                    }
                
                if (shotProgressCounter >= warning)                             // 90 Seconds has elapsed without Brew Switch being turned off,
                {                  
                    piezoOutput = 1;                                            // Activate Piezo Buzzer for 1/2 second
                }

                if(shotProgressCounter >= warning + 50)                          // Piezo has been on for 1/2 second
                { 
                    piezoOutput = 0;                                            // So, Shut it off! (pulsing alarm)
                    shotProgressCounter = (warning - 50);                       // set time back 2 seconds, so it can go again.(in 1.5 seconds)
                    warningTimer++;                                             // Increment z every 2 seconds, after 10 counts, alarm will go solid
                }

                if(warningTimer >= 10)                                          // After 10 seconds of pulsing alarm being ignored,
                { 
                    piezoOutput = 1;                                            // turn Piezo on constantly,
                    shotProgressCounter = (warning - 250);                       // and set tenCount to below the pulsing alarm time,
                    warningTimer = 10;                                          // so Piezo will not start pulsing alarm again.
                }                                       
                
                
                if(IFS0bits.T2IF)
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

                    IFS0bits.T2IF = 0;
                }
            }

            else
            {
                piezoOutput =           0;
                warningTimer =          0;
                T2CONbits.TON =         0;
                shotProgressCounter =   0;
                dutyCycle =             0;
                a += 1;
                if(a >= 12500)                                                  //Approximately 20 seconds (about 625 counts/second)
                {
                    shotTimer =         0;
                }
            }

// ******************************************************************************
            if(waterSwitch)
            {
                dutyCycle = 2048;
            }
        }
        else
        {
            boilerOutput        = 0;
            groupheadOutput     = 0;
            shotTimer           = 0;
            dutyCycle           = 0;
            piezoOutput         = 0;
        }

// ******************************************************************************
        if(!brewSwitch && !steamSwitch && !waterSwitch)
        {
            dutyCycle =     0;
        }

// ******************************************************************************
        TestKey = menuRead();
// ******************************************************************************
//        heartBeat();                                                            // HeartBeat displays the HeartBeat on the LCD,
// ******************************************************************************  
        if (TestKey == KEY_1)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto done2;
            }
            
            cls();
            loadimg(&menu2[0], 1024,0);                         //Draw Menu2
            LCDWriteStringXY(3,2,"Press 'ENTER' ");
            LCDWriteStringXY(3,16,"to Set the Time");

            while(TestKey != KEY_3)
            {
                TestKey = menuRead();
                timer +=1;
                __delay_ms(10);
                if (timer > 500)
                {
                    timer = 0;
                    cls();
                    loadimg(&menu3[0], 1024,0);                  //Draw Menu3
                    goto done2;
                }
            }

            RTCC_TimeSet(&currentTime);
            
            timer = 0;

            loadimg(&menu3[0], 1024,0);                         //Draw Menu3
            __delay_ms(500);
            
            done2:;
        }
        
// ******************************************************************************
        
        if(TestKey == KEY_2)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit2;
            }

//            TestKey = KEY_NONE;
            
            cls();
            loadimg(&menu2[0], 1024,0);                         //Draw Menu2
            LCDWriteStringXY(3,1,"ENTER to Set St");
            LCDWriteStringXY(3,16,"art/Stop Times");

            while(TestKey != KEY_3)
            {
                TestKey = menuRead();
                 timer +=1;
                 __delay_ms(10);
               
                if(timer > 500)
                {
                    timer = 0;
                    cls();
                    loadimg(&menu3[0], 1024,0);                  //Draw Menu2
                    goto Exit2;                                                 
                }
            }
            
            timer = 0;
            
            
            
            
            
            
            
            
            
            
            writeStartStopTimes();






            loadimg(&menu3[0], 1024,0);                          //Draw Menu2
            __delay_ms(500);
            
            Exit2:; 
        }
// ******************************************************************************

        if (TestKey == KEY_3)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit;
            }

            if(timer < 2)
            {
                cls();
                loadimg(&menu2[0], 1024,0);                     //Draw Menu2
                TestKey = KEY_NONE;
                __delay_ms(750);
            }
            
            
            int8_t choice = 0;

            while(TestKey != KEY_3)
            {
                TestKey = menuRead();
                __delay_ms(10);
                
                if(timer > 500)
                {
                    timer = 0;
                    cls();
                    loadimg(&menu3[0], 1024,0);                  //Draw Menu3
                    goto Exit;                                   //This uses less memory than TestKey = KEY_3
//                    TestKey = KEY_3;                           // This functions fine, but forces a write to EEProm
                }

                switch(TestKey)
                {
                    case KEY_1:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;

                        
                    case KEY_2:
                    {
                        choice += 1;
                            
                        if(choice > 2)
                        {
                            choice = 2;
                        }
                    }
                    break;
                }


                GoToXY(1,2);
                LCDWriteString("PID Settings f");
                LCDWriteStringXY(1,16,"or ");
                LCDWriteString(desc[choice]);
                LCDWriteStringXY(2,6,"Up/Dn Keys");
                LCDWriteStringXY(2,17,"to change");
                LCDWriteStringXY(3,7,"\"Enter\" t")
                LCDWriteStringXY(3,16,"o Accept")

                timer += 1;
            }
            
            TestKey = 0;
            
            cls();
            loadimg(&menu2[0], 1024,0);              //Draw Menu2
            LCDWriteStringXY(1,1,"SetPoint = ");
            setpoint[choice] = setParameter(1,16,1750,2950,setpoint[choice]);
            
            LCDWriteStringXY(2,1,"DeadBand =");
            deadband[choice] = setParameter(2,16,5,100,deadband[choice]);            

            LCDWriteStringXY(3,1,"Gain =");
            Kp[choice] = setParameter(3,16,0,200,Kp[choice]);

            LCDWriteStringXY(4,1,"Integral =");
            Ki[choice] = setParameter(4,16,0,500,Ki[choice]);

            LCDWriteStringXY(5,1,"Derivative =");
            Kd[choice] = setParameter(5,16,0,100,Kd[choice]);
            
            
            Init_PID(choice,Kp[choice],Ki[choice],Kd[choice]);                

            timer = 0;

            cls();
            loadimg(&menu3[0], 1024,0);                  //Draw Menu2
            __delay_ms(500);
        }
 
        Exit:
                        
// ******************************************************************************
        if (TestKey == KEY_4)
        {
            init_lcd();
            cls();
            loadimg(&menu3[0], 1024,0);                         //Draw Menu3
        }
        
// ******************************************************************************
        ClrWdt();                                                               //Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************
