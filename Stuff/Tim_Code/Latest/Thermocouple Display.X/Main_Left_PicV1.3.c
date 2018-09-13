//Thermocouple Display
//Main_left_picV1.2.c received 10 bytes from main processor, Main_left_picV1.3.c receives 5 
//#include    <htc.h>
#include <xc.h>
#include <pic16f726.h>


//__CONFIG (FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & BOREN_OFF & PLLEN_ON);
//__CONFIG(WRTEN_OFF);


#pragma config FOSC = INTOSCIO //This is the reason it would not work.
#pragma config WDTE = OFF
#pragma config PLLEN = ON//500K or 16M

#define _XTAL_FREQ 16000000	//16mhz default after reset




int temp_array[25];
long int cycles = 0;
int a = 0;
long int spi_timer = 0;

void Init() {

	//di();	//disable all interrupts

	//Initialization
	TRISA = 0x00;	//not used inputs 0 = output
	ANSELA = 0x00;	//all digital not analog
	PORTA = 0xff;
    TRISA5 = 1;     //Slave Select for SPI

	TRISB = 0x00;	//0 = output
	ANSELB = 0x00;	//digital not analog
	PORTB = 0x00;

	TRISC = 0x00;	//0 = output
    TRISC4 = 1;     //Input for SPI Data
    TRISC3 = 1;     //Input for SPI Clock
//	ANSELC = 0x00;	digital not analog
	PORTC = 0x00;
    IRCF1 = 0;      //oscillator post scaler
    IRCF0 = 0;      //oscillator post scaler

   
    




  //      INTCON = 0;
 //       T0CS = 1;
  //      T0XCS = 0;
 //       PSA = 1;
  //      PS2 = 1;
 //       PS1 = 0;
  //      PS0 = 1;
 //       ADCON1 = 0x70;     // conversion speed for ADC




}

void spi_init(void){
    SSPEN = 1;  //Enables Serial Data pins
    SSPM0 = 0;  //SSPM* sets SPI clock and mode 0100 = Slave and SS enabled
    SSPM1 = 0;
    SSPM2 = 1;
    SSPM3 = 0;
    CKE = 1;    //1
    CKP = 0;    //0
 //   SSPM = 0x2;
    SMP = 0;    //must be cleared for Slave mode
    SSSEL = 0;


    }

void display_test(void){
    RA0 = 1; //thousands digit
    RA6 = 0; //top bar
    __delay_us(3000);
    RA6 = 1; //top bar   
    RA7 = 0; //top right bar
    __delay_us(3000);
    RA7 = 1; //top right bar
    RC0 = 0; //bottom right bar
    __delay_us(3000);
    RC0 = 1; //bottom right bar
    RB1 = 0; //bottom bar
    __delay_us(3000);
    RB1 = 1; //bottom bar
    RB2 = 0; //bottom left bar
    __delay_us(3000);
    RB2 = 1; //bottom left bar
    RB3 = 0; //top left bar
    __delay_us(3000);
    RB3 = 1; //top left bar
 //   RB4 = 0; //middle bar
 //   __delay_us(1000);
    RB4 = 1; //middle bar
 //   RB5 = 0; //bottom decimals
 //   __delay_us(1000);
    RB5 = 1; //bottom decimals
    
    
    
}
char (SPI_TRANSFER)(char byte_to_send){
    char byte_recieved;
    byte_recieved = SSPBUF;      
    SSPBUF = byte_to_send;
    __delay_us(5);
        while (WCOL == 1){     //Check for write collision
        WCOL = 0;       //Reset collision bit
        __delay_us(5);
        SSPBUF = byte_to_send;
        __delay_us(5);
    }
    BF = 0; // Reset Data arrived flag. This is probably reset automatically on an SSPBUF read
    return byte_recieved;
}

//SPI_DATA_HANDLING passes 10 Bytes and receives 10 Bytes
//*data_pointer points at an array of 21 Bytes. The first Byte is a status Byte.
//It increments from 1 to 10 signifying which byte is being sent and received
//Byte 1 to 10 are Bytes to send, Byte 11 to are received bytes/
void (SPI_DATA_HANDLING)(char *data_pointer){
    char byte_to_send;
    char byte_received;
    char offset;
    char address;
    char *offset_pointer;
    if (*data_pointer > 1){
        spi_timer++;
    }
//      if (spi_timer > 20000){    //adjust this timer to clear missed info
//            spi_timer = 0;
//            *data_pointer = 1;
//            if (RA3 == 1){  //diagnostic
//                RA3 = 0;    //diagnostic
//              }             //diagnostic
//            else RA3 = 1;   //diagnostic

    
    if  (*data_pointer > 5){   //Reset array address pointer to 1. Changed from 10 to 5
        *data_pointer = 1;
  //      spi_timer = 0;
    } 

    if (BF == 1){
        if (RA0 == 1){  //diagnostic
            RA0 = 0;    //diagnostic
          }             //diagnostic
        else RA0 = 1;   //diagnostic
        spi_timer = 0;
        offset = *data_pointer;
        address = data_pointer + offset;
        offset_pointer = address;
        byte_to_send = *offset_pointer;
        byte_received = SPI_TRANSFER(byte_to_send);
        offset_pointer = offset_pointer + 10;
        *offset_pointer = byte_received;
        *data_pointer = *data_pointer + 1;
        if ((byte_received == 0xaa) && (*data_pointer <= 5)){//look for last byte in sequence. Changed from 10 to 5
            *data_pointer = 1; //reset data_pointer so as to disregard data.
            if (RA3 == 1){  //diagnostic
                RA3 = 0;    //diagnostic
              }             //diagnostic
            else RA3 = 1;   //diagnostic

        }
    }
}

