// Program CLCD_F84.C (CCS PCW)
//
// This is a collection of routines to interface with a PIC-n-LCD
// or similar serial LCD capable of 9600 baud, inverted, no parity.
//
// 	16F84				PIC-n-LCD
//
//	RA0 (term 17) --------------->	Serin In (term 3)
//
// void delay_ms(long t);		// delays for t ms
// void delay_10us(int t);		// delays for t * 10 us
// void lcd_init(void);	// inits PIC-n-LCD, sends 0x0c with a delay
// void out_RAM_str(int *s);		// output null terminated str
// void lcd_hex_byte(int val);	// output val in two digit hex
// void lcd_dec_byte(int val, int digits);
	// output val in dec to significant figures specified
	// by digits.  For example, if val is 014, specifying
	// digits as 3, will cause "014".  Specifying digits as 2
	// will cause "14" and specifying digits as 1 will cause
	// "4"
// int num_to_char(int val);	// converts val in range of
				// 0 - 15 to hex character
// void lcd_char(int c);	// outputs character c, 9600 baud, inverted
// void lcd_new_line(void);	// outputs 0x0d, 0x0a

// copyright, Peter H. Anderson, Mecklenburg CO, VA , MD, Mar, '99


#case

//#include <16F84.h>
#include <string.h>
//#include <defs_f84.h>

#define TxData 0	// RA.0 - output to serial LCD

// LCD routines
void delay_ms(long t);
void delay_10us(int t);
void lcd_init(void);
void out_RAM_str(int *s);
void lcd_hex_byte(int val);
void lcd_dec_byte(int val, int digits);
int num_to_char(int val);
void lcd_char(int ch);
void lcd_new_line(void);

main()
{
//  byte s[15];
    char s[15];
   while(1)
   {
      lcd_init();
      strcpy(s, "Morgan State");
         // note that CONST string is copied to RAM string
      out_RAM_str(s);
      lcd_new_line();
      strcpy(s, "University");
      out_RAM_str(s);

      lcd_new_line();
      lcd_hex_byte(254);	// display FE
      lcd_char(' ');
      lcd_dec_byte(192, 3);	// display 192

      delay_ms(500);
   }
}

void delay_10us(int t)
{
    __delay_ms(10);
/*#asm
      BCF STATUS, RP0
DELAY_10US_1:
      CLRWDT
      NOP
      NOP
      NOP
      NOP
      NOP
      NOP
      DECFSZ t, F
      GOTO DELAY_10US_1
#endasm */
}

void delay_ms(long t)	// delays t millisecs
{
   do
   {
     delay_10us(100);
   } while(--t);
}

int num_to_char(int val)	// converts val to hex character
{
   int ch;
   if (val < 10)
   {
     ch=val+'0';
   }
   else
   {
     val=val-10;
     ch=val + 'A';
   }
   return(ch);
}

void lcd_char(int ch)	// serial output to PIC-n-LCD, 9600 baud
{
   int n, dly;
   		// start bit + 8 data bits

  #asm
       BCF STATUS, RP0
       MOVLW 9
       MOVWF n
       BCF STATUS, C

  LCD_CHAR_1:

       BTFSS STATUS, C
       BSF PORTA, TxData
       BTFSC STATUS, C
       BCF PORTA, TxData
       MOVLW 32
       MOVWF dly

  LCD_CHAR_2:
       DECFSZ dly, F
       GOTO LCD_CHAR_2
       RRF ch, F
       DECFSZ n, F
       GOTO LCD_CHAR_1

       BCF PORTA, TxData
       CLRWDT
       MOVLW 96
       MOVWF dly

  LCD_CHAR_3:
       DECFSZ dly, F
       GOTO LCD_CHAR_3
       CLRWDT
   #endasm
}

void lcd_init(void)	// sets TxData in idle state and resets PIC-n-LCD
{
  #asm
        BCF STATUS, RP0
        BCF PORTA, TxData
        BSF STATUS, RP0
        BCF TRISA, TxData
        BCF STATUS, RP0
   #endasm
   lcd_char(0x0c);
   delay_ms(250);
}

void lcd_new_line(void)	// outputs 0x0d, 0x0a
{
   lcd_char(0x0d);
   delay_ms(10);	// give the PIC-n-LCD time to perform the
   lcd_char(0x0a);	// new line function
   delay_ms(10);
}


void out_RAM_str(int s)
{
   while(*s)
   {
      lcd_char(*s);
      ++s;
   }
}

void lcd_hex_byte(int val) // displays val in hex format
{
   int ch;
   ch = num_to_char((val>>4) & 0x0f);
   lcd_char(ch);
   ch = num_to_char(val&0x0f);
   lcd_char(ch);
}

void lcd_dec_byte(int val, int digits)
// displays byte in decimal as either 1, 2 or 3 digits
{
   int d;
   int ch;
   if (digits == 3)
   {
      d=val/100;
      ch=num_to_char(d);
      lcd_char(ch);
   }
   if (digits >1)	// take the two lowest digits
   {
       val=val%100;
       d=val/10;
       ch=num_to_char(d);
       lcd_char(ch);
   }
   if (digits == 1)	// take the least significant digit
   {
       val = val%100;
   }

   d=val % 10;
   ch=num_to_char(d);
   lcd_char(ch);
}

