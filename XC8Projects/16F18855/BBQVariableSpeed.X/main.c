// <editor-fold defaultstate="collapsed" desc="Includes & Defines">

// *************** Includes ****************************************************    
#include "system.h"

// *************** Defines *****************************************************
#define pitSetpoint             setpoint[0]
#define backlightIntensity      setpoint[1]
#define ambientTemperature      analogs[0]                                      // Analog Chanell 1,  Pin 3
#define pitTemperature          analogs[1]                                      // Analog Chanell 3,  Pin 5
#define enterKey                RB2
#define numOutSamples           5                                               // Number of Output samples to be Averaged into Output

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="Variables">
// *************** Main Routine ************************************************    


void main(void)
{
    SYSTEM_Initialize();
    
    int16_t         analogs[2]                      =   {0};                    // array of analog readings 
    
    extern uint16_t setpoint[2];                                                // defined in menu.c
    
    int16_t         output                          =   0;
    
    int32_t         outputTotal                     =   0;
    
    uint8_t         outputIndex                     =   0;
    
    int16_t         outputSamples[numOutSamples]    = {0};
    
    uint8_t         holdOutput                      =   0;
    
    int16_t         currentTemperature              =   750;
    
    int16_t         lastTemperature                 =   750;
    
    uint8_t         lidOpenCount                    =   0;
    
    uint8_t         j                               =   0;                      // Variable to loop readAnalog function
    
    uint8_t         x                               =   0;                      // Looping Initializer
    
    extern uint8_t  loop;                                                       // cycle (loop) counter
 
    uint16_t        viperFanOut                     =   0;                      // Pit Viper Fan Output
    
    extern int16_t errorValue;

    extern int16_t integralValue;
    
    extern int16_t  oldError;

    extern int16_t derivativeValue;

    // </editor-fold>
    
    PWM6_LoadDutyValue(viperFanOut);

    PWM7_LoadDutyValue(backlightIntensity);

    __delay_ms(300);

    LCD_Clear();
    
//    volatile unsigned char value = 0x09;
  //  unsigned char address = 0xE5;
    //eeprom_write(address, value);     // Writing value 0x9 to EEPROM address 0xE5        
    //value = eeprom_read (address);    // Reading the value from address 0xE5
    
//    eeprom_write(Kp_offset,10);
  //  eeprom_write(Ki_offset,4);
    //eeprom_write(Kd_offset,2);
        

    while (1)
    {
        if(loop>253)
        {
            PWM6_LoadDutyValue(viperFanOut);
            PWM7_LoadDutyValue(backlightIntensity);
            
            LCDWriteIntXY(0,0,errorValue,5,0,0);
            LCD_Write_Char(' ');
            LCD_Write_Char(' ');
            LCDWriteIntXY(8,0,integralValue,5,0,0);
            LCD_Write_Char(' ');
            LCD_Write_Char(' ');

            LCDWriteIntXY(0,1,derivativeValue,4,0,0);
//            LCDWriteIntXY(0,1,oldError,4,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,1,pitTemperature,4,1,0);
            LCDWriteIntXY(12,1,viperFanOut,4,0,0);
        
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
                output = PID_Calculate(pitSetpoint,pitTemperature);             // Assign the ADC(9) Boiler Temp to a temporary variable
                outputTotal = outputTotal - outputSamples[outputIndex];         // Subtract the oldest sample data from the total
                outputSamples[outputIndex] = output;                            // Assign the just read temperature to the location of the current oldest data
                outputTotal = outputTotal + outputSamples[outputIndex];         // Add that new sample to the total
                viperFanOut = (uint16_t)(outputTotal/numOutSamples);                    // Assign the average value of total to the boilerTemperature variable
                if(viperFanOut<25)viperFanOut=0;
                outputIndex+=1;                                                 // and move to the next index location
                if(outputIndex >= numOutSamples)outputIndex = 0;
            }
            else
            {
                holdOutput-=1;
            }

            currentTemperature=pitTemperature; 
            
            if(lidOpenCount<10)                                                 //  every 10 loop cycles(approx 10 Seconds))
            {
                lidOpenCount+=1;
            }
            else
            {
                lastTemperature=currentTemperature;                             // Update the lastTemperature value
                lidOpenCount=0;                                                 // and reset the lidOpenCount counter
            }
            
            if(lastTemperature-currentTemperature>100 || lastTemperature-currentTemperature<-100) // If the temp changed by more than 10F in 10 seconds
            {
                viperFanOut=0;                                                  // Turn OFF the Pit Fan
                holdOutput=30;                                                  // for 30 seconds           Fix (Set to proper duration)
            }
            loop=0;
        }

        for(j=0;j<2;j++) analogs[j]=readAnalog(j);                              // Read analog Temperatures
        
        ambientTemperature=tempCalc(analogs[0]);

        pitTemperature=tempCalc(analogs[1]);


        if(enterKey)
        {
//            PWM6MD      =   1;                                                  // Disable Pit Fan Output while in Menu
            LCD_Clear();
            LCDWriteStringXY(0,0,"Alter with Up/Dn");
            LCDWriteStringXY(0,1,"Enter Key to Set");
            __delay_ms(1500);
            LCD_Clear();
            menuChoice();
            __delay_ms(500);
            viperFanOut=0;
            PWM6_LoadDutyValue(viperFanOut);
//            PWM6MD      =   0;                                                  // Re-enable PWM6 Module (viperFanOut) 

        }
        loop+=1;
    }
}