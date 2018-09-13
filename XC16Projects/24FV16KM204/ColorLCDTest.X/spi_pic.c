#include    "system.h"
#include    "spi_pic.h"

void SPI1_Init(void)
{
    TRIS_SCK1   = 0; 
    TRIS_SDO1   = 0;
    TRIS_SDI1   = 1;
    TRIS_SS1    = 0;
//    SPI1STAT    = 0xC0;
  //  SPI1CON1    = 0x20;
    SSP1STAT = 0xC0;
    SSP1CON1 = 0x20;
}

void SPI1_Close(void)
{
//    SPI1CON1    &=  0xDF;
    SSP1CON1 &= 0xDF;
}

void SPI1_Write(unsigned char data)
{
    SSP1CON1bits.WCOL = 0;
//    SPI1BUF = data;
    SSP1BUF = data;
//    while(!SPI1STATbits.SPITBF);  
  //  data = SPI1BUF;
    while(!SSP1STATbits.BF);  
    data = SSP1BUF;
}

unsigned char SPI1_Read(void)
{    
//    SPI1BUF = 0x00;
  //  while(!SPI1STATbits.SPIRBF);
    //return SPI1BUF; 
    SSP1BUF = 0x00;
    while(!SSP1STATbits.BF);
    return SSP1BUF; 
}