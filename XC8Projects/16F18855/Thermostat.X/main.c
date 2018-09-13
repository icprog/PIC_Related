/************************************
*       Electronic Thermostat       *
*            11 Jan 2017            *
*                                   *
************************************/
/*
Name: electronic thermostat ver 1
Description:
This project is a simple electronic thermostat. Displays the temperature as two 
digits on 7 segment LED display.  Temperature setpoint is entered by rotary encoder.  
There are two modes.
1) Setpoint: Rotate knob to display the desired temperature and press the knob to
enter the temperature set point. DP1 lights when relay is closed.
2) Bypass: Rotate knob to select a temporary setting (don't press the knob). 
After 4 seconds, the temporary setpoint is active for 1 hour. DP2 blinks 
while in the bypass mode. Cancel the bypass mode by rotating the knob to enter 
a new setpoint and press the knob to enter.
Depressing the rotary knob will momentarily display the current setpoint.

Processor: PIC16F18855, control algorithm is a simple on/off with a 2 degree Hysteresis. 
Sensor: MCP9700A, 10mV/C

Requires:
Hardware configuration: PIC16F18855
MCU configuration
Pin: function: connection
1: Vpp/MCLR/RE3: ICSP 1
2: RA0: D2
3: RA1: DP
4: RA2: G_seg
5: RA3: F_seg
6: RA4: E_seg
7: RA5: D_seg
8: Vss: ground
9: RA7: C_seg
10: RA6: B_seg
11: RC0: A_seg
12: RC1: D1
13: RC2: SW1_A
14: RC3: SW1_D

15: RC4: SW1_B
16: RC5: RELAY
17: RC6: LED_blue
18: RC7: NC
19: Vss: ground
20: Vdd: +5VDC
21: RB0: this pin always seems to be low when configured as an input
22: RB1: NC
23: RB2: NC
24: RB3: NC 
25: RB4: NC
26: RB5: MCP9700A
27: RB6: ICSPCLK: ICSP 5
28: RB7: ICSPDAT: ICSP 4 

The set point is stored in eeprom at address 0x00

Author: Tony Cirineo
Date: 12/18/2016 coding started
Revision History
Original version: 

*/

#include "mcc.h"
#include <math.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned int word;

//function definitions
void read_MCP9700A(void);
byte decToBcd(byte val);
void display(byte val);
void display_digit(char count);
void read_encoder(void);
void delay_us(void);
byte debounce_sw(byte port);

//defines
#define LOW 0
#define HIGH 1
#define TRUE 1
#define FALSE 0

