
#include "xc.h"
#include "lcd.h"
#include "system.h"                     // System funct/params, like osc/peripheral config
#include "user.h"                       // User Functions (ADC Conversion, LCD Functions, etc...)
#include "rtcc.h"                       // Real Time clock & Calendar Functions
#include <string.h>
#include "eeprom.h"
#include "touch.h"
#include "adc.h"

// ******************************************************************************
#define DeckFloorOut        _LATC8
#define UtilityRoomFloorOut _LATC9
#define EntranceFloorOut    _LATA7
#define MasterBathFloorOut  _LATB10
#define OfficeFloorOut      _LATB11
#define CraftRoomFloorOut   _LATA10
#define SEBasementFloorOut  _LATA11
#define MediaRoomFloorOut   _LATA2
#define GarageFloorOut      _LATA3

#define backLightOn         _LATA1
// ******************************************************************************

int __attribute__ ((space(eedata))) Settings[44];                               // Global variable located in EEPROM (created by the space()attribute

RTCTime time;                                                                   // declare the type of the time object

char const setpoint[] =         {0,  8, 16, 24, 32, 40, 48, 56, 64, 72, 80};    //setpoint EEPROM Address "offset" values

unsigned char const deadband[] ={2, 10, 18, 26, 34, 42, 50, 58, 66, 74, 82};    //dead band EEPROM Address "offset" values

signed char const biasNeg15[] = {4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84};    //biasNeg15 (Temperature between -15C and -25C) EEPROM Address "offset" values

signed char const biasNeg25[] = {6, 14, 22, 30, 38, 46, 54, 62, 70, 78, 86};    //biasNeg25 (Temperature below -25C) EEPROM Address "offset" values

signed char Bias[11];

signed char BiasWarm[] =        {-99, -99, -30, -40, -40, -55, -55, -30, -30, -10,  -5};    //Setpoint Bias when Temperature above +5C (Hard coded, non-EEPROM values)

signed char Bias5[] =           {-20,  -5, -20,  -5, -20, -15, -15, -20, -10,  -5,  -5};    //Setpoint Bias when Temperature between 0C and +5C (Hard coded, non-EEPROM values)

signed char Bias0[] =           {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};    //Setpoint Bias when Temperature between -5C and 0C (Hard coded, non-EEPROM values)

signed char BiasNeg5[] =        { 20,   5,  15,  10,  10,   5,   5,   0,  10,   0,   0};    //Setpoint Bias when Temperature between -15C and -5C (Hard coded, non-EEPROM values)

char *desc[] = {"Deck Floor ","Deck Rm Air ","Utility Flr ","Entrance Flr ","Master Bath ","Office Floor ","Craft Rm Flr ","SE BedRm Flr ","Media Rm Flr ","Garage Floor ","Garage Rm Air"};

_Bool outState[11] = {0};

int outStateCounter[11] = {0};

_Bool lastOutState[11] = {0};

uint8_t mainTimer = 0;

char call = 0;                                                                  //call is used to set HMI key delay time, based on what function you are in 

char powerFail = 1;                                                             //Setting powerFail to 1, flashes clock until set

extern uint8_t toggle;

// ******************************************************************************



