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
        IRCF1 = 0;      //oscillator postscaler
        IRCF0 = 0;      //oscillator postscaler



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
        RC5 = i;        //load data bit
        _delay(2000);
        RC3 = 1;        //set clock bit high
        _delay(2000);
        i <<=1;
    }
    RC2 = 1;    // Unselect Graphical display

    }




void comm_out(unsigned char j){ //Command output serial interface
    unsigned int n;    
    RC2 = 0;    //Chip Select for Graphical display
    RC0 = 0;    //Command = 0 Data = 1;
    for (n=0; n<8; n++){
        RC3 = 0;        //set clock bit low
        RC5 = j;        //load data bit
       // _delay(2000);
        RC3 = 1;        //set clock bit high
       // _delay(2000);
        j <<=1;
    }
    RC2 = 1;    // Unselect Graphical display

    }





main(void) {
    Init();
    int x;
    int result;
    RB5 = 0;

    RC1 = 0;    //Reset Graphical display
    _delay(100000);
    RC1 = 1;    //Reset Graphical display
    _delay(100000);

    x = 0xfE;
    RB5 = (x >> 7);
   // result = (x >> 7);
    //    if (result & 1){
//        RB5 = 1;
//    }

    while(1){
//       RB5 = 1;
       RC7 = 1;
       _delay(100000);
//       RB5 = 0;
       _delay(100000);

 

    }

}

