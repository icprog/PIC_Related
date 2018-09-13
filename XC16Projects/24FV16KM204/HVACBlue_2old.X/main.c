
#include "system.h"
// ******************************************************************************
#define DeckFloorOut        _LATA3
#define UtilityRoomFloorOut _LATA2
#define EntranceFloorOut    _LATA11
#define MasterBathFloorOut  _LATA10
#define OfficeFloorOut      _LATB11
#define CraftRoomFloorOut   _LATB10
#define SEBasementFloorOut  _LATA7
#define MediaRoomFloorOut   _LATC9
#define GarageFloorOut      _LATC8
#define backLightOn         _LATA1
#define numSamples          60                                                  //Number of samples to average for Outdoor Air temp

// ******************************************************************************
int16_t __attribute__ ((space(eedata))) Settings[85];                               // Global variable located in EEPROM (created by the space()attribute

RTCTime time;                                                                   // declare the type of the time object

uint8_t const setpoint[]  = {0,  8, 16, 24, 32, 40, 48, 56, 64, 72, 80};  //setpoint EEPROM Address "offset" values

uint8_t const deadband[]  = {2, 10, 18, 26, 34, 42, 50, 58, 66, 74, 82};  //dead band EEPROM Address "offset" values

uint8_t const BiasWarm[]  = {118,120,122,124,126,128,130,132,134,136,138};//Setpoint Bias when Temperature above +10C (EEPROM offset values)

uint8_t const Bias0[]     = {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};  //Setpoint Bias when Temperature between -5C and 5C (Hard coded, non-EEPROM values)

uint8_t const biasNeg5[]  = {96,98,100,102,104,106,108,110,112,114,116};  //Setpoint Bias when Temperature between -15C and -5C (EEPROM Address "offset" values)

uint8_t const biasNeg15[] = {4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84};  //biasNeg15 (Temperature between -15C and -25C) EEPROM Address "offset" values

uint8_t const biasNeg25[] = {6, 14, 22, 30, 38, 46, 54, 62, 70, 78, 86};  //biasNeg25 (Temperature below -25C) EEPROM Address "offset" values

uint8_t const startMonth = 88, startDay = 90, endMonth = 92, endDay = 94; //EEPROM Address offset values to store user settable Start/Stop dates

uint8_t const earlyStartMonth = 140, earlyStartDay = 142, extendedEndMonth = 144, extendedEndDay = 146;

uint8_t const extendedRunEnable[] = {148,150,152,154,156,158,160,162,164,166,168};

int16_t Bias[] =                    {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};    // Storage Location for Bias Values (When between Switch points)

char channel[] =                    {  4,  0,  5,  6, 10, 11, 12, 17, 18, 20, 19};  // Reversed both

char *desc[] = {"Deck Floor ","Deck Rm Air ","Utility Flr ","Entrance Flr ","Master Bath ","Office Floor ","Craft Rm Flr ","SE BedRm Flr ","Media Rm Flr ","Garage Rm Air","Garage Floor "};    // Reversed both

_Bool enabled[11]               = {0};                              // Determines if an Output should be on at this date.

_Bool outState[11]              = {0};                              // State of the output (1 or 0) not the actual output, which is _Bool Out[]

_Bool lastOutState[11]          = {0};                              // Check if the outState has changed

unsigned int outStateCounter[11]= {0,0,0,0,0,0,0,0,0,0,0};          // Track which outputs are turning on most often

//int16_t outStateCounter[11] = {342,407,319,578,414,84,66,0,24,71,49}; //Keeps track of which outputs are turning on most often

uint8_t call = 0;                                                   // Set HMI key delay time, based on what function you are in 

_Bool powerFail = 1;                                                // Setting powerFail to 1, displays "set Clock" Message

int16_t samples[numSamples];                                        // Outside Air Temperature Samples to average temp over x number of samples

