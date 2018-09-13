
#include "xc.h"
#include <stdio.h>                    // Not needed, included from user.h
#include "lcd.h"
//#include <stdint.h>                   // " Includes int16_t definition
//#include <stdbool.h>                  // " Includes true/false definition
#include "system.h"                     // System funct/params, like osc/peripheral config
#include "user.h"                       // User Functions (ADC Conversion, LCD Functions, etc...)
#include "rtcc.h"                       // Real Time clock & Calendar Functions
#include <string.h>
//#include <stdlib.h>
#include "eeprom.h"

// ******************************************************************************
#define DeckFloor   _RC8
// ******************************************************************************

// typedef struct Controller{char const setpoint[11] = {0,  8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88}; unsigned char const deadband[11] = {2, 10, 18, 26, 34, 42, 50, 58, 66, 74, 82, 90};}Controllers;



int __attribute__ ((space(eedata))) Settings[48];                                       // Global variable located in EEPROM (created by the space()attribute

RTCTime time;                                                                           // declare the type of the time object



char const setpoint[] =             {0,  8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88};    //setpoint EEPROM Address "offset" values

unsigned char const deadband[] =    {2, 10, 18, 26, 34, 42, 50, 58, 66, 74, 82, 90};    //deadband EEPROM Address "offset" values

signed char const biasNeg15[] =     {4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84, 92};    //biasNeg15 (Temperature between -15C and -25C) EEPROM Address "offset" values

signed char const biasNeg25[] =     {6, 14, 22, 30, 38, 46, 54, 62, 70, 78, 86, 94};    //biasNeg25 (Temperature below -25C) EEPROM Address "offset" values

signed char Bias[12];

signed char BiasWarm[] ={-99, -99, -40, -40, -99, -40, -40, -50, -40, -50, -50, 0};     //Setpoint Bias when Tempereature above +5C (Hard coded, non-EEPROM values)

signed char Bias5[] =   {-20, -20, -20, -20, -40, -30, -30, -40, -30, -40, -30, 0};     //Setpoint Bias when Tempereature between 0C and +5C (Hard coded, non-EEPROM values)

signed char Bias0[] =   {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 0};     //Setpoint Bias when Tempereature between -5C and 0C (Hard coded, non-EEPROM values)

signed char BiasNeg5[] ={ 20,   5,  15,  20,  20,  25,  25,  10,  20,  20,  10, 0};     //Setpoint Bias when Tempereature between -15C and -5C (Hard coded, non-EEPROM values)

char *desc[] = {"Deck Floor ","Deck Rm Air ","Utility Flr ","Entrance Flr ","Master Bath ","Office Floor ","Craft Rm Flr ","SE BedRm Flr ","Media Rm Flr ","Garage Floor ","Garage Rm Air","Spare        "};

bool outState[12] = {0};

int outStateCounter[12] = {0};

bool lastOutState[12] = {0};

uint8_t mainTimer = 0;
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
    
    int8_t loopCounter = 13, previousLoopCounter = 13;
    
    int OutAirTemp;                                                     

    int OldTemp[12] = {300};

    bool Out[12] = {0};                                                         // Startup values for all outputs, 0 = OFF (Output 0 - 11))
    
    bool OutSum = 0, outSumOldState = 0;                                        // Sum of all Outputs, Previous scan OutSum state
    
    unsigned char i = 0;

    char TestKey;                   // Variable used for Storing Which Menu Key is Pressed
// ******************************************************************************

    while(1)
    {
// ******************************************************************************
        time = getRTCTime();            // get the time
        
        unsigned int timer = 0;             // Used to count up time in a loop, to auto exit if user in a menu too long
        
        int Temp[] = {ADCRead(0), ADCRead(4), ADCRead(5), ADCRead(10),ADCRead(11), ADCRead(12), ADCRead(13), ADCRead(17),ADCRead(18), ADCRead(19), ADCRead(20), ADCRead(21)};
// ******************************************************************************
        OutAirTemp = ((ADCRead(9) - 785)/3.2 - 500); 
//        OutAirTemp = ((ADCRead(9) - 819)/3.276 - 500); 
// ******************************************************************************
         for(i = 0;i<12;++i)
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
        for(i=0;i<12;i++)
        {
            if(OutAirTemp <= -250)
            {
                Bias[i] = eepromGetData(biasNeg25[i]);
            }
    
            else if (OutAirTemp > -250 && OutAirTemp <= -150)
            {
                Bias[i] = eepromGetData(biasNeg15[i]);
            }
            
            else if (OutAirTemp > -150 && OutAirTemp <= -50)
            {
                Bias[i] = BiasNeg5[i];
            }

            else if (OutAirTemp > -50 && OutAirTemp <= 0)
            {
                Bias[i] = Bias0[i];
            }
    
            else if (OutAirTemp > 0 && OutAirTemp <= 50)
            {
                Bias[i] = Bias5[i];
            }

            else 
            {
                Bias[i] = BiasWarm[i];
            }
        }
// ******************************************************************************
        for (i=0;i<12;i++)
        {
            Out[i] = SetOutput(Out[i], eepromGetData(setpoint[i]), Bias[i], Temp[i], eepromGetData(deadband[i]));
        }
// ******************************************************************************
        for(i=0;i<12;i++)
        {
            if (Temp[i] <= eepromGetData(setpoint[i]) + Bias[i])                                                    //If Out is not Off
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
                if (outState[i] != lastOutState[i])                                  //If Out changed since last read
                {
                    outStateCounter[i]+=1;                                      //Increment the OutState Counter
                }
            }
            lastOutState[i] = outState[i];                                           //And set them equal to each other, so, it doesn't count again next time through
        }
