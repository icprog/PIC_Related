/* 
 * File:   I2C_BB.h
 * Author: DAVE
 *
 * Created on February 14, 2015, 3:04 PM
 */

#ifndef I2C_BB_H
#define	I2C_BB_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_BB_H */

#ifndef _I2C_BB_H
#define _I2C_BB_H

void Init_I2C(void);
unsigned char I2C_IN(char NACK);
char I2C_OUT(unsigned char data);
void I2C_SP(void);
void I2C_ST(void);

void delay(unsigned int time);
void delay2(unsigned int time);

#define SCL_HIGH() (SCL = 1)
#define SDA_HIGH() (SDA = 1)
#define SDA_LOW() (SDA = 0,SDA_IN=0)
#define SCL_LOW() (SCL = 0,SCL_IN=0)

#define SCL     TRISCbits.TRISC0
#define SDA     TRISCbits.TRISC1
#define SCL_IN  PORTCbits.RC0
#define SDA_IN  PORTCbits.RC1

//INT CHANNELS
#define CH1 PORTAbits.RA0
#define CH2 PORTAbits.RA1
#define CH3 PORTBbits.RB0
#define CH4 PORTBbits.RB1
#define CH5 !PORTBbits.RB2
#define CH6 !PORTBbits.RB3
#define CH7 !PORTBbits.RB4
#define CH8 !PORTBbits.RB5

#endif

