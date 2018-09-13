#include<xc.h>
#include "lcd_hd44780_pic16.h"
#include "PID_Lib.h"

#pragma config FOSC = INTOSCIO                                          // Oscillator Selection bits
#pragma config WDTE = OFF                                               // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON                                               // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON                                               // Brown-out Reset Enable bit (BOR enabled)
#define _XTAL_FREQ 2000000                                              // Must be defined, or Compiler will error out using __delay_ms()

/*

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;
void setup()
{
  windowStartTime = millis();

  //initialize the variables we're linked to
  Setpoint = 100;

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = analogRead(0);
  myPID.Compute();

  /************************************************
   * turn the output pin on/off based on pid output
   ************************************************
  unsigned long now = millis();
  if(now - windowStartTime>WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if(Output > now - windowStartTime) digitalWrite(RelayPin,HIGH);
  else digitalWrite(RelayPin,LOW);

}

*/
int Kp = 1, Ki = 1, Kd = 0, MinOutput = -100, MaxOutput = 100;
char hh = 1, hl = 2, mh = 0, ml = 3, sh = 0, sl = 0;                    // Time keeping variables(Sec low, Sec High...)
unsigned int bres = 0;                                                  // Short for Bresenham's Algorithm, but actually the overflow counter
char Toggle = 1, Toggle2 = 1;
int CalCurrentTemp = 0, CurrentTemp = 0, FixedV = 0;

int SetPoint = 12, InputValue = 10;
int WindowSize = 10;
int windowStartTime;
int output = 0;
int Err;

int PID_Calculate(int SetPoint, int InputValue);

void SPI_Init(void);
void SPI_Write(unsigned char data);
unsigned char dummy;
void SPI_Write_Enable(void);
void IO_Init(void);

void Init();
void ADCInit();                                                         // Initialize the Analog to Digital Converter
unsigned char ADCRead(unsigned char);                                   // Read the analog values of moisture probes, to determine if we need water.

