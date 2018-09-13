

#include <xc.h>
#include "adcc.h"
#include "tempCalc.h"
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled, SWDTEN is ignored)

int button_array[4][6];   //[x][y] x = button number y = on timer,off timer, button active, valid input 
int H_alarm_point_array[4][4];//[x][y] x = button number y = alarm setpoint, alarm active, timer
void OSCILLATOR_Initialize(void)
{
    OSCCON1 = 0x60;                 // NOSC HFINTOSC; NDIV 1; 
    OSCCON3 = 0x00;                 // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCEN = 0x00;                   // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCFRQ = 0x00;                  // HFFRQ 32_MHz; 0x00 = 1MHz
    OSCTUNE = 0x00;                 // HFTUN 0; 
}

void IO_Initialize(void){
    TRISA = 0xFF;    //All PortA pins are input
    ANSELA = 0x0F;   //RA7-RA4 are Digital RA3-RA0 are Analog 0000 1111        
    PORTA = 0x00;    //Set all port A low
            
	TRISB = 0x00;	//RB7,RB6 programming RB5-RB0 are Duel Purpose Used for LEDs currently 
	ANSELB = 0x00;	//digital not analog
	PORTB = 0x00;   //Set all Port B low
    
    TRISC = 0x10;   //RC4 is SPI Data In 0001 0000
    ANSELC = 0x00;   //digital not analog
    PORTC = 0x00;    //set all Port C low    
}

void spi_init(void){
//    SSPEN = 1;  //Enables Serial Data pins
//    SSPM0 = 0;  //SSPM* sets SPI clock and mode 0010 = Master and oscillator /64
//    SSPM1 = 1;
//    SSPM2 = 0;
//    SSPM3 = 0;
//    CKE = 1;    //1
//    CKP = 0;    //0
    SSP1CON1 = 0x22;
    SSP1DATPPS = 0x14;  //PPS for RC4 to be SDI
    RC5PPS = 0x15;  //PPS for RC5 points at SDO1
    RC3PPS = 0x14;  //PPS for RC3 points at SCK
    CKE1 = 1;

    }

char (SPI_TRANSFER)(char byte_to_send){
    char byte_recieved;
    byte_recieved = SSP1BUF; // dummy read in case unread value might be in register from start up or something      
    SSP1BUF = byte_to_send;
    __delay_us(35);
//    byte_recieved = SSPBUF;
    __delay_us(5);
        while (SSP1CON1bits.WCOL == 1){     //Check for write collision
    //    SSP1CON1bits.WCOL = 0;       //Reset collision bit
            WCOL1 = 0;
        __delay_us(5);
        SSP1BUF = byte_to_send;
        __delay_us(5);
    }
    byte_recieved = SSP1BUF;
//    BF = 0; // Reset Data arrived flag. This is probably reset automatically on an SSPBUF read
    SSP1STATbits.BF = 0;
    return byte_recieved;
}

//SPI_DATA_HANDLING passes 10 Bytes and receives 10 Bytes
//*data_pointer points at an array of 21 Bytes. The first Byte is a status Byte.
//It increments from 1 to 10 signifying which byte is being sent and received
//Byte 1 to 10 are Bytes to send, Byte 11 to 20 are received bytes
void (SPI_DATA_HANDLING)(char *data_pointer){
    char byte_to_send;
    char byte_received;
    char offset;
    char address;
    char *offset_pointer;

    if (*data_pointer > 0){
        offset = *data_pointer;
        address = data_pointer + offset;
        offset_pointer = address;
        byte_to_send = *offset_pointer;
        byte_received = SPI_TRANSFER(byte_to_send);
        offset_pointer = offset_pointer + 10;
        *offset_pointer = byte_received;
        *data_pointer = *data_pointer + 1;
    }
    if  (*data_pointer > 5){   //Reset array address pointer to 1 //changed from 10 to 5
        *data_pointer = 0;
        //Add Delay here
//        _delay(10000000);
    }     
}

