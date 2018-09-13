/*
 * File:   top_pic_mainv1.0.c
 * Author: narif
 *
 * Created on January 11, 2018, 10:24 AM
 */


#include <xc.h>
#include <pic16f720.h>
#pragma config FOSC = INTOSCIO //This is the reason it would not work.
#pragma config WDTE = OFF
#pragma config PLLEN = OFF//500K or 16M

#define _XTAL_FREQ 16000000	//16mhz default after reset
int no_slave_selected = 0;
void Init() {

	//di();	//disable all interrupts

	//Initialization
	TRISA = 0x14;	//not used inputs 0 = output
	ANSELA = 0x00;	//all digital not analog
	PORTA = 0xff;

	TRISB = 0x00;	//0 = output
	ANSELB = 0x00;	//digital not analog
	PORTB = 0xFF;

	TRISC = 0x00;	//0 = output
	ANSELC = 0x00;	//all digital not analog
	PORTC = 0xff;
//    IRCF1 = 0;      //oscillator post scaler
//    IRCF0 = 0;      //oscillator post scaler

   
   


}

void increment_slave_select (void){
    if (no_slave_selected == 1){
        RC1 = 0;    //thermocouple IC top right
        no_slave_selected = 0;

    }
    else if (RC1 == 0){
        RC1 = 1;    //thermocouple IC second from top right
        RC0 = 0;
    }
    else if (RC0 == 0){
        RC0 = 1;    //thermocouple IC third from top right
        RB7 = 0;
    }
    //add more code here if adding more thermocouple input chips.
    else if (RB7 == 0){
        RB7 = 1;
        no_slave_selected = 1;
    }
    
    
}

void clear_slave_select (void){
    no_slave_selected = 1;
    RC1 = 1;
//    RC0 = 1;
    RB7 = 1;

}





void main(void) {
    Init();
    int RA4_one_shot = 0;
    int RA2_one_shot = 0;
    PORTC = 0xff;

//        RC0 = 0;
//        RC1 = 1;
   
    
    
    while(1){
        if ((RA4 == 0)&& (RA4_one_shot != 1)){
            RA4_one_shot = 1;    
            increment_slave_select();    
        }
        if (RA4 == 1){
            RA4_one_shot = 0;   
        }

        if ((RA2 == 0)&& (RA2_one_shot != 1)){
            RA2_one_shot = 1;    
            clear_slave_select();  

        }
        if (RA2 == 1){
            RA2_one_shot = 0;   

        }
        if (no_slave_selected == 1){
            RA5 = 1;
        }
        if (no_slave_selected == 0){
            RA5 = 0;
        }
        
    }
//    if (RA5 == 1){          //toggle bit on increment to send back to Master for debugging
  //      RA5 = 0;
    //}
//    else{
  //      RA5 = 1;
    //}

        
   
}
