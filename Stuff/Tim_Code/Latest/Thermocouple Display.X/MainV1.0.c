//Thermocouple Display

//#include    <htc.h>
#include <xc.h>
#include <pic16f726.h>


//__CONFIG (FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & BOREN_OFF & PLLEN_ON);
//__CONFIG(WRTEN_OFF);


#pragma config FOSC = INTOSCIO //This is the reason it would not work.
#pragma config WDTE = OFF
#pragma config PLLEN = ON

#define _XTAL_FREQ 16000000	//16mhz default after reset




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
	PORTC = 0xFF;

        IRCF0 = 0;      //oscillator speed
        IRCF1 = 0;      //oscillator speed
  //      INTCON = 0;
 //       T0CS = 1;
  //      T0XCS = 0;
 //       PSA = 1;
  //      PS2 = 1;
 //       PS1 = 0;
  //      PS0 = 1;
 //       ADCON1 = 0x70;     // conversion speed for ADC





}





main(void) {
    Init();
    int j;
    SSPEN = 1;  //Enables Serial Data pins
    SSPM0 = 0;  //SSPM* sets SPI clock and mode 0010 = Master and oscillator /64
    SSPM1 = 1;
    SSPM2 = 0;
    SSPM3 = 0;

    RC0 = 0;    //Command = 0 Data = 1;
    RC2 = 0;    //Chip Select for Graphical display
    CKE = 1;    //1
    CKP = 0;    //0
    _delay(100000);
    _delay(100000);
    RC1 = 0;    //Reset Graphical display
    _delay(100000);
    RC1 = 1;
    _delay(100000);

    RC2 = 0;    //Chip Select for Graphical display
       _delay(0100);
    SSPBUF = 0xE3;  //NOP
       _delay(1000);
       _delay(1000);
    SSPBUF = 0xA0;
       _delay(1000);
       _delay(1000);
    SSPBUF = 0xAE;
       _delay(1000);
       _delay(1000);
    SSPBUF = 0xC0;
       _delay(1000);
       _delay(1000);
    SSPBUF = 0xA2;
       _delay(1000);
       _delay(1000);
    SSPBUF = 0x2F;
       _delay(1000);
       _delay(1000);
    SSPBUF = 0x21;
       _delay(1000);
       _delay(1000);
    SSPBUF = 0x81;
       _delay(1000);
       _delay(1000);
    SSPBUF = 0x3F;
       _delay(1000);
       _delay(1000);
    SSPBUF = 0xAF;
       _delay(1000);
       _delay(1000);
    
    while(1){
       RB5 = 1;
       RC7 = 0;
       _delay(100000);
       RB5 = 0;
       _delay(100000);
       SSPBUF = 0xAE;   //Turn display off
        SSPBUF = 0x40;  //Sets the display RAM start line display address = 0
       _delay(100000);
        SSPBUF = 0x10;  //Sets the Column start address upper bits = 0
       _delay(100000);
        SSPBUF = 0x00;  //Sets the Column start address lower bits = 0
       _delay(100000);
       SSPBUF = 0xB4;  //Set Page address to 4
       _delay(100000);

       RC0 = 1;    //Command = 0 Data = 1;

    }

}

