/* Still to do:
 * 1. Re-write to run on larger PIC, include LED display of moisture levels, current actions taking place, and current time.
 * 2. Re-write to allow addition of Master/Slave expansion boards
 *
 *
 * Automatic Plant Watering utilizing PIC16F720, with TMR0 as RTC (Starts @ 08:00 on Power-up or Re-Set)
 * Checks soil moisture between 5AM and 5 PM (checks once an hour), waters if needed.
 * 3 sets of 3 sensors each, to water 3 pots,(or 3 garden locations) using median select between the 3 sensors
 * at each location. Therefore, there are also 3 solenoid valves, one assigned to each group of 3 sensors.
 *
 * File:   NewClock.c
 * Author: DAVE
 *
 * Created on November 8, 2014, 8:01 AM
 *
 * Modified December 08, 2014, to change delays to micro seconds, rather than clock cycles
 *
 * Modified Dec 12, 2104, Wrote function to do median select, with Damon's guidance
 *
 * Modified Dec 16, 2014, Wrote function to read ADC values and assign to variables
 *
 * Modified Dec 18, 2014, Changed TMR0 Pre-Scaler from 128 to 256, x count from >14 to >7, OSCTUNE to 0x1e,
 * and added .25 seconds 4 times a minute.
 *
 * Dec 18, 2014, Re-wrote clock completely, changed Processor speed to 16MHz, added new var called bres,
 * add 256 to bres each time TMR0 overflows, (15625 times a second) then subtract 15625 and increment sl
 * This allows me to keep track of any error, which these numbers have none of!
 *
 * Dec 19, 2014, Changed Processor speed down to 2 MHz, I do not think there was enough time to execute
 * the loop at 16 MHz (because of the __delay_us(15)) Clock was definately WONKY
 *
 * Have figured out that running a RTC on the internal clock is useless,
 * it never runs at the same speed twice!!
 *
 * TRY CHANGING OSCTUNE VALUE DEPENDING ON WHAT IS HAPPENING, ie: Slower when not testing, faster when testing.
 *
 * Also, Program must run through every 512 us, or TMR0IF will not get re-set correctly, so Time will be incorrect,
 * not really a factor anymore since slowing down processor, but, was a factor when running @ 16 MHz, and using 15 us delay.
 * EDIT: Maybe it can run at 16MHz, I was caught by starting at say 8hrs and 40 minutes, then expecting the 5 minute operation
 * to happen at 5 minutes past 1 hour of stopwatch, but in reality it happened at 25 minutes, because of the 40 minute offset start.
 * So, I hadn't realized this, and maybe thought I was out by a shitTon, but was an error?
 *
 * PINOUTS on Main Board (from Top, Down LEFT side of board)
 * AN2, used for Sensor 1 of Solenoid 1
 * AN3, used for Sensor 2 of Solenoid 1
 * AN4, used for Sensor 3 of Solenoid 1
 *
 * AN5, used for Sensor 1 of Solenoid 2
 * AN7, used for Sensor 2 of Solenoid 2
 * AN8, used for Sensor 3 of Solenoid 2
 *
 * AN9, used for Sensor 1 of Solenoid 3
 * AN10, used for Sensor 2 of Solenoid 3
 * COMMON for ALL Analog probe inputs
 * AN11, used for Sensor 3 of Solenoid 3
 *
 * PINOUTS on Main Board (from Top, Down RIGHT side of board)
 * SSR Output, Solenoid 1 Positive Terminal
 * SSR Output, Solenoid 2 Positive Terminal
 * SSR Output, Solenoid 3 Positive Terminal
 * SSR Output, Solenoid Common Negative Terminal
 * NC
 * NC
 * -5V Input
 * +5V Input
 * NC
 * NC
 *
 * PINOUTS on PIC Board
 * Vdd (Pin 1)  +5V Supply
 * Vss (Pin 20) -5V Supply
 * RA0 (Pin 19) ICSPDAT ICSP Pin 4
 * RA1 (Pin 18) ICSPCLK ICSP Pin 5
 * RA2 (Pin 17) Analog 2, NC
 * RA3 (Pin 4)  Vpp ICSP Pin 1, also R3 Pad, and through R3 to ICSP Pin 2
 *              Programming Voltage, as well as Hardware reset Button
 * RA4 (Pin 3)  Analog 3, NC
 * RA5 (Pin 2)  Digital Out, Probe Voltage, JP1 Test hole
 * RB4 (Pin 13) Analog 10, R8 Pad
 * RB5 (Pin 12) Analog 11, R7 Pad
 * RB6 (Pin 11) Digital Out, Solenoid Valve 2 SSR, R6 Pad
 * RB7 (Pin 10) Digital Out, Probe Voltage, R5 Pad or 2 Solder Holes
 * RC0 (Pin 16) Analog 4, R4 Pad and Q3 Opto hole
 * RC1 (Pin 15) Analog 5, R2 Pad and Q2 Opto hole
 * RC2 (Pin 14) Digital Out, Solenoid Valve 3 SSR, R1 Pad and Q1 Opto hole
 * RC3 (Pin 7)  Analog 7, NC
 * RC4 (Pin 6)  Digital Out, Solenoid Valve 1 SSR, R12 Pad or 2 solder holes, or R11 Pad
 * RC5 (Pin 5)  Digital Out, R10 Pad, HeartBeat LED, on for 1 second, Off for 1 second
 * RC6 (Pin 8)  Analog 8, NC
 * RC7 (Pin 9)  Analog 9, R9 Pad
 */

