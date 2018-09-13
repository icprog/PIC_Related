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

int thermocouple_temp[12][3];


void Init() {

	//di();	//disable all interrupts

	//Initialization
	TRISA = 0x00;	//not used inputs 0 = output
	ANSELA = 0x00;	//all digital not analog
	PORTA = 0xff;
    TRISA4 = 1;
    TRISA3 = 1;     //input for feedback from top SS pic

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
void data_out(unsigned char i){ //Data output serial interface
    unsigned int n;
    RC2 = 0;    //Chip Select for Graphical display
    RC0 = 1;    //Command = 0 Data = 1;
    SSPBUF = i;  
    __delay_us(1000);
    RC2 = 1;    // deselect Graphical display

    }

/*void data_out(unsigned char i){ //Data output serial interface
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
*/



void comm_out(unsigned char j){ //Command output serial interface
    unsigned int n;    
    RC2 = 0;    //Chip Select for Graphical display
    RC0 = 0;    //Command = 0 Data = 1;
    SSPBUF = j;  
    __delay_us(1000);
    RC2 = 1;    // Unselect Graphical display

    }

void comm_to_7_seg_pic(unsigned char j){ //Command output serial interface
    unsigned int n;    
    RC6 = 0;    //Chip Select for left hand pic
    __delay_us(1000);
    SSPBUF = j;  
    __delay_us(1000);
    RC6 = 1;    // Unselect left hand display

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
        data_out (0x0F);
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

void location (int position[2]){
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

}


const char fonts [] = {
    0x00, 0x00, 0x00,  // sp
    0x00, 0x4E, 0x00,  // ! *
    0x06, 0x00, 0x06,  // " *
    0xff, 0xff, 0xff,  // #  35
    0x48, 0xd6, 0x24,  // $ *
    0x12, 0x08, 0x24,  // % *
//    0x13, 0x6B, 0x64,  // % *
    0xff, 0xff, 0xff,  // &
    0x00, 0x06, 0x00,  // ' *
    0x38, 0x44, 0x82,  // ( * 40
    0x82, 0x44, 0x38,  // ) *
    0x14, 0x08, 0x3E,  // *
    0x10, 0x38, 0x10,  // + *
    0xa0, 0x60, 0x00,  // , *
    0x10, 0x10, 0x10,  // - * 45
    0x60, 0x60, 0x00,  // . *
    0x60, 0x18, 0x06,  // / *
    0x7c, 0x42, 0x7c,  // 0 *
    0x44, 0x7e, 0x40,  // 1 *
    0x64, 0x52, 0x4c,  // 2 * 50
    0x4a, 0x4a, 0x34,  // 3 *
    0x38, 0x24, 0x7e,  // 4 *
    0x4e, 0x4a, 0x32,  // 5 *
    0x3c, 0x4a, 0x32,  // 6 *
    0x62, 0x1a, 0x06,  // 7 * 55
    0x76, 0x4a, 0x76,  // 8 *
    0x4c, 0x52, 0x3c,  // 9 *
    0x6c, 0x6c, 0x00,  // : *
    0xac, 0x6c, 0x00,  // ; *
    0x10, 0x28, 0x44,  // < * 60
    0x28, 0x28, 0x28,  // = *
    0x44, 0x28, 0x10,  // > *
    0x02, 0x59, 0x06,  // ?
    0xFF, 0xFF, 0xFF,  // @
    0x7c, 0x12, 0x7c,  // A * 65
    0x7E, 0x5A, 0x34,  // B *
    0x3c, 0x42, 0x42,  // C *
    0x7e, 0x42, 0x3c,  // D *
    0x7e, 0x4a, 0x42,  // E *
    0x7e, 0x0a, 0x0a,  // F * 70
    0x3c, 0x52, 0x34,  // G *
    0x7e, 0x08, 0x7e,  // H *
    0x42, 0x7e, 0x42,  // I *
    0x30, 0x40, 0x3e,  // J *
    0x7e, 0x18, 0x66,  // K * 75
    0x7e, 0x40, 0x40,  // L *
    0x7e, 0x1c, 0x7e,  // M *
    0x7e, 0x02, 0x7e,  // N *
    0x3c, 0x42, 0x3c,  // O *
    0x7e, 0x12, 0x0c,  // P * 80
    0x7e, 0x62, 0xfe,  // Q *
    0x7e, 0x32, 0x4e,  // R *
    0x44, 0x4a, 0x32,  // S *
    0x02, 0x7e, 0x02,  // T *
    0x7E, 0x40, 0x7E,  // U * 85
    0x3e, 0x40, 0x3e,  // V *
    0x7E, 0x38, 0x7E,  // W *
    0x66, 0x18, 0x66,  // X *
    0x0e, 0x70, 0x0e,  // Y *
    0x62, 0x5a, 0x46,  // Z * 90
    0x00, 0x7e, 0x42,  // [ *
    0x06, 0x18, 0x60,  // backslash *
    0x42, 0x7e, 0x00,  // ] *
    0x04, 0x02, 0x04,  // ^ *
    0x40, 0x40, 0x40,  // _ * 95
    0x00, 0x02, 0x04,  // ` *
    0x74, 0x54, 0x78,  // a *
    0x7e, 0x48, 0x30,  // b *
    0x30, 0x48, 0x48,  // c *
    0x30, 0x48, 0x7e,  // d * 100
    0x38, 0x54, 0x58,  // e *
    0x7C, 0x0A, 0x02,  // f *
    0x98, 0xa4, 0x7c,  // g *
    0x7e, 0x08, 0x70,  // h *
    0x48, 0x7a, 0x40,  // i * 105
    0x88, 0xfa, 0x00,  // j *
    0x7e, 0x18, 0x64,  // k *
    0x42, 0x7E, 0x40,  // l *
    0x7c, 0x38, 0x7c,  // m *
    0x7C, 0x04, 0x78,  // n * 110
    0x38, 0x44, 0x38,  // o *
    0xFC, 0x24, 0x18,  // p *
    0x18, 0x24, 0xFC,  // q *
    0x78, 0x04, 0x04,  // r *
    0x48, 0x54, 0x24,  // s * 115
    0x04, 0x3e, 0x44,  // t *
    0x7C, 0x40, 0x7C,  // u *
    0x3c, 0x40, 0x3c,  // v *
    0x7c, 0x30, 0x7c,  // w *
    0x6c, 0x10, 0x6c,  // x * 120
    0x9c, 0xa0, 0x7c,  // y *
    0x64, 0x54, 0x4c,  // z *
    0x0C, 0x12, 0x0c,  // degree symbol
    0xFF, 0xFF, 0xFF,  // O
    0xFF, 0xFF, 0xFF,  // U   125
    0xFF, 0xFF, 0xFF,  // a
    0xFF, 0xFF, 0xFF,  // o
    0xFF, 0xFF, 0xFF,  // u
    0xFF, 0xFF, 0xFF,  // 
    0xfc, 0x40, 0x7c,  // µ * 130
    0xFF, 0xFF, 0xFF,  // <
    0xFF, 0xFF, 0xFF,  // 
};

void LCDWriteCharacter(const char character)
{
    unsigned int base, before_swap, after_swap, i, j;
    base = character - 32;
    base *= 3;                                  // 3 bit Font, so location * 3 will pull up correct font
    after_swap = 0;
    for (i=0;i<3;i++){
        before_swap = fonts[base];
        for (j=0;j<7;j++){
            if (before_swap & 1 == 1){
            after_swap = after_swap | 1;
            }
        before_swap = before_swap >> 1;
        after_swap = after_swap << 1;
        }
        data_out(after_swap);             // fonts are written 1 vertical line of 8 bits at a time
        base++;
    }
    data_out(0x00);                   // write a blank line to space the font
}

/*void LCDWriteCharacter(const char character)
{
    unsigned int base;
    base = character - 32;
    base *= 3;                                  // 3 bit Font, so location * 3 will pull up correct font
    data_out(fonts[base]);             // fonts are written 1 vertical line of 8 bits at a time
    data_out(fonts[base + 1]);         // so, this is the second vertical line
    data_out(fonts[base + 2]);         // third vertical line of font character
    data_out(0x00);                   // write a blank line to space the font
}*/

/*void String_test(void){
    char test_string [] = "Tim's String";
    char *test_pointer;
    int x = 0;
    test_pointer = &test_string;
    while (x < 12){
        LCDWriteCharacter(*test_pointer);
        x++;
        test_pointer++;
    }
}*/
void String_test(void){
    char test_string [] = "Tim's String";
    char *test_pointer;
  //  int x = 0;
    test_pointer = &test_string;
    while (*test_pointer != 0){
        LCDWriteCharacter(*test_pointer);
   //     x++;
        test_pointer++;
    }
}

char (SPI_TRANSFER)(char byte_to_send){
    char byte_recieved;
    byte_recieved = SSPBUF; // dummy read in case unread value might be in register from start up or something      
    SSPBUF = byte_to_send;
    __delay_us(35);
//    byte_recieved = SSPBUF;
    __delay_us(5);
        while (WCOL == 1){     //Check for write collision
        WCOL = 0;       //Reset collision bit
        __delay_us(5);
        SSPBUF = byte_to_send;
        __delay_us(5);
    }
    byte_recieved = SSPBUF;
    BF = 0; // Reset Data arrived flag. This is probably reset automatically on an SSPBUF read
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
    if  (*data_pointer > 10){   //Reset array address pointer to 1
        *data_pointer = 0;
        //Add Delay here
//        _delay(10000000);
    }     
}



void (chip_select)(int chip){
    RC6 = 1;    
    if (chip == 1){
        RC6 = 0;    //Chip Select for left hand pic
        
    }
    else{
        RC6 = 1;
    }
}


void (char_to_decimal_print)(int value){
    char x = 0;
    while (value >= 100){    //Determine hundreds digit
        value = value - 100;
        x++;
    }
    x = x + 48;      //convert to asci
    LCDWriteCharacter(x);
    x = 0;  //reset x for next calculation
    while (value >= 10){
        value = value - 10;
        x++;
    }
    x = x + 48;      //convert to asci
    LCDWriteCharacter(x);
    x = 0;  //reset x for next calculation
    while (value > 0){
        value = value - 1;
        x++;
    }
    x = x + 48;      //convert to asci
    LCDWriteCharacter(x);
    x = 0;  //reset x for next calculation
}


/*void (get_temp_from_right_tcs)(int *pointer_thermocouple_temp){       
    char byte_to_send = 0;
    char byte_received = 0;
    char byte1 = 0;
    char byte2 = 0;
    char byte3 = 0;
    char byte4 = 0;
 //   __delay_us(1000000);
    RA2 = 0; //increment SS to point to first TC chip
    __delay_us(100);
    byte1= SPI_TRANSFER(byte_to_send);
    byte2 = SPI_TRANSFER(byte_to_send);
    byte3 = SPI_TRANSFER(byte_to_send);
    byte4 = SPI_TRANSFER(byte_to_send);
    RA2 = 1; //increment SS to point to first TC chip
//    LCDWriteCharacter('G');
    __delay_us(200);
    char_to_decimal_print(byte1);
    LCDWriteCharacter(' ');
    char_to_decimal_print(byte2);
    LCDWriteCharacter(' ');
    char_to_decimal_print(byte3);
    LCDWriteCharacter(' ');
    char_to_decimal_print(byte4);
    LCDWriteCharacter(' ');
 //   char_to_decimal_print(10);
    
    __delay_us(2000000);
 




    RA1 = 0;    //resets SS pic
    __delay_us(100);
    RA1 = 1;

    
}  */

void (get_temp_from_right_tcs)(void){       
    char byte_to_send = 0;
    char byte_received = 0;
    char byte1 = 0;
    char byte2 = 0;
    char byte3 = 0;
    char byte4 = 0;
    int x = 1;
    int position[2];
//    long int working_register = 0;
    position[0] = 00;  //0 to 127
    position[1] = 16;   //0 to 31
    RA1 = 0;    //reset top SS pic
    __delay_us(100);
    RA1 = 1;
    while (x <= 3){  //number is equal to amount of thermocouple inputs
        RA2 = 0; //increment SS to point to first TC chip
        __delay_us(100);
//        RA2 = 1; //increment SS
        byte1= SPI_TRANSFER(byte_to_send);
        byte2 = SPI_TRANSFER(byte_to_send);
        byte3 = SPI_TRANSFER(byte_to_send);
        byte4 = SPI_TRANSFER(byte_to_send);
        thermocouple_temp[x][0] = (byte1 & 0x00FF); //isolate thermocouple hot junction bits 
        thermocouple_temp[x][0] = thermocouple_temp[x][0] << 8;
        thermocouple_temp[x][0] = (thermocouple_temp[x][0] | byte2);
        thermocouple_temp[x][0] = thermocouple_temp[x][0] >> 2;     // get rid of reserved and fault bit 
        
        thermocouple_temp[x][1] = (byte3 & 0x00FF); //isolate thermocouple cold junction bits 
        thermocouple_temp[x][1] = thermocouple_temp[x][1] << 8;
        thermocouple_temp[x][1] = (thermocouple_temp[x][1] | byte4);
        thermocouple_temp[x][1] = thermocouple_temp[x][1] >> 4;     // get rid of reserved and fault bit 

        thermocouple_temp[x][2] = (byte4 & 0x000F); //isolate error bits junction bits 
        
        x++;
        RA2 = 1; //increment SS
        __delay_us(100);
    }
//    __delay_us(200);
    char_to_decimal_print(byte1);
    LCDWriteCharacter(' ');
    char_to_decimal_print(byte2);
    LCDWriteCharacter(' ');
    char_to_decimal_print(byte3);
    LCDWriteCharacter(' ');
    char_to_decimal_print(byte4);
    LCDWriteCharacter(' ');
 //   char_to_decimal_print(10);

    location(position);
    char_to_decimal_print(thermocouple_temp[1][0]);
    LCDWriteCharacter(' ');
    char_to_decimal_print(thermocouple_temp[1][1]);
    LCDWriteCharacter(' ');
    char_to_decimal_print(thermocouple_temp[1][2]);
    position[1] = 8;   //0 to 31
    location(position);
    char_to_decimal_print(thermocouple_temp[2][0]);
    LCDWriteCharacter(' ');
    char_to_decimal_print(thermocouple_temp[2][1]);
    LCDWriteCharacter(' ');
    char_to_decimal_print(thermocouple_temp[2][2]);
    position[1] = 0;   //0 to 31
    location(position);
    char_to_decimal_print(thermocouple_temp[3][0]);
    LCDWriteCharacter(' ');
    char_to_decimal_print(thermocouple_temp[3][1]);
    LCDWriteCharacter(' ');
    char_to_decimal_print(thermocouple_temp[3][2]);




    __delay_us(200);
 




    RA1 = 0;    //resets SS pic
    __delay_us(100);
    RA1 = 1;

    
}

void display_temps_to_screen(void){
    int position[2];
    long int working_register = 0;
    char sensor_one_string [] = "S1 = ";
    char *sensor_one_string_pointer;
    sensor_one_string_pointer = &sensor_one_string;
    char sensor_two_string [] = "S2 = ";
    char *sensor_two_string_pointer;
    sensor_two_string_pointer = &sensor_two_string;
    char sensor_three_string [] = "S3 = ";
    char *sensor_three_string_pointer;
    sensor_three_string_pointer = &sensor_three_string;
    char celsius_string [] = " Celsius";
    char *celsius_string_pointer;
    celsius_string_pointer = &celsius_string;
    char open_string [] = "OPEN ";
    char *open_string_pointer;
    open_string_pointer = &open_string;
    char shortvcc_string [] = "SHORT VCC ";
    char *shortvcc_string_pointer;
    shortvcc_string_pointer = &shortvcc_string;
    char shortgnd_string [] = "SHORT GND ";
    char *shortgnd_string_pointer;
    shortgnd_string_pointer = &shortgnd_string;
    char fault_string [] = "FAULT ";
    char *fault_string_pointer;
    fault_string_pointer = &fault_string;

/////////////////////////////////////////////////////        
    position[0] = 64;  //0 to 127
    position[1] = 24;   //0 to 31
        location(position);
    while (*sensor_one_string_pointer != 0){
        LCDWriteCharacter(*sensor_one_string_pointer);
        sensor_one_string_pointer++;
        }    
    if (thermocouple_temp[1][2] == 1){
        while (*open_string_pointer != 0){
        LCDWriteCharacter(*open_string_pointer);
        open_string_pointer++;
        } 
    open_string_pointer = &open_string;
    }
    else if (thermocouple_temp[1][2] == 4){
        while (*shortvcc_string_pointer != 0){
        LCDWriteCharacter(*shortvcc_string_pointer);
        shortvcc_string_pointer++;
        }
        shortvcc_string_pointer = &shortvcc_string;
    }
    else if (thermocouple_temp[1][2] == 2){
        while (*shortgnd_string_pointer != 0){
        LCDWriteCharacter(*shortgnd_string_pointer);
        shortgnd_string_pointer++;
        }
        shortgnd_string_pointer = &shortgnd_string;
    }
    else if (thermocouple_temp[1][2] > 4){
        while (*fault_string_pointer != 0){
        LCDWriteCharacter(*fault_string_pointer);
        fault_string_pointer++;
        }
        fault_string_pointer = &fault_string;
    }
/*        
    else{
        working_register = (thermocouple_temp[1][0]) * .25;
        char_to_decimal_print(working_register);
        while (*celsius_string_pointer != 0){
            LCDWriteCharacter(*celsius_string_pointer);
            celsius_string_pointer++;
        }
        celsius_string_pointer = &celsius_string;
    }
 */ 
    else{
        working_register = (thermocouple_temp[1][0]) & 0x2000;    //look for sign bit
        if ((working_register == 0x2000)){
            working_register = thermocouple_temp[1][0] & 0x1FFF;   //AND out sign bit

            working_register = ~ working_register;      //invert so we can multiply
            working_register =  working_register & 0x0FFF;
            working_register = working_register * .25;
            LCDWriteCharacter('-');
            char_to_decimal_print(working_register);
        }
        else{
            working_register = (thermocouple_temp[1][0]) * .25;
            char_to_decimal_print(working_register);
        }
        while (*celsius_string_pointer != 0){
            LCDWriteCharacter(*celsius_string_pointer);
            celsius_string_pointer++;
        }
        celsius_string_pointer = &celsius_string;
    }
        
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////        
    position[0] = 64;  //0 to 127
    position[1] = 16;   //0 to 31
    location(position);
    while (*sensor_two_string_pointer != 0){
            LCDWriteCharacter(*sensor_two_string_pointer);
            sensor_two_string_pointer++;
         }
    if (thermocouple_temp[2][2] == 1){
        while (*open_string_pointer != 0){
        LCDWriteCharacter(*open_string_pointer);
        open_string_pointer++;
        }
        open_string_pointer = &open_string;
    }
    else if (thermocouple_temp[2][2] == 4){
        while (*shortvcc_string_pointer != 0){
        LCDWriteCharacter(*shortvcc_string_pointer);
        shortvcc_string_pointer++;
        }
        shortvcc_string_pointer = &shortvcc_string;
    }
    else if (thermocouple_temp[2][2] == 2){
        while (*shortgnd_string_pointer != 0){
        LCDWriteCharacter(*shortgnd_string_pointer);
        shortgnd_string_pointer++;
        }
        shortgnd_string_pointer = &shortgnd_string;
    }
    else if (thermocouple_temp[2][2] > 4){
        while (*fault_string_pointer != 0){
        LCDWriteCharacter(*fault_string_pointer);
        fault_string_pointer++;
        }
        fault_string_pointer = &fault_string;
    }
    else{
        working_register = (thermocouple_temp[2][0]) * .25;
 //       location(position);
            
        char_to_decimal_print(working_register);
        while (*celsius_string_pointer != 0){
            LCDWriteCharacter(*celsius_string_pointer);
            celsius_string_pointer++;
        }
        celsius_string_pointer = &celsius_string;
    }
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////        
    position[0] = 64;  //0 to 127
    position[1] = 8;   //0 to 31
    location(position);
    while (*sensor_three_string_pointer != 0){
            LCDWriteCharacter(*sensor_three_string_pointer);
            sensor_three_string_pointer++;
         }
    if (thermocouple_temp[3][2] == 1){
        while (*open_string_pointer != 0){
            LCDWriteCharacter(*open_string_pointer);
            open_string_pointer++;
        }
        open_string_pointer = &open_string;
    }
    else if (thermocouple_temp[3][2] == 4){
        while (*shortvcc_string_pointer != 0){
            LCDWriteCharacter(*shortvcc_string_pointer);
            shortvcc_string_pointer++;
        }
        shortvcc_string_pointer = &shortvcc_string;
    }
    else if (thermocouple_temp[3][2] == 2){
        while (*shortgnd_string_pointer != 0){
            LCDWriteCharacter(*shortgnd_string_pointer);
            shortgnd_string_pointer++;
        }
        shortgnd_string_pointer = &shortgnd_string;
    }
    else if (thermocouple_temp[3][2] > 4){
        while (*fault_string_pointer != 0){
            LCDWriteCharacter(*fault_string_pointer);
            fault_string_pointer++;
        }
        fault_string_pointer = &fault_string;
    }
    else{
        working_register = (thermocouple_temp[3][0]) * .25;
 //       location(position);
            
        char_to_decimal_print(working_register);
        while (*celsius_string_pointer != 0){
            LCDWriteCharacter(*celsius_string_pointer);
            celsius_string_pointer++;
        }
        celsius_string_pointer = &celsius_string;
    }
/////////////////////////////////////////////////////
    
}
void move_temp_to_send (char *data_pointer){
    int x = 0;
    char *reg = 0;    //working register for data_pointer addresses
    int working_register = 0;
    char byte_to_send = 0; 
    if (*data_pointer == 0){
        *data_pointer = 1;  //set status byte to one.
        reg = data_pointer + 1; //move the address of data_pointer plus one into reg
        *reg = 0x81;//command for display temp
        reg = data_pointer + 2; //move in address for temperature number
        x = *reg;   // get last temperature number sent
        x++;    //increment to next temp number
        if (x > 3){ //check to see if all temps have been sent increment to send more temps
            x = 1;//
//            _delay(100000); //Delay to allow left hand pic time to timeout, This should be changed so that it gives timeout after each set of Bytes
        }
        *reg = x;   //move in current temperature number to send.
        reg = data_pointer + 4;
        byte_to_send = thermocouple_temp[x][0] & 0xff;  //isolate first byte
        *reg = byte_to_send;
        reg = data_pointer + 3;
        working_register = thermocouple_temp[x][0];
        working_register = working_register >> 8;
        byte_to_send = working_register & 0xff;
        *reg = byte_to_send;
        
        
    }
}
main(void) {
    Init();
    spi_init();

    char spi_data[22];//byte 0 is status byte 1-10 are for output, 11-20 are for input
    spi_data[0] = 1;
    char *data_pointer;
    data_pointer = &spi_data[0];
    spi_data[1] = 0x81; //test value 0x81 is command to display temp
    spi_data[2] = 0x01; //test value 0x01 is addition to command to display temp 1
    spi_data[3] = 0x13; //test byte 0x1348 is equal to 1234 degrees
    spi_data[4] = 0x48; //test byte 0x1348 is equal to 1234 degrees
    spi_data[5] = 0x48; 
    spi_data[6] = 0x48; 
    spi_data[7] = 0x48; 
    spi_data[8] = 0x48; 
    spi_data[9] = 0x48; 
    spi_data[10] = 0xaa; //last byte in communication sequence 
//    int thermocouple_temp[12][3];
//    int *pointer_thermocouple_temp;
//    pointer_thermocouple_temp = &thermocouple_temp[0];
    int position[2];
    position[0] = 00;  //0 to 127
    position[1] = 24;   //0 to 31
    char display_matrix[10];
    int x;
    long int count = 0;
//    int before;
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
//       dot (position);
       location(position);
//       LCDWriteCharacter(48);
       x = 48;
//       before = 5;
//       if (before & 1 == 1){
//           RB5 = 1;     //Turn on LED
//              }
       String_test();
//       get_temp_from_right_tcs();
       while (1){
//       increasing_bar();
//       eating_bar();
//       pattern_bar();

       RB5 = 1;     //Turn on LED
//       _delay(100);
//       String_test();
//       LCDWriteCharacter(x);
//       x++;
//       RB5 = 0;         //Turn off LED
//       _delay(100000);
//       comm_to_7_seg_pic('0');
//       chip_select(1);      //select left hand pic
       

///////////////////////////////////////////////////////
/*
       while (1){

       RB5 = 1;     //Turn on LED
       __delay_us(20000);
//       _delay(1000000);
       RB5 = 0;         //Turn off LED
       __delay_us(20000);
//       _delay(1000000);
       RC6 = 0;
//       _delay(1000);
       __delay_us(50);
//       SSPBUF = 0x88;
       SSPBUF = data_pointer;
       //       _delay(1000);
       __delay_us(50);
       RC6 = 1;
       }
*/
//////////////////////////////////////////////////////////
       
       
       
       
       
       
       chip_select(1);      //select left hand pic       
        __delay_us(10);
       SPI_DATA_HANDLING(data_pointer);
        __delay_us(10);
       chip_select(0);      //de select left hand pic
//       blank_image();
       location(position);
       get_temp_from_right_tcs();
       RB5 = 0;         //Turn off LED
       display_temps_to_screen(); 
       move_temp_to_send (data_pointer);

//       count++;
       if (count > 20){
           *data_pointer = 1;
           count = 0;
       }
       }

    }

}

