/* 
 * File:   main.c
 * Author: DAVE
 *
 * Created on December 20, 2014, 10:00 AM
 * Re_Worked Starting April 27, 2015
 *
 * RC0 (Pin 16)Input connected through Sharp 8171 Opto-isolator and 34.6K resistor to Brew Switch, (use bi-directional Opto next time, less trouble wth seeing input)
 * RC1 (Pin 15)Input connected through Opto-isolator and 27.7K resistor to Water Switch
 * RC4 (Pin 6) Output direct connected to Piezo Buzzer for Alarm
 * RC5 (Pin 5) Output connected to LED and SSR, used to drive water solenoid into boiler(after pressure tank)
 * RC7 (Pin 9) Output connected to LED and SSR, used to drive pump (Use PWM on pump next time, Need to set period to 120 Hz, and pulse width to no more than 1/2, Pump Relax time)
 */

#include <xc.h>
#include "system.h"
#include "user.h"


#define _XTAL_FREQ 2000000                                                      // Must be defined, or Compiler will error out using __delay_ms()

#define BrewSwitch          PORTCbits.RC0            
#define WaterSwitch         PORTCbits.RC1
#define Piezo               PORTCbits.RC4
#define WaterSolenoid       PORTCbits.RC5
#define Pump                PORTCbits.RC7

#define PreInfusionTime     (25 + 1)                                            // PreInfusion time in Tenths of seconds, so, 25 tenths = 2.5 seconds(26)
#define Pressurize          (95 + PreInfusionTime)                              // Duration of Pressurize Cycle, StartPull runs on completion of Pressurize Time
#define StartPull           (20 + Pressurize)                                   // StartPull opens Water Solenoid , and leaves pump run for StartPull Duration
#define ContinuePull        (600 + 1)                                           // Shot duration, 60 seconds from Start of Cycle(601)
#define Warning             (650 + 1)                                           // Turn on Warning Piezo @ 65 Seconds, reminder to turn off switch (651)

