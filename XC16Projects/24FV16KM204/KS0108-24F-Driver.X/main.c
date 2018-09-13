#include "xc.h"
#include "system.h"                     // System funct/params, like osc/peripheral config
#include "glcd.h"
#include "user.h"                       // User Functions (Temperature Calculation, Heartbeat indication, etc...)
#include "rtcc.h"                       // Real Time clock & Calendar Functions
#include <string.h>                     // Using strlen Functionality
#include "eeprom.h"                     // EEProm used to store Setpoints, deadbands, Bias values, etc, to be retained through power cycle
#include "touch.h"                      // Resistive touch screen interface Routines
#include "adc.h"                        // Analog to Digital conversion periferal, reading temperatures
#include "menus.h"
// ******************************************************************************

#define numSamples          60                                                  //Number of samples to average for Outdoor Air temp
// ******************************************************************************

int __attribute__ ((space(eedata))) Settings[70];                               // Global variable located in EEPROM (created by the space()attribute

RTCTime time;                                                                   // declare the type of the time object

unsigned char const setpoint[]  = {0,  8, 16, 24, 32, 40, 48, 56, 64, 72, 80};  //setpoint EEPROM Address "offset" values

unsigned char const deadband[]  = {2, 10, 18, 26, 34, 42, 50, 58, 66, 74, 82};  //dead band EEPROM Address "offset" values

unsigned char const BiasWarm[]  = {118,120,122,124,126,128,130,132,134,136,138};//Setpoint Bias when Temperature above +10C (EEPROM offset values)

unsigned char const Bias0[]     = {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};  //Setpoint Bias when Temperature between -5C and 5C (Hard coded, non-EEPROM values)

unsigned char const biasNeg5[]  = {96,98,100,102,104,106,108,110,112,114,116};  //Setpoint Bias when Temperature between -15C and -5C (EEPROM Address "offset" values)

unsigned char const biasNeg15[] = {4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84};  //biasNeg15 (Temperature between -15C and -25C) EEPROM Address "offset" values

unsigned char const biasNeg25[] = {6, 14, 22, 30, 38, 46, 54, 62, 70, 78, 86};  //biasNeg25 (Temperature below -25C) EEPROM Address "offset" values

unsigned char const startMonth = 88, startDay = 90, endMonth = 92, endDay = 94; //EEPROM Address offset values to store user settable Start/Stop dates

signed int Bias[] =             {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};    //Set Bias values all to 0, in case of a startup when temps are between assigned switch points                                                        //Bias value added to Setpoint, based on outdoor air temp (will be a negative number when outside air is warmer)

char *desc[] = {"Deck Rm Air ","Deck Floor ","Utility Flr ","Entrance Flr ","Master Bath ","Office Floor ","Craft Rm Flr ","SE BedRm Flr ","Media Rm Flr ","Garage Floor ","Garage Rm Air"};

_Bool outState[11] = {0};                                                       //State of the output (1 or 0) not the actual output, which is _Bool Out[]

int outStateCounter[11] = {0,0,0,0,0,0,0,0,0,0,0};                              //Keeps track of which outputs are turning on most often

_Bool lastOutState[11] = {0};                                                   //Used to check if the outState has changed

char call = 0;                                                                  //call is used to set HMI key delay time, based on what function you are in 

char powerFail = 1;                                                             //Setting powerFail to 1, displays "set Clock" Message

int samples[numSamples];                                                        //Outside Air Temperature Samples to average temp over x number of samples

// ******************************************************************************


