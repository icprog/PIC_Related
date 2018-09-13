// <editor-fold defaultstate="collapsed" desc="Includes & Defines">

// *************** Includes ****************************************************    
#include "system.h"

// *************** Defines *****************************************************
#define pitSetpoint             setpoint[0]
#define backlightIntensity      setpoint[1]
#define ambientTemperature      analogs[0]                                      // Analog Chanell 1,  Pin 3
#define pitTemperature          analogs[1]                                      // Analog Chanell 3,  Pin 5
#define pitViperOutput          LATC2
//#define upKey                   RB0
//#define downKey                 RB1
#define enterKey                RB2
//#define delayNumber             30                              // Number of cycles for keypress delay at 200ms, before switch to 10ms delay, also defined in menu.c
#define numOutSamples           10                                // Number of Output samples to be Averaged into Output

//#define celcius                 analogs[0]                      // Touch pad to select Degrees C
//#define farenheit               analogs[1]                      // Touch pad to select Degrees F
//#define down                    analogs[2]                      // Touch pad to select Backlight Intencity Down
//#define up                      analogs[3]                      // Touch pad to select Backlight Intencity Up
//#define solarInTemp             analogs[4]
//#define solarOutTemp            analogs[5]
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="Variables">
// *************** Main Routine ************************************************    


