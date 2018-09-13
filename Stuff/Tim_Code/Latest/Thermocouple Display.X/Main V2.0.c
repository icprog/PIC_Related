//Thermocouple Display

//#include    <htc.h>
#include <xc.h>
//#include <pic16f726.h>


//__CONFIG (FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & BOREN_OFF & PLLEN_ON);
//__CONFIG(WRTEN_OFF);


#pragma config FOSC = INTOSCIO //This is the reason it would not work.
#pragma config WDTE = OFF
#pragma config PLLEN = ON

#define _XTAL_FREQ 16000000	//16mhz default after reset
#define SYS_FREQ = 1600000



void Init() {

	//di();	//disable all interrupts

	//Initialization
	TRISA = 0x00;	//not used inputs 0 = output
	ANSELA = 0x00;	//all digital not analog
	PORTA = 0xff;
        TRISA4 = 1;

	TRISB = 0x00;	//0 = output
	ANSELB = 0x00;	//digital not analog
	PORTB = 0x00;

	TRISC = 0x00;	//0 = output
        TRISC4 = 1;     //Input for SPI Data
//	ANSELC = 0x00;	digital not analog
	PORTC = 0x00;
        IRCF1 = 0;      //oscillator post scaler
        IRCF0 = 0;      //oscillator post scaler



        RC3 = 1;
         _delay(2000);

  //      INTCON = 0;
 //       T0CS = 1;
  //      T0XCS = 0;
 //       PSA = 1;
  //      PS2 = 1;
 //       PS1 = 0;
  //      PS0 = 1;
 //       ADCON1 = 0x70;     // conversion speed for ADC





}
void data_out(unsigned char i){ //Data output serial interface
    unsigned int n;
    RC2 = 0;    //Chip Select for Graphical display
    RC0 = 1;    //Command = 0 Data = 1;
    for (n=0; n<8; n++){
        RC3 = 0;        //set clock bit low
        RC5 = (i >> 7);       //load data bit
        _delay(10);
        RC3 = 1;        //set clock bit high
        _delay(10);
        i <<=1;
    }
    RC2 = 1;    // deselect Graphical display

    }




void comm_out(unsigned char j){ //Command output serial interface
    unsigned int n;    
    RC2 = 0;    //Chip Select for Graphical display
    RC0 = 0;    //Command = 0 Data = 1;
    for (n=0; n<8; n++){
        RC3 = 0;        //set clock bit low
        RC5 = (j >> 7);       //load data bit
        _delay(10);
        RC3 = 1;        //set clock bit high
        _delay(10);
        j <<=1;
    }
    RC2 = 1;    // Unselect Graphical display

    }

void test_image (void){
    unsigned int i,j;
    unsigned char page = 0xB0;
    comm_out (0xAE);    //Turn Display off
    comm_out (0x40);    //Display RAM start = 0
    for (i=0;i<4;i++){
        comm_out (page);    //set page number
        comm_out (0x10);    //Set column
        comm_out (0x00);    //Set column
        for (j=0;j<128;j++){
            data_out (0x0F);
        }
        page++;
    }
    comm_out (0xAF);
}

void test_image_page (void){
    unsigned int i,j;
    unsigned char page = 0xB2;
    comm_out (0xAE);    //Turn Display off
    comm_out (0x40);    //Display RAM start = 0
    comm_out (page);    //set page number
    comm_out (0x10);    //Set column
    comm_out (0x00);    //Set column
    for (j=0;j<128;j++){
        data_out (0x0F);
    }

    comm_out (0xAF);
}

void image_1 (void){
    unsigned int i,j;
    unsigned char page = 0xB3;
    comm_out (0xAE);    //Turn Display off
    comm_out (0x40);    //Display RAM start = 0
    comm_out (page);    //set page number
    comm_out (0x12);    //Set column
    comm_out (0x0F);    //Set column
    data_out (0x01);

    comm_out (0xAF);
}
void moving_bar (void){
    unsigned int i; //lower column bit
    unsigned int k; //upper column bit
    unsigned int j; //Ball location
    unsigned int w; //working register
    unsigned char page = 0xB3;
    j = 0;
    while(1){
        k = 0x10;
        j++;
        if (j > 15){
            w = j;
            k = 0x10;
            while (w > 15){
                k++;
                w = w - 16;
            }
            i = w;
        }
        else {
            i = j;
        }
        //comm_out (0xAE);    //Turn Display off
        comm_out (0x40);    //Display RAM start = 0
        comm_out (page);    //set page number
        comm_out (k);    //Set column 0x10=16,0x18=24
        comm_out (i);    //Set column
        data_out (0xFF);
        if (i == 0){
            w = 15;
            k--;
        }
        else {
            w = i - 1;
        }
        comm_out (k);    //Set column 0x10=16,0x18=24
        comm_out (w);    //Set column
        data_out (0x00);

        comm_out (0xAF);    //Turn Display On
       _delay(100);
       if (j > 128){j = 0;}
    }
}