#include <xc.h>

//#pragma config FOSC = INTOSCIO           // This line enables internal oscillator (Default runs @ 8 MHz) See Page 72
//#pragma config WDTE = OFF                // Sets WatchDog Timer Off See Manual Page 72

//#define _XTAL_FREQ 2000000		 // Must be defined, or Compiler will error out using __delay_ms()

#define Solenoid1 RC4
#define Solenoid2 RB6
#define Solenoid3 RC2
#define ProbePositiveV RA5
#define ProbeNegativeV RB7

char hh = 1, hl = 1, mh = 5, ml = 9, sh = 0, sl = 0; // Time keeping variables(Sec low, Sec High...)


void Init();                             // Initialize PORT, TRIS, ANSEL, OSCTUNE, etc.


main(void){                              //  Main Program

    unsigned int bres = 0;               // Short for Bresenham's Algorithm, but actually the overflow counter
//    bool Toggle = 1;                     // Try this?
    static signed bit Toggle;            // Toggle bit, used to generate heartBeat
    Toggle = 1;

    TMR0 = 0;                            // TMR0 Pre-set
    T0CS = 0;                            // TMR0 Clock source 0 = internal clock (FOSC/4)
    T0SE = 0;                            // Triggering on Low to High edge
    PSA = 0;                             // Work with a PreScaler
    PS0 = 1;                             // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS1 = 1;                             // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS2 = 1;                             // Set Pre-Scaler for TMR0 to 256 (1:256)

    Init();                              //  Initialize TRIS,ANSEL,PORT,OSCTUNE, and OSC Frequency

    while (1){                           //  Or, while true, so, Run continuously

        if (TMR0IF){                     // TMR0 Interupt caused by an overflow
            bres += 256;         	 // add 256 x 256(because of the pre-scaler) ticks to bresenham total
            TMR0IF = 0;                  // Re-set TMR0 Interupt
        }


	if(bres >= 1953){                // if we reached 500000(256 x 1953.125) 1 second has passed!
            bres -= 1953;         	 // subtract 1 second, retain error (except the .125)
            ++sl;                        // update clock, etc
            Toggle = Toggle - 1;         // Toggle LED marking passing of 1 Second (1 Sec on, 1 Sec off)
	}


        if(sl>9){
            sl = sl - 10;                // Reset sl to zero, accounting for Time correction as well
            ++sh;


            if(sh>5){                    // 1 Minute has passed
                sh=0;                    // Reset seconds high to zero
                ++ml;
   //             Toggle = 1 - Toggle;     // Toggle LED marking passing of 1 Minute (1 Min on, 1 Min off)
            }
        }

        if(ml>9){                        // 10 minutes have passed, re-set minutes low counter
            ml = 0;
            mh++;                        // And increment minutes high counter
        }

        if(mh>5){                        // 1 hour has passed, re-set minutes high counter
            mh = 0;
            ++hl;                        // And increment hours low counter
        }

        if(hl>9){                        // Have reached the 10 hr mark,
            hl = 0;                      // Reset hours low,
            ++hh;                        // and increment hh
        }

        if(hh >=2 && hl>3){              // 24 hours has passed, so,
            hh = 0;                      // reset hours high,
            hl = 0;                      // and hours low.
        }

        if(Toggle != 1){                 // If Toggle not equal to 1 (This is from toggle above)
            RC5 = 0;                     // Turn on RC5 for 1 second,
        }
            else{
            RC5 = 1;                     // otherwise, if Sec is equal to zero, turn Off RC5 for 1 second
            }

        if(hl + hh * 10 >= 5 && hl + hh *10 <= 17) {//Do on hr rollover, should run between 5 AM & 5 PM
            MoistureCheck();
        }


    }
}





