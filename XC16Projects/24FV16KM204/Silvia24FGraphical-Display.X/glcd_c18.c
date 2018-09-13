#include <p18cxxx.h>
#include <stdio.h>
#include <delays.h>

#pragma config WDT = OFF, OSC = HS, LVP = OFF

void delay_s(unsigned char x);
void delay_ms(unsigned char x);
void delay_us(unsigned char x);

#define glcd_lat LATB
#define glcd_tris TRISB
#define BSY PORTB

#define E LATCbits.LATC2
#define RW LATCbits.LATC1
#define DI LATCbits.LATC0

#define CS1 LATAbits.LATA0
#define CS2 LATAbits.LATA1
#define RS LATAbits.LATA2

void e_togg(void);
void busy(void);
void cmd_write(unsigned char x);
void data_write(unsigned char x);
void init(void);
void cls(void);
void loadimg(rom char *image, unsigned int len);
void load_char(rom char *image, char letter);
char load_num(rom char *image, char number, int y, char x);

unsigned rom char toplogo_bmp[1024] = {
0  ,254,254,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,
6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,
6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,
6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,
6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,
6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,
6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,
6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,6  ,254,254,0  ,
0  ,255,255,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,224,252,31 ,3  ,31 ,252,224,0  ,
0  ,0  ,48 ,254,255,48 ,48 ,0  ,0  ,128,224,96 ,48 ,48 ,48 ,48 ,
96 ,224,128,0  ,0  ,240,240,96 ,48 ,48 ,48 ,240,192,96 ,48 ,48 ,
48 ,240,224,0  ,0  ,0  ,60 ,126,102,195,195,195,195,131,134,14 ,
12 ,0  ,0  ,128,224,96 ,48 ,48 ,48 ,48 ,96 ,224,128,0  ,48 ,48 ,
254,255,51 ,51 ,51 ,254,255,48 ,48 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,255,255,0  ,
0  ,255,255,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,96 ,124,31 ,3  ,3  ,3  ,3  ,3  ,3  ,3  ,31 ,
124,96 ,0  ,63 ,127,96 ,96 ,0  ,0  ,15 ,63 ,48 ,96 ,96 ,96 ,96 ,
48 ,63 ,15 ,0  ,0  ,127,127,0  ,0  ,0  ,0  ,127,127,0  ,0  ,0  ,
0  ,127,127,0  ,0  ,12 ,28 ,56 ,112,96 ,96 ,96 ,96 ,97 ,49 ,63 ,
30 ,0  ,0  ,15 ,63 ,48 ,96 ,96 ,96 ,96 ,48 ,63 ,15 ,0  ,0  ,0  ,
127,127,0  ,0  ,0  ,63 ,127,96 ,96 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,255,255,0  ,
0  ,255,255,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,112,80 ,208,16 ,208,80 ,240,16 ,112,64 ,112,16 ,240,
16 ,80 ,80 ,80 ,80 ,240,0  ,0  ,0  ,240,16 ,208,16 ,240,16 ,240,
16 ,80 ,80 ,80 ,80 ,240,16 ,240,16 ,240,16 ,240,0  ,0  ,0  ,240,
16 ,208,16 ,240,16 ,240,16 ,80 ,80 ,80 ,16 ,240,16 ,208,16 ,208,
16 ,240,16 ,80 ,80 ,80 ,80 ,240,0  ,0  ,0  ,240,16 ,80 ,80 ,80 ,
80 ,240,16 ,208,80 ,208,16 ,240,16 ,80 ,80 ,80 ,16 ,240,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,255,255,0  ,
0  ,255,255,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,7  ,4  ,199,64 ,71 ,68 ,199,65 ,199,68 ,71 ,
68 ,69 ,69 ,197,69 ,199,64 ,192,64 ,199,4  ,7  ,4  ,197,68 ,71 ,
68 ,69 ,69 ,197,69 ,71 ,68 ,69 ,68 ,197,68 ,71 ,64 ,64 ,64 ,199,
68 ,199,4  ,197,68 ,199,68 ,71 ,65 ,199,68 ,199,68 ,71 ,68 ,71 ,
68 ,199,68 ,197,5  ,5  ,5  ,199,64 ,64 ,64 ,71 ,68 ,199,65 ,65 ,
65 ,71 ,68 ,197,69 ,197,4  ,199,68 ,199,7  ,4  ,5  ,7  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,255,255,0  ,
0  ,255,255,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,31 ,16 ,31 ,16 ,23 ,16 ,31 ,16 ,21 ,
21 ,21 ,21 ,31 ,16 ,23 ,16 ,23 ,16 ,31 ,0  ,0  ,0  ,1  ,1  ,31 ,
16 ,31 ,1  ,31 ,16 ,21 ,21 ,21 ,21 ,31 ,16 ,23 ,21 ,21 ,21 ,31 ,
16 ,29 ,5  ,29 ,16 ,31 ,16 ,31 ,16 ,23 ,16 ,31 ,16 ,23 ,21 ,23 ,
16 ,31 ,16 ,23 ,20 ,20 ,20 ,31 ,16 ,23 ,21 ,23 ,16 ,31 ,20 ,21 ,
21 ,21 ,16 ,31 ,20 ,21 ,21 ,21 ,16 ,31 ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,255,255,0  ,
0  ,255,255,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,255,255,0  ,
0  ,127,127,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,
96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,
96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,
96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,
96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,
96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,
96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,
96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,96 ,127,127,0  };

