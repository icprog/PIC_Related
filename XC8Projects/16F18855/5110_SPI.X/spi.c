#include    "spi.h"


void SPI_Init(void)
{
//    SSPEN = 1;  //Enables Serial Data pins
//    SSPM0 = 0;  //SSPM* sets SPI clock and mode 0010 = Master and oscillator /64
//    SSPM1 = 1;
//    SSPM2 = 0;
//    SSPM3 = 0;
//    CKE = 1;    //1
//    CKP = 0;    //0
    SSP1CON1 = 0x22;
    SSP1DATPPS = 0x14;                      //PPS for RC4 to be SDI
    RC5PPS = 0x15;                          //PPS for RC5 points at SDO1
    RC3PPS = 0x14;                          //PPS for RC3 points at SCK
    SSP1STATbits.CKE =  1;
//    CKE1 = 1;
}


/*char (SPI_TRANSFER)(char byte_to_send)
{
    char byte_recieved;
    
    byte_recieved = SSP1BUF;                // dummy read in case unread value might be in register from start up or something 
    
    SSP1BUF = byte_to_send;
//    __delay_us(35);

    __delay_us(5);
        
    while (SSP1CON1bits.WCOL == 1)      //Check for write collision
    {
        SSP1CON1bits.WCOL = 0;          //Reset collision bit
        __delay_us(5);
        SSP1BUF = byte_to_send;
        __delay_us(5);
    }
    
    byte_recieved = SSP1BUF;

    SSP1STATbits.BF = 0;                    // Reset Data arrived flag. This is probably reset automatically on an SSPBUF read
    
    return byte_recieved;
}*/
