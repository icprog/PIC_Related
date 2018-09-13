#include    "system.h"                                                             // System funct/params, like osc/peripheral config
#include    "menu.h"
// *************** Outputs ***************************************************************************************************************************************
//#define fanOutput             _LATD6                                          // Pit Viper Fan PWM Output

// *************** Inputs ****************************************************************************************************************************************
//**************** Timer2 set in pwm.c, determines Period (along with OC4RS) *************************************************************************************
#define power                   !_RG9                                           // Power Switch Input G             

#define pitSetpoint             setpoint[0]

#define pitTemperature          analogs[0]                                      // Analog Chanell 6,  Pin 17
#define Temperature1            analogs[1]                                      // Analog Chanell 7,  Pin 18
#define Temperature2            analogs[2]                                      // Analog Chanell 8,  Pin 21
#define Temperature3            analogs[3]                                      // Analog Chanell 9,  Pin 22
#define Temperature4            analogs[4]                                      // Analog Chanell 10, Pin 23
#define Temperature5            analogs[5]                                      // Analog Chanell 11, Pin 24
#define Temperature6            analogs[6]                                      // Analog Chanell 12, Pin 27
// ***************************************************************************************************************************************************************

extern struct tm currentTime;

uint16_t setpoint[]    =   {2250, 2050, 2050, 2050, 2050, 2050, 2050};          //setpoint values

char *desc[] = {"Pit:   ","Food 1:","Food 2:","Food 3:","Food 4:","Food 5:","Food 6:"};

uint8_t call = 0;

int powerFail = 0;

// ******************************************************************************
int main(void)
{
    SYSTEM_Initialize();
// ******************************************************************************
    int j                                       =   0;                      // Looping Initializer, to read all Analogs
    
    uint16_t count2                             =   0;

    uint16_t analogs[6]                         =   {0};                    // array of analog readings (button presses and temperatures)
    
    uint8_t errorCount                          = 0;                        // errorCount disables power, if level remains low too long, count2 ramps pump pressure

    char TestKey;                                                               // Variable used for Storing Which Menu Key is Pressed

    int internalBGV;
    
    int previous_time = 0;                                                      //Used with time.second to limit some stuff to once a second
            
    char ONTimer = 0, powerSwitch = 0;
    
    extern int16_t pidIntegrated;
    
    extern int16_t derivativeValue;
    
    extern     uint16_t x,y;                                               

    
// ******************************************************************************

    loadimg(&menu3[0], 1024,0);                 //Draw Menu3

    while(1)
    {
        static int timer = 0;                                                   // Used to count up time in a loop, to auto exit if user in a menu too long

        RTCC_TimeGet(&currentTime); 

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

            previous_time = currentTime.tm_sec;

// ******************************************************************************
            internalBGV = ADCRead(0x1A);
      
// ******************************************************************************

            if(powerFail == 1)
            {
                LCDWriteStringXY(6,3,"Please Set");
                LCDWriteStringXY(17,3,"the Time!");
            }
            else
            {
                displayTime();

                GoToXY(1,2);                                                //LCD Line 2 Display
                
//                OC4R=PID_Calculate(pitSetpoint,pitTemperature);

                OC4R= 2047;
  
                LCDWriteString(desc[0]);
                LCDWriteInt(pitTemperature,4,1);
                LCDWriteChar(129);                                              // generate degree symbol in font list
                LCDWriteChar(70);
                    
                LCDWriteStringXY(17,2,"Set: ");
                LCDWriteInt(pitSetpoint,4,1);
                LCDWriteChar(129);                                              // generate degree symbol in font list
                LCDWriteChar(70);
//                LCDWriteStringXY(1,3,"O");
                LCDWriteIntXY(1,3,OC4R,5,0);
                LCDWriteChar(' ');
//                LCDWriteInt(error,5,0);
  //              LCDWriteChar(' ');
                LCDWriteIntXY(1,5,x,5,0);
                LCDWriteChar(' ');
                LCDWriteInt(y,5,0);
                LCDWriteChar(' ');
//                LCDWriteIntXY(1,5,derivativeValue,5,0);
  //              LCDWriteChar(' ');
    //            LCDWriteInt((pidIntegrated),5,0);
      //          LCDWriteChar(' ');
                LCDWriteIntXY(1,4,OC5R,5,0);
                LCDWriteChar(' ');
                
/*                    LCDWriteString(desc[0]);
                    LCDWriteString("/Set");
                    GoToXY(25,2);
                    LCDWriteChar('/');
                    LCDWriteInt(setpoint[0],4,1);
*/
/*                GoToXY(1,3);                                                //LCD Line 3 Display
                LCDWriteString(desc[2]);
                LCDWriteString("/Set");
//                LCDWriteIntXY(3,17,GroupHeadTemp,4,1);
                LCDWriteChar(129);                                          // generate degree symbol in font list
                LCDWriteChar(70);
                LCDWriteChar(' ');
                LCDWriteChar('/');
                LCDWriteInt(setpoint[2],4,1);
  */              
            }
        }
        
// ******************************************************************************
//        if(powerSwitch == 1)
  //      {
            for(j=0;j<7;j++) analogs[j]=readAnalog(j);                          // Read all 7 analog Temperatures
    //    }
      //  else
        //{
          //  dutyCycle           = 0;
            //piezoOutput         = 0;
        //}

// ******************************************************************************
        TestKey = menuRead();                                                   // Check Status of TouchScreen Inputs
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
            LCDWriteStringXY(2,3,"Press 'ENTER' ");
            LCDWriteStringXY(16,3,"to Set the Time");

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
            if(OC5R>20)OC5R-=20;
            
/*            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit2;
            }

//            TestKey = KEY_NONE;
            
            cls();
            loadimg(&menu2[0], 1024,0);                         //Draw Menu2
            LCDWriteStringXY(1,3,"ENTER to Set St");
            LCDWriteStringXY(16,3,"art/Stop Times");

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
*/ 
        }