int main(void)
{
    ConfigureOscillator();

    InitApp();
    
    ADCInit();

    LCD_Init(NONE);
    
    __delay_ms(100);
    
    LCD_Clear();
    
    RTCC_Initialize();
    
    InitCustomChars();
    
// ******************************************************************************
    char * WeekDay[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
    
    int8_t loopCounter = 12, previousLoopCounter = 12;
    
    int OutAirTemp;                                                     

    int Temp[11];

    int OldTemp[11] = {300};

    _Bool Out[11] = {0};                                                         // Startup values for all outputs, 0 = OFF (Output 0 - 11))
    
    _Bool OutSum = 0, outSumOldState = 0;                                        // Sum of all Outputs, Previous scan OutSum state
    
    unsigned char i = 0;
    
    char reset = 0;

    char TestKey;                                                               // Variable used for Storing Which Menu Key is Pressed

    int internalBGV;
    
    unsigned int backLightTimer = 0;

// ******************************************************************************

    while(1)
    {
        time = getRTCTime();                                                    // get the time
        
        unsigned int timer = 0;                                                 // Used to count up time in a loop, to auto exit if user in a menu too long

// ******************************************************************************
        OutAirTemp = ((ADCRead(9) - 785)/3.2 - 500); 
//        OutAirTemp = ((ADCRead(9) - 819)/3.276 - 500); 
// ******************************************************************************
        Temp[0] = ADCRead(0);   //Read Deck floor temperature Pin 19
// ******************************************************************************
        Temp[1] = ADCRead(4);   //Read Deck air temperature Pin 23
// ******************************************************************************
        Temp[2] = ADCRead(5);   //Read Utility room floor temperature Pin 24
// ******************************************************************************
        Temp[3] = ADCRead(6);   //Read Entrance floor temperature Pin 25
// ******************************************************************************
        Temp[4] = ADCRead(10);   //Read Master bathroom floor temperature Pin 14
// ******************************************************************************
        Temp[5] = ADCRead(11);   //Read Office floor temperature Pin 11
// ******************************************************************************
        Temp[6] = ADCRead(12);   //Read Craft room floor temperature Pin 10
// ******************************************************************************
        Temp[7] = ADCRead(17);   //Read SE basement bedroom floor temperature Pin 41
// ******************************************************************************
        Temp[8] = ADCRead(18);   //Read Media room floor temperature Pin 42
// ******************************************************************************
        Temp[9] = ADCRead(19);   //Read Garage floor temperature Pin 43
// ******************************************************************************
        Temp[10] = ADCRead(20);   //Read Garage room air temperature Pin 44
// ******************************************************************************
        internalBGV = ADCRead(0x1A);
        
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
                Bias[i] = BiasNeg5[i];
            }

            else if (OutAirTemp > -50 && OutAirTemp <= -40)
            {
                Bias[i] = Bias[i];
            }
    
            else if (OutAirTemp > -40 && OutAirTemp <= 0)
            {
                Bias[i] = Bias0[i];
            }
    
            else if (OutAirTemp > 0 && OutAirTemp <= 10)
            {
                Bias[i] = Bias[i];
            }
    
            else if (OutAirTemp > 10 && OutAirTemp <= 50)
            {
                Bias[i] = Bias5[i];
            }

            else if (OutAirTemp > 50 && OutAirTemp <= 60)
            {
                Bias[i] = Bias[i];
            }
    
            else 
            {
                Bias[i] = BiasWarm[i];
            }
        }
// ******************************************************************************
        for (i=0;i<11;i++)
        {
            Out[i] = SetOutput(Out[i], eepromGetData(setpoint[i]), Bias[i], Temp[i], eepromGetData(deadband[i]));
        }
// ******************************************************************************
        for(i=0;i<11;i++)
        {
            if (Temp[i] <= eepromGetData(setpoint[i]) + Bias[i])                //If Out is not Off
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
                if (outState[i] != lastOutState[i])                             //If Out changed since last read
                {
                    outStateCounter[i]+=1;                                      //Increment the OutState Counter
                }
            }
            lastOutState[i] = outState[i];                                      //And set them equal to each other, so, it doesn't count again next time through
        }
// ******************************************************************************
        OutSum = Out[1] + Out[2] + Out[3] + Out[4] + Out[5] + Out[6] + Out[7] + Out[8] + Out[10];
        
        if(outSumOldState != OutSum)                                            // OutSum has changed,
        {
            if(OutSum != 0)                                                     // because an Out was turned on
            {
                for(i=0;i<11;i++)
                {
                    if (Temp[i] < eepromGetData(setpoint[i]) + eepromGetData(deadband[i]) + Bias[i])// Check for other PV's below SP + DB + Bias,
                    {
                        Out[i] = 1;                                             // and turn them on.
                    }

                    else
                    {
                        Out[i] = 0;                                             // Turn them off if they are already too hot!!
                    }
                }
            }
            outSumOldState = OutSum;
        }