void (display_ADC_count_on_LEDs)(int temp){
    
if (temp > 150){
    RB0 = 1;
} 
else RB0 = 0;

if (temp > 300){
    RB1 = 1;
} 
else RB1 = 0;

if (temp > 450){
    RB2 = 1;
} 
else RB2 = 0;

if (temp > 600){
    RB3 = 1;
} 
else RB3 = 0;

if (temp > 750){
    RB4 = 1;
} 
else RB4 = 0;    
    
if (temp > 1000){
//    RB5 = 1;
} 
//else RB5 = 0;    
    
    
    
}
void display_temperature_on_LEDs(float temp){
if (temp > 200){
    RB0 = 1;
} 
else RB0 = 0;

if (temp > 220){
    RB1 = 1;
} 
else RB1 = 0;

if (temp > 240){
    RB2 = 1;
} 
else RB2 = 0;

if (temp > 260){
    RB3 = 1;
} 
else RB3 = 0;

if (temp > 280){
    RB4 = 1;
} 
else RB4 = 0;    
    
if (temp > 300){
//    RB5 = 1;
} 
//else RB5 = 0;    
    
    
    
    
}

void display_temperature_on_LEDs2(float temp){
if (temp > 230){
    RB0 = 1;
} 
else RB0 = 0;

if (temp > 240){
    RB1 = 1;
} 
else RB1 = 0;

if (temp > 250){
    RB2 = 1;
} 
else RB2 = 0;

if (temp > 260){
    RB3 = 1;
} 
else RB3 = 0;

if (temp > 270){
    RB4 = 1;
} 
else RB4 = 0;    
    
if (temp > 280){
//    RB5 = 1;
} 
//else RB5 = 0;    
    
    
    
    
}

//void average_temps(int *pointer_to_temp_array){
//    int *working_pointer;
//    working_pointer = pointer_to_temp_array;
 //   working_pointer = working_pointer + 1;    //point to second int in array
 //   *pointer_to_temp_array = *working_pointer;
//    working_pointer = working_pointer + 2;    //point to second int in array
    
//}
int average_temps(int temp_array[] ){
    
//    temp_array[0] = temp_array[1];
    int x = 0;
    int temp = 0;
    while (x < 10){
        temp_array[x] = temp_array[x+1];
        temp = temp_array[x] + temp;
        x++;
    }
    temp = temp / 10;
    return temp;
}