// variables
float avg, ns, spv;     //avg=average, ns=new sample, spv=scratch pad variable
byte encoder_Pin_A_Last, n;
byte encoder_pos, encoder_pos_old;
word millis, seconds; 
byte setpoint, temp;  // 0 to 99 degrees F in binary
byte LED_blue_flg, bypass_flg, relay_on_flg, done_reading_ADDC_flg, num;
byte dsply_sp_flg, getting_new_sp_flg, getting_new_sp_tmr, dsply_sp_tmr, bypass_tmr;
byte heater_min_on_tmr, heater_max_on_tmr, heater_rest_tmr;
/************************************
*              main                 *
************************************/
/*
Name: main
Synopsis: this function has the initialization code and 
code to be run only once at power up.
Requires: na
Description: This is function initializes hardware and variables
Author: Tony Cirineo
Date:  12/6/2016
Revision History:
*/
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    ADCC_Initialize();
    //initialize the averaging of temperature readings
    delay_us();
    avg = (float) ADCC_GetSingleConversion(MCP9700A);    // get 1st sample and set as the average 
    // 0.2C per count, convert to F
    avg /= 10.0;
    avg *= 9.0;
    avg /=5.0;
    avg -= 58.0;

    //no need to process temperatures beyond normal range
    spv = avg;
    if(spv < 0.0)
        spv = 0.0;  // limit low temp to 0F, -17.7C
    if(spv > 200.0)
        spv = 200.0;	//limit high temp to 200F, 93.3C
    if(spv > 99.0)
        spv -= 100.0;  // past 100F only display ones and tens digits.
    temp = (byte) round(spv);     

    // read set point from eeprom
    setpoint = eeprom_read(0x00);

    // initialize flags and timers on reset
    encoder_Pin_A_Last = HIGH;
    n = LOW;
    encoder_pos = encoder_pos_old = 50;
    millis = seconds = 0; 
    LED_blue_flg = bypass_flg = relay_on_flg = done_reading_ADDC_flg = FALSE;
    dsply_sp_flg = getting_new_sp_flg = getting_new_sp_tmr = FALSE;
    dsply_sp_tmr = bypass_tmr = 0;
    heater_min_on_tmr = heater_max_on_tmr = heater_rest_tmr = 0;

    while(1){
    
        // check for user inputs, read encoder
        read_encoder();
        if((encoder_pos != encoder_pos_old) && !dsply_sp_flg) // is new position different than the old position? Then consider this a new input.
            getting_new_sp_flg = TRUE;	//in the process of inputting new setpoint, timer is allowed to run

        if(getting_new_sp_flg && (encoder_pos != encoder_pos_old)){
            getting_new_sp_tmr = 0;     // keep the timer reset as long as there is activity
            encoder_pos_old = encoder_pos;
        }
        
        // check for push on encoder switch while getting a new input, this locks in new setpoint
        if(getting_new_sp_flg && !debounce_sw(SW1_D_PORT)){
            // save new setpoint and display setpoint for 3 seconds, no new inputs for 3 seconds
            setpoint = encoder_pos;    // save new setpoint
            getting_new_sp_flg = FALSE; // no longer getting new set point
            bypass_flg = FALSE;     // by pass mode is cancelled
            eeprom_write(0x00, setpoint);  // save setpoint to eeprom
            encoder_pos_old = encoder_pos;  //remember the encoder position
            dsply_sp_flg = TRUE;    // display new set point for 3 seconds before switching back to temperature
            dsply_sp_tmr = 0;    //reset display timer
        }  

        // display setpoint when encoder switch is depressed
        if(!getting_new_sp_flg && !debounce_sw(SW1_D_PORT)){
            // display setpoint for 3 seconds, no new inputs for 3 seconds
            dsply_sp_flg = TRUE;    // display new set point for 3 seconds before switching back to temperature
            dsply_sp_tmr = 0;    //reset 3 second timer
            encoder_pos = encoder_pos_old;  //don't allow new inputs
        }
        
        // cancel setpoint display after 3 seconds
        if(dsply_sp_flg && dsply_sp_tmr > 3){
            dsply_sp_flg = FALSE;    // cancel setpoint mode
            dsply_sp_tmr = 0;    //reset 3 second timer
        }
        
        // if encoder switch is not pushed after setting new value, enter bypass mode 5 = 5:35
        if((getting_new_sp_tmr > 5) && getting_new_sp_flg){ 
            if(encoder_pos != setpoint){ // if setting = setpoint, don't go into by pass mode
                bypass_flg = TRUE;
                setpoint = encoder_pos;     //capture the bypass setpoint
                encoder_pos_old = encoder_pos;
                bypass_tmr = 0;     //reset the by pass timer, expires in 1 hour
            }
            getting_new_sp_flg = FALSE; //new input time has expired
            getting_new_sp_tmr = 0; 
        }

        // check on status of bypass 
        if(bypass_flg && (bypass_tmr > 5)){   //set for 5 min for testing
            bypass_flg = FALSE;     // cancel bypass
            setpoint = eeprom_read(0x00);   // restore setpoint from eeprom
            encoder_pos_old = encoder_pos = setpoint;
            bypass_tmr = 0;     //reset the by pass timer       
        }
        
        // check millis and update seconds & minutes
        if(millis > 999){
            seconds++;
            millis = 0;
            LED_blue_SetLow();  // turn on blue LED
            LED_blue_flg = 1;             
            // increment timers
            if(getting_new_sp_flg)
                getting_new_sp_tmr++;                
            if(dsply_sp_flg)
                dsply_sp_tmr++;

            if(seconds > 59){
                seconds = 0;
                // update minute timers
                if(bypass_flg)
                    bypass_tmr++;
            }
            // read temperature every second
            ADCC_StartConversion(MCP9700A);
            done_reading_ADDC_flg = 0;
        }
      
        // check temperature, include 1 degree of hysteresis 
        if(!getting_new_sp_flg && !dsply_sp_flg){
            if(temp < (setpoint - 1))
                relay_on_flg = 1;
            if (temp > (setpoint + 1))
                relay_on_flg = 0;
        }
        
        // control LED_blue, if on, turn off after 50 ms
        if((millis > 50) && LED_blue_flg){
            LED_blue_SetHigh();
            LED_blue_flg = 0; 
        }        

        // monitor ADC, read value when conversion is done
        // add averaging to this code <-----
        if(ADCC_IsConversionDone() && !done_reading_ADDC_flg){
            read_MCP9700A();    //need to profile this
            done_reading_ADDC_flg = 1;
        }
    
         // control heater relay
        if(relay_on_flg)
            RELAY_SetHigh(); // energize relay
        else
            RELAY_SetLow();  // deactivate relay

        // update the two digit display
        if(getting_new_sp_flg)
            num = decToBcd(encoder_pos);  // display encoder value
        else if(dsply_sp_flg)
            num = decToBcd(setpoint);  // display setpoint
        else
            num = decToBcd(temp);        // display temperature
        if((millis & 0x000f) < 8){  // switch between ones and tens every 8ms
            // display ones digit
            D1_SetLow();
            display_digit(num & 0x0f); 
            D2_SetHigh();
            if(relay_on_flg)    //DP1 is on if relay is on
                DP_SetHigh();
            else
                DP_SetLow();
        }
        else{
            // display tens digit
            D2_SetLow();
            if(bypass_flg && (millis < 500))
                DP_SetHigh();    // blink DP in bypass mode
            else
                DP_SetLow();
            display_digit(num >> 4);            
            D1_SetHigh();
        }
        
        //limit minute timers
    }
}