int main(void)
{
    ConfigureOscillator();

    InitApp();
    
    init_lcd();
    
    ADCInit();

//    LCD_Init(NONE);
    
    __delay_ms(100);
    
  //  LCD_Clear();
    
    RTCC_Initialize();
    
    //InitCustomChars();
    
// ******************************************************************************
//    extern char *WeekDay[7];
    
  //  extern char *month[13];
    
    //signed char loopCounter = 12, previousLoopCounter = 12;                     //Loopcounter value determines which screen info is displayed on LCD
    
//    int OutAirTemp;                                                             //Average Outside air temp (Avg of numSamples))
    
  //  int tempOutAirTemp;                                                         //Temporary calculated Outside air temp as read by the ADC 

    //int Temp[11];                                                               //Calculated loop temperatures as read by the ADC, these display in 1/10 of Degrees Celcius
    
//    unsigned char sampleIndex = 0;                                              //Used to calculate average outdoor temp
    
  //  int total = 0;                                                              //Running total of Outside air samples 
    
    //unsigned char StartUpDelay = 0;                                             // Startup delay so outputs do not turn on until after OutAirTemp has been averaged
    
//    int OldTemp[11] = {300};                                                    //Used to smooth temperature readings

  //  _Bool Out[11] = {0};                                                        // Startup values for all outputs, 0 = OFF (Output 0 - 11))
    
    //_Bool OutSum = 0;// outSumOldState = 0;                                       // Sum of all Outputs, Previous scan OutSum state
    
//    unsigned char i = 0;
    
  //  char TestKey;                                                               // Variable used for Storing Which Menu Key is Pressed

    //int internalBGV;                                                            // Variable to store the internal BandGapVoltage as read by the ADC
    
//    unsigned int backLightTimer = 0;                                            //Used to turn off the LCD backlight after an interval of inactivity (60 seconds))

  //  unsigned char previous_time = 0;                                            //Used to limit temp readings and LCD updates to once a second
    
    int mine = 12345;
// ******************************************************************************

    
    while(1)
    {
        
        _RA0 = 0;
        __delay_ms(1000);
        _RA0 = 1;
        __delay_ms(1000);
        
        cls();
        
        lcd_putchar(0,0,'C');
        LCDWriteStringXY(0,0, "ABCDEFGHIJKLMNOP");
        LCDWriteStringXY(0,16,"QRSTUVWXYZabcdef");
        LCDWriteStringXY(1,0, "ghijklmnopqrstuv");
        LCDWriteStringXY(1,16,"wxyz0123456789!@");
        LCDWriteStringXY(2,0, "#$%^&*()_+=-?><|");
        LCDWriteStringXY(2,16,"}{][~`/|\")");
        
        LCDWriteStringXY(4,2,"I guess the fo");
        LCDWriteStringXY(4,16,"nts are not");
        LCDWriteStringXY(5,5,"100% yet!!");
        __delay_ms(12000);

        loadimg(&toplogo_bmp[0], 1024);             //Draw my logo(or start screen)
        __delay_ms(2000);
    
        cls();
        
        LCDWriteIntXY(0,10,mine,-1);
        __delay_ms(1000);
        LCDWriteStringXY(5,0, "DAVE likes progr");
        LCDWriteStringXY(5,16,"amming!!");
        __delay_ms(2000);
        LCDWriteStringXY(2,0,"DAVE is an OK'is");
        LCDWriteStringXY(2,16,"h programmer!!??");
        __delay_ms(2000);
        LCDWriteStringXY(3,7,"FUCK!!, O");
        LCDWriteStringXY(3,16,"K, it works now!");
        __delay_ms(2000);
        LCDWriteStringXY(7,0,"Oh, and Damon SU");
        LCDWriteStringXY(7,16,"CKS!!!");
        __delay_ms(4000); 
        
/*        time = getRTCTime();                                                    // get the time
        
        unsigned int timer = 0;                                                 // Used to count up time in a loop, to auto exit if user in a menu too long

        if(previous_time != time.second)                                        // Only update if an additional second has passed
        {
// ******************************************************************************
            tempOutAirTemp = ((ADCRead(9) - 840)/3.276 - 500);                  // Read Outdoor air temperature & assign it to a temporary variable 
            
            total = total - samples[sampleIndex];                               // Subtract the oldest sample data from the total

            samples[sampleIndex] = tempOutAirTemp;                              // Assign the just read temperature to the location of the current oldest data

            total = total + samples[sampleIndex];                               // Add that new sample to the total
            
            sampleIndex += 1;                                                   // and move to the next index location
            
            if(sampleIndex >= numSamples)
            {
                sampleIndex = 0;
            }
            
            OutAirTemp = total / numSamples;                                    // assign the average value of total to the OutAirTemp variable
            
// ******************************************************************************
            Temp[0] = ADCRead(0);                                               //Read Deck air temperature Pin 19
// ******************************************************************************
            Temp[1] = ADCRead(4);                                               //Read Deck floor temperature Pin 23
// ******************************************************************************
            Temp[2] = ADCRead(5);                                               //Read Utility room floor temperature Pin 24
// ******************************************************************************
            Temp[3] = ADCRead(6);                                               //Read Entrance floor temperature Pin 25
// ******************************************************************************
            Temp[4] = ADCRead(10);                                              //Read Master bathroom floor temperature Pin 14
// ******************************************************************************
            Temp[5] = ADCRead(11);                                              //Read Office floor temperature Pin 11
// ******************************************************************************
            Temp[6] = ADCRead(12);                                              //Read Craft room floor temperature Pin 10
// ******************************************************************************
            Temp[7] = ADCRead(17);                                              //Read SE basement bedroom floor temperature Pin 41
// ******************************************************************************
            Temp[8] = ADCRead(18);                                              //Read Media room floor temperature Pin 42
// ******************************************************************************
            Temp[9] = ADCRead(19);                                              //Read Garage floor temperature Pin 43
// ******************************************************************************
            Temp[10] = ADCRead(20);                                             //Read Garage room air temperature Pin 44
// ******************************************************************************
            internalBGV = ADCRead(0x1A);                                        //Read the internal band Gap Voltage, used later to measure input voltage
// ******************************************************************************
        
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
// ******************************************************************************
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

// ******************************************************************************  Following line turns off all outputs & disables writes to the output pins, unless between start & stop dates
      
            if (((time.month < eepromGetData(startMonth)) || (time.month <= eepromGetData(startMonth) && time.day < eepromGetData(startDay)))  && ((time.month > eepromGetData(endMonth)) || ((time.month >= eepromGetData(endMonth)) && (time.day >= eepromGetData(endDay)))))
            {
                for(i = 0;i<11;i++)
                {
                    Out[i] = 0;
                    outState[i] = 0;
                }
            }

            else
            {
                if (StartUpDelay > numSamples)
                {
                    for (i=0;i<11;i++)
                    {
                        Out[i] = SetOutput(Out[i], eepromGetData(setpoint[i]), Bias[i], Temp[i], eepromGetData(deadband[i]));       //Set Outputs 
                    }

                    
                    
                    for(i=0;i<11;i++)                                                                                               //Set screen state indicators
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
// ******************************************************************************
                    
                    OutSum = Out[0] + Out[2] + Out[3] + Out[4] + Out[5] + Out[6] + Out[7] + Out[8] + Out[10];
        
//                    if(outSumOldState != OutSum)                                        // OutSum has changed,
  //                  {
                        if(OutSum != 0)                                                 // because an Out is turned on
                        {
                            for(i=0;i<11;i++)
                            {
                                if (Temp[i] < eepromGetData(setpoint[i]) + eepromGetData(deadband[i]) + Bias[i])// Check for other PV's below SP + DB + Bias,
                                {
                                    Out[i] = 1;                                         // and turn them on.
                                }

                                else
                                {
                                    Out[i] = 0;                                         // Turn them off if they are already too hot!!
                                }
                            }
                        }
    //                    outSumOldState = OutSum;
      //              }
// ******************************************************************************
                    if(Out[0] == 0)                                                     // If Deck Air Temp is NOT calling,
                    {
                        Out[1] = 0;                                                     // turn OFF Deck Floor Out           
                    }
        
                    if(Out[10] == 0)                                                    // If Garage Air Temp is NOT calling,
                    {
                        Out[9] = 0;                                                     // turn OFF Garage Floor Out
                    }
        
            
                }
            
                else
                {
                    StartUpDelay +=1;
                }

                
            }
            
// ******************************************************************************
            
            previous_time = time.second;                                        // We have updated all readings (because it was a new second), so set previous_time to current time
        
        }

// ******************************************************************************
        if(previousLoopCounter != loopCounter)
        {
//            LCD_Clear();
            previousLoopCounter = loopCounter;
        }
// ******************************************************************************

        
        if(loopCounter < 11)
        {
  //          LCD_Set_Cursor(0,0);                                                //LCD Line 0 Display
    //        LCD_Write_String(desc[loopCounter]);
      //      LCDWriteStringXY(0,13,"Loop ");
        //    LCD_Write_Int(loopCounter,2);
            
//            LCDWriteStringXY(1,0,"Bs");                                        //LCD Line 1 SetPoint Display
  //          LCDWriteSignedDecIntXY(1,2,eepromGetData(setpoint[loopCounter]) + Bias[loopCounter],3);
    //        LCD_Write_Char(0);
      //      LCD_Write_Char('C');
        //    LCDWriteStringXY(1,10,"Set:");
          //  LCDWriteDecIntXY(1,14,eepromGetData(setpoint[loopCounter]),3);
            //LCD_Write_Char(0);
//            LCD_Write_Char(67);

  //          LCDWriteStringXY(2,0,"Temp:");                                      //LCD Line 2 Temperature Display
    //        LCDWriteDecIntXY(2,5,Temp[loopCounter],3);
      //      LCD_Write_Char(0);
        //    LCD_Write_Char(67);

          //  LCDWriteStringXY(2,12,"Db:");                                       //LCD Line 2 Deadband Display
//            LCDWriteDecIntXY(2,15,eepromGetData(deadband[loopCounter]),2);
  //          LCD_Write_Char(0);
    //        LCD_Write_Char(67);
            
      //      LCDWriteIntXY(3,0,outStateCounter[loopCounter],5);
            
        //    LCDWriteStringXY(3,6,"On: ");                                       //LCD Line 3 Out Display
            
            if(outState[loopCounter] == 1)
            {
          //      LCD_Write_Char('Y');
            }
            
            else
            {
//                LCD_Write_Char('N');
            }

  //          LCDWriteStringXY(3,12,"FOn: ");
            
            if(outState[loopCounter] == 1 || Out[loopCounter] == 0)
            {
    //            LCD_Write_Char('N');
            }
            
            else
            {
      //          LCD_Write_Char('Y');
            }
        }
// ******************************************************************************
        
        TestKey = menuRead();

        if(loopCounter == 11)
        {
        //    LCDWriteIntXY(0,0,outStateCounter[0],5);
          //  LCDWriteIntXY(0,6,outStateCounter[1],5);
            //LCDWriteIntXY(0,12,outStateCounter[2],5);
//            LCDWriteIntXY(1,0,outStateCounter[3],5);
  //          LCDWriteIntXY(1,6,outStateCounter[4],5);
    //        LCDWriteIntXY(1,12,outStateCounter[5],5);
      //      LCDWriteIntXY(2,0,outStateCounter[6],5);
        //    LCDWriteIntXY(2,6,outStateCounter[7],5);
          //  LCDWriteIntXY(2,12,outStateCounter[8],5);
            //LCDWriteIntXY(3,0,outStateCounter[9],5);
//            LCDWriteIntXY(3,6,outStateCounter[10],5);
  //          LCD_Set_Cursor(3,12);
    //        LCD_Write_2Dec_Int(405515/internalBGV,3);                          //Write the BandGap voltage to the LCD
      //      LCD_Write_Char('V');

            if(TestKey == KEY_RESET)                                            //KEY_RESET does a re-set on outStateCounter, if pressed on loop page 11
            {
                TestKey = KEY_NONE;
                
        //        LCD_Clear();
          //      LCDWriteStringXY(0,0,"'Enter' ReSets Count");
                
                while(TestKey != KEY_ENTER)                                     //If KEY_ENTER is not pressed,
                {
                    TestKey = menuRead();
                    timer +=1;
                    __delay_ms(20);
                    if (timer > 500)
                    {
                        timer = 0;
            //            LCD_Clear();
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
        
        
        if(loopCounter == 12)
        {
            if(powerFail == 1)
            {
              //  LCDWriteStringXY(0,0,"Please Set The Time ");
            }
            
            else
            {
                //LCDWriteIntXY(0,0,time.year,2);
//                LCD_Write_String(month[time.month]);
  //              LCD_Write_Int(time.day,2);
    //            LCDWriteStringXY(0,8,WeekDay[time.weekday]);
      //          LCDWriteIntXY(0,12,time.hour,2);
        //        LCD_Write_String(":");
          //      LCD_Write_Int(time.minute,2);
            //    LCD_Write_String(":");
              //  LCD_Write_Int(time.second,2);



                LCDWriteIntXY(0,0,time.year,2);
                LCDWriteStringXY(0,2,"/");
                LCDWriteIntXY(0,3,time.month,2);
                LCDWriteStringXY(0,5,"/");
                LCDWriteIntXY(0,6,time.day,2);
                LCDWriteStringXY(0,9,WeekDay[time.weekday]);
                LCDWriteIntXY(0,12,time.hour,2);
                LCDWriteStringXY(0,14,":");
                LCDWriteIntXY(0,15,time.minute,2);
                LCDWriteStringXY(0,17,":");
                LCDWriteIntXY(0,18,time.second,2);
*/
//            }
              
/*            LCDWriteStringXY(1,0,"X Pos:");
            LCDWriteIntXY(1,7,x,5);
            LCDWriteStringXY(1,13,"Col:");
            LCDWriteIntXY(1,18,col,1);

            LCDWriteStringXY(2,0,"Y Pos:");
            LCDWriteIntXY(2,7,y,5);
            LCDWriteStringXY(2,13,"Row:");
            LCDWriteIntXY(2,18,row,1);
*/
//            LCD_Clear();
//                LCDWriteStringXY(0,0,"Total:");
  //              LCDWriteIntXY(0,10,total,8);

//                LCDWriteStringXY(1,0,"OutSide:");
  //              LCDWriteIntXY(1,10,OutAirTemp,6);
           
    //            LCDWriteStringXY(2,0,"tmp");
      //          LCDWriteIntXY(2,4,ADCRead(20),5);
        //        LCDWriteIntXY(2,10,Temp[10],6);

          //      LCDWriteStringXY(3,0,"sample:");
            //    LCDWriteIntXY(3,7,sampleIndex,2);
              //  LCDWriteIntXY(3,10,samples[sampleIndex],6);
                //__delay_ms(1000);
/*            
            LCDWriteStringXY(0,0,"Bs");                                        //LCD Line 1 SetPoint Display
            LCDWriteIntXY(0,3,Bias[0],4);
            LCDWriteIntXY(0,9,eepromGetData(biasNeg25[0]),4);
            LCDWriteIntXY(0,15,BiasWarm[0],4);
//            LCDWriteDecIntXY(0,8,eepromGetData(biasNeg25[0],4);
            
            LCDWriteStringXY(1,0,"Set:");
            LCDWriteDecIntXY(1,5,eepromGetData(setpoint[0]),4);
            LCDWriteDecIntXY(1,11,eepromGetData(setpoint[1]),4);
 
            LCDWriteStringXY(2,0,"T");                                      //LCD Line 2 Temperature Display
            LCDWriteDecIntXY(2,2,Temp[0],3);
            LCDWriteDecIntXY(2,7,Temp[1],3);

            LCDWriteStringXY(2,11,"D");                                       //LCD Line 2 Deadband Display
            LCDWriteDecIntXY(2,13,eepromGetData(deadband[0]),2);
            LCDWriteDecIntXY(2,17,eepromGetData(deadband[1]),2);
            
            LCDWriteIntXY(3,0,Out[0],2);
            LCDWriteIntXY(3,4,Out[1],2);
            LCDWriteIntXY(3,7,OutAirTemp,5);
//            LCDWriteIntXY(3,14,TestVar,5);
*/            
            
            
//            if(mainTimer <= 8)
  //          {
//                LCDWriteStringXY(1,0,"OutSide Temp:");
  //              LCDWriteSignedDecIntXY(1,13,OutAirTemp,3);
    //            LCD_Write_Char(0);
      //          LCD_Write_Char(67);
    //            LCDWriteStringXY(2,0,"Enter Key Sets Time ");
      //          LCDWriteStringXY(3,0,"Menu Key Sets Temp ");
        //    }
            
          //  if(mainTimer > 8 && mainTimer <= 16)
            //{
              //  LCDWriteStringXY(1,0,"OutSide Temp:");
                //LCDWriteSignedDecIntXY(1,13,OutAirTemp,3);
//                LCD_Write_Char(0);
  //              LCD_Write_Char(67);
        //        LCDWriteStringXY(2,0," <- / -> Keys page ");
          //      LCDWriteStringXY(3,0," through Loop Info ");
    //        }
            
      //      if(mainTimer > 16 && mainTimer <= 20)
        //    {
          //      LCDWriteStringXY(1,0,"Left Key to display ");
            //    LCDWriteStringXY(2,0," all Loop Run-time  ");
              //  LCDWriteStringXY(3,0,"  Info on One Page ");
            //}
//        }
        

  //      if(mainTimer > 19)
    //    {
      //      mainTimer = 0;
//        }
        
// ******************************************************************************
//        TestKey = menuRead();
// ******************************************************************************
//        heartBeat();                                                            // HeartBeat displays the HeartBeat on the LCD
// ******************************************************************************  
/*     
        if(TestKey == KEY_NONE)             // If no key is pressed for 60 seconds
        {                                   // Turn OFF the LCD Backlight
            backLightTimer += 1;
        }
        
        else
        {
            backLightTimer = 0;
        }
        
        if (backLightTimer < 4450)
        {
//            backLightOn = 1;
            
        }
        else
        {
            backLightTimer = 4450;
  //          backLightOn = 0;
        }
// ******************************************************************************
        
        if (TestKey == KEY_RESET)                                               //This will soft reset the processor
        {
            TestKey = KEY_NONE;
            
    //        LCD_Clear();
      //      LCDWriteStringXY(0,0," You want to Reset? ");
//            LCDWriteStringXY(1,0,"ReSet the Processor");
        //    LCDWriteStringXY(2,0,"Hit 'Enter' to ReSet");

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                timer +=1;
                __delay_ms(20);
                if (timer > 500)
                {
                    timer = 0;
          //          LCD_Clear();
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
            
//            LCD_Clear();
  //          LCDWriteStringXY(0,0,"Press 'ENTER' to Set");
    //        LCDWriteStringXY(1,0,"Time");

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                timer +=1;
                __delay_ms(20);
                if (timer > 500)
                {
                    timer = 0;
      //              LCD_Clear();
                    goto done2;
                }
            }
            SetTime();
        }
        
        done2:
// ******************************************************************************

        if (TestKey == KEY_SET_START)                                           // Set Heating Season Start/Stop Dates
        {
        //    LCD_Clear();

          //  LCDWriteStringXY(0,0,"Start Month?");
            eepromPutData(startMonth, SetStartEndMonth(eepromGetData(startMonth)));
            //LCDWriteStringXY(1,0,"Start Day?");
            eepromPutData(startDay, SetStartEndDay(eepromGetData(startDay)));

//            LCD_Clear();
            
  //          LCDWriteStringXY(0,0,"End Month?");
            eepromPutData(endMonth, SetStartEndMonth(eepromGetData(endMonth)));
    //        LCDWriteStringXY(1,0,"End Day?");
            eepromPutData(endDay, SetStartEndDay(eepromGetData(endDay)));

      //      LCD_Clear();
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
            signed char choice = 5;

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                
                if(timer > 1000)
                {
                    timer = 0;
                    goto exit;                                                  //This uses less memory than TestKey = KEY_ENTER
                    
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
                        goto exit;
                    }
                    break;
                        
                }

                if(timer < 2)
                {
//                    LCD_Clear();
                }

  //              LCD_Set_Cursor(0,0);
    //            LCD_Write_String("Set Temperature for");
      //          LCD_Set_Cursor(1,0);
        //        LCD_Write_String(desc[choice]);
          //      LCDWriteStringXY(2,0,"Up/Dn Keys to change");
            //    LCDWriteStringXY(3,0,"Enter Key for Yes   ");
                
                heartBeat();                                                    // HeartBeat displays the HeartBeat on the LCD,
                                                                                // but, also increments mainTimer every second
                timer += 1;
            }
            
//            TestKey = 9;
            
//            LCD_Clear();


  //          LCD_Set_Cursor(0,0);
    //        LCD_Write_String(desc[choice]);
      //      LCDWriteStringXY(0,strlen(desc[choice]),"Set Tmp");
            eepromPutData(setpoint[choice], TempSetpoint(eepromGetData(setpoint[choice])));
            
        //    LCD_Set_Cursor(2,0);
          //  LCD_Write_String(desc[choice]);
            //LCDWriteStringXY(2,strlen(desc[choice]),"Set DB");
            eepromPutData(deadband[choice], SetDeadband(eepromGetData(deadband[choice])));            

//            LCD_Clear();

  //          LCD_Set_Cursor(0,0);
    //        LCD_Write_String(desc[choice]);
      //      LCDWriteStringXY(0,strlen(desc[choice]),"WrmBias");
            eepromPutData(BiasWarm[choice], SetBiasWarm(eepromGetData(BiasWarm[choice])));

        //    LCD_Set_Cursor(2,0);
          //  LCD_Write_String(desc[choice]);
            //LCDWriteStringXY(2,strlen(desc[choice]),"-5 Bias");
            eepromPutData(biasNeg5[choice], SetBiasNeg5(eepromGetData(biasNeg5[choice])));
            
//            LCD_Clear();

  //          LCD_Set_Cursor(0,0);
    //        LCD_Write_String(desc[choice]);
      //      LCDWriteStringXY(0,strlen(desc[choice]),"-15Bias");
            eepromPutData(biasNeg15[choice], SetBiasNeg15(eepromGetData(biasNeg15[choice])));

        //    LCD_Set_Cursor(2,0);
          //  LCD_Write_String(desc[choice]);
            //LCDWriteStringXY(2,strlen(desc[choice]),"-25Bias");
            eepromPutData(biasNeg25[choice], SetBiasNeg25(eepromGetData(biasNeg25[choice])));
            
//            exit:
                        
//            LCD_Clear();
        }
        exit:  */
// ******************************************************************************
        ClrWdt();                                                               //Clr (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************
