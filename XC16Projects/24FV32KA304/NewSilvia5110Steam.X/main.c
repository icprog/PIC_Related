// Add Escape keys to user menu's

#include    "system.h"
#include    "menumain.h"
#include    "coffee.h"
// *****************************************************************************
#define piezoOutput             _LATA1         //FIX        // Output to turn on Piezo, if Brew switch left on too long, or water level too low  Add option for user to disable
#define backLightOFF            _LATA9                  // Backlight is active LOW, so "0" is "ON", "1" is "OFF" Pin 35
#define airPump                 _LATA11                 // Run air pump for bubbler for Water Tank Level
#define pumpOutput              OC1R                    // OC1 will drive water pump
#define boilerOutput            OC2R                    // OC2 will drive Water Boiler
#define steamOutput             OC3R                    // OC3 will drive Steam Boiler
#define groupOutput             _LATB8                  // Coded for software PWM
#define brewSolenoid            _LATA3                  // Control the Brew Water delivery Solenoid
#define steamSolenoid           _LATB9                  // Control the Steam delivery Solenoid
#define waterSolenoid           _LATA2                  // Control the Wand Water delivery Solenoid

// *************** Inputs ******************************************************
//#define waterLevel              level                   // ADCRead(6) is Water Tank level signal
//#define readButtons           ADCRead(7)              // ADC Input to read Button press (User Input Keys) on _RC1 (AN7) Pin 26 

#define boilerTemperature       temp[0]                 // ADCRead(9)
#define steamTemperature        temp[1]                 // ADCRead(0)
#define groupHeadTemp           temp[2]                 // ADCRead(4)

#define power                   bits[0]                 // _RB11 Power switch input state  
#define brewSwitch              bits[1]                 // _RB10 Brew Switch Input
#define steamSwitch             bits[2]                 // _RA7  Steam Switch Input          
#define waterSwitch             bits[3]                 // _RC9  Water Switch Input          

#define powerSwitch             bits[4]                 // Power Switch (Soft Bit)
#define lastPowerState          bits[5]                 // Last State of powerSwitch (Soft Bit)
#define blink                   bits[6]                 // blink flashes display when water level low
#define steamPower              bits[7]                 // set to turn on steam boiler
#define toggle                  bits[8]                 // toggle display between steam & group Temperatures
// *****************************************************************************

//**************** Timer2 set in pwm.c (Timer2 Runs the Shot Counter) **********
// All times are in 1/10th's of a second, so 10 = 1 seconds, 30 = 3 seconds, 15 = 1.5 seconds, etc 

#define max                     256                     // Maximun Pump Output (256 = 100%)
#define min                     26                      // Minimum Pump Output (0 = OFF)
//#define preInfusionDutyCycle    90              //FIX   // This needs to move to EEPROM & have a User Interface set up so user can change it
#define preInfusionDutyCycle    120              //FIX   // This needs to move to EEPROM & have a User Interface set up so user can change it
//#define preInfusionTime         25              //FIX   // length of time to run pump to preInfuse puck (also needs Interface & EEPROM location)
#define preInfusionTime         30              //FIX   // length of time to run pump to preInfuse puck (also needs Interface & EEPROM location)
#define soakTime                (preInfusionTime + 30)//FIX    // Length of time for wetted puck to soak EEPROM
#define startRamp               (soakTime + 30)//FIX    // StartRamp starts pump and Ramps up to Max Pressure
#define continuePull            (800 + 1)               // Shot duration, 80 seconds from Start of Cycle(801)
#define warning                 (850 + 1)               // Turn on Warning Piezo, reminder to turn off switch (851)
//#define steamPumpPower          38                      // DutyCycle to run pump during steam cycle
#define steamPumpPower          45                      // DutyCycle to run pump during steam cycle

#define waterSetpoint           eepromGetData(setpoint[0])
#define steamSetpoint           eepromGetData(setpoint[1])
#define groupHeadSetpoint       eepromGetData(setpoint[2])

#define waterPID                PIDValue[0]
#define steamPID                PIDValue[1]
#define groupHeadPID            PIDValue[2]


