
#include<xc.h>
#include "lcd_hd44780_pic16.h"
#include "configuration_bits.c"
#include "system.h"
#include"user.h"

#define ProbePositiveV RA2
#define ProbeNegativeV RA5

char hh = 0, hl = 8, mh = 0, ml = 0, sh = 0, sl = 0;            // Time keeping variables(Sec low, Sec High...)
unsigned int bres = 0;                                          // Short for Bresenham's Algorithm, but actually the overflow counter
char Toggle2 = 1;

void WaterCheck();                       // Used to check if we need to turn on Solenoids to output WATER (The whole purpose of this thing!!)


void main ()
{
    Init();                              //  Initialize TRIS,ANSEL,PORT,OSCTUNE, and OSC Frequency
    
    delay_ms(500);
    LCDInit(0x00);                                      // Initialize the LCD Module
    LCDClear();                                         // Clear LCD Screen

    while (1)                            //  Or, while true, so, Run continuously
    {
        if (TMR0IF)                      // TMR0 Interupt caused by an overflow
        {
            bres += 256;         	 // add 256 x 256(because of the pre-scaler) ticks to bresenham total
            TMR0IF = 0;                  // Re-set TMR0 Interupt
        }


	if(bres >= 1953){                // if we reached 500000(256 x 1953.125) 1 second has passed!
            bres -= 1953;         	 // subtract 1 second, retain error (except the .125)
            ++sl;                        // update clock, etc
            Toggle2 = 1 - Toggle2;       // Toggle LED marking passing of 1 Second (1 Sec on, 1 Sec off)

            if(sl>9){
                sl = 0;                         // Reset sl to zero, accounting for Time correction as well
                sh++;


                if(sh>5){                    // 1 Minute has passed
                    sh=0;                    // Reset seconds high to zero
                    ml++;
                }
            }
            WaterCheck();
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

        if(Toggle2 != 1){                 // If Toggle not equal to 1 (This is from toggle above)
            RC7 = 0;                     // Turn on RC5 for 1 second,
        }
            else{
            RC7 = 1;                     // otherwise, if Sec is equal to zero, turn Off RC5 for 1 second
        }
    }
}




void WaterCheck()
{

    ADCInit();

    unsigned char a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, t;   // Analog values of AN2, 3, 4, 5, 7, 8, 9, 10, 11 and cycle counter t
    
                LCDWriteIntXY(0,0,a,3);
                LCDWriteIntXY(4,0,c,3);
                LCDWriteIntXY(8,0,e,3);
                LCDWriteIntXY(12,0,g,3);
            //    LCDWriteIntXY(16,0,sl,1);
                LCDWriteIntXY(0,1,i,3);
                LCDWriteIntXY(4,1,m,3);
                LCDWriteIntXY(8,1,q,3);
                LCDWriteIntXY(12,1,ml,1);
                LCDWriteStringXY(13,1,":");
                LCDWriteIntXY(14,1,sh,1);
                LCDWriteIntXY(15,1,sl,1);
                LCDWriteIntXY(17,2,k,3);
                LCDWriteIntXY(17,3,i,3);
     /*       if(sl <=1){
                LCDClear();
                LCDGotoXY(0,0);
                LCDWriteString("Current Time is:");
                LCDWriteIntXY(4,1,hh,1);
                LCDWriteIntXY(5,1,hl,1);
                LCDGotoXY(6,1);
                LCDWriteString(":");
                LCDWriteIntXY(7,1,mh,1);
                LCDWriteIntXY(8,1,ml,1);
                LCDGotoXY(9,1);
                LCDWriteString(":");
                LCDWriteIntXY(10,1,sh,1);
                LCDWriteIntXY(11,1,sl,1);
                LCDGotoXY(12,1);
                LCDWriteString("     ");
            //    LCDWriteIntXY(10,1,PORTC,6);
             //   LCDWriteIntXY(12,1,Toggle2,1);
            }
       */   //     if(sl > 1 && sl <= 10){
          //      LCDClear();
         //       LCDWriteIntXY(0,0,q,3);
//                LCDWriteIntXY(9,0,ADCRead(14),3);
         //       }


    //    ADCON1=0x10;                // Set ADC conversion clock FOSC/8 See Page 80 Now in ADCInit

    if(ml < 1){                  //0 - 1 minutes, Turn on Probe Voltage, + on RA5, - on RB7
        ProbePositiveV = 1;              // Apply 5V to RA5 Pin 2, Used to generate V relative to soil moisture
        ProbeNegativeV = 0;              // Apply 0V to RB6 (Pin 11) 0V reference for Soil moisture probe
    }

    if(ml >= 1 && ml < 2){              //1 - 2 minutes, Read Analogs
        ++t;

        if(t >= 9)
        {
            a = ADCRead(3);              // Read ADC Channel 2
            t = 0;                       // Reset t to zero, Restart all conversions
        }

        if(t == 8)
        {
            c = ADCRead(3);              // Read ADC Channel 3
        }

        if(t == 7)
        {
            e = ADCRead(3);              // Read ADC Channel 4
        }

        if(t == 6)
        {
            g = ADCRead(3);              // Read ADC Channel 5
        }

        if(t == 5)
        {
            i = ADCRead(3);              // Read ADC Channel 7
        }

        if(t == 4)
        {
            k = ADCRead(3);              // Read ADC Channel 8
        }

        if(t == 3)
        {
            m = ADCRead(3);              // Read ADC Channel 9
        }

        if(t == 2)
        {
            o = ADCRead(3);             // Read ADC Channel 10
        }

        if(t == 1)
        {
            q = ADCRead(3);             // Read ADC Channel 11
        }

    }

        if(ml >= 2 && ml < 3)                //2 - 4 minutes, every 10 minutes
        {
            ProbePositiveV = 0;          // Apply 0V to RA5 Pin 2, Used to reverse current to probe, preventing buildup on probe
            ProbeNegativeV = 1;          // Apply 5V to RB6 (Pin 11) Used to reverse current to probe, preventing buildup on probe
        }

        if(ml >= 3 && ml < 4)               //4 - 5 minutes,
        {
            ++t;
        if(t >= 9){
            b = !ADCRead(3);              // Using ! Operator is same as using b = ADCRead(ch); b = 255 - b;     ADC Channel 2
            t = 0;                       // Reset t to zero, Restart all conversions
        }

        if(t == 8){
            d = !ADCRead(3);              // Read ADC Channel 3
        }

        if(t == 7){
            f = !ADCRead(3);              // Read ADC Channel 4
        }

        if(t == 6){
            h = !ADCRead(3);              // Read ADC Channel 5
        }

        if(t == 5){
            j = !ADCRead(3);              // Read ADC Channel 7
        }

        if(t == 4){
            l = !ADCRead(3);              // Read ADC Channel 8
        }

        if(t == 3){
            n = !ADCRead(3);              // Read ADC Channel 9
        }

        if(t == 2){
            p = !ADCRead(3);             // Read ADC Channel 10
        }

        if(t == 1)
        {
            r = !ADCRead(3);             // Read ADC Channel 11
        }
   }

    if(ml >= 5 && ml <6)
        {
            ProbePositiveV = 0;          // Apply 0V to RA5 Pin 2, Turn off Voltage to Probes
            ProbeNegativeV = 0;          // Apply 0V to RB6 (Pin 11) Turn off Voltage to Probes
        }

        //                    E N D   O F   P R O G R A M

}