void increasing_bar (void){
    unsigned int i; //lower column bit
    unsigned int k; //upper column bit
    unsigned int j; //Ball location
    unsigned int w; //working register
    unsigned char page = 0xB0;
    j = 0;
        //comm_out (0xAE);    //Turn Display off
        comm_out (0x40);    //Display RAM start = 0
        comm_out (page);    //set page number
        comm_out (0x10);    //Set column 0x10=16,0x18=24
        comm_out (0x00);    //Set column
        comm_out (0xAF);    //Turn Display On
        for (j=0;j<128;j++){
        data_out (0xFF);
       _delay(10000);
        }


        comm_out (0xAF);    //Turn Display On
       _delay(100);
 }

void eating_bar (void){
    unsigned int i; //lower column bit
    unsigned int k; //upper column bit
    unsigned int j; //Ball location
    unsigned int w; //working register
    unsigned char page = 0xB0;
    j = 0;
        //comm_out (0xAE);    //Turn Display off
        comm_out (0x40);    //Display RAM start = 0
        comm_out (page);    //set page number
        comm_out (0x10);    //Set column 0x10=16,0x18=24
        comm_out (0x00);    //Set column
        for (j=0;j<128;j++){
        data_out (0x00);
       _delay(10000);
        }


        comm_out (0xAF);    //Turn Display On
       _delay(100);
 }
void pattern_bar (void){
    unsigned int i; //lower column bit
    unsigned int k; //upper column bit
    unsigned int j; //Ball location
    unsigned int w; //working register
    unsigned char page = 0xB1;
    j = 0;
        //comm_out (0xAE);    //Turn Display off
        comm_out (0x40);    //Display RAM start = 0
        comm_out (page);    //set page number
        comm_out (0x10);    //Set column 0x10=16,0x18=24
        comm_out (0x00);    //Set column
        for (j=0;j<128;j++){
        data_out (0x00);
        data_out (0x00);
        data_out (0x00);
        data_out (0x00);
        data_out (0xFF);
       _delay(10000);
        }


        comm_out (0xAF);    //Turn Display On
       _delay(100);
 }

void blank_image (void){
    unsigned int i,j;
    unsigned char page = 0xB0;
    comm_out (0xAE);    //Turn Display off
    comm_out (0x40);    //Display RAM start = 0
    for (i=0;i<4;i++){
        comm_out (page);    //set page number
        comm_out (0x10);    //Set column
        comm_out (0x00);    //Set column
        for (j=0;j<128;j++){
            data_out (0x00);
        }
        page++;
    }
    comm_out (0xAF);
}

void dot (int position[2]){
    unsigned int i,k,j;
    unsigned int q;
    char lownib,upnib;
    unsigned char page = 0xB0;  
//    comm_out (0xAE);    //Turn Display off
    comm_out (0x40);    //Display RAM start = 0
    upnib = 0x10;
    lownib = 0x00;
    for (i=0;i<128;i++){    //Search for horizontal value
        if (position[0] == i){
            k = i;          //maintain value of i
            while (k > 15){
                k = k - 16; //reduce k until it is under 16
                upnib++;    //increment the upper nibble for every 16
            }
            lownib = k;     //assign remainder for horizontal
        }
    }
    j = 0;
    q = 0x0001;
    while (position[1] != j){
        q = q << 1;
        j++;
        if (q == 0x100){
            page++;
            q = 0x01;
        }
    }
    comm_out (upnib);
    comm_out (lownib);
    comm_out (page);
    data_out (q);    //test write
    comm_out (0xAF);    //Turn Display On

}

main(void) {
    Init();
    int position[2];
    position[0] = 100;  //0 to 127
    position[1] = 15;   //0 to 31
    char display_matrix[10];

    RC1 = 0;    //Reset Graphical display
     _delay(100000);
    RC1 = 1;    //Reset Graphical display
    _delay(100000);

    comm_out (0xE3);    // NOP
    comm_out (0xA0);
    comm_out (0xAE);
    comm_out (0xC0);
    comm_out (0xA2);
    comm_out (0x2F);    //Turns on Power Booster
    comm_out (0x21);    //Voltage regulator resister ratio set *This was set too high
    comm_out (0x81);
    comm_out (0x2F);
    comm_out (0xA6);
 

    _delay(100000);
    _delay(100000);

    while(1){
       RB5 = 1;         //Turn on LED
       RC7 = 1;         //Turn on Backlight
       _delay(100000);
       RB5 = 0;         //Turn off LED
       _delay(100000);
//       test_image();
//       test_image_page();
       blank_image();
//       image_1();
//       increasing_bar();
//       moving_bar();
//       eating_bar();
//       moving_bar();
       dot (position);
       while (1){
//       increasing_bar();
//       eating_bar();
//       pattern_bar();

       RB5 = 1;     //Turn on LED
       _delay(100000);
       RB5 = 0;         //Turn off LED
       _delay(100000);
       }

    }

}

