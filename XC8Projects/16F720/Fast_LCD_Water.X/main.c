
#include <xc.h>
#include "hd44780.h"                // LCD Display driver
#include "configuration_bits.c"     // Config settings
#include "system.h"                 // App Initialization settings
#include "user.h"                   // ADC & Median Select Modules


#define MenuButton      RA2         // Used to display Probe Readings and SetPoint, Uses Weak Pull-up
#define ProbePositiveV  RA5         // Voltage applied to Probe/reistor network, for ADC input
#define ProbeNegativeV  RB7         // Voltage applied to Probe/reistor network, for ADC input
#define Solenoid        RB6         // Output that turns on Water Solenoid
#define StartWater      45          // Time in minutes after the hour to Start Watering (Measuring Starts @ 40 minutes, so can't start before then!!)
#define EndWater        46          // Time in minutes after the hour to End Watering (Must end before 60)

signed char    dd = 0;              // Time keeping variable Days
signed char    hh = 1;              // Time keeping variable Hours high
signed char    hl = 0;              // Time keeping variable Hours low
signed char    mh = 0;              // Time keeping variable Minutes high
signed char    ml = 0;              // Time keeping variable Minutes low
signed char    sh = 0;              // Time keeping variable Seconds high
signed char    sl = 0;              // Time keeping variable Seconds low

unsigned int bres = 0;              // Short for Bresenham's Algorithm, but actually the overflow counter
char Watered = 0;                   // Watered bit, used to generate text on Display
unsigned int num, ofnum;            // Count the number of times Solenoid ran out of possible run times
unsigned char a, c, e, g, t = 3;    // Analog values of AN9, AN10, AN11, Median (g), and ADC cycle counter (t)
unsigned char Setpoint;             // Setpoint = Value set on Pot connected to Analog 3

void MoistureCheck();               // Used to check if we need to turn on Solenoids to output WATER (The whole purpose of this thing!!)

void main ()
{
    ConfigureOscillator();          // Set-up Oscillator, OSCTUNE, and OSC Frequency
    
    Init();                         //  Initialize TRIS,ANSEL,& PORT Settings

    delay_ms(1000);                 // Wait 1 second for LCD to start-up
    LCDInit(0x00);                  // Initialize the LCD Module
    LCDClear();                     // Clear LCD Screen

    while (1)                       //  Or, while true, so, Run continuously
    {
        if (TMR0IF)                 // TMR0 Interupt caused by an overflow
        {
            bres += 256;         	// add 256 x 256(because of the pre-scaler) ticks to bresenham total
            TMR0IF = 0;             // Re-set TMR0 Interupt
        }

    	if(bres >= 1953)            // if we reached 500000(256 x 1953.125) 1 second has passed!
        {
            bres -= 1953;         	// subtract 1 second, retain error (except the .125)
            ++sl;                   // update clock, etc

            if(sl>9)
            {
                sl -= 10;           // Reset sl to zero
                sh++;

                if(sh>5)            // 1 Minute has passed
                {
                    sh=0;           // Reset seconds high to zero
                    ml++;
                }
            }
            
            if(ml>9)                // 10 minutes have passed,
            {
            ++mh;                   // Increment minutes high counter,
            ml = 0;                 // and, re-set minutes low counter
                
                if (mh%2 ==0)       // If mh is 0, 2, or 4, so, three times in 60 minutes
                {
                sl -= 2;            // Subtract 1 second to account for clock inacuracies
                }

            LCDReset(0x00);         // Automatically re-set the LCD every 10 minutes
            }

            if(mh>5)
            {                       // One hour has passed, re-set minutes high counter
            mh = 0;                 // Re-set minutes high to zero
            ++hl;                   // Increment hours low counter

            sl += 1;                // Once an hour, Add 1 second to account for clock inacuracies

            if(Watered == 0)        // Check if Solenoid was activated
            {
                ++ofnum;            // Increment Number of Possible watering count times
            }

            if(Watered ==1)         // Check if Solenoid was activated
            {
                ++num;              // Increment the solenoid run counter
                ++ofnum;            // Also Increment Number of Possible watering count times
                Watered = 0;        // and, Re-set the Watered Bit, ready to go again
            }
        }

        if(hl>9)
        {                           // Have reached the 10 hr mark,
            hl = 0;                 // Reset hours low,
            ++hh;                   // and increment hours high
        }

        if(hh >=2 && hl>3)          // 24 hours has passed, so,
        {
            hh = 0;                 // reset hours high,
            hl = 0;                 // and hours low.
            ++dd;                   // and, Increment Days in operation
            sl -= 2;                // Subtract 12 seconds at the end of the day
        }

        Setpoint = ADCRead(3);
        MoistureCheck();

        if(MenuButton == 0)
            {
    // LCD LINE ONE
                LCDWriteIntXY(0,0,c,3);
                LCDWriteStringXY(3,0," ");
                LCDWriteIntXY(4,0,e,3);
                LCDWriteStringXY(7,0," ");
                LCDWriteIntXY(8,0,a,3);
                LCDWriteStringXY(11,0," ");
                LCDWriteIntXY(12,0,num,4);

    // LCD LINE TWO
                LCDWriteStringXY(0,1,"  SETPOINT:  ");
                LCDWriteIntXY(13,1,Setpoint,3);
            }

            if(MenuButton == 1)
            {
                if(Watered == 1 && mh *10 + ml <=EndWater)
                {
                    LCDWriteStringXY(0,1,"Watering ");
                }

                if(Watered == 1 && mh *10 + ml >=EndWater)
                {
                    LCDWriteStringXY(0,1,"Watered  ");
                }

                if(Watered == 0 && mh * 10 + ml <= StartWater)
                {
                    LCDWriteStringXY(0,1,"Waiting  ");
                }

                if(Watered == 0 && mh * 10 + ml >= StartWater)
                {
                    LCDWriteStringXY(0,1,"No Water ");
                }

                LCDWriteIntXY(9,1,num,3);
                LCDWriteStringXY(12,1,"/");
                LCDWriteIntXY(13,1,ofnum,3);

                LCDWriteStringXY(0,0,"TIME ");
                LCDWriteIntXY(5,0,dd,2);
                LCDWriteStringXY(7,0,":");
                LCDWriteIntXY(8,0,hh,1);
                LCDWriteIntXY(9,0,hl,1);
                LCDWriteStringXY(10,0,":");
                LCDWriteIntXY(11,0,mh,1);
                LCDWriteIntXY(12,0,ml,1);
                LCDWriteStringXY(13,0,":");
                LCDWriteIntXY(14,0,sh,1);
                LCDWriteIntXY(15,0,sl,1);

            }
        }
    }
}