// *************** Main ********************************************************
int16_t main(void)
{
    InitApp();
    
// *****************************************************************************
    int8_t loopCounter = 12, previousLoopCounter = 12;              // Loopcounter value determines which screen info is displayed on LCD
    
    int16_t OutAirTemp;                                             // Average Outside air temp (Avg of numSamples))
    
    int16_t tempOutAirTemp;                                         // Temporary calculated Outside air temp as read by the ADC 

    int16_t Temp[11];                                               // Calculated loop temperatures as read by the ADC, these display in 1/10 of Degrees Celcius
    
    uint8_t sampleIndex = 0;                                        // Calculate average outdoor temp over time with Sample averaging
    
    int16_t total = 0;                                              // Running total of Outside air samples (for smoothing)
    
    uint8_t StartUpDelay = 0;                                       // Startup delay so outputs do not turn on until after OutAirTemp has been averaged
    
    int16_t OldTemp[11] = {300};                                    // Smooth (average) temperature readings

    bool Out[11] = {0};                                             // Startup values for all outputs, 0 = OFF (Output 0 - 11))
    
    _Bool OutSum = 0;                                               // Sum of all Outputs
    
    uint8_t i = 0;                                                  // For loop counter
    
    int8_t TestKey;                                                 // Variable used for Storing Which Menu Key is Pressed

    int16_t internalBGV;                                            // Variable to store the internal BandGapVoltage as read by the ADC
    
    int16_t backLightTimer = 0;                                     // Turn off the LCD backlight after an interval of inactivity (60 seconds))

    uint8_t previous_time = 0;                                      // Limit temp readings and LCD updates to once a second

// *****************************************************************************
    while(1)
    {
        time = getRTCTime();                                        // get the time
        
        uint16_t timer = 0;                                         // Count up time in a loop, to auto exit if user in a menu too long

// *************** Read Raw Temperature Data ***********************************
        if(previous_time != time.second)                            // Only update if an additional second has passed
        {
            tempOutAirTemp = ((ADCRead(9) - 840)/3.276 - 500);      // Read Outdoor air temperature & assign it to a temporary variable 
            
            total = total - samples[sampleIndex];                   // Subtract the oldest sample data from the total

            samples[sampleIndex] = tempOutAirTemp;                  // Assign the just read temperature to the location of the current oldest data

            total = total + samples[sampleIndex];                   // Add that new sample to the total
            
            sampleIndex += 1;                                       // and move to the next index location
            
            if(sampleIndex >= numSamples)
            {
                sampleIndex = 0;
            }
            
            OutAirTemp = total / numSamples;                        // assign the average value of total to the OutAirTemp variable


            for(i=0;i<11;i++)
            {
                Temp[i] = ADCRead(channel[i]);                      // Read All 11 Floor Temperatures
            }
// ******************************************************************************
//            Temp[0] = ADCRead(0);                                               //Read Deck air temperature Pin 19
// ******************************************************************************
//            Temp[1] = ADCRead(4);                                               //Read Deck floor temperature Pin 23
// ******************************************************************************
//            Temp[2] = ADCRead(5);                                               //Read Utility room floor temperature Pin 24
// ******************************************************************************
//            Temp[3] = ADCRead(6);                                               //Read Entrance floor temperature Pin 25
// ******************************************************************************
//            Temp[4] = ADCRead(10);                                              //Read Master bathroom floor temperature Pin 14
// ******************************************************************************
//            Temp[5] = ADCRead(11);                                              //Read Office floor temperature Pin 11
// ******************************************************************************
//            Temp[6] = ADCRead(12);                                              //Read Craft room floor temperature Pin 10
// ******************************************************************************
//            Temp[7] = ADCRead(17);                                              //Read SE basement bedroom floor temperature Pin 41
// ******************************************************************************
//            Temp[8] = ADCRead(18);                                              //Read Media room floor temperature Pin 42
// ******************************************************************************
//            Temp[9] = ADCRead(19);                                              //Read Garage floor temperature Pin 43
// ******************************************************************************
//            Temp[10] = ADCRead(20);                                             //Read Garage room air temperature Pin 44
// ******************************************************************************
            internalBGV = ADCRead(0x1A);                            //Read the internal band Gap Voltage, used later to measure input voltage
// *************** Calculate Temperatures **************************************
        
            for(i = 0;i<11;++i)
            {
            Temp[i] = TempCalc(Temp[i]);
        
            if(Temp[i] > OldTemp[i] + 1 || Temp[i] < OldTemp[i] - 1)
            {
                Temp[i] = ((OldTemp[i] + Temp[i])/2);
                OldTemp[i] = Temp[i];
            }
            else Temp[i] = OldTemp[i];
            }
// *************** Determine Temperature Biases ********************************
            for(i=0;i<11;i++)
            {
                if(OutAirTemp <= -250)
                {
                    Bias[i] = eepromGetData(biasNeg25[i]);
                }
            
                else if (OutAirTemp > -250 && OutAirTemp <= -240)
                {
                    Bias[i] = Bias[i];
                }
    
                else if (OutAirTemp > -240 && OutAirTemp <= -150)
                {
                    Bias[i] = eepromGetData(biasNeg15[i]);
                }
            
                else if (OutAirTemp > -150 && OutAirTemp <= -140)
                {
                    Bias[i] = Bias[i];
                }
    
                else if (OutAirTemp > -140 && OutAirTemp <= -50)
                {
                    Bias[i] = eepromGetData(biasNeg5[i]);
                }

                else if (OutAirTemp > -50 && OutAirTemp <= -40)
                {
                    Bias[i] = Bias[i];
                }
    
                else if (OutAirTemp > -40 && OutAirTemp <= 100)
                {
                    Bias[i] = Bias0[i];
                }
    
                else if (OutAirTemp > 100 && OutAirTemp <= 110)
                {
                    Bias[i] = Bias[i];
                }
    
                else 
                {
                    Bias[i] = eepromGetData(BiasWarm[i]);
                }
            }

// *************** Turn off all outputs & disables writes to the output pins, unless between auto start & stop dates

            if (((time.month < eepromGetData(earlyStartMonth)) || (time.month <= eepromGetData(earlyStartMonth) && time.day < eepromGetData(earlyStartDay)))  && ((time.month > eepromGetData(extendedEndMonth)) || ((time.month >= eepromGetData(extendedEndMonth)) && (time.day >= eepromGetData(extendedEndDay)))))
            {
                for(i=0;i<11;i++)
                {
                    enabled[i] = 0;
                }
            }
            else if (((time.month < eepromGetData(startMonth)) || (time.month <= eepromGetData(startMonth) && time.day < eepromGetData(startDay)))  && ((time.month > eepromGetData(endMonth)) || ((time.month >= eepromGetData(endMonth)) && (time.day >= eepromGetData(endDay)))))
            {
                for(i=0;i<11;i++)
                {
                    if (eepromGetData(extendedRunEnable[i]) == 1)
                    {
                        enabled[i] = 1;
                    }
                    else
                    {
                        enabled[i] = 0;
                    }
                }
            }
            else
            {
                for(i=0;i<11;i++)
                {
                    enabled[i]=1;
                }
            }
           

            if (StartUpDelay > numSamples)
            {
                for (i=1;i<10;i++)
                {
                    if(enabled[i] == 1)
                    {
                        Out[i] = SetOutput(Out[i], eepromGetData(setpoint[i]), Bias[i], Temp[i], eepromGetData(deadband[i]));       //Set Outputs 
                    }
                    else
                    {
                        Out[i] = 0;
                    }
                }

                if(Out[1] == 1)   // Added this to fix Master running because of Deck  // If Deck Air Temp is NOT calling, // Reversed both and reversed Out from 0 to 1
                {
                    Out[0] = 1;                                                     // turn OFF Deck Floor Out           // Reversed both and reversed Out from 0 to 1
                    outState[0]=1;    
                }
                else 
                {
                    Out[0]=0;                       // Reversed both added else to turn off Output
                    outState[0]=0;    
                }
       
                if(Out[9] == 1)                                                    // If Garage Air Temp is NOT calling, // Reversed both and reversed Out from 0 to 1
                {
                    Out[10] = 1;                                                     // turn OFF Garage Floor Out // Reversed both and reversed Out from 0 to 1
                    outState[10]=1;    
                }
                else
                {
                    Out[10]=0;                      // Reversed both added else to turn off Output
                    outState[10]=0;    
                }
                
                for(i=0;i<11;i++)                                                                                               //Set screen state indicators
                {
                    if(enabled[i] == 1)
                    {
                        if (Temp[i] <= eepromGetData(setpoint[i]) + Bias[i])            //If Out is not Off
                        {
                            outState[i] = 1;
                        }
          
                        else if (Temp[i] >= eepromGetData(setpoint[i]) + Bias[i] + eepromGetData(deadband[i]))
                        {
                            outState[i] = 0;
                        }
            
                        else
                        {
                            outState[i] = outState[i];
                        }
            
                        if(outState[i] != 0)
                        {
                            if (outState[i] != lastOutState[i])                         //If Out changed since last read
                            {
                                outStateCounter[i]+=1;                                  //Increment the OutState Counter
                            }
                        }
                        lastOutState[i] = outState[i];                                  //And set them equal to each other, so, it doesn't count again next time through
                    }
                    else
                    {
                        outState[i] = 0;
                    }
// ******************************************************************************
                    
                    OutSum = Out[1] + Out[2] + Out[3] + Out[4] + Out[5] + Out[6] + Out[7] + Out[8] + Out[9];// Reversed both
        
//                    if(outSumOldState != OutSum)                                        // OutSum has changed,
  //                  {
                    if(OutSum != 0)                                             // because an Out is turned on
                    {
                        for(i=1;i<10;i++)                           // Reversed both (took 0 and 10 out of equation)
                        {
                            if(enabled[i] == 1)
                            {
                                if (Temp[i] < eepromGetData(setpoint[i]) + eepromGetData(deadband[i]) + Bias[i])// Check for other PV's below SP + DB + Bias,
                                {
                                    Out[i] = 1;                                 // and turn them on.
                                }

                                else
                                {
                                    Out[i] = 0;                                 // Turn them off if they are already too hot!!
                                }
                            }
                        }
                    }
    //                    outSumOldState = OutSum;
      //              }
// ******************************************************************************
                    if(Out[1] == 1)                                                     // If Deck Air Temp is NOT calling, // Reversed both and reversed Out from 0 to 1
                    {
                        Out[0] = 1;                                                     // turn OFF Deck Floor Out           // Reversed both and reversed Out from 0 to 1
                    }
        
                    if(Out[9] == 1)                                                    // If Garage Air Temp is NOT calling,   // Reversed both and reversed Out from 0 to 1
                    {
                        Out[10] = 1;                                                     // turn OFF Garage Floor Out    // Reversed both and reversed Out from 0 to 1
                    }
        
                    DeckFloorOut =          Out[0];                 // Reversed both
                    UtilityRoomFloorOut =   Out[2];
                    EntranceFloorOut =      Out[3];
                    MasterBathFloorOut =    Out[4];
                    OfficeFloorOut =        Out[5];
                    CraftRoomFloorOut =     Out[6];
                    SEBasementFloorOut =    Out[7]; 
                    MediaRoomFloorOut =     Out[8];
                    GarageFloorOut =        Out[10];                // Reversed both
            
                }
            }
            else
            {
                StartUpDelay +=1;
                
                for (i=0;i<11;i++)
                {
                    enabled[i] = 0;
                }
            }
            
            previous_time = time.second;                                        // We have updated all readings (because it was a new second), so set previous_time to current time
        }

// ******************************************************************************
        if(previousLoopCounter != loopCounter)
        {
            LCD_Clear();
            previousLoopCounter = loopCounter;
        }
// ******************************************************************************

        
        if(loopCounter < 11)
        {
            LCD_Set_Cursor(0,0);                                                //LCD Line 0 Display
            LCD_Write_String(desc[loopCounter]);
            LCDWriteStringXY(0,13,"Loop ");
            LCD_Write_Int(loopCounter,2,0,0);
            
            LCDWriteStringXY(1,0,"Bs");                                        //LCD Line 1 SetPoint Display
            LCDWriteIntXY(1,2,eepromGetData(setpoint[loopCounter]) + Bias[loopCounter],3,1,1);
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCDWriteStringXY(1,10,"Set:");
            LCDWriteIntXY(1,14,eepromGetData(setpoint[loopCounter]),3,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char(67);

            LCDWriteStringXY(2,0,"Temp:");                                      //LCD Line 2 Temperature Display
            LCDWriteIntXY(2,5,Temp[loopCounter],3,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char(67);

            LCDWriteStringXY(2,12,"Db:");                                       //LCD Line 2 Deadband Display
            LCDWriteIntXY(2,15,eepromGetData(deadband[loopCounter]),2,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char(67);
            
            LCDWriteIntXY(3,0,outStateCounter[loopCounter],5,0,0);
            
            LCDWriteStringXY(3,6,"On: ");                                       //LCD Line 3 Out Display
            
            if(outState[loopCounter] == 1)
            {
                LCD_Write_Char('Y');
            }
            
            else
            {
                LCD_Write_Char('N');
            }

            LCDWriteStringXY(3,12,"FOn: ");
            
            if(outState[loopCounter] == 1 || Out[loopCounter] == 0)
            {
                LCD_Write_Char('N');
            }
            
            else
            {
                LCD_Write_Char('Y');
            }
        }
// ******************************************************************************
        
        TestKey = menuRead();

        if(loopCounter == 11)
        {
            LCDWriteIntXY(0,0,outStateCounter[0],5,0,0);                // Reversed both
            LCDWriteIntXY(0,6,outStateCounter[1],5,0,0);                // Reversed both
            LCDWriteIntXY(0,12,outStateCounter[2],5,0,0);
            LCDWriteIntXY(1,0,outStateCounter[3],5,0,0);
            LCDWriteIntXY(1,6,outStateCounter[4],5,0,0);
            LCDWriteIntXY(1,12,outStateCounter[5],5,0,0);
            LCDWriteIntXY(2,0,outStateCounter[6],5,0,0);
            LCDWriteIntXY(2,6,outStateCounter[7],5,0,0);
            LCDWriteIntXY(2,12,outStateCounter[8],5,0,0);
            LCDWriteIntXY(3,0,outStateCounter[9],5,0,0);               // Reversed both
            LCDWriteIntXY(3,6,outStateCounter[10],5,0,0);                // Reversed both
            LCD_Set_Cursor(3,12);
            LCD_Write_Int(405515/internalBGV,3,2,0);                          //Write the BandGap voltage to the LCD
            LCD_Write_Char('V');

            if(TestKey == KEY_RESET)                                            //KEY_RESET does a re-set on outStateCounter, if pressed on loop page 11
            {
                TestKey = KEY_NONE;
                
                LCD_Clear();
                LCDWriteStringXY(0,0,"'Enter' ReSets Count");
                
                while(TestKey != KEY_ENTER)                                     //If KEY_ENTER is not pressed,
                {
                    TestKey = menuRead();
                    timer +=1;
                    __delay_ms(20);
                    if (timer > 500)
                    {
                        timer = 0;
                        LCD_Clear();
                        goto done3;                                             //time out and return to previous display
                    }
                }
                
                for(i=0;i<11;i++)                                               //if KEY_ENTER is pressed                                      
                {
                    outStateCounter[i]= 0;                                      //Set all outStateCounters to zero
                }
            }
        }
        
        done3:

// ******************************************************************************
        if(loopCounter == 12)                                                   // This is the Main Display
        {
            if(powerFail == 1)
            {
                LCDWriteStringXY(0,0,"Please Set The Time ");
            }
            
            else
            {
                displayTime();
                LCDWriteStringXY(1,0,"OutSide Temp:");
                LCDWriteIntXY(1,13,OutAirTemp,3,1,1);
                LCD_Write_Char(0);
                LCD_Write_Char(67);
                LCDWriteStringXY(2,0," <- / -> Keys page ");
                LCDWriteStringXY(3,0," through Loop Info ");
            }
        }

        
// *************** HeartBeat displays the HeartBeat on the LCD *****************
        heartBeat();  
        
// *************** Back Light Control ******************************************  
        if(TestKey == KEY_NONE)                             // If no key is pressed for 60 seconds
        {                                                   // Turn OFF the LCD Backlight
            backLightTimer += 1;                            // Increment Counter
        }
        else
        {
            backLightTimer = 0;                             // Reset Counter
        }
        
        if (backLightTimer < 4450)
        {
            backLightOn = 1;
        }
        else
        {
            backLightTimer = 4450;
            backLightOn = 0;
        }
        
// *************** Processor Reset Key Test ************************************
        if (TestKey == KEY_RESET)                           //This will soft reset the processor
        {
            TestKey = KEY_NONE;
            
            LCD_Clear();
            LCDWriteStringXY(0,0," You want to Reset? ");
//            LCDWriteStringXY(1,0,"ReSet the Processor");
            LCDWriteStringXY(2,0,"Hit 'Enter' to ReSet");

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                timer +=1;
                __delay_ms(20);
                if (timer > 500)
                {
                    timer = 0;
                    LCD_Clear();
                    goto done;
                }
            }
            asm( "reset" );
        }
        
        done:
// ******************************************************************************
        
        
        if (TestKey == KEY_SET_TIME)
        {
            TestKey = KEY_NONE;
            __delay_ms(500);
            
            LCD_Clear();
            LCDWriteStringXY(0,0,"Press 'ENTER' to Set");
            LCDWriteStringXY(1,0,"Time");

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                timer +=1;
                __delay_ms(20);
                if (timer > 500)
                {
                    timer = 0;
                    LCD_Clear();
                    goto done2;
                }
            }
            SetTime();
        }
        
        done2:
// ******************************************************************************

        if (TestKey == KEY_SET_START)                                           // Set Heating Season Start/Stop Dates
        {
            LCD_Clear();

            LCDWriteStringXY(0,0,"Start Month?");
            eepromPutData(startMonth, SetStartEndMonth(eepromGetData(startMonth)));
            LCDWriteStringXY(2,0,"Start Day?");
            eepromPutData(startDay, SetStartEndDay(eepromGetData(startDay)));

            LCD_Clear();
            
            LCDWriteStringXY(0,0,"Early Start Month?");
            eepromPutData(earlyStartMonth, SetStartEndMonth(eepromGetData(earlyStartMonth)));
            LCDWriteStringXY(2,0,"Early Start Day?");
            eepromPutData(earlyStartDay, SetStartEndDay(eepromGetData(earlyStartDay)));

            LCD_Clear();
            
            LCDWriteStringXY(0,0,"End Month?");
            eepromPutData(endMonth, SetStartEndMonth(eepromGetData(endMonth)));
            LCDWriteStringXY(2,0,"End Day?");
            eepromPutData(endDay, SetStartEndDay(eepromGetData(endDay)));

            LCD_Clear();

            LCDWriteStringXY(0,0,"Extended Run Month?");
            eepromPutData(extendedEndMonth, SetStartEndMonth(eepromGetData(extendedEndMonth)));
            LCDWriteStringXY(2,0,"Extended Run Day?");
            eepromPutData(extendedEndDay, SetStartEndDay(eepromGetData(extendedEndDay)));

            LCD_Clear();
        }

// ******************************************************************************
        if(TestKey == KEY_LEFT)
        {
            loopCounter -=1;
            
            if(loopCounter < 0)
            {
                loopCounter = 12;
            }
        }
        
// ******************************************************************************
        if(TestKey == KEY_RIGHT)
        {
            loopCounter +=1;
            
            if(loopCounter >12)
            {
                loopCounter = 0;
            }
        }
        
// ******************************************************************************
        if (TestKey == KEY_MENU)
        {
            int8_t choice = 5;

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                
                if(timer > 1000)
                {
                    timer = 0;
                    goto Exit;                                                  //This uses less memory than TestKey = KEY_ENTER
                    
//                    TestKey = KEY_ENTER;                                      // This functions fine, but forces a write to EEProm
                }

                switch(TestKey)
                {
                    case KEY_DOWN:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;

                    case KEY_LEFT:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;
                        
                    case KEY_UP:
                    {
                        choice += 1;
                            
                        if(choice > 10)
                        {
                            choice = 10;
                        }
                    }
                    break;
                        
                    case KEY_RIGHT:
                    {
                        choice += 1;
                            
                        if(choice > 10)
                        {
                            choice = 10;
                        }
                    }
                    break;
                    
                    case KEY_RESET:
                    {
                        goto Exit;
                    }
                    break;
                        
                }

                if(timer < 2)
                {
                    LCD_Clear();
                }

                LCD_Set_Cursor(0,0);
                LCD_Write_String("Set Temperature for");
                LCD_Set_Cursor(1,0);
                LCD_Write_String(desc[choice]);
                LCDWriteStringXY(2,0,"Up/Dn Keys to change");
                LCDWriteStringXY(3,0,"Enter Key for Yes   ");
                
                heartBeat();                                                    // HeartBeat displays the HeartBeat on the LCD,
                                                                                // but, also increments mainTimer every second
                timer += 1;
            }
            
//            TestKey = 9;
            
            LCD_Clear();


            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"Set Tmp");
            eepromPutData(setpoint[choice], TempSetpoint(eepromGetData(setpoint[choice])));
            
            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"Set DB");
            eepromPutData(deadband[choice], SetDeadband(eepromGetData(deadband[choice])));            

            LCD_Clear();

            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"WrmBias");
            eepromPutData(BiasWarm[choice], SetBiasWarm(eepromGetData(BiasWarm[choice])));

            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"-5 Bias");
            eepromPutData(biasNeg5[choice], SetBiasNeg5(eepromGetData(biasNeg5[choice])));
            
            LCD_Clear();

            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"-15Bias");
            eepromPutData(biasNeg15[choice], SetBiasNeg15(eepromGetData(biasNeg15[choice])));

            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"-25Bias");
            eepromPutData(biasNeg25[choice], SetBiasNeg25(eepromGetData(biasNeg25[choice])));

            LCD_Clear();

            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"Ext Run");
            eepromPutData(extendedRunEnable[choice], SetExtendedRunBit(eepromGetData(extendedRunEnable[choice])));
            
            Exit:
                        
            LCD_Clear();
        }
// ******************************************************************************
        ClrWdt();                                                               //Clr (Re-Set) the WatchDog Timer
    }
    return(0);
}
//***************************************************************************************************************************************************************