void (LOOK_FOR_TEMP_DATA)(char *data_pointer){
    char *working_pointer;
    int x = 1;
    int temp = 0;
    if  (*data_pointer > 5){   //check to see if all 10 Bytes have been received. changed from 10 to 5
        if (RA1 == 1){  //diagnostic
            RA1 = 0;    //diagnostic
          }             //diagnostic
        else RA1 = 1;   //diagnostic

        working_pointer = data_pointer;
        working_pointer = working_pointer + 11;
        if (*working_pointer == 0x81){ // look for command 1000 0001 which is equal to write temp 
            working_pointer++;  //increment to register that holds temp sensor number
//////////////////////////////////////////////////
           if (RA4 == 1){  //diagnostic
                RA4 = 0;    //diagnostic
             }             //diagnostic
           else RA4 = 1;   //diagnostic
//////////////////////////////////////////////////
//            __delay_us(500000);
            while (*working_pointer != x){  // search for sensor number
                x++;
            }
            //Interpret temperature
            //0000 0000 0000 00 = 0
            //1111 1111 1111 11 = -0.25
            working_pointer++;   //increment to first Byte of temp data
//////////////////////////////////////////////////
/*            if(*working_pointer == 0x13){
                if (RA4 == 1){  //diagnostic
                    RA4 = 0;    //diagnostic
                }             //diagnostic
                else RA4 = 1;   //diagnostic
            }*/
//////////////////////////////////////////////////
//            working_pointer++;   //increment to first Byte of temp data

            temp = temp | *working_pointer;
            temp = temp << 8;
            working_pointer++;
//////////////////////////////////////////////////
 /*           if(*working_pointer == 0x48){
                if (RA4 == 1){  //diagnostic
                    RA4 = 0;    //diagnostic
                }             //diagnostic
                else RA4 = 1;   //diagnostic
            }*/
//////////////////////////////////////////////////

            temp = temp | *working_pointer;
            working_pointer = data_pointer;
            working_pointer = working_pointer + x;
            temp_array[x] = temp;

//////////////////////////////////////////////////
/*            if(temp_array[x] == 0x1348){
                if (RA4 == 1){  //diagnostic
                    RA4 = 0;    //diagnostic
                }             //diagnostic
                else RA4 = 1;   //diagnostic
            }*/
//////////////////////////////////////////////////


        }
        
    } 
    
}