//*****************************************************************************************
// Function to test Moisture level of soil, Turn on Solenoid valves if required
//*****************************************************************************************
void MoistureCheck()
{
//****************************************************************************************
// Initialize ADC Converter
//*****************************************************************************************
    ADCInit();

//*****************************************************************************************
// 40 minutes to 40 minutes and 16 seconds, Turn on Probe Voltage, + on RA5, - on RB7
//*****************************************************************************************
    if(mh * 10 + ml == 40 && sh * 10 + sl >= 10 && sh * 10 +sl < 26)
    {
        ProbePositiveV = 1;         // Apply 5V to RA5 Pin 2, Used to generate V relative to soil moisture
        ProbeNegativeV = 0;         // Apply 0V to RB&6 (Pin 10) 0V reference for Soil moisture probe
            
        if(t >= 3)
        {
            a = ADCRead(9);         // Read ADC Channel 9
            t = 0;                  // Reset t to zero, Restart all conversions
        }

        if(t == 2)
        {
            c = ADCRead(10);        // Read ADC Channel 10
        }

        if(t == 1)
        {
            e = ADCRead(11);        // Read ADC Channel 11
        }
         
        ++t;
    }
    
    else if(mh * 10 + ml == 40 && sh * 10 + sl >= 26 && sh * 10 +sl < 36)
    {
        delay_us(200);
        ProbePositiveV = 0;         // Apply 0V to RA5 Pin 2, Used to generate 0V relative to soil moisture
        ProbeNegativeV = 1;         // Apply 5V to RB6 (Pin 10) 5V reverse Voltage on moisture probe
    }

    else
        
    {
        ProbePositiveV = 0;         // Apply 5V to RA5 Pin 2, Used to generate V relative to soil moisture
        ProbeNegativeV = 0;         // Apply 0V to RB&6 (Pin 10) 0V reference for Soil moisture probe
    }


     
    if(mh * 10 + ml  >=StartWater && mh * 10 + ml < EndWater)
    {
        g = Median(a, c, e);        // Take the Median of the three Probe readings, and Assign it to g
       
        if(g < Setpoint)            // Compare g to desired setpoint, Larger Setpoint = more water
        {
            Solenoid = 0;           // 0 is on, as there is 5 volts on SSR lead, and 0 Volts here = current flow.
            Watered = 1;
        }
    }
       
    if(mh * 10 + ml  < StartWater || mh * 10 + ml >= EndWater)
    {
        Solenoid = 1;               // 1 is Off, as there is 5 volts on SSR lead, and 5 Volts here = No current flow.
    }
}