unsigned rom char num[70] = {
	0x00,0x3e,0x51,0x49,0x45,0x3e,0x00,	//0
	0x00,0x00,0x42,0x7f,0x40,0x00,0x00,	//1
	0x00,0x72,0x49,0x49,0x49,0x46,0x00,	//2
	0x00,0x22,0x49,0x49,0x49,0x36,0x00,	//3
	0x00,0x0f,0x08,0x08,0x7f,0x08,0x00,	//4
	0x00,0x2f,0x49,0x49,0x49,0x31,0x00,	//5
	0x00,0x3e,0x49,0x49,0x49,0x32,0x00,	//6
	0x00,0x41,0x21,0x11,0x09,0x07,0x00,	//7
	0x00,0x36,0x49,0x49,0x49,0x36,0x00,	//8
	0x00,0x26,0x49,0x49,0x49,0x3e,0x00};	//9 

unsigned rom char alpha[130] = {
	0x7c,0x0a,0x09,0x0a,0x7c,	//A
	0x7f,0x49,0x49,0x49,0x36,	//B
	0x3e,0x41,0x41,0x41,0x22,	//C
	0x7f,0x41,0x41,0x41,0x3e,	//D
	0x7f,0x49,0x49,0x49,0x41,	//E
	0x7f,0x09,0x09,0x09,0x01,	//F
	0x3e,0x41,0x49,0x49,0x3a,	//G
	0x7f,0x08,0x08,0x08,0x7f,	//H
	0x00,0x41,0x7f,0x41,0x00,	//I
	0x20,0x40,0x40,0x40,0x3f,	//J
	0x7f,0x08,0x14,0x22,0x41,	//K
	0x7f,0x40,0x40,0x40,0x40,	//L
	0x7f,0x02,0x04,0x02,0x7f,	//M
	0x7f,0x04,0x08,0x10,0x7f,	//N
	0x3e,0x41,0x41,0x41,0x3e,	//O
	0x7f,0x09,0x09,0x09,0x06,	//P
	0x3e,0x41,0x51,0x21,0x5e,	//Q
	0x7f,0x09,0x09,0x09,0x76,	//R
	0x26,0x49,0x49,0x49,0x32,	//S
	0x01,0x01,0x7f,0x01,0x01,	//T
	0x3f,0x40,0x40,0x40,0x3f,	//U
	0x1f,0x20,0x40,0x20,0x1f,	//V
	0x7f,0x20,0x10,0x20,0x7f,	//W
	0x63,0x14,0x08,0x14,0x63,	//X
	0x01,0x02,0x7c,0x02,0x01,	//Y
	0x61,0x51,0x49,0x45,0x43};	//Z

void main(void)
{
    char x,z;
    char y,q;

    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    ADCON1 = 0x0F;

    init();

    loadimg(&toplogo_bmp[0], 1024);             //Draw my logo(or start scren)

        CS1 = 1;    
        CS2 = 0;
        z = 0xB8 + 6;                           //Select Left Side and page 7
        cmd_write(z);  

        y = 0x40 + 0x1f;                        //Goto fist y position
        cmd_write(y);

    for(x=0;x<10;x++){                          //Loop through numbers
        q = load_num(&num[0],x,y,z);            //to show them all 0-9
        y = q;
    }

    while(1);
}