// ******************************************************************************

        if (TestKey == KEY_3)
        {
            if(OC5R<2027)OC5R+=20;
/*            if(timer<1)
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


                GoToXY(2,1);
                LCDWriteString("PID Settings f");
                LCDWriteStringXY(16,1,"or ");
                LCDWriteString(desc[choice]);
                LCDWriteStringXY(6,2,"Up/Dn Keys");
                LCDWriteStringXY(17,2,"to change");
                LCDWriteStringXY(7,3,"\"Enter\" t")
                LCDWriteStringXY(16,3,"o Accept")

                timer += 1;
            }
            
            TestKey = 0;
            
            cls();
            loadimg(&menu2[0], 1024,0);              //Draw Menu2
*//*            LCDWriteStringXY(1,1,"SetPoint = ");
            setpoint[choice] = setParameter(16,1,1750,2950,setpoint[choice]);
*/            
/*            LCDWriteStringXY(1,2,"DeadBand =");
            deadband[choice] = setParameter(16,2,5,100,deadband[choice]);            
*/
/*            LCDWriteStringXY(1,3,"Gain =");
            Kp[choice] = setParameter(16,3,0,200,Kp[choice]);

            LCDWriteStringXY(1,4,"Integral =");
            Ki[choice] = setParameter(16,4,0,500,Ki[choice]);

            LCDWriteStringXY(1,5,"Derivative =");
            Kd[choice] = setParameter(16,5,0,100,Kd[choice]);
            
  */          
/*            timer = 0;

            cls();
            loadimg(&menu3[0], 1024,0);                  //Draw Menu2
            __delay_ms(500);
*/
        }
//        Exit:
                        
// ******************************************************************************
/*        if (TestKey == KEY_4)
        {
            count2+=5;
            
            if(count2>32)
            {
                init_lcd();
                cls();
                loadimg(&menu3[0], 1024,0);                         //Draw Menu3
                count2 = 0;
            __delay_ms(500);
            }
        }
        if(count2>0)count2-=1;    */
// ******************************************************************************
        ClrWdt();                                                               //Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************
