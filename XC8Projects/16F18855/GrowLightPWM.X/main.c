#include "system.h"

#define     numSamples  61                      // Number of Temperature readings to Average (61 Hz, so 61 samples = 1 second of averaging)

unsigned int samples[numSamples]    = {0};

unsigned int Vsense                 = 0;        // Voltage across Rsense

bool readBit                        = 1;        // Allow an ADCRead once a cycle to measure current



void main(void)
{
    SYSTEM_Initialize();                        // Initialize the Device
    
    unsigned int sampleIndex        = 0;

    int32_t totals                  = 0;
    
    unsigned int I                  = 0;        // Average value of Vsense
    
    unsigned int currentFlow        = 0;        // Calculated Current Flow (based on Vsense)
    
    unsigned int setPoint           = 700;      // Current Flow Set Point
    
    unsigned int dutyCycle          = 0;        // Output Duty Cycle required to drive LED's
    
    signed char count               = 0;
    
    drawBox();                                  // Draw an Outline around the display
    

    while (1)
    {
        if(TMR2 >0x7F)
        {
            if(readBit)
            {
                Vsense = ADCRead(7);            // Measure the Voltage across the sense resistor
                readBit-=1;                     // Set readBit to 0, only allow one ADCRead/cycle (Set by ZCD Interrupt Flag)
            }
        }
        
        if(dutyCycle<1 || dutyCycle>1022)       // There is no Zero Cross to detect, so,
        {
            Vsense = ADCRead(7);                //  Read the ADC here
        }

        totals = totals - samples[sampleIndex]; // Subtract the oldest sample data from the total

        samples[sampleIndex] = Vsense;          // Assign the just read temperature to the location of the current oldest data

        totals = totals + samples[sampleIndex]; // Add that new sample to the total
            
        sampleIndex += 1;                       // and move to the next index location
            
        if(sampleIndex >= numSamples)
        {
            sampleIndex = 0;
        }
            
        I = totals / numSamples;                // assign the average value of total to the readTemperature variable
        
        
        currentFlow = I;                        // Do some math to make Voltage = Current in circuit  FIX
        
        if(currentFlow>setPoint)                // currentFlow is too high
        {
            count-=1;
            
            if(count<-10)
            {
                dutyCycle>0?dutyCycle-=1:dutyCycle; // if currentFlow is >0, decrement Output
                count = 0;
            }
        }
        else if(currentFlow<setPoint)           // currentFlow is below setPoint, so,           
        {
            count+=1;
            if(count>10)
            {
                dutyCycle<1023?dutyCycle+=1:dutyCycle;// if currentFlow is less than Maximum, increment Output
                count = 0;
            }
        }
        else
        {
            ;
        }

            
        PWM6_LoadDutyValue(dutyCycle);          // Load the just calculated dutyCycle
        
        LCDWriteStringXY(4,1,"Set Point:");
        LCD_Write_Int(setPoint,-1,0,0);
        LCD_Write_String("mA ");

        LCDWriteStringXY(8,2,"Amperage:");
        LCD_Write_Int(currentFlow,-1,0,0);
        LCD_Write_String("mA ");
        
        LCDWriteStringXY(4,3,"DutyCycle:");
        LCD_Write_Int(dutyCycle,5,0,0);
        
        I+=1;                                   // If we stop updating the Amperage reading, increment it to force a shutdown
        
        CLRWDT();                               // Clear the WatchDog Timer
    }
}