main(void)                                                                      // Main Program
{
    char z = 0;                                                                 // z counts seconds alarm has been active
    int i = 0, j = 0, y = 0;                                                    // i and j are used with Water Switch Logic, y for BrewSwitch
    unsigned int bres = 0;                                                      // Short for Bresenham's Algorithm, but actually the overflow counter
    int tenthCount = 0;                                                         // 1/10 seconds running count

    ConfigureOscillator();

    Init();                                                                     // Initialize TRIS,ANSEL,PORT,OSCTUNE, and OSC Frequency

    delay_ms(1000);                                                             // Delay attempt to Stop random actions at Startup
    
    while (1)                                                                   // Or, while true, so, Run continuously
    { 
                                                                                // Following runs the Pump and Solenoid while Brewing
BrewInProcess: ;

        if(BrewSwitch == 1)                                                     // Check if Brew Switch is On
        {
            y += 20;                                                            // Increment BrewSwitch variable by 20, as most of the time, waveform has Opto-Isolator turned Off

            if (y > 1000)
            {
                y = 1000;                                                       // Limit windup on BrewSwitch variable
            }
        }

        if (BrewSwitch == 0)                                                    // Check if brew swith is Off, or on negative half of wave
        {
            y -= 1;                                                             // Decrement BrewSwitch by 1, as waveform has Opto-Isolator in this state most of the time

            if(y < 0)                                                           // If y is less than zero,
            {
                y = 0;                                                          // re-set to zero, so it does not underflow.
            }
        }

        if (y <= 0)                                                             // BrewSwitch is zero when switch has been off 1000 cycles
        {
            tenthCount = 0;                                                     // Set tenCount to zero, as Brew Switch is Off
            Piezo = 1;                                                          // Turn off Buzzer. (Needed if Brew switch shut off while buzzer is on)
            z = 0;                                                              // Re-set z (alarm counter)
            }

        if  (y > 10)                                                            // Switch is On, as value is greater than 10
        {
            if(TMR0IF)                                                          // TMR0 Interupt caused by an overflow
            {
                bres += 256;                                                    // add 256 x 256(because of the pre-scaler) ticks to Bresenham total
                TMR0IF = 0;                                                     // Re-set TMR0 Interupt
            }

            if(bres >= 195)                                                     // if we reached 50000(256 x 195.3125) 1/10 second has passed! (50,000 is 2 MHz/4 or Fosc/4 / 10, for 1/10 seconds)
            {
                bres -= 195;                                                    // subtract 1/10 second, retain error (except the .3125, this is adjusted out with OSCTUNE)
                ++tenthCount;                                                   // Update variable we use to time program (when to start & stop stuff)
            }
        }

        if (tenthCount == 0)                                                    // If Brew Switch is Off, Set outputs to SSR's Off
        {
            WaterSolenoid = 1;                                                  // Turn Off Solenoid valve
            Pump = 1;                                                           // Turn Off Pump
        }

        if (tenthCount > 0 && tenthCount <= PreInfusionTime)                    // Brew Switch is on, Run Preinfusion
        {
            WaterSolenoid = 0;                                                  // Turn on Solenoid to allow water into boiler (Preinfusion, 10 tenCount or 2.5 seconds)
            Pump = 0;                                                           // Also, Start the Pump
        }

        if (tenthCount > PreInfusionTime && tenthCount <= Pressurize)           // Between 2.6 and 16 seconds
        {
            WaterSolenoid = 1;                                                  // Turn Off Solenoid valve
            Pump = 0;                                                           // And, Leave Punp Running
        }

        if (tenthCount > Pressurize && tenthCount <= StartPull)                 // From 16 seconds to 18 seconds
        {
            WaterSolenoid = 0;                                                  // Turn On Solenoid Valve again
            Pump = 0;                                                           // Leave Pump Running for an additional 2 seconds
        }

        if (tenthCount > StartPull && tenthCount <= ContinuePull)               // From 18 seconds to 85 seconds
        {
            WaterSolenoid = 0;                                                  // Keep Solenoid Valve Open (to deliver shot),
            Pump = 1;                                                           // Shut Off Pump
        }

        if (tenthCount > ContinuePull && tenthCount < Warning)                  // Between 85 and 90 seconds
        {                  
            WaterSolenoid = 1;                                                  // Shut Off Solenoid Valve
            Pump = 1;                                                           // Keep Pump Off
        }

        if (tenthCount >= Warning)                                              // 90 Seconds has elapsed without Brew Switch being turned off,
        {                  
            Piezo = 0;                                                          // Activate Piezo Buzzer for 1/2 second
        }

        if(tenthCount >= Warning + 5)                                           // Piezo has been on for 1/2 second
        { 
            Piezo = 1;                                                          // So, Shut it off! (pulsing alarm)
            tenthCount = (Warning - 5);                                         // set time back 2 seconds, so it can go again.(in 1.5 seconds)
            z++;                                                                // Increment z every 2 seconds, after 10 counts, alarm will go solid
        }

        if(z >= 10)                                                             // After 18 seconds of pulsing alarm being ignored,
        { 
            Piezo = 0;                                                          // turn Piezo on all the time,
            tenthCount = (Warning - 25);                                        // and set tenCount to below the pulsing alarm time,
            z = 10;                                                             // so Piezo will not start pulsing alarm again.
        }                                       
    

        if (WaterSwitch == 1)                                                   // Water switch is closed and on top of waveform
        {
            j += 20;                                                            // Increment value of j, to determine if switch is On or Off
        }

        if (WaterSwitch == 0)                                                   // Water switch waveform has opto-isolator off, or Water switch off.
        {
            j -= 1;                                                             // Decrement value of j, as switch appears to be Off

            if(j < 0)
            {
                j = 0;
            }
        }

        if (j > 10)                                                             // Switch is On
        {
            i++;                                                                // Increment Counter
        }

        if (j > 1000)                                                           // Limit windup of j value
        {
            j = 1000;
        }

        if (j == 0)                                                             // Switch is Off
        {
            i = 0;                                                              // Therefore, set counter to Zero

            if(y > 10)
            {
                goto BrewInProcess;
            }
        }

        if (i == 0)                                                             // Switch is Off, Set Solenoid and Pump to Off
        {
            WaterSolenoid = 1;                                                  // Set Solenoid to Off
            Pump = 1;                                                           // Set Pump to Off
        }


        if (i >= 1000)                                                          // Switch is On
        {
            WaterSolenoid = 0;                                                  // Set Solenoid to On
            Pump = 0;                                                           // Set Pump to On
            i = 1000;                                                           // Limit windup on Counter
        }
    }
}                                                                               // E N D   O F   P R O G R A M ! ! !