// ******************************************************************************
        OutSum = Out[0] + Out[2] + Out[3] + Out[4] + Out[5] + Out[6] + Out[7] + Out[8] + Out[9] + Out[10] + Out[11];
        
        if(outSumOldState != OutSum)                                            // OutSum has changed,
        {
            if(OutSum != 0)                                                     // because an Out was turned on
            {
                for(i=0;i<12;i++)
                {
                    if (Temp[i] < eepromGetData(setpoint[i]) + eepromGetData(deadband[i]) + Bias[i])                   // Check for other PV's below SP + DB + Bias,
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
        
        DeckFloor = Out[0];
// ******************************************************************************
        TestKey = MenuRead();
// ******************************************************************************
        if(previousLoopCounter != loopCounter)
        {
            LCD_Clear();
            mainTimer = 0;
            previousLoopCounter = loopCounter;
        }

        
        if(loopCounter < 12)
        {
            LCD_Set_Cursor(0,0);                                    //LCD Line 0 Display
            LCD_Write_String(desc[loopCounter]);
            LCDWriteStringXY(0,13,"Loop ");
            LCD_Write_Int(loopCounter,2);
            
            LCDWriteStringXY(1,0,"Bs:");                       //LCD Line 1 SetPoint Display
            LCDWriteDecIntXY(1,3,eepromGetData(setpoint[loopCounter]) + Bias[loopCounter],3);
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCDWriteStringXY(1,10,"Set:");
            LCDWriteDecIntXY(1,14,eepromGetData(setpoint[loopCounter]),3);
            LCD_Write_Char(0);
            LCD_Write_Char(67);

            LCDWriteStringXY(2,0,"Temp:");                      //LCD Line 2 Temperature Display
            LCDWriteDecIntXY(2,5,Temp[loopCounter],3);
            LCD_Write_Char(0);
            LCD_Write_Char(67);

            LCDWriteStringXY(2,12,"Db:");                       //LCD Line 2 Deadband Display
            LCDWriteDecIntXY(2,15,eepromGetData(deadband[loopCounter]),2);
            LCD_Write_Char(0);
            LCD_Write_Char(67);
            
            LCDWriteIntXY(3,0,outStateCounter[loopCounter],5);
            
            LCDWriteStringXY(3,6,"On: ");                       //LCD Line 3 Out Display
            
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
        
        if(loopCounter == 12)
        {
            LCDWriteStringXY(0,0,"Output loop counters");

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
            LCDWriteIntXY(3,15,outStateCounter[11],4);
        }
        
        if(loopCounter == 13)
        {
            LCDWriteIntXY(0,0,time.year,2);
            LCDWriteStringXY(0,2,"/");
            LCDWriteIntXY(0,3,time.month,2);
            LCDWriteStringXY(0,5,"/");
            LCDWriteIntXY(0,6,time.day,2);
            LCDWriteStringXY(0,9,WeekDay[time.weekday]);
            LCDWriteIntXY(0,12,time.hour,2);
            LCDWriteStringXY(0,14,"/");
            LCDWriteIntXY(0,15,time.minute,2);
            LCDWriteStringXY(0,17,"/");
            LCDWriteIntXY(0,18,time.second,2);
               
            
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
                LCDWriteStringXY(2,0,"Up / Down Keys page ");
                LCDWriteStringXY(3,0," through Loop Info ");
            }
            
            if(mainTimer > 12 && mainTimer <= 20)
            {
                LCDWriteStringXY(1,0,"Down Key to display ");
                LCDWriteStringXY(2,0," all Loop Run-time  ");
                LCDWriteStringXY(3,0,"  Info on One Page ");
            }
        }
        
        if (TestKey == KEY_CANCEL)
        {
            LCD_Reset(NONE);
        }
        

        if(mainTimer > 19)
        {
            mainTimer = 0;
//            loopCounter = 13;
        }
// ******************************************************************************
        heartBeat();                                        // HeartBeat displays the HeartBeat on the LCD, but, also increments mainTimer every second
// ******************************************************************************
        if (TestKey == KEY_ENTER)
        {
            TestKey = 9;
            SetTime();
        }
// ******************************************************************************
        if(TestKey == KEY_UP)
        {
            loopCounter -=1;
            
            if(loopCounter < 0)
            {
                loopCounter = 13;
            }
        }
// ******************************************************************************
        if(TestKey == KEY_DOWN)
        {
            loopCounter +=1;
            
            if(loopCounter >13)
            {
                loopCounter = 0;
            }
        }
// ******************************************************************************
        if (TestKey == KEY_MENU)
        {
            signed char choice = 0;

            while(TestKey != KEY_ENTER)
            {
                TestKey = MenuRead();
                
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
                        __delay_ms(200);
                    }
                    break;
                        
                    case KEY_UP:
                    {
                        choice += 1;
                            
                        if(choice > 11)
                        {
                            choice = 11;
                        }
                        __delay_ms(200);
                    }
                    break;
                    
                    case KEY_MENU:
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
                
                heartBeat();                                        // HeartBeat displays the HeartBeat on the LCD, but, also increments mainTimer every second
                
                timer += 1;
            }
            
            TestKey = 9;
            __delay_ms(200);
            
            
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
        TestKey = 9;
        __delay_ms(100);
    }
    return(0);
}
//***************************************************************************************************************************************************************
