//Thermocouple Display
//This Program is for the right hand processor
//#include    <htc.h>
#include <xc.h>
//#include <pic16f726.h>


//__CONFIG (FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & BOREN_OFF & PLLEN_ON);
//__CONFIG(WRTEN_OFF);


#pragma config FOSC = INTOSCIO //This is the reason it would not work.
#pragma config WDTE = OFF
#pragma config PLLEN = ON

#define _XTAL_FREQ 16000000	//16mhz default after reset
//#define SYS_FREQ = 16000000



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
void spi_init(void){
    SSPEN = 1;  //Enables Serial Data pins
    SSPM0 = 0;  //SSPM* sets SPI clock and mode 0010 = Master and oscillator /64
    SSPM1 = 1;
    SSPM2 = 0;
    SSPM3 = 0;
    CKE = 1;    //1
    CKP = 0;    //0


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



main(void) {
    Init();
    spi_init();


    while(1){
       RB5 = 1;         //Turn on LED
       RC7 = 1;         //Turn on Backlight
       _delay(100000);
       RB5 = 0;         //Turn off LED
       _delay(100000);
       while (1){

       RB5 = 1;     //Turn on LED
       _delay(10000000);
       RB5 = 0;         //Turn off LED
       _delay(10000000);
       RC6 = 0;
       _delay(100000);
       SSPBUF = 0x88;
       _delay(100000);
       RC6 = 1;
       }

    }

}

