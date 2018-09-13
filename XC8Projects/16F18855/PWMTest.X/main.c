#include "system.h"
#include "lcd.h"
#include <math.h>

#define     numSamples  10                                                      // Number of Temperature readings to Average


uint16_t samples[numSamples] = {0};


void main(void)
{
    SYSTEM_Initialize();
    
    LCD_Init(NONE);

    __delay_ms(100);
    
    LCD_Clear();

    InitCustomChars();
    
    uint16_t readTemperature, setpoint = 70, outCurrent = PWM6_INITIALIZE_DUTY_VALUE, readTemperatureOld = 20;
    
    float R, steinhart;
    
    static uint16_t sampleIndex = 0;

    int32_t totals = 0;
    

    
    while (1)
    {
        readTemperature = ADCC_GetSingleConversion(2);                          // Assign the just read temperature to the location of the current oldest data
            
        totals = totals - samples[sampleIndex];                                 // Subtract the oldest sample data from the total

        samples[sampleIndex] = readTemperature;                                 // Assign the just read temperature to the location of the current oldest data

        totals = totals + samples[sampleIndex];                                 // Add that new sample to the total
            
        sampleIndex += 1;                                                       // and move to the next index location
            
        if(sampleIndex >= numSamples)
        {
            sampleIndex = 0;
        }
            
        readTemperature = totals / numSamples;                                  // assign the average value of total to the readTemperature variable

        if(readTemperature > readTemperatureOld)
        {
            readTemperatureOld += 1;
        }
        
        if(readTemperature < readTemperatureOld)
        {
            readTemperatureOld -= 1;
        }
        
        readTemperature = readTemperatureOld;

        
        if(setpoint > readTemperature)
        {
            if(outCurrent < 1022)
            {
//                x+=1;
  //              if (x>9)
    //            {
                    outCurrent++;
      //              x = 0;
        //        }
            }
            else
            {
                outCurrent = 1023;
            }
        }
        
        if(setpoint < readTemperature)
        {
            if(outCurrent > 1)
            {
//                x-=1;
  //              if(x<-9)
    //            {
                    outCurrent-=1;
//                    x = 0;
      //          }
             }
            else
            {
                outCurrent = 0;
            }
        }
        
        R = 9970/(1023/ (float)readTemperature - 1);
        
//        readTemperature = (1023 /(float)readTemperature) - 1;
  //      readTemperature = 10000 / (float)readTemperature;
 
//        float steinhart;
        steinhart = R / 9970;     // (R/Ro)
        steinhart = log(steinhart);                  // ln(R/Ro)
        steinhart /= 3490;                   // 1/B * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15); // + (1/To)
        steinhart = 1.0 / steinhart;                 // Invert
        steinhart -= 273.15;                         // convert to C
 
//        percentOutput = (uint16_t)(outCurrent*.09765625);
        
//        measuredCurrent = (uint16_t)(readCurrent * 1.5454545454);
        
        
//        LCDWriteIntXY(0,0,measuredCurrent,-1,0,0);
  //      LCD_Write_Char('m');
    ///    LCD_Write_Char('a');
       // LCD_Write_Char(' ');
//        LCD_Write_Char(' ');

  //      LCDWriteIntXY(0,8,percentOutput,2,0,0);
    //    LCD_Write_Char('%');
      //  LCD_Write_Char(' ');
        //LCD_Write_Char(' ');
        
        LCDWriteIntXY(0,0,(unsigned int)R,-1,0,0);
//        LCD_Write_Char(' ');
  //      LCD_Write_Char(' ');
 
        LCDWriteIntXY(1,0,(unsigned int)steinhart,-1,0,0);
        LCD_Write_Char(' ');
//        LCD_Write_Char(' ');
 
//        LCDWriteIntXY(1,4,z,-1,0,0);
  //      LCD_Write_Char(' ');
    //    LCD_Write_Char(' ');
        
        

//        __delay_ms(10);
        

        PWM6_LoadDutyValue(outCurrent);
    }
}