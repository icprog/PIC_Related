//Thermocouple Display

//#include    <htc.h>
#include <xc.h>
#include <pic16f726.h>


//__CONFIG (FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & BOREN_OFF & PLLEN_ON);
//__CONFIG(WRTEN_OFF);


#pragma config FOSC = INTOSCIO //This is the reason it would not work.
#pragma config WDTE = OFF
#pragma config PLLEN = OFF//500K or 16M

#define _XTAL_FREQ 16000000	//16mhz default after reset





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
 //   SSPEN = 1;  //Enables Serial Data pins


    }






main(void) {
    Init();
    spi_init();
    int x = 0;
    char y = 0;
 
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
       
       while (1){
           if (BF == 1){
               _delay(100);
               y = SSPBUF;
               _delay(100);
               SSPBUF = 0x11;
               SSPIF = 0;
//               x++;
               if (RA0 == 1){
                   RA0 = 0;
               }
               else RA0 = 1;
               
           }
           if (x > 0){
               RA0 = 0;
           }
           if (x > 1){
               RA1 = 0;
           }
           if (x > 2){
               RA3 = 0;
           }
       }
       
}

}