void load_char(rom char *image, char letter)
{
//To tired to write right now lol. 
//I will have this seperate tho
}

char load_num(rom char *image, char number,int y, char x)  //number = number , y = Pixel y, x = page
{
/*
TODO: Add code to determine if we reached last pixel on right site to add 1 to page and 
jumpt down . And use left side to continue. 

*/
    char i;
    char w = 7 * number;                    //w will be what number to print (7 bytes wide)

    image= image + w;                       //w = image location + w (which is 7* the number)

    for(i=0;i<7;i++){                       //Loop through 7 bytes 0-6

        if(y > 0x7F){                       //if we reached 80 thats last pixel 7 + 1 goto 
            CS1 = 0;                        //Right Side on
            CS2 = 1;                        //left side off
            cmd_write(x);                   //Right the page we are on
            cmd_write(0x40);                //Y pixel 0 on right side
            y = 0x40;                       //Set y = 0x40 (1st pixel)
        }

        data_write(*image);                 //Write to where ever we are at.
        image++;                            //add 1 to pointer position
        y++;                                //Add 1 to y
    }
    return y;                               //Return 1 so we can use it to check if we reached last pixel
}


void loadimg(rom char *image, unsigned int len)
{
    char i,x,y;

    int z = 0;
    while(z != len)            
    {

    for(i=0;i<8;i++){

        CS1 = 1;
        CS2 = 0;
        y = 0xB8 + i;
        cmd_write(y);  
        cmd_write(0x40);

        for(x=0;x<64;x++){
            if(z == len)
                break;
            data_write(*image);
            image++;
            z++;
        }

        CS1 = 0;
        CS2 = 1;
        y = 0xB8 + i;
        cmd_write(y);  
        cmd_write(0x40);

        for(x=0;x<64;x++){
            if(z == len)
                break;
            data_write(*image);
            image++;
            z++;
        }

        if(z == len)
            break;
    }
    if(z == len)
        break;
    
    }
}
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//////////////  Thank You Futz For Below  ///////////////////
//////////////////////// Code  //////////////////////////////
/////////////////////////////////////////////////////////////
void busy(void)
{
	unsigned char stat;
	glcd_tris = 0xff;						//portd all inputs
	DI = 0;
	RW = 1;
	if(CS1==1&&CS2==1)
	{
		CS1 = 0;
		do
		{
			E = 1;
			delay_us(1);
			stat = BSY;
			E = 0;
		}while(stat==0x80);
		CS1 = 1;
		CS2 = 0;
		do
		{
			E = 1;
			delay_us(1);
			stat = BSY;
			E = 0;
		}while(stat==0x80);
		CS2 = 1;
	}
	else
	{
		do
		{
			E = 1;
			delay_us(1);
			stat = BSY;
			E = 0;
		}while(stat==0x80);
	}
	glcd_tris = 0;
}

void cmd_write(unsigned char x)
{
	busy();
	DI = RW = 0;
	glcd_lat = x;
	e_togg();
}

void data_write(unsigned char x)
{
	busy();
	DI = 1;
    RW = 0;
	glcd_lat = x;
	e_togg();
}

void init(void)
{
	RS = 1;
	E = 0;
	CS1 = CS2 = 1;
	cmd_write(0x3f);			//turn on display
	cmd_write(0x40);			//go to left side
	cmd_write(0xb8);			//go to top page
	cls();						//clear the screen
}	

void e_togg(void)
{
	E = 1;
	delay_us(1);
	E = 0;
}

void cls(void)			//clear screen
{
	char x,y;
	CS1 = CS2 = 1;
	for(y=0;y<8;y++)		//page loop
	{
		cmd_write(0xb8 + y);
		for(x=0;x<64;x++)	//y loop
			data_write(0x00);
	}
	//cmd_write(0xc0);		//display start line = 0
	cmd_write(0x40);		//go to left side
	cmd_write(0xb8);		//go to top page
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void delay_s(unsigned char x)
{
    char var1;
	for(var1=0;var1<x;var1++)
	{				
        Delay10KTCYx(500);
	} 
}

void delay_ms(unsigned char x)
{
    char var1;
	for(var1=0;var1<x;var1++)
	{				
        Delay1KTCYx(5);
	} 
}

void delay_us(unsigned char x)
{
    char var1,y;
	for(var1=0;var1<x;var1++)
	{				
        for(y=0;y<5;y++)
            Delay1TCY();
	} 
}