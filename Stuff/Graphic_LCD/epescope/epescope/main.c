#include <p18f4620.h>
#include <stdlib.h>
#include <delays.h>
#include <stdio.h>
#include "KS0108.h" 	/*file with KS0108 command codes*/
#include <adc.h>

#define ABS(N) ( (N) >= 0 ? (N) : -(N) ) 

#pragma config WDT = OFF
#pragma config OSC = HS 
#pragma config PWRT = ON 
#pragma config PBADEN = OFF 
void delayMs(int x);
void getfromAdc(unsigned char channel);
void printFloat(char * flt, int number);
signed char graph[128];
char text[25];
unsigned char vert;
int LOpeak, HIpeak;
unsigned int freqtot,freq,volts;
char cycle = 0;
char rate = 1;
void main()

	{
	int x =1;
	int y =0, t = 2;
	char str[6];
	int pix,oldpix,offset;
	TRISB = 0xFF;
	INTCON2bits.RBPU = 0;
	GLCD_Initalize();
	OpenADC( ADC_FOSC_8 & ADC_LEFT_JUST & ADC_8_TAD ,
			ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS,
			ADC_4ANA );
	
	while(1)
		{
		clr();
		getfromAdc(ADC_CH0);
		sprintf(text," GSCOPE      RATE %d ",rate);
		strput(text,0,0);
		if(!PORTBbits.RB0)
			{
			delayMs(200);
			if(++rate == 4) rate = 1;
			switch (rate)
				{
				case 1:
					{
					ADCON2bits.ADCS2 = 0;
					ADCON2bits.ADCS1 = 0;
					ADCON2bits.ADCS0 = 1;
					break;
					}
				case 2:
					{
					ADCON2bits.ADCS2 = 1;
					ADCON2bits.ADCS1 = 0;
					ADCON2bits.ADCS0 = 1;
					break;
					}
				case 3:
					{
					ADCON2bits.ADCS2 = 0;
					ADCON2bits.ADCS1 = 1;
					ADCON2bits.ADCS0 = 0;
					}
				}
			}
		if(PORTBbits.RB1)
			{
			printFloat(str,volts);
			sprintf(text,"Vp/p %5s  %6d Hz ",str, freq);
			strput(text,0,56);	
			}
		vert -= 128;
		vert += 32;
		for(x = 0;x<128;x++)
			{
			offset = oldpix - graph[x];
			pix = oldpix = graph[x];
			pix += vert;
			if(pix > 63)pix = 63;
			if(pix < 0)pix = 0;
			if(x == 0 || offset == 0) 
				pixel(x, pix,0);
			else
				{
				if(offset > 0)
					{
					for(t = 0 ; t < offset; t++)
						pixel(x,pix+t,0);
					}
				else
					{
					for(t = 0 ; t > offset; t--)
						pixel(x, pix+t,0);
					}
				}
			}
		blit();
		}
	}

void getfromAdc(unsigned char channel)
	{
	int x,FR = 0;
	char lock;
	LOpeak = HIpeak= 0;
	lock = 0;
	SetChanADC(ADC_CH2);
	ConvertADC();
	while(BusyADC());
	vert = ADRESH ;
	SetChanADC(channel);
	for(x=0;x<128;x++)
		{
		ConvertADC();
		while(BusyADC());
		graph[x] = (255 - ADRESH) - vert;
		if(graph[x]< LOpeak) LOpeak = graph[x];
		if(graph[x]> HIpeak) HIpeak = graph[x];
		if(graph[x] > 0)
			{
			if(!lock)
				{
				FR+=208;
				lock = 1;
				}
			}
		if(graph[x] < 0)
			lock = 0;
		}
	volts = (ABS(LOpeak) + HIpeak) * 2;
	freqtot += FR;
	if(++cycle > 9) 
		{
		freq = freqtot/10;
		if(rate == 2) freq = freqtot/12;
		if(rate == 3) freq = freqtot/15;
		freqtot = cycle = 0;
		}
	return ;	
	}

void printFloat(char * flt, int number)
	{
	if(number < 0)
		{
		number = ABS(number);
		}
	flt[0] = number / 1000 + 48;
	if(flt[0] == 48) flt[0] = 0x20;
	flt[1] = ((number % 1000) / 100)+ 48;
	flt[2] = 46;
	flt[3] = ((number % 100) / 10)+ 48;
	flt[4] = (number % 10) + 48;
	flt[5] = 0;

	}
void delayMs(int x)
	{
	int y;
	for(y = 0; y < x; y++)
		{
		Delay100TCYx(49);
		y=y+1;
		y=y-1;
		}
	}