void main(void)
{
    SYSTEM_Initialize();
    
    uint16_t analogs[2]                 =   {0};                    // array of analog readings 
    
    extern int16_t setpoint[2];                            // defined in menu.c
    
//    char set                            =   0;                      // Variable (Pit Setpoint, Backlight Intensity)) to be set.
    
    //char menuDelay                      =   0;
    
    //char delayCount                     =   0;
    
    int output                          =   0;
    
    int32_t outputTotal                 =   0;
    
    char outputIndex                    =   0;
    
    int16_t outputSamples[numOutSamples]= {0};
    
    char holdOutput                     =   0;
    
    int currentTemperature              =   750;
    
    int lastTemperature                 =   750;
    
    char lidOpenCount                   =   0;
    
//    float displayTemp, displayTemp2;                    // Calculate R of Thermistor, and Temp using SteinHart/Hart equation
    
    char j                      =   0;                      // Variable to loop readAnalog function
    
    char x                      =   0;                      // Looping Initializer
    
    int pidPeriodCounter        =   0;
    
    extern int pidMaxOutput;
    
    extern unsigned char loop;                              // cycle (loop) counter
    
  //  char choice                 =   2;                      // Display degrees C or degrees F, or cycle through both if choice is "2".
    
    //char C_or_F                 =   1;                      // Default Temperature Display is degrees F
    
//    unsigned int bCount         =   0;                      // Loop counter for Backlight setting delay (to allow selection of both pads touched)
    
  //  unsigned char startDelay    =   0;                      // Loop counter to delay touchpad input until ADC stable
    
    //unsigned char resetDelay    =   0;                      // Loop counter to delay backlight touchpad input until determined if two pads are touched for Reset
    
//    unsigned char tPadCount     =   10;                     // Touch pad counter (counts up or down from 10, to determine is one or both pads touched) (for C_or_F choice))
    
    
    uint16_t dutyCycle6         =   0;                      // Pit Viper Fan Output
    
//    uint16_t dutyCycle7         =   523;                    // display back light brightness

//    PWM6_LoadDutyValue(dutyCycle6);

    PWM7_LoadDutyValue(backlightIntensity);

    __delay_ms(300);

    LCD_Clear();
    // </editor-fold>
    
//    volatile unsigned char value = 0x09;
  //  unsigned char address = 0xE5;
    //eeprom_write(address, value);     // Writing value 0x9 to EEPROM address 0xE5        
    //value = eeprom_read (address);    // Reading the value from address 0xE5
    
//    eeprom_write(Kp_offset,10);
  //  eeprom_write(Ki_offset,4);
    //eeprom_write(Kd_offset,2);
        

    while (1)
    {
        extern int16_t errorValue;
        extern int16_t integralValue;
        extern int16_t derivativeValue;
   
        if(loop>253)
        {
            PWM7_LoadDutyValue(backlightIntensity);
            
            LCDWriteIntXY(0,0,errorValue,5,0,0);
            LCD_Write_Char(' ');
            LCD_Write_Char(' ');
            LCDWriteIntXY(8,0,integralValue,5,0,0);
            LCD_Write_Char(' ');
            LCD_Write_Char(' ');

            LCDWriteIntXY(0,1,derivativeValue,5,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,1,pitTemperature,4,1,0);
            LCDWriteIntXY(12,1,dutyCycle6,4,0,0);
        
//            LCDWriteStringXY(0,0,"Pit:");
//            LCDWriteIntXY(5,0,pitTemperature,-1,1,0);
  //          LCD_Write_Char(0);                                              // generate degree symbol in font list
    //        LCD_Write_Char(70);
      //      LCD_Write_Char(' ');                                              
        //    LCD_Write_Char(' ');                                              

          //  LCDWriteStringXY(0,1,"Output:");
            //LCD_Write_Char(' ');                                              
//            LCD_Write_Int(dutyCycle6,5,0,0);
//        LCD_Write_Int(ambientTemperature,-1,1,0);
//        LCD_Write_Char(0);                                              // generate degree symbol in font list
  //      LCD_Write_Char(70);

            if(holdOutput==0)
            {
                output = PID_Calculate(pitSetpoint,pitTemperature);       //Assign the ADC(9) Boiler Temp to a temporary variable
                outputTotal = outputTotal - outputSamples[outputIndex];  // Subtract the oldest sample data from the total
                outputSamples[outputIndex] = output;     // Assign the just read temperature to the location of the current oldest data
                outputTotal = outputTotal + outputSamples[outputIndex];  // Add that new sample to the total
                dutyCycle6 = outputTotal/numOutSamples;        // Assign the average value of total to the boilerTemperature variable

                outputIndex+=1;                                                 // and move to the next index location
                if(outputIndex >= numOutSamples)outputIndex = 0;
            }
            else
            {
                dutyCycle6=0;
                holdOutput-=1;
            }

            currentTemperature=pitTemperature; 
            
            if(lidOpenCount<10)
            {
                lidOpenCount+=1;
            }
            else
            {
                lastTemperature=currentTemperature;
                lidOpenCount=0;
            }
            
            if(lastTemperature-currentTemperature>100 || lastTemperature-currentTemperature<-100)
            {
                dutyCycle6=0;
                holdOutput=5;
            }

            if(dutyCycle6<50)dutyCycle6=0;
   
            loop=0;
        }

        pidPeriodCounter+=1;
        
        if(pidPeriodCounter>pidMaxOutput)pidPeriodCounter=0;
        
        if(dutyCycle6>pidPeriodCounter)pitViperOutput=1;
        else pitViperOutput=0;
        
        for(j=0;j<2;j++) analogs[j]=readAnalog(j);                          // Read analog Temperatures
        
        ambientTemperature=tempCalc(analogs[0]);

        pitTemperature=tempCalc(analogs[1]);


        if(enterKey==1)
        {
            TRISC2      =   1;                                      // Disable Pit Fan Output while in Menu
            LCD_Clear();
            LCDWriteStringXY(0,0,"Alter with Up/Dn");
            LCDWriteStringXY(0,1,"Enter Key to Set");
            __delay_ms(1500);
            LCD_Clear();
            menuChoice();
            __delay_ms(500);
        }

/*        if(upKey==1)
        {
            delayCount+=2;
            pitSetpoint+=1;
            if(pitSetpoint>2750)pitSetpoint=2750;
            LCDWriteIntXY(5,0,pitSetpoint,-1,1,0);
            menuDelay=255;
            if(delayCount<delayNumber)
            {
                __delay_ms(150);
            }
            
            if(delayCount>(delayNumber+10))delayCount=(delayNumber+10);
        }
        
        if(downKey==1)
        {
            delayCount+=2;
            pitSetpoint-=1;
            if(pitSetpoint<750)pitSetpoint=750;
            LCDWriteIntXY(5,0,pitSetpoint,-1,1,0);
            menuDelay=255;

            if(delayCount<delayNumber)
            {
                __delay_ms(150);
            }
            
            if(delayCount>(delayNumber+10))delayCount=(delayNumber+10);
        }
        
        if(delayCount>0)delayCount-=1;
        
        if(!(downKey || upKey))
        {
            if(menuDelay>0)
            {
                loop=0;
                menuDelay-=1;
            }
        }*/
        
        
/*        for(x=0;x<6;x++) analogs[x]=readAnalog(x);
        
        if(analogs[0]<1020)tPadCount+=1;
            
            
        if(analogs[1]<900)tPadCount-=1;
            
        if(tPadCount<1)
        {
            choice=1;
            LCD_Clear();
            LCDWriteStringXY(0,0,"You Chose ");
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCDWriteStringXY(0,1,"for User Display");
            tPadCount=10;
            __delay_ms(1000);
            LCD_Clear();
        }
        
        if(tPadCount>19)
        {
            choice=0;
            LCD_Clear();
            LCDWriteStringXY(0,0,"You Chose ");
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCDWriteStringXY(0,1,"for User Display");
            tPadCount=10;
            __delay_ms(1000);
            LCD_Clear();
        }
        
        if(analogs[0]<1020&&analogs[1]<970)
        {
            tPadCount=10;
            choice=2;
            LCD_Set_Cursor(0,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
            LCD_Write_Char('&');
            LCD_Write_Char(' ');
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCD_Write_String(" Chosen ");
            
            LCDWriteStringXY(0,1,"for User Display");
            __delay_ms(100);
            LCD_Clear();
        }
        
        
        
        startDelay+=1;
        
        if(startDelay>254)
        {
            startDelay=254;
            
            if(down<900&&up<900)RESET();
            
            if(down<900)
            {
                resetDelay+=1;
                
                if(resetDelay>20)
                {
                    while(down<975)
                    {
                        down=ADCRead(4);
                        
                        if(bCount<1)LCD_Clear();
                        bCount+=1;

                        if(dutyCycle>0)dutyCycle-=1;
                
                        LCDWriteStringXY(0,0,"   BackLight   ");
                        LCDWriteStringXY(0,1,"Intensity: ");
                        LCD_Write_Int(dutyCycle/10,-1,0,0);
                        LCD_Write_Char('%');
                        LCD_Write_Char(' ');
                        PWM6_LoadDutyValue(dutyCycle);
                    }
                    bCount=0;
                    __delay_ms(1000);
                    LCD_Clear();
                    resetDelay=0;
                }
            }

            if(up<900)
            {
                resetDelay+=1;
                
                if(resetDelay>20)
                {
                    while(up<975)
                    {
                        up=ADCRead(5);

                        if(bCount<1)LCD_Clear();
                        bCount+=1;

                        if(dutyCycle<1009)dutyCycle+=1;
                
                        LCDWriteStringXY(0,0,"   BackLight   ");
                        LCDWriteStringXY(0,1,"Intensity: ");
                        LCD_Write_Int(dutyCycle/10,-1,0,0);
                        LCD_Write_Char('%');
                        LCD_Write_Char(' ');
                        PWM6_LoadDutyValue(dutyCycle);
                    }
                    bCount=0;
                    __delay_ms(1000);
                    LCD_Clear();
                    resetDelay=0;
                }
            }
        }

// *************** Calculate & Display Temp ************************************   
        
        displayTemp = (tempCalc(solarInTemp))-6;
        
        displayTemp2 = tempCalc(solarOutTemp);

        if(loop>254)
        {
            tPadCount=10;
            LCDWriteStringXY(0,0,"In");
            LCD_Write_Char(1);
            LCD_Write_String("Solar");
            
            LCDWriteStringXY(0,1,"Out");
            LCD_Write_Char(1);
            LCD_Write_String("Pool");
  
            if(C_or_F==0)
            {
                LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('C');
                LCD_Write_Char(' ');
            
                LCDWriteIntXY(9,1,(int)displayTemp2,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('C');
                LCD_Write_Char(' ');
            }
            
            if(C_or_F==1)
            {
                displayTemp = displayTemp*9/5+320;          // Display Temperature in DegF
                displayTemp2 = displayTemp2*9/5+320;        // Display Temperature in DegF

                LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('F');
                LCD_Write_Char(' ');
            
                LCDWriteIntXY(9,1,(int)displayTemp2,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('F');
                LCD_Write_Char(' ');
            }
            
            
            if(choice==0)C_or_F=0;

            if(choice==1)C_or_F=1;

*/            
        //if(choice==2)C_or_F=1-C_or_F;
/*            LCDWriteIntXY(0,0,analogs[0],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,0,analogs[1],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(11,0,analogs[2],-1,0,0);
            LCD_Write_Char(' ');

            LCDWriteIntXY(0,1,analogs[3],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,1,analogs[4],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(11,1,analogs[5],-1,0,0);
            LCD_Write_Char(' ');
            
  */          
//            loop=0;
  //      }
        loop+=1;
    }
}