void format_temp_to_send (int temp){
    char byte_1 = 0;
    char dummy_char = 0;
    temp = temp / 10;
    byte_1 = (char) temp;
//   RC0 = 0; 
   __delay_us(100);
   dummy_char = (SPI_TRANSFER)(byte_1);
   __delay_us(100);
//   RC0 = 1;


}
void check_for_button_push(void){
    
    //Beginning of RA4 input Switch debounce code
    if ((RA4 == 0) && (button_array[0][3] == 0)){  //0 equals button depressed and button_array[0][3] is for off bit latch
        button_array[0][2] = 1; //[x][y] x = switch 1(RA4) y = on bit active (switch one latched or active)
    }
    if (button_array[0][2] == 1){
        button_array[0][0]++;   //[x][y] x = switch 1(RA4) y = latched on timer
        if (button_array[0][0] > 200){
            button_array[0][0] == 100; //keep timer from overflowing if button is depressed for a long time
        }
    }
    if ((button_array[0][0] > 5) && (RA4 == 1)){ //check if latched on timer has expired and button no longer depressed
        button_array[0][2] = 0; //turn off active button depression for RA4
        button_array[0][0] = 0; //reset latch on timer
        button_array[0][3] = 1; //[x][y] x = switch 1(RA4) y = off bit active (switch one not active)
        button_array[0][1] = 0; //reset off timer        
    }
    if (button_array[0][3] == 1){
        button_array[0][1]++;   //increment button off timer
    }
    if (button_array[0][1] > 5){
        button_array[0][3] = 0; //[x][y] x = switch 1(RA4) y = off bit active (switch one not active)
    }
//End of RA4 Switch debounce code

    //Beginning of RA5 input Switch debounce code
    if ((RA5 == 0) && (button_array[1][3] == 0)){  //0 equals button depressed and button_array[0][3] is for off bit latch
        button_array[1][2] = 1; //[x][y] x = switch 2(RA5) y = on bit active (switch one latched or active)
    }
    if (button_array[1][2] == 1){
        button_array[1][0]++;   //[x][y] x = switch 2(RA5) y = latched on timer
        if (button_array[1][0] > 200){
            button_array[1][0] == 100; //keep timer from overflowing if button is depressed for a long time
        }
    }
    if ((button_array[1][0] > 5) && (RA5 == 1)){ //check if latched on timer has expired and button no longer depressed
        button_array[1][2] = 0; //turn off active button depression for RA4
        button_array[1][0] = 0; //reset latch on timer
        button_array[1][3] = 1; //[x][y] x = switch 2(RA5) y = off bit active (switch one not active)
        button_array[1][1] = 0; //reset off timer        
    }
    if (button_array[1][3] == 1){
        button_array[1][1]++;   //increment button off timer
    }
    if (button_array[1][1] > 5){
        button_array[1][3] = 0; //[x][y] x = switch 2(RA5) y = off bit active (switch one not active)
    }
//End of RA5 Switch debounce code
    
    //Beginning of RA7 input Switch debounce code
    if ((RA7 == 0) && (button_array[2][3] == 0)){  //0 equals button depressed and button_array[0][3] is for off bit latch
        button_array[2][2] = 1; //[x][y] x = switch 3(RA7) y = on bit active (switch one latched or active)
    }
    if (button_array[2][2] == 1){
        button_array[2][0]++;   //[x][y] x = switch 3(RA7) y = latched on timer
        if (button_array[2][0] > 200){
            button_array[2][0] == 100; //keep timer from overflowing if button is depressed for a long time
        }
    }
    if ((button_array[2][0] > 10) && (RA7 == 1)){ //check if latched on timer has expired and button no longer depressed
        button_array[2][2] = 0; //turn off active button depression for RA7
        button_array[2][0] = 0; //reset latch on timer
        button_array[2][3] = 1; //[x][y] x = switch 3(RA7) y = off bit active (switch one not active)
        button_array[2][1] = 0; //reset off timer        
    }
    if (button_array[2][3] == 1){
        button_array[2][1]++;   //increment button off timer
    }
    if (button_array[2][1] > 10){
        button_array[2][3] = 0; //[x][y] x = switch 3(RA7) y = off bit active (switch one not active)
    }
//End of RA5 Switch debounce code


    if (button_array[2][2] == 1){
        RB4 = 1;
    }
    else RB4 = 0;
    
    
    
}    
    
    

void set_alarm_point(void){
 
    if (button_array[0][2] == 1){   //check button RA4
        RC0 = 0;
        __delay_us(100);
        format_temp_to_send(H_alarm_point_array[0][0]);
        RC0 = 1;
        __delay_us(100);
        if ((button_array[1][2] == 1) && (H_alarm_point_array[0][2] < 1)){
            H_alarm_point_array[0][0] = H_alarm_point_array[0][0] + 10; //10 is equal to 1 degree
            H_alarm_point_array[0][2] = 15;    //increase delay timer
            
        }
        if (H_alarm_point_array[0][2] > 0){
            H_alarm_point_array[0][2]--;
        }
        if ((button_array[2][2] == 1) && (H_alarm_point_array[0][3] < 1)){
            H_alarm_point_array[0][0] = H_alarm_point_array[0][0] - 10; //10 is equal to 1 degree
            H_alarm_point_array[0][3] = 15;    //increase delay timer
            
        }
        if (H_alarm_point_array[0][3] > 0){
            H_alarm_point_array[0][3]--;
        }
        
    }
}