// ******************************************************************************
        if(Out[1] == 0)                                                         // If Deck Air Temp is NOT calling,
        {
            Out[0] = 0;                                                         // turn OFF Deck Floor Out           
        }
        
        if(Out[10] == 0)                                                        // If Garage Air Temp is NOT calling,
        {
            Out[9] = 0;                                                         // turn OFF Garage Floor Out
        }
        
        DeckFloorOut =          Out[0];
        UtilityRoomFloorOut =   Out[2];
        EntranceFloorOut =      Out[3];
        MasterBathFloorOut =    Out[4];
        OfficeFloorOut =        Out[5];
        CraftRoomFloorOut =     Out[6];
        SEBasementFloorOut =    Out[7]; 
        MediaRoomFloorOut =     Out[8];
        GarageFloorOut =        Out[9];

// ******************************************************************************
        if(previousLoopCounter != loopCounter)
        {
            LCD_Clear();
            mainTimer = 0;
            previousLoopCounter = loopCounter;
        }

        
        if(loopCounter < 11)
        {
            LCD_Set_Cursor(0,0);                                                //LCD Line 0 Display
            LCD_Write_String(desc[loopCounter]);
            LCDWriteStringXY(0,13,"Loop ");
            LCD_Write_Int(loopCounter,2);
            
            LCDWriteStringXY(1,0,"Bs:");                                        //LCD Line 1 SetPoint Display
            LCDWriteDecIntXY(1,3,eepromGetData(setpoint[loopCounter]) + Bias[loopCounter],3);
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCDWriteStringXY(1,10,"Set:");
            LCDWriteDecIntXY(1,14,eepromGetData(setpoint[loopCounter]),3);
            LCD_Write_Char(0);
            LCD_Write_Char(67);

            LCDWriteStringXY(2,0,"Temp:");                                      //LCD Line 2 Temperature Display
            LCDWriteDecIntXY(2,5,Temp[loopCounter],3);
            LCD_Write_Char(0);
            LCD_Write_Char(67);

            LCDWriteStringXY(2,12,"Db:");                                       //LCD Line 2 Deadband Display
            LCDWriteDecIntXY(2,15,eepromGetData(deadband[loopCounter]),2);
            LCD_Write_Char(0);
            LCD_Write_Char(67);
            
            LCDWriteIntXY(3,0,outStateCounter[loopCounter],5);
            
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

        if(loopCounter == 11)
        {
            if(mainTimer < 10)
            {
            LCDWriteStringXY(0,0,"Output loop counters");
            }
            if(mainTimer >= 10)
            {
            LCDWriteStringXY(0,0,"Hold Cancel to Reset");
            }
            
            LCDWriteIntXY(1,0,outStateCounter[0],4);
            LCDWriteIntXY(1,5,outStateCounter[1],4);
            LCDWriteIntXY(1,10,outStateCounter[2],4);
            LCDWriteIntXY(1,15,outStateCounter[3],4);
            LCDWriteIntXY(2,0,outStateCounter[4],4);
            LCDWriteIntXY(2,5,outStateCounter[5],4);
            LCDWriteIntXY(2,10,outStateCounter[6],4);
            LCDWriteIntXY(2,15,outStateCounter[7],4);
            LCDWriteIntXY(3,0,outStateCounter[8],4);
            LCDWriteIntXY(3,5,outStateCounter[9],4);
            LCDWriteIntXY(3,10,outStateCounter[10],4);
            LCDWriteDecIntXY(3,15,40950/internalBGV,2);
            LCD_Write_Char('V');

            if(TestKey == KEY_CANCEL)
            {
                reset += 1;
                
                if(reset > 10)
                {
                    for(i=0;i<11;i++)
                    {
                        outStateCounter[i]= 0;
                        reset = 0;
                    }
                }
            }
            else
            {
                reset -= 1;
                if(reset < 0)
                {
                    reset = 0;
                }
            }
        }
        
        if(loopCounter == 12)
        {
            if(powerFail == 1)
            {
                if(toggle == 1)
                {
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
                }
                
                else 
                {
                    LCDWriteStringXY(0,0,"                    ");
                }
            }
            
            else
            {
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
            }
               
/*            LCDWriteStringXY(1,0,"X Pos:");
            LCDWriteIntXY(1,7,x,5);
            LCDWriteStringXY(1,13,"Col:");
            LCDWriteIntXY(1,18,col,1);

            LCDWriteStringXY(2,0,"Y Pos:");
            LCDWriteIntXY(2,7,y,5);
            LCDWriteStringXY(2,13,"Row:");
            LCDWriteIntXY(2,18,row,1);
*/
            if(mainTimer <= 6)
            {
                LCDWriteStringXY(1,0,"OutSide Temp:");
                LCDWriteSignedDecIntXY(1,13,OutAirTemp,3);
                LCD_Write_Char(0);
                LCD_Write_Char(67);
                LCDWriteStringXY(2,0,"Enter Key Sets Time ");
                LCDWriteStringXY(3,0,"Menu Key Sets Temp ");
            }
            
            if(mainTimer > 6 && mainTimer <= 12)
            {
                LCDWriteStringXY(1,0,"OutSide Temp:");
                LCDWriteSignedDecIntXY(1,13,OutAirTemp,3);
                LCD_Write_Char(0);
                LCD_Write_Char(67);
                LCDWriteStringXY(2,0," <- / -> Keys page ");
                LCDWriteStringXY(3,0," through Loop Info ");
            }
            
            if(mainTimer > 12 && mainTimer <= 20)
            {
                LCDWriteStringXY(1,0,"Left Key to display ");
                LCDWriteStringXY(2,0," all Loop Run-time  ");
                LCDWriteStringXY(3,0,"  Info on One Page ");
            }
        }
        

        if(mainTimer > 19)
        {
            mainTimer = 0;
//            loopCounter = 12;
        }
// ******************************************************************************
        TestKey = menuRead();
// ******************************************************************************
        heartBeat();                                                            // HeartBeat displays the HeartBeat on the LCD,
// ******************************************************************************  but, also increments mainTimer every second 
     
        if(TestKey == KEY_NONE)             // If no key is pressed for 60 seconds
        {                                   // Turn OFF the LCD Backlight
            backLightTimer += 1;
        }
        
        else
        {
            backLightTimer = 0;
        }
        
        if (backLightTimer < 875)
        {
            backLightOn = 1;
            
        }
        else
        {
            backLightTimer = 875;
            backLightOn = 0;
        }
            
        
        if (TestKey == KEY_ENTER)
        {
//            TestKey = 9;
            SetTime();
        }

        if (TestKey == KEY_RESET_LCD)
        {
            LCD_Cmd(0x08);
            LCD_Cmd(0x00);
            LCD_Cmd(0x0C|0);      //Enable Display ON with style selected (BLINK, ULINE, BLUL, or NONE))
            LCD_Cmd(0x00);
        }

        if(TestKey == KEY_LEFT)
        {
            loopCounter -=1;
            
            if(loopCounter < 0)
            {
                loopCounter = 12;
            }
        }

        if(TestKey == KEY_RIGHT)
        {
            loopCounter +=1;
            
            if(loopCounter >12)
            {
                loopCounter = 0;
            }
        }

        if (TestKey == KEY_MENU)
        {
            signed char choice = 5;

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
                    
                    case KEY_CANCEL:
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
            LCDWriteStringXY(0,strlen(desc[choice]),"15 Bias");
            eepromPutData(biasNeg15[choice], SetBiasNeg15(eepromGetData(biasNeg15[choice])));

            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"25 Bias");
            eepromPutData(biasNeg25[choice], SetBiasNeg25(eepromGetData(biasNeg25[choice])));
            
            Exit:
                        
            LCD_Clear();
        }
// ******************************************************************************
        ClrWdt();                                                               //Clr (Re-Set) the WatchDog Timer
    }
    return(0);
}
//***************************************************************************************************************************************************************