/************************************
*         read_MCP9700A             *
************************************/
/*
Name: read_MCP9700A
Synopsis: Uses ADC to read the output pin on the MCP9700A.
Requires: MCP9700A
Description: Reads the MCP9700A and converts the analoge voltage
to degrees F.  The value returned is a 8 bits, 0 to 99F.
The MCP9700A can accurately measure temperature from -40C to +150C.
The MCP9700A is a linear active thermistor IC whose output voltage is 
directly proportional to measured temperature. The output of 
the MCP9700A is calibrated to a slope of 10mV/°C and has a DC offset 
of 500mV. The offset allows reading negative temperatures without 
the need for a negative supply. The MCP9700A is packaged in space 
saving 5-pin SC-70, and 3 lead TO-92 packages
Temperature accuracy 
0°C to +70°C: -2.0 minimum,  ±1 typical +2.0 maximum
-40°C to +125°C: -2.0 minimum, ±1 typical, +4.0 maximum
(125C = 257F, -40C = -40F)
Storage Temperature: -65°C to +150°C
Ambient Temp. with Power Applied: -40°C to +150°C
Manufacturer: Microchip Technology
Part Number: MCP9700A-E/TO
Author: Tony Cirineo
Date:  12/6/2016
Revision History:
*/
void read_MCP9700A(void)
{
    ns = (float) ADCC_GetConversionResult();    
    // 0.2C per count, convert to F
    ns /= 10.0;
    ns *= 9.0;
    ns /= 5.0;
    ns -= 58.0;

    avg = avg - (avg - ns)/4.0;   // average over 4 samples

    //no need to process temperatures beyond normal range
    spv = avg;
    if(spv < 0.0)
        spv = 0.0;  // limit low temp to 0F, -17.7C
    if(spv > 200.0)
        spv = 200.0;	//limit high temp to 200F, 93.3C
    if(spv > 99.0)
        spv -= 100.0;  // past 100F only display ones and tens digits.

    temp = (byte) round(spv); 
}

/************************************
*      Read encoder                 *
************************************/
/*
Name: reads the rotary encoder
Synopsis: 
Requires:
Description:
Author: copied from internet with modification by Tony Cirineo
Date:  8/5/03
Revision History:
*/
void read_encoder(void)
{
    n = debounce_sw(SW1_A_PORT);
    if((encoder_Pin_A_Last == LOW) && (n == HIGH)){
        if(debounce_sw(SW1_B_PORT) == LOW)
            encoder_pos++;
        else
            encoder_pos--;
    } 
    encoder_Pin_A_Last = n;
    //limit encoder_Pos range to between 10 and 99
    if(encoder_pos > 200)
        encoder_pos = 0;   
    if(encoder_pos > 99)
        encoder_pos = 99;

}