void main(void) {

//int button_array[4][6];   //[x][y] x = button number y = on timer,off timer, button active, valid input 
long unsigned int program_cycles = 0;    
int temp0 = 257;
float temp_in_degree_C = 0;
char test_char = 0;
int final_temps[4];
int temp_array0[11];
int temp_array1[11];
int temp_array2[11];
int temp_array3[11];
H_alarm_point_array[0][0] = 500;
OSCILLATOR_Initialize();
IO_Initialize();
spi_init();
ADCC_Initialize();
RC7 = 1;    //Thermistor power    
while (1){
    program_cycles++;
    
    if (program_cycles > 250){
        RB5 = 1 - RB5;  //toggle LED
        program_cycles = 0;
    }
 //   RC7 = 1;    //Thermistor power
//    temp0 = ADCRead(3);
//     temp0 = 1023 - temp0;
//    temp_in_degree_C = tempCalc(temp0);
    if (program_cycles == 10){
        temp_array0[10] = ADCRead(0);
    }
    if (program_cycles == 20){
        temp_array0[10] = 1023 - temp_array0[10];
        if (temp_array0[10] >= 1010){           //send 127 to display if no thermistor present
            temp_array0[10] = 53;   //53 count = 127
        }
    }
    if (program_cycles == 30){
        temp_array0[10] = tempCalc(temp_array0[10]);
    }
    if (program_cycles == 40){
        final_temps[0] = average_temps(temp_array0);
    }
    if ((program_cycles == 50) && (button_array[0][2] == 0)){
        RC0 = 0;    //SS for Display 0
         __delay_us(80);
        format_temp_to_send(final_temps[0]);
        RC0 = 1;    //SS for Display 0
        __delay_us(80);
    }
    if (program_cycles == 60){
        temp_array1[10] = ADCRead(1);
    }
    if (program_cycles == 70){
        temp_array1[10] = 1023 - temp_array1[10];
        if (temp_array1[10] >= 1010){       //send 127 to display if no thermistor present
            temp_array1[10] = 53;   //53 count = 127
        }
    }
    if  (program_cycles == 80){
        temp_array1[10] = tempCalc(temp_array1[10]);
    }
    if  (program_cycles == 90){
        final_temps[1] = average_temps(temp_array1);
    }
    if (program_cycles == 100){
        RC1 = 0;    //SS for Display 1
        __delay_us(80);
        format_temp_to_send(final_temps[1]);
        RC1 = 1;    //SS for Display 1
         __delay_us(80);
    }
    if (program_cycles == 110){
        temp_array2[10] = ADCRead(2);
    }
    if (program_cycles == 120){
        temp_array2[10] = 1023 - temp_array2[10];
        if (temp_array2[10] >= 1010){   //send 127 to display if no thermistor present
            temp_array2[10] = 53;   //53 count = 127
        }
    }
    if (program_cycles == 130){
        temp_array2[10] = tempCalc(temp_array2[10]);
    }
    if (program_cycles == 140){
        final_temps[2] = average_temps(temp_array2);
    }
    if (program_cycles == 150){
        RC2 = 0;    //SS for Display 2
        __delay_us(80);
        format_temp_to_send(final_temps[2]);
        RC2 = 1;    //SS for Display 2
         __delay_us(80);
    }
    if (program_cycles == 160){
        temp_array3[10] = ADCRead(3);
    }
    if (program_cycles == 170){
        temp_array3[10] = 1023 - temp_array3[10];
        if (temp_array3[10] >= 1010){   //send 127 to display if no thermistor present
            temp_array3[10] = 53;   //53 count = 127
        }
    }
    if (program_cycles == 180){
        temp_array3[10] = tempCalc(temp_array3[10]);
    }
    if (program_cycles == 190){
        final_temps[3] = average_temps(temp_array3);
    }
    if (program_cycles == 200){
        RC6 = 0;    //SS for Display 3
         __delay_us(80);
        format_temp_to_send(final_temps[3]);
        RC6 = 1;    //SS for Display 3
         __delay_us(80);
    }




//    display_temperature_on_LEDs2(final_temps[0]);
    
    check_for_button_push();
    set_alarm_point();
    
//    display_ADC_count_on_LEDs(temp0);
//    display_temperature_on_LEDs2(temp_in_degree_C);
//    display_temperature_on_LEDs2(final_temps[0]);
//   RC0 = 0; 
//   __delay_us(100);
//   test_char = (SPI_TRANSFER)('U');
//   __delay_us(100);
//   RC0 = 1;
//   if (test_char == 'U'){
//       RB5 = 1;
//   }
//   else RB5 = 0;
//   __delay_us(10000);
//   __delay_us(10000);
//    RB0 = 0;
//    RB1 = 0;
//    RB2 = 0;
//    RB3 = 0;
//    RB4 = 0;
//    RB5 = 1;
        
   
}
}
