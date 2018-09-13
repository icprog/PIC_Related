#line 1 "C:/Documents and Settings/Administrator/Desktop/Microcontroller Stuff/My mikroC Projects/PIC12F683/SerialLCD/SerialLcdTestforELab.c"
#line 5 "C:/Documents and Settings/Administrator/Desktop/Microcontroller Stuff/My mikroC Projects/PIC12F683/SerialLCD/SerialLcdTestforELab.c"
sbit Data_Pin at GP5_bit;
sbit Clk_Pin at GP1_bit;
sbit Enable_Pin at GP2_bit;


unsigned short Low_Nibble, High_Nibble, p, q, Mask, N,t, RS, Flag, temp;

void Delay_50ms(){
 Delay_ms(50);
}

void Write_LCD_Nibble(unsigned short N){
 Enable_Pin = 0;

 Clk_Pin = 0;
 Data_Pin = RS;
 Clk_Pin = 1;
 Clk_Pin = 0;



 Mask = 8;
 for (t=0; t<4; t++){
 Flag = N & Mask;
 if(Flag==0) Data_Pin = 0;
 else Data_Pin = 1;
 Clk_Pin = 1;
 Clk_Pin = 0;
 Mask = Mask >> 1;
 }

 Clk_Pin = 1;
 Clk_Pin = 0;
 Data_Pin = 0;
 Enable_Pin = 1;
 Enable_Pin = 0;
}


 void Write_LCD_Data(unsigned short D){
 RS = 1;
 Low_Nibble = D & 15;
 High_Nibble = D/16;
 Write_LCD_Nibble(High_Nibble);
 Write_LCD_Nibble(Low_Nibble);
 }

void Write_LCD_Cmd(unsigned short C){
 RS = 0;
 Low_Nibble = C & 15;
 High_Nibble = C/16;
 Write_LCD_Nibble(High_Nibble);
 Write_LCD_Nibble(Low_Nibble);
}

void Initialize_LCD(){
 Delay_50ms();
 Write_LCD_Cmd(0x20);
 Delay_50ms();
 Write_LCD_Cmd(0x20);
 Delay_50ms();
 Write_LCD_Cmd(0x20);
 Delay_50ms();
 Write_LCD_Cmd(0x28);
 Delay_50ms();
 Write_LCD_Cmd(0x0C);
 Delay_50ms();
 Write_LCD_Cmd(0x06);
 Delay_50ms();
 Write_LCD_Cmd(0x01);
 Delay_50ms();
}

void Position_LCD(unsigned short x, unsigned short y){
 temp = 127 + y;
 if (x == 2) temp = temp + 64;
 Write_LCD_Cmd(temp);
}

void Write_LCD_Text(char *StrData){
 q = strlen(StrData);
 for (p = 0; p<q; p++){
 temp = StrData[p];
 Write_LCD_Data(temp);
 }

}

char Message1[] = "3-Wire LCD";
char Message2[] = "using 74HC595";

void main() {
CMCON0 = 7;
TRISIO = 0b00001000;
ANSEL = 0x00;

Initialize_LCD();

do {
 Position_LCD(1,4);
 Write_LCD_Text(Message1);
 Position_LCD(2,2);
 Write_LCD_Text(Message2);
 Delay_ms(1500);
 Write_LCD_Cmd(0x01);
 delay_ms(1000);
} while(1);

}
