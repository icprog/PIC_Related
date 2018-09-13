#ifndef SPI_PIC_H
#define	SPI_PIC_H

#define TRIS_SCK1   TRISBbits.TRISB11         
#define TRIS_SDO1   TRISBbits.TRISB13
#define TRIS_SDI1   TRISBbits.TRISB10
#define TRIS_SS1    TRISBbits.TRISB15

void SPI1_Init(void);
void SPI1_Close(void);
void SPI1_Write(unsigned char data);
unsigned char SPI1_Read(void);

#endif