void (DISPLAY_TEMP)(int sensor_number){
            //Interpret temperature
            //0000 0000 0000 00 = 0
            //1111 1111 1111 11 = -0.25
    //    int test_int = 0x
    ;  //0x1348 is equal to 1234 Degrees
    int temp;
    int working_register;
    int array[4][2];
    array[0][0] = 1000;
    array[1][0] = 100;
    array[2][0] = 10;
    array[3][0] = 1;
    array[0][1] = 0;
    array[1][1] = 0;
    array[2][1] = 0;
    array[3][1] = 0;
   
    int x = 0;  
    char y = 1;
    char z = 0;
    char q = 0;
    char u = 0;
    char t = 0;
    char seven_seg = 0;
    int thousands_digit = 0;
    //sensor_number = 1;
//    if (temp_array[sensor_number] > 0x1FFF){         //Look for sign bit
    working_register = (temp_array[sensor_number]) & 0x2000;    //look for sign bit
    if ((working_register == 0x2000)){
        temp = temp_array[sensor_number] & 0x1FFF;   //AND out sign bit

        temp = ~ temp;      //invert so we can multiply
        temp =  temp & 0x0FFF;
        temp = temp * .25;   //should equal 123400 using 0x1348
//        temp = temp + .25;
//    temp = temp_array[1] * .25;   //should equal 123400 using 0x1348
        while (x < 4){
           while (temp >= array[x][0]){    //array[x][0] is equal to 1000, 100, 10, 1
              temp = temp - array[x][0];
              array[x][1]++;
           }
          x++;    //cycle though all digits
       }
        array[0][1] = 10;
    }



    else{
        temp = (temp_array[sensor_number]) * .25;   //should equal 123400 using 0x1348
//    temp = temp_array[1] * .25;   //should equal 123400 using 0x1348
        while (x < 4){
           while (temp >= array[x][0]){    //array[x][0] is equal to 1000, 100, 10, 1
              temp = temp - array[x][0];
              array[x][1]++;
           }
          x++;    //cycle though all digits
       }
    }
    //////////////////////////////////////////////////
/*      if (temp_array[1][1] ==
                if (RA4 == 1){  //diagnostic
                    RA4 = 0;    //diagnostic
                }             //diagnostic
                else RA4 = 1;   //diagnostic
*/
//////////////////////////////////////////////////





    x = 0;  //reset x to use again for different loop

    // RB5 RB4 RB3 RB2 RB1 RC0 RA7 RA6
    while(x < 4){
        if (array[x][1] == 0){
            seven_seg = 0xC0;
         }
        if (array[x][1] == 1){
            seven_seg = 0xF9;
        }
        if (array[x][1] == 2){
            seven_seg = 0xA4;
        }
        if (array[x][1] == 3){
            seven_seg = 0xB0;
        }
        if (array[x][1] == 4){
            seven_seg = 0x99;
        }
        if (array[x][1] == 5){
            seven_seg = 0x92;
        }
        if (array[x][1] == 6){
            seven_seg = 0x82;
        }
        if (array[x][1] == 7){
            seven_seg = 0xF8;
        }
        if (array[x][1] == 8){
            seven_seg = 0x80;
        }
        if (array[x][1] == 9){
            seven_seg = 0xA0;
        }
        if (array[x][1] == 10){
            seven_seg = 0xBF;
        }
        
        u = seven_seg >> 2;
        q = PORTB;
        q = q & 0xC1;   //mask out RB6 and RB7 and RB0
        q = q | u;
//        PORTB = q;
        
        u = seven_seg >> 2;
        t = PORTC;
        t = t & 0xFE;
        t = t | u;
//        PORTC = t;
        
        u = seven_seg << 6;       
        z = PORTA;
        z = z & 0x20;
        z = z | y;
        z = z | u;
        PORTA = z;
        PORTB = q;
        PORTC = t;
        
        y = y << 1;     //shift to next digit
        if (x == 1){    //skip a bit to match with port Skip RA2
            y = y << 1;
        }
        x++;
    }
    __delay_us(100);
    RA4 = 0;    //Turn off Digit so it is not brighter than the rest.
    
}
    
    
int (CYCLE_TEMPS)(int temp){
  //  int temp;
    cycles++;
    if (cycles > 200){  //Increases or decreases cycle speed
//////////////////////////////////////////////////
/*
                if (RA4 == 1){  //diagnostic
                    RA4 = 0;    //diagnostic
                }             //diagnostic
                else RA4 = 1;   //diagnostic
*/
//////////////////////////////////////////////////
        cycles = 0;
        a++;
        if (a >= 4){        //adjust for amount of temps to cycle through n+1. Changed from 7 to 4
            a = 1;
        }
        temp = a;

//////////////////////////////////////////////////
/*        if (temp == 1){
                if (RA4 == 1){  //diagnostic
                    RA4 = 0;    //diagnostic
                }             //diagnostic
                else RA4 = 1;   //diagnostic
        }*/
//////////////////////////////////////////////////


        
    }
//   temp = 2;
   return temp; 
}
main(void) {
    Init();
    spi_init();
    char spi_data[22];//byte 0 is status byte 1-10 are for output, 11-20 are for input
    spi_data[0] = 1;
    spi_data[1] = 0x10;
    spi_data[21] = 0x25;
    char *data_pointer;
    data_pointer = &spi_data[0];
    int temp_number;
    ///////////////////////////
    temp_array[0] = 10; //2.5 C
    temp_array[1] = 20; //5 C
    temp_array[2] = 50; //12.5 C
    temp_array[3] = 100;   //25 C
    temp_array[4] = 200;    //50 C
    temp_array[5] = 1000;  //250 C
    temp_array[6] = 0xFFFb;

 ///////////////////////////
    while(1){
       _delay(10);
       RA0 = 1; //thousands digit
       RA1 = 1; //hundreds digit
       RA3 = 1; //tens digit
       RA4 = 1; //ones digit
       RA2 = 0; //colon
       RA6 = 0; //top bar
       RA7 = 0; //top right bar
       RC0 = 0; //bottom right bar
       RB1 = 0; //bottom bar
       RB2 = 0; //bottom left bar
       RB3 = 0; //top left bar
       RB4 = 0; //middle bar
       RB5 = 0; //bottom decimals
       
       while(1){
    //   display_test();
       SPI_DATA_HANDLING(data_pointer);
       LOOK_FOR_TEMP_DATA(data_pointer);
       temp_number = (CYCLE_TEMPS)(temp_number);
//////////////////////////////////////////////////
/*
        if (temp_number == 2){
                if (RA4 == 1){  //diagnostic
                    RA4 = 0;    //diagnostic
                }             //diagnostic
                else RA4 = 1;   //diagnostic
        }*/
//////////////////////////////////////////////////

       DISPLAY_TEMP(temp_number);
       
               
       }
    }

}