void main (void){



    ADCInit();

    Init();                                                             //  Initialize TRIS,ANSEL,PORT,OSCTUNE, and OSC Frequency

    __delay_ms(500);
    LCDInit(0x00);                                                      // Initialize the LCD Module
    LCDClear();                                                         // Clear LCD Screen
    windowStartTime = bres;

    while (1){                           //  Or, while true, so, Run continuously

        output = PID_Calculate(SetPoint, InputValue);
        int now = bres;

        if(now - windowStartTime>WindowSize){       //time to shift the Relay Window
            windowStartTime += WindowSize;
        }

        if(output > now - windowStartTime){
            RC7 = 0;
        }

        else RC7 = 1;




        if(Toggle){

            CalCurrentTemp = CurrentTemp * 125 / 212 - 40;


     /*       if(sl <=3){
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
 */     //          if(sl > 3 && sl <= 10){
         //       LCDClear();
/*                LCDWriteIntXY(0,0,CalCurrentTemp,3);
                LCDWriteIntXY(5,0,CurrentTemp,3);
                LCDWriteIntXY(9,0,ADCRead(14),3);
                LCDWriteIntXY(0,1,FVREN,3);
                LCDWriteIntXY(4,1,FixedV,6);
 */             LCDWriteIntXY(0,0,output,5);
                LCDWriteIntXY(10,0,SetPoint,3);
                LCDWriteIntXY(0,1,InputValue,4);
                LCDWriteIntXY(6,1,bres,4)
                LCDWriteIntXY(11,1,Err,2);
          //      }



/*            if(sl > 2 && sl <= 4){
                LCDClear();
//                LCDGotoXY(0,0);
                LCDWriteStringXY(0,0,"   M E R R Y    ");
                LCDGotoXY(0,1);
                LCDWriteString("   X M A S !    ");
            }

            if(sl > 4 && sl <= 6){
               // LCDClear();
//                LCDGotoXY(0,0);
                LCDWriteStringXY(0,0," & a  H A P P Y ");
                LCDGotoXY(0,1);
                LCDWriteString(" N E W  Y E A R ");
            }

            if(sl > 6 && sl <= 10){
                LCDClear();
//                LCDGotoXY(0,0);
                LCDWriteStringXY(0,0,"   to ALL!!!!  ");
                LCDGotoXY(0,1);
 */  //             LCDWriteString("Especially RILEY");

            Toggle = 0;
        }




        if (TMR0IF){                     // TMR0 Interupt caused by an overflow
            bres += 256;         	 // add 256 x 256(because of the pre-scaler) ticks to bresenham total
            TMR0IF = 0;                  // Re-set TMR0 Interupt
        }


	if(bres >= 1953){                // if we reached 500000(256 x 1953.125) 1 second has passed!
            bres -= 1953;         	 // subtract 1 second, retain error (except the .125)
            ++sl;                        // update clock, etc
            ++Toggle;                    // Toggle LED marking passing of 1 Second (1 Sec on, 1 Sec off)
            Toggle2 = 1 - Toggle2;       // Toggle LED marking passing of 1 Minute (1 Min on, 1 Min off)
            CurrentTemp = ADCRead(14);
            FixedV = ADCRead(15);

        }


        if(sl>9){
            sl = 0;                         // Reset sl to zero, accounting for Time correction as well
            ++sh;
            ++InputValue;

            if(sh>5){                    // 1 Minute has passed
                sh=0;                    // Reset seconds high to zero
                ++ml;
                InputValue -=6;
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

 /*       if(Toggle2 != 1){                 // If Toggle not equal to 1 (This is from toggle above)
            RC7 = 0;                     // Turn on RC5 for 1 second,
        }
            else{
            RC7 = 1;                     // otherwise, if Sec is equal to zero, turn Off RC5 for 1 second
        }
*/    }
}

void ADCInit(){
        ADCON1 = 0x10;                   // Set ADC conversion clock FOSC/8 See Page 80
}

unsigned char ADCRead(unsigned char ch){ //Function to Read given ADC channel (0-14)

    ADCON0=0x00;                         // Set ADCON0 to all zero's
    ADCON0=(ch<<2);                      // Select ADC Channel (write the decimal value of ch, Left shifted two places, writing to Bits 5,4,3 and 2)
    ADON=1;                              // Enable the ADC module (on selected channel)
    __delay_us(200);                      // Delay 150 us to allow the ADC cap to charge
    GO_nDONE=1;                          // Start conversion
    while(GO_nDONE);                     // Wait for the conversion to finish
    ADON=0;                              // Disable the ADC
    return ADRES;                        // Return the Analog value
}

void Init() {                           // Initialization Function

    TRISA = 0b00011111;                 //  0 = output 1 = input
    ANSELA = 0b00010100;                // RA2 and RA4 as Analog (0 = Digital, 1 = Analog)
    PORTA = 0xff;                       // Set all port A register to 1, 1 = off, 0 = on, (if sinking)

    TRISB = 0b00110000;                 // 0 = output, 1 = input
    ANSELB = 0b00110000;                // RB4 and RB5 as Analog (0 = Digital, 1 = Analog)
    PORTB = 0xff;                       // Set all port B register to 1, 1 = off, 0 = on

    TRISC = 0x00;                       // 0 = output 1 = input
    ANSELC = 0x00;                      // 0 = Digital, 1 = Analog
    PORTC = 0xff;                       // Set all port C register to 1, 1 = off, 0 = on

    IRCF1 = 0;                           // These 2 parameters set Clock @ 2 MHz
    IRCF0 = 0;                           // These 2 parameters set Clock @ 2 MHz
    OSCTUNE = 0x00;                      // Change default oscilator speed (See page 68)

    TMR0 = 0;                            // TMR0 Pre-set
    T0CS = 0;                            // TMR0 Clock source 0 = internal clock (FOSC/4)
    T0SE = 0;                            // Triggering on Low to High edge
    PSA = 0;                             // Work with a PreScaler
    PS0 = 1;                             // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS1 = 1;                             // Set Pre-Scaler for TMR0 to 256 (1:256)
    PS2 = 1;                             // Set Pre-Scaler for TMR0 to 256 (1:256)

    FVRCON = 0xf3;

//    TSEN = 1;
  //  TSRNG = 1;
}