void MoistureCheck(){

    ADCInit();

    unsigned char a, c, e, g, i, k, m, o, q, t;   // Analog values of AN2, 3, 4, 5, 7, 8, 9, 10, 11 and cycle counter t

//    ADCON1=0x10;                // Set ADC conversion clock FOSC/8 See Page 80 Now in ADCInit

    if(mh * 10 + ml >= 0 && mh * 10 + ml < 1){//0 - 1 minutes, Turn on Probe Voltage, + on RA5, - on RB7
        ProbePositiveV = 1;              // Apply 5V to RA5 Pin 2, Used to generate V relative to soil moisture
        ProbeNegativeV = 0;              // Apply 0V to RB6 (Pin 11) 0V reference for Soil moisture probe
    }

    if(mh * 10 + ml >= 1 && mh * 10 + ml < 2){ //1 - 2 minutes, Read Analogs
        ++t;

        if(t >= 9){
            a = ADCRead(2);              // Read ADC Channel 2
            t = 0;                       // Reset t to zero, Restart all conversions
        }

        if(t == 8){
            c = ADCRead(3);              // Read ADC Channel 3
        }

        if(t == 7){
            e = ADCRead(4);              // Read ADC Channel 4
        }

        if(t == 6){
            g = ADCRead(5);              // Read ADC Channel 5
        }

        if(t == 5){
            i = ADCRead(7);              // Read ADC Channel 7
        }

        if(t == 4){
            k = ADCRead(8);              // Read ADC Channel 8
        }

        if(t == 3){
            m = ADCRead(9);              // Read ADC Channel 9
        }

        if(t == 2){
            o = ADCRead(10);             // Read ADC Channel 10
        }

        if(t == 1){
            q = ADCRead(11);             // Read ADC Channel 11
        }
    }

    if(mh * 10 + ml >= 2 && mh * 10 + ml < 4){ //2 - 4 minutes,
        ProbePositiveV = 0;              // Apply 0V to RA5 Pin 2, Used to reverse current to probe, preventing buildup on probe
        ProbeNegativeV = 1;              // Apply 5V to RB6 (Pin 11) Used to reverse current to probe, preventing buildup on probe
    }

    if(mh * 10 + ml >= 4 && mh * 10 + ml < 5){ //4 - 5 minutes,
        ProbePositiveV = 0;              // Apply 0V to RA5 Pin 2, Turn off Voltage to Probes
        ProbeNegativeV = 0;              // Apply 0V to RB6 (Pin 11) Turn off Voltage to Probes
    }

    if(mh * 10 + ml >= 5 && mh * 10 + ml < 6){//5 - 6 minutes,1st sol run time, but could run until 20 if required

        unsigned char f = Median(a, c, e); // Take the Median of the three Probe readings, and Assign it to f

        if(f < 127){                     // f is the median result, so compare to desired setpoint
            Solenoid1 = 0;               // 0 is on, as there is 5 volts on SSR lead, and 0 Volts here = current flow.
        }
        else{
            Solenoid1 = 1;               // 1 is Off, as there is 5 volts on SSR lead, and 5 Volts here = No current flow.
        }
    }

    if(mh * 10 + ml >= 6 && mh * 10 + ml < 20){ //Turn off RB4 after watering
        Solenoid1 = 1;                   // 1 is Off, as there is 5 volts on SSR lead, and 5 Volts here = No current flow.
    }


    if(mh * 10 + ml >= 20 && mh * 10 + ml < 21){ //20 - 21 minutes

        unsigned char l = Median(g, i, k); // Take the Median of the three Probe readings, and Assign it to l

        if(l < 127){                     // l is the median result, so compare to desired setpoint
            Solenoid2 = 0;               // 0 is on, as there is 5 volts on SSR lead, and 0 Volts here = current flow.
        }
        else{
            Solenoid2 = 1;               // 1 is Off, as there is 5 volts on SSR lead, and 5 Volts here = No current flow.
        }
    }

    if(mh * 10 + ml >= 21 && mh * 10 + ml < 35){         //21 - 35 minutes,turn off RB4
        Solenoid2 = 1;                   // 1 is Off, as there is 5 volts on SSR lead, and 5 Volts here = No current flow.
    }


    if(mh * 10 + ml >= 35 && mh * 10 + ml < 36){ //15 - 16 minutes,but could run until 60 if required

        unsigned char r = Median(m, o, q); // Take the Median of the three Probe readings, and Assign it to r

        if(r < 127){                     // r is the median result, so compare to desired setpoint
            Solenoid3 = 0;               // 0 is on, as there is 5 volts on SSR lead, and 0 Volts here = current flow.
        }
        else{
            Solenoid3 = 1;               // 1 is Off, as there is 5 volts on SSR lead, and 5 Volts here = No current flow.
        }
    }

    if(mh * 10 + ml >= 36 && mh * 10 + ml < 60){ //Turn off RB4 after watering
        Solenoid3 = 1;                   // 1 is Off, as there is 5 volts on SSR lead, and 5 Volts here = No current flow.
    }
}
//                                       E N D   O F   P R O G R A M