#define shotProgressCounter     counter[0]              // Timer for Steps in an extraction
#define shotTimer               counter[1]              // Times the duration of the extraction 
#define warningTimer            counter[2]              // Initiate Piezo Warning if Brew switch not turned OFF
#define shotDisplayTimer        counter[3]              // Determines how long the Shot Timer Value remains on the Display
#define backLightCounter        counter[4]              // Used to count time until Backlight turns Off
#define groupPeriodCounter      counter[5]              // Group PID Period Counter
#define lowWaterReminder        counter[6]              // Remind User level is Low when below 25%
#define numSamples              10                      // Number of samples to average for temp[] readings 
#define PIDDuration             100                     // Number of Program cycles (Period) for Group Head PID
    

// *************** Global Variables ********************************************
int __attribute__ ((space(eedata))) Settings[43];       // Global variable located in EEPROM (created by the space()attribute

RTCTime time;                                           // declare the type of the time object

unsigned int setpoint[] =   {0, 2,  4};                 //setpoint EEPROM Address "offset" values

int const Kp[]          =   {6, 8, 10};

int const Ki[]          =   {12,14,16};

int const Kd[]          =   {18,20,22};

char *desc[]            =   {"Water Temp:","Steam Temp:","Group Temp:"};

int powerFail           =   1;                          //Setting powerFail to 1, instructs the user to set the time

extern int run;

int8_t tuning[3]        =   {0};

char pull               =   0;                          // pull a 25 second shot with a display key

// *************** Main Routine ************************************************
int main(void)
{
    InitApp();
    
    InitializeTimers();
    
    InitializePWM();                                    // Init PWM for Water Pump, Water Boiler, and Steam Boiler

// *************** PWM Controller Initialization *******************************
    uint8_t initCon = 0;
    
    for(initCon=0;initCon<3;initCon++)
    {
        Init_PID(initCon,eepromGetData(Kp[initCon]),eepromGetData(Ki[initCon]),eepromGetData(Kd[initCon]));
    }
        
// *************** Local Variables *********************************************
    uint16_t powerOut       = 0;                        // Power Output Displayed to screen
    
    char errorCount         = 0;                        // errorCount disables power, if water level remains low too long
    
    char errorSustained     = 0;

    uint8_t count2          = 0;                        // count2 ramps pump pressure
    
    static int samples[3][numSamples]      ={[0 ... 2] = {0}}; //Used to average temp[] over "numSamples" of samples
    
    static unsigned int temp[3]     = {0,0,0};
    
    unsigned int shortTermTemp[3]   = {0,0,0};                                              
    
    uint8_t sampleIndex     = 0;                        // Used to calculate average sample of temp[]
    
    static uint32_t total[3]       = {0,0,0};                  // Running total of temp[] samples 
    
    unsigned char testKey   = 0;                        // Variable used for Storing Which Menu Key is Pressed
    
    int bits[9]             = {0,0,0,0,0,0,0,0,0};
 
    //    int internalBGV;
    
    int PIDValue[]          = {0,0,0};                  // PID calculated values (Water, Steam and Group)
    
    int previousSecond      = 0;                        //Used with time.second to limit some stuff to once a second
    
    unsigned int counter[7] = {0,0,0,0,1140,0,0};       // Shot progress, Shot timer, Shot Warning timer, Shot display Timer, Back Light, groupPeriodCounter,
                                                        // Low Water Reminder
    uint16_t level          = 0;
    
    static char ONTimer     = 0;                        // Bit to enable Auto Start of Machine
    
    int8_t groupPulse       = 0;  
    
//    extern int pidIntegral;
    
  //  extern int result;
    //extern float  error, errorValue;
    //extern long derivativeValue;

    
// ******************************************************************************
//    LCDBitmap(&menumain[0], 5, 59);                        //Draw Menu0

    while(1)
    {
        power       =   !_RB11;                         // RB11 is pulled high normally, pulled low by turning ON Power switch, so 0 is ON, 1 is OFF
        
        brewSwitch  =   !_RB10;                         // RB10 is pulled high normally, pulled low by turning ON Brew switch, so 0 is ON, 1 is OFF
        
        steamSwitch =   !_RA7;                          // RA7 is pulled high normally, pulled low by turning ON Steam switch, so 0 is ON, 1 is OFF
        
        waterSwitch =   !_RC9;                          // RC9 is pulled high normally, pulled low by turning ON Water switch, so 0 is ON, 1 is OFF

        time = getRTCTime();                            // get the time
        

// *************** Calculate Temperature Averages ******************************
        shortTermTemp[0] = aTempCalc(ADCRead(9));       // Assign the ADC(9) Boiler Temp to a temporary variable
        total[0] = total[0] - samples[0][sampleIndex];  // Subtract the oldest sample data from the total
        samples[0][sampleIndex] = shortTermTemp[0];     // Assign the just read temperature to the location of the current oldest data
        total[0] = total[0] + samples[0][sampleIndex];  // Add that new sample to the total
        shortTermTemp[0]=total[0]/numSamples;           // Assign the average value of total to the shortTermTemp variable
        if(shortTermTemp[0]>boilerTemperature)boilerTemperature+=1;     // Limit Ramp rate to 1/10th degree/cycle
        else if(shortTermTemp[0]<boilerTemperature)boilerTemperature-=1;// Limit Ramp rate to -1/10th degree/cycle
        else boilerTemperature = boilerTemperature;                     // No change, so leave as is

//        boilerTemperature = total[0]/numSamples;        // Assign the average value of total to the boilerTemperature variable

 //       boilerTemperature = aTempCalc(ADCRead(9));        // Assign the average value of total to the boilerTemperature variable

        shortTermTemp[1] = tempCalc(ADCRead(0));        // Assign the ADC(0) (Steam Temp) to a temporary variable
        total[1] = total[1] - samples[1][sampleIndex];  // Subtract the oldest sample data from the total
        samples[1][sampleIndex] = shortTermTemp[1];     // Assign the just read temperature to the location of the current oldest data
        total[1] = total[1] + samples[1][sampleIndex];  // Add that new sample to the total
        steamTemperature = total[1] / numSamples;       // Assign the average value of total to the GroupHeadTemp variable

 
        shortTermTemp[2] = tempCalc(ADCRead(4));        // Assign the ADC(4) Group Head Temp to a temporary variable
        total[2] = total[2] - samples[2][sampleIndex];  // Subtract the oldest sample data from the total
        samples[2][sampleIndex] = shortTermTemp[2];     // Assign the just read temperature to the location of the current oldest data
        total[2] = total[2] + samples[2][sampleIndex];  // Add that new sample to the total

        sampleIndex += 1;                               // and move to the next index location
        if(sampleIndex >= numSamples)                   // If we have reached the max number of samples
        {
            sampleIndex = 0;                            // Reset to zero
        }
        groupHeadTemp = total[2] / numSamples;          // Assign the average value of total to the GroupHeadTemp variable

// *************** Auto Turn ON Machine at User selected Dates & Times *********
        if(previousSecond != time.second)                // Only execute the following code once a second
        {
            previousSecond = time.second;

            ONTimer = runTimer(time.weekday,time.hour,time.minute);
            
            if(power==1 || ONTimer==1)
            {
                powerSwitch = 1;                        // powerSwitch is the Virtual Power control Variable
                (power==1)?(run=0):(run=run);           // if power switch is on, disable AutoStart, or Kill AutoStart by cycling Power Switch (run is in RTCC.C)
            }
            else
            {
                powerSwitch = 0;                        // powerSwitch can turn OFF Machine, even if Power is ON
            }
            
// *************** Check for and re-act to Low Water Level *********************
            errorCount>9?powerSwitch=0:powerSwitch;    // If errorCount (water Level Low) > 9 seconds, turn OFF Power
            
//            level = waterTankLevel();
            level = 30;
            
            if(level < 15)
            {
                errorCount +=1;                         // Increment the Error Counter
                piezoOutput = 1-piezoOutput;            // Turn On the Piezo Alarm
                errorCount>10?(errorCount=10,piezoOutput=0):errorCount; // Limit Error Counter to 10, and turn piezo OFF
            }
            else
            {
                errorCount -= 1;
                errorCount<0?errorCount=0:errorCount;
            }
            
            if(errorCount > 1)
            {
                errorSustained>8?airPump=0:(airPump=1,errorSustained+=1);
            }
            
// *************** Increment counter to Auto turn OFF BackLight ****************
            backLightCounter +=1;                       // Increment the "Seconds" counter to turn OFF Backlight

// ******************************************************************************
            if(powerSwitch)
            {
                if(lastPowerState!=powerSwitch)
                {
                    LCDClear();
                    LCDBitmap(&menumain[0], 5, 59);        //Draw Menu0
                    gotoXY(1,4);
                    LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
                    OC1CON2bits.OCTRIS  = 0;
                    OC2CON2bits.OCTRIS  = 0;
                    OC3CON2bits.OCTRIS  = 0;
                    backLightCounter    = 0;
                    backLightOFF        = 0;
                }
                
                if(powerFail == 1)
                {
                    LCDWriteStringXY(4,1,"Press \"SET\" to Set");
                    LCDWriteStringXY(4,2,"the Current Time");
                }
                else
                {
                    if(tuning[0])
                    {
                        waterPID        = PID_Calculate(0, waterSetpoint, boilerTemperature);// Calculate Water PID Value
                        goto there;
                    }
                    
                    if(tuning[1])
                    {
                        steamPID        = PID_Calculate(1, steamSetpoint, steamTemperature); // Calculate Steam PID Value
                        goto there;
                    }
                    
                    if(tuning[2])
                    {
                        OC2CON2bits.OCTRIS  = 1;
                        OC3CON2bits.OCTRIS  = 1;
                        groupHeadPID    = PID_Calculate(2, groupHeadSetpoint, groupHeadTemp);// Calculate Group PID Value
                        goto there;
                    }

                    waterPID        = PID_Calculate(0, waterSetpoint, boilerTemperature);// Calculate Water PID Value
                    steamPID        = PID_Calculate(1, steamSetpoint, steamTemperature); // Calculate Steam PID Value
                    groupHeadPID    = PID_Calculate(2, groupHeadSetpoint, groupHeadTemp);// Calculate Group PID Value
                    
                    displayTime();
                    
                    LCDWriteStringXY(2,1,desc[0]);
                    LCDWriteIntXY(52,1,boilerTemperature,4,1,0);
                    LCDWriteCharacter(123);         // generate degree symbol in font list
                    LCDWriteCharacter(70);

                    LCDWriteStringXY(2,2,desc[1]);
                    LCDWriteIntXY(52,2,steamTemperature,4,1,0);
                    LCDWriteCharacter(123);         // generate degree symbol in font list
                    LCDWriteCharacter(70);

                    if(!shotTimer)
                    {
                        toggle+=1;
                    
                        if(toggle>4)
                        {
                            toggle=5-toggle;
                            LCDWriteStringXY(2,3,desc[2]);
                            LCDWriteIntXY(52,3,groupHeadTemp,4,1,0);
                            LCDWriteCharacter(123);             // generate degree symbol in font list
                            LCDWriteCharacter(70);
                            LCDWriteCharacter(' ');
                        }
                    
                        if(toggle>1)
                        {
                            LCDWriteStringXY(2,3,"Tank Level:  ");
                            LCDWriteInt(level,-1,0,0);
                            LCDWriteCharacter('%');
                            LCDWriteString("    ");
                    
                            if(level < 25)                  // Tank level < 25%
                            {
                                blink = 1 - blink;          // toggle blink variable
        
                                if(blink)
                                {
                                    LCDWriteStringXY(48,3,"LOW");
                                    LCDWriteString("    ");

                                    lowWaterReminder+=1;    

                                    if(lowWaterReminder>29) // blink toggles every other second, so, 1/2 the delay time - 1.
                                    {
                                        piezoOutput=1;
                        
                                        if(!brewSwitch)     // Disable delay if we are pulling a shot (will mess with pump timing)
                                        {
                                            __delay_ms(30); // Short, but, annoying piezo reminder
                                        }
                                        piezoOutput=0;      
                                        lowWaterReminder=0;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        LCDWriteStringXY(2,3,"Shot Timer:  ");
                        LCDWriteIntXY(48,3,shotTimer,-1,1,0);
                        LCDWriteString("     ");
                    }                    
                }
            }
            else
            {
                LCDBitmap(&coffee[0], 0,504);           //Draw Splash Screen
                gotoXY(1,4);
                LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
                backLightCounter    +=1200;             // 1200 counts is the number required to turn OFF the Backlight
                waterSolenoid       = 0;
                steamSolenoid       = 0;
                brewSolenoid        = 0;
                piezoOutput         = 0;
                airPump             = 0;
                groupHeadPID        = 0;                // Turn OFF Group Head Heat
                groupOutput         = 0;                // Zero Group output, as there will be no more writes, so, if we don't zero, we do not know where it will be
                OC1CON2bits.OCTRIS  = 1;                // Tri-State the OC1 Pin, if powerSwitch is OFF
                OC2CON2bits.OCTRIS  = 1;                // Tri-State the OC2 Pin, if powerSwitch is OFF
                OC3CON2bits.OCTRIS  = 1;                // Tri-State the OC3 Pin, if powerSwitch is OFF
                shotTimer           = 0;                // Re-Set the ShotTimer
                pull                = 0;
            }
            lastPowerState          = powerSwitch;
        }
        
        there:

// *************** Run Air Pump once an hour for Level transmitter *************
        if(powerSwitch)
        {
            if(time.minute == 0 && time.second < 5)
            {
                airPump = 1;
            }
            else
            {
                airPump = 0;
            }

// *************** Drive PID Outputs *******************************************
            groupPeriodCounter+=1;
            
//            LCDWriteIntXY(0,0,(groupHeadSetpoint-groupHeadTemp),4,1,0);
  //          LCDWriteCharacter(' ');
    //        LCDWriteIntXY(34,0,(groupOutput),1,0,0);
      //      LCDWriteIntXY(42,0,(groupPeriodCounter),3,0,0);
        //    LCDWriteCharacter(' ');
          //  LCDWriteIntXY(64,0,(groupHeadPID),3,0,0);
            //LCDWriteCharacter(' ');
        
            if(groupPeriodCounter >= PIDDuration)
            {
                groupPeriodCounter = 0;
            }
        
            if(groupHeadPID > groupPeriodCounter)
            {
                groupOutput = 1;
            }
            else
            {
                groupPulse-=1;
                if(groupPulse<0)groupPulse=0;

                if(!groupPulse)
                {
                    if(groupHeadTemp+10<groupHeadSetpoint)
                    {
                        groupPulse=100;
                    }
                }
            
                if(groupPulse>90)
                {
                    groupOutput=1;
                }
                else groupOutput = 0;
            }
            
    // OC3 is Initialized as edge aligned, OC2 as center-aligned (OC3R is dutycycle for OC3, OC2R is start of cycle for OC2)
            if(steamPower)                              //Steam setpoint takes priority
            {                                     
                OC3R=steamPID;                          // Start Steam Boiler Output at beginning of cycle, can use up to 100% of cycle    
                    
                if(steamTemperature>2870)
                {
                    OC3R        =   1;
                }

                if(steamSwitch)
                {
                    steamSolenoid   =   1;              // Let water into Steam Boiler
                    OC3R            +=  6000;           // Sum 6000 onto PID output for steamPID
                    pumpOutput      =   steamPumpPower; // Run water pump at flow required to make steam
                }
                else
                {
                    steamSolenoid   =   0;
                }

                OC2R=0X1E85-waterPID+OC3R;
                
                (waterPID+OC2R>0X1E84)?(OC2RS=0X1E84):(OC2RS=waterPID+OC2R+1); // Water PID takes what it needs from whatever cycle is left
                
//                LCDWriteIntXY(2,0,waterPID,4,0,0);
  //              LCDWriteIntXY(22,0,steamPID,4,0,0);
    //            LCDWriteIntXY(44,0,groupOutput,2,0,0);
//                LCDWriteIntXY(44,0,OC2R,4,0,0);
  //              LCDWriteIntXY(66,0,OC3RS,4,0,0);

                LCDWriteStringXY(68,5,"ON ")
            }
            else                                //Water setpoint takes priority
            {
//                LCDWriteIntXY(2,0,waterPID,4,0,0);
  //              LCDWriteIntXY(22,0,steamPID,4,0,0);
    //            LCDWriteIntXY(44,0,groupOutput,2,0,0);
//                LCDWriteIntXY(44,0,OC3R,4,0,0);
  //              LCDWriteIntXY(66,0,OC2R,4,0,0);

                LCDWriteStringXY(68,5,"OFF")

                steamSolenoid=0;

                OC3R=0;
                OC2R=0x1E85-waterPID;           // OC2R must be at least 1, so 0x1E85 instead of 0x1E84!!
            }
            

// *************** Brew a Shot of Espresso *************************************
            
            if(brewSwitch)
            {
                if(shotProgressCounter<200)OC2R = 2;// Turn Boiler Output ON (for 20 seconds), rather than wait for PID to catch Temp drop
                
                backLightCounter = 0;           // Turn on Backlight if you are pulling a shot.
                
                T2CONbits.TON       =   1;      // Turn Timer2 ON
                
                shotDisplayTimer    =   0;      // Timer to reset Shot Counter    
                
                if(shotProgressCounter <= preInfusionTime)
                {
                    brewSolenoid=1;
                    pumpOutput = preInfusionDutyCycle;
                    pull+=1;
                }
                
                if(shotProgressCounter > preInfusionTime && shotProgressCounter <= soakTime)
                {
                    pumpOutput = 0;
                    pull = 0;
                }

                if (shotProgressCounter > soakTime && shotProgressCounter <= startRamp)               
                {
                    if(pumpOutput <= max)
                    {
                        count2+=1;
                        
//                        if(count2 >5)           // 13 gets us to 100% in 2.5 seconds (the current amount of StartRamp Time)
                        if(count2 >4)           // 13 gets us to 100% in 2.5 seconds (the current amount of StartRamp Time)
                        {
//                            if(pumpOutput<max) pumpOutput +=16;
                            if(pumpOutput<max) pumpOutput +=12;
                            count2 = 0;
                        }
                    }
                }
            
                if(shotProgressCounter > startRamp && shotProgressCounter <= continuePull)
                {
                    if(pumpOutput >= min)
                    {   
                        count2 +=1;
                        
//                        if(count2 > 15)
                        if(count2 > 10)
                        {
//                            pumpOutput -=2;
                            pumpOutput -=1;
                            count2 = 0;
                        }
                    }
                } 
                    
                if(shotProgressCounter > 300 + preInfusionTime + soakTime)//&& shotProgressCounter < warning-30)// Allow up to 30 second pull, them limit pump output to min
                {
                    pumpOutput = min;
                }
                
                if(shotProgressCounter > 600) pumpOutput  = 0;  // Turn off the Pump as well
                
                
                if (shotProgressCounter >= warning)             // 90 Seconds has elapsed without Brew Switch being turned off,
                {                  
                    piezoOutput = 1;                            // Activate Piezo Buzzer for 1/2 second
                }

                if(shotProgressCounter >= warning + 5)          // Piezo has been on for 1/2 second
                { 
                    piezoOutput = 0;                            // So, Shut it off! (pulsing alarm)
                    shotProgressCounter = (warning - 25);       // set time back 2.5 seconds, so it can go again.(in 2 seconds)
                    warningTimer+=1;                            // Increment warningTimer every 2.5 seconds, after 10 counts, alarm will go solid
                }

                if(warningTimer >= 10)                          // After 10 counts of pulsing alarm being ignored,
                { 
                    piezoOutput = 1;                            // turn Piezo on constantly,
                    shotProgressCounter = (warning - 250);      // and set tenCount to below the pulsing alarm time,
                    warningTimer = 10;                          // so Piezo will not start pulsing alarm again.
                }                                       
                
                
                if(IFS0bits.T2IF)
                {
                    shotProgressCounter +=1;
    
                    if(shotProgressCounter > soakTime)
                    {
                        shotTimer +=1;
                    }

                    IFS0bits.T2IF = 0;
                }
                powerOut = pumpOutput*100/256;
            }
            else if(pull)                                       // pull is set by turning OFF the brewSwitch before soakTime has elapsed 
            {                                                   // thus,starting an automatically timed "Shot Pull"
                if(shotProgressCounter<200)OC2R = 2;            // Turn Boiler Output ON (for 20 seconds), rather than wait for PID to catch Temp drop

                backLightCounter = 0;                           // Turn on Backlight if you are pulling a shot.
                
                T2CONbits.TON       =   1;                      // Turn Timer2 ON
                
                if(shotProgressCounter <= preInfusionTime)
                {
                    brewSolenoid=1;
                    pumpOutput = preInfusionDutyCycle;
                }
                
                if(shotProgressCounter > preInfusionTime && shotProgressCounter <= soakTime)
                {
                    pumpOutput = 0;
                }

                if (shotProgressCounter > soakTime && shotProgressCounter <= startRamp)               
                {
                    if(pumpOutput <= max)
                    {
                        count2+=1;
                        
                        if(count2 >5)           // 13 gets us to 100% in 2.5 seconds (the current amount of StartRamp Time)
                        {
                            if(pumpOutput<max) pumpOutput +=16;
                            count2 = 0;
                        }
                    }
                }
            
                if(shotProgressCounter > startRamp && shotProgressCounter <= continuePull)
                {
                    if(pumpOutput >= min)
                    {   
                        count2 +=1;
                        
                        if(count2 > 15)
                        {
                            pumpOutput -=2;
                            count2 = 0;
                        }
                    }
                } 
                    
                if(shotProgressCounter > 250-preInfusionTime+soakTime)
                {
                    pumpOutput  =   0;
                    pull        =   0;
                }

                if(IFS0bits.T2IF)
                {
                    shotProgressCounter +=1;
    
                    IFS0bits.T2IF = 0;
                }
                powerOut = pumpOutput*100/256;
            }
            else
            {
                brewSolenoid        =   0;
                piezoOutput         =   0;
                warningTimer        =   0;
                T2CONbits.TON       =   0;
                shotProgressCounter =   0;
                shotDisplayTimer    +=  1;

                if(shotDisplayTimer >=4000)                                    // Approximately 20 seconds (about 200 counts/second)
                {
                    shotTimer =         0;
                }
            }
            
// ******************************************************************************
            if(waterSwitch)
            {
                waterSolenoid   =   1;
                pumpOutput      =   max;
                OC2R            =   2;
            }
            else
            {
                waterSolenoid   =   0;
            }
        }
        
// ******************************************************************************
        if(!brewSwitch && !steamSwitch && !waterSwitch && !pull)
        {
            pumpOutput          =   0;
        }
        
// ******************************************************************************
        testKey = readButton();
        
        if(testKey!=None)
        {
            groupOutput         = 0;                // Zero Group output, as there will be no more writes, so, if we don't zero, we do not know where it will be
            OC1CON2bits.OCTRIS  = 1;                // Tri-State the OC1 Pin, if powerSwitch is OFF
            OC2CON2bits.OCTRIS  = 1;                // Tri-State the OC2 Pin, if powerSwitch is OFF
            OC3CON2bits.OCTRIS  = 1;                // Tri-State the OC3 Pin, if powerSwitch is OFF
            backLightOFF        = 0;                // sb 0
            backLightCounter    = 0;                // Reset BackLight counter
            lastPowerState      = 2;                // Set to 2 to force a reset of OCTRIS on menu exit, as well as a write to lastPowerState   
        }


        if (testKey == Menu)
        {
            userMenu();
        }
        
        if (testKey == Enter)                      // Reset the LCD
        {
//            Pull();
//            tuning = 1-tuning;
            
            LCDInit();
            __delay_ms(100);
            LCDClear();
            backLightCounter = 0;               // Reset BackLight counter
            LCDBitmap(&menumain[0], 5, 59);        // Draw Menu0
            gotoXY(5,79);
            LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
            __delay_ms(500);
        }
        
        if(testKey==Down)
        {
            steamPower=0;
            lastPowerState = 2;
        }
        
        if(testKey==Up)
        {
            steamPower=1;
            lastPowerState = 2;
        }
// ******************************************************************************
        if(backLightCounter>1200)               // Keep backLight on for short period after Power is switched OFF
        {
            if(backLightCounter>16000)
            {
                backLightOFF = 1;               // so, we might as well shut OFF the LCD BackLight
                backLightCounter=16001;
            }
        }
        else if(backLightCounter > 1199)        // No Keys Pressed for 20 Minutes
        {
            backLightOFF = 1;                   // so, we might as well shut OFF the LCD BackLight
            backLightCounter = 0;               // and, reset the count, so it will turn on with the next Key Press
        }
        else
        {
            backLightOFF = 0;                   
        }
        
// *****************************************************************************
        ClrWdt();                               // Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************