/************************************
*           debounce_sw             *
************************************/
/*
Name: debounce_sw
Synopsis: debounce switch input
Requires: na
Description: Delay used to allow data lines
to stabilize from the key fill device.
Author: Tony Cirineo
Date:  
Revision History:

*/
byte debounce_sw(byte port)
{
byte sp1, sp2;
    do{
        sp1 = port;
        delay_us();
        sp2 = port;
    } while(sp1 != sp2);
    return(sp1);
}

/************************************
*           delay_us                *
************************************/
/*
Name: delay_us
Synopsis: various fixed delays
Requires: na
Description: Delay used to allow data lines
to stabilize from the key fill device.
Author: Tony Cirineo
Date:  
Revision History:

*/
void delay_us(void)
{
word i;
	for(i = 0;i < 100;i++);	// loop for a small delay
}

/************************************
*      Dec & BCD Conversions        *
************************************/
/*
Name: 
Synopsis: 
Requires:
Description: 
Author: Tony Cirineo
Date:  8/5/03
Revision History:
*/
byte decToBcd(byte val){
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}
#if 0
byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}
#endif

/************************************
*            display_digit          *
************************************/
/*
Name: display_digit
Synopsis: controls the segements to display a number
Requires: na
Description:

Author: Tony Cirineo
Date:  5/16/2017
Revision History:
*/
void display_digit(char count)
{
    switch(count){
        case 0://when count value is zero show”0” on disp
            A_seg_SetHigh();
            B_seg_SetHigh();
            C_seg_SetHigh();
            D_seg_SetHigh();
            E_seg_SetHigh();
            F_seg_SetHigh();
            G_seg_SetLow();
            break;
        case 1:// when count value is 1 show”1” on disp
            A_seg_SetLow();
            B_seg_SetHigh();
            C_seg_SetHigh();
            D_seg_SetLow();
            E_seg_SetLow();
            F_seg_SetLow();
            G_seg_SetLow();
            break;
        case 2:// when count value is 2 show”2” on disp
            A_seg_SetHigh();
            B_seg_SetHigh();
            C_seg_SetLow();
            D_seg_SetHigh();
            E_seg_SetHigh();
            F_seg_SetLow();
            G_seg_SetHigh();
            break;
        case 3:// when count value is 3 show”3” on disp
            A_seg_SetHigh();
            B_seg_SetHigh();
            C_seg_SetHigh();
            D_seg_SetHigh();
            E_seg_SetLow();
            F_seg_SetLow();
            G_seg_SetHigh();
            break;
        case 4:// when count value is 4 show”4” on disp
            A_seg_SetLow();
            B_seg_SetHigh();
            C_seg_SetHigh();
            D_seg_SetLow();
            E_seg_SetLow();
            F_seg_SetHigh();
            G_seg_SetHigh();
            break;
        case 5:// when count value is 5 show”5” on disp
            A_seg_SetHigh();
            B_seg_SetLow();
            C_seg_SetHigh();
            D_seg_SetHigh();
            E_seg_SetLow();
            F_seg_SetHigh();
            G_seg_SetHigh();
            break;
        case 6:// when count value is 6 show”6” on disp
            A_seg_SetHigh();
            B_seg_SetLow();
            C_seg_SetHigh();
            D_seg_SetHigh();
            E_seg_SetHigh();
            F_seg_SetHigh();
            G_seg_SetHigh();
            break;
        case 7:// when count value is 7 show”7” on disp
            A_seg_SetHigh();
            B_seg_SetHigh();
            C_seg_SetHigh();
            D_seg_SetLow();
            E_seg_SetLow();
            F_seg_SetLow();
            G_seg_SetLow();
            break;
        case 8:// when count value is 8 show”8” on disp
            A_seg_SetHigh();
            B_seg_SetHigh();
            C_seg_SetHigh();
            D_seg_SetHigh();
            E_seg_SetHigh();
            F_seg_SetHigh();
            G_seg_SetHigh();
            break;
        case 9:// when count value is 9 show”9” on disp
            A_seg_SetHigh();
            B_seg_SetHigh();
            C_seg_SetHigh();
            D_seg_SetHigh();
            E_seg_SetLow();
            F_seg_SetHigh();
            G_seg_SetHigh();
            break;
    }  
} 

/**
 End of File
*/