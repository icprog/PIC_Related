#include <xc.h>
#include "glcd.h" 

unsigned char XPos,YPos,W;

void plot(unsigned char x,unsigned char y)
{
    unsigned char d;
	if(x>63)
    {
		b_GLCD_GCS1=0;
		b_GLCD_GCS2=1;
		x-=64;
	}
	else
	{
		b_GLCD_GCS1=1;
		b_GLCD_GCS2=0;
	}
	GLCD_Write_Cmd(0x40+x);			//write column address
	GLCD_Write_Cmd(0xb8+(y>>3));	//write row address
	d=GLCD_Read_Data();				//dummy read
	d=GLCD_Read_Data();
	GLCD_Write_Cmd(0x40+x);			//write column address again
	d=d&(0xff-(1<<(y&7)));
	GLCD_Write_Data(d);
}

void hline(unsigned char x,unsigned char y1,unsigned char y2)
{
    unsigned char i;
	for(i=y1;i<y2;i++)
    {
		plot(x,i);
    }
}

void vline(unsigned char x1,unsigned char x2,unsigned char y)
{
    unsigned char i;
	for(i=x1;i<x2;i++)
		plot(i,y);
}

void box(unsigned char x1,unsigned char y1,	unsigned char x2,unsigned char y2)
{
	vline(x1,x2,y1);
	vline(x1,x2,y2);
	hline(x1,y1,y2);
	hline(x2,y1,y2);
}

unsigned char GLCD_Read(void)
{
	b_GLCD_E=1;
	__delay_us(1);
	W=GLCD_Data;
	b_GLCD_E=0;
	return W;
}

void Wait_Not_Busy(void)
{
	TRIS_Data=0xff;
	b_GLCD_RS=0;
	b_GLCD_RW=1;
	if (b_GLCD_GCS1==1 && b_GLCD_GCS2==1)
    {
		b_GLCD_GCS1=0;
		while (GLCD_Read()&0x80);
		b_GLCD_GCS1=1;
		b_GLCD_GCS2=0;
		while (GLCD_Read()&0x80);
        {
		b_GLCD_GCS2=1;
        }
	}
	else{
		while (GLCD_Read()&0x80);
	}
	TRIS_Data=0x00;
}

void GLCD_Write_Cmd(unsigned char data)
{
	Wait_Not_Busy();
	GLCD_Data = data;
	b_GLCD_RS=0;
	b_GLCD_RW=0;
	b_GLCD_E=1;
	__delay_us(1);
	b_GLCD_E=0;
}

void GLCD_Write_Data (unsigned char data)
{
	Wait_Not_Busy();
	GLCD_Data = data;
	b_GLCD_RS=1;
	b_GLCD_RW=0;
	b_GLCD_E=1;
	__delay_us(1);
	b_GLCD_E=0;
}

void MoveRight(void)
{
	if(++XPos==64)
    {
		WritePosition();
	}
	if(XPos==128)
    {
		XPos=0;
		YPos+=8;
		YPos=YPos&0x3f;
		WritePosition();
	}
}

void WritePosition(void)
{
	if(XPos>63)
    {
		b_GLCD_GCS1=0;
		b_GLCD_GCS2=1;
	}
	else
    {
		b_GLCD_GCS1=1;
		b_GLCD_GCS2=0;
	}
	GLCD_Write_Cmd(0x40+(XPos&0x3f));	//column=0
	GLCD_Write_Cmd(0xb8+((YPos&0x3f)>>3));	//row=0	
}

unsigned char GLCD_Read_Data(void)
{
	Wait_Not_Busy();
	TRIS_Data=0xff;
	b_GLCD_RS=1;
	b_GLCD_RW=1;
	b_GLCD_E=1;
	__delay_us(1);
	W=GLCD_Data;
	b_GLCD_E=0;
	TRIS_Data=0x00;
	return W;
}

void ClearScreen(void)
{
    unsigned char i,j;
	b_GLCD_GCS1=1;
	b_GLCD_GCS2=1;	
	for(i=0;i<8;i++)
    {
		GLCD_Write_Cmd(0x40);	//y=0
		GLCD_Write_Cmd(0xb8+i);	//x=0
		for(j=0;j<0x40;j++)
        {
			GLCD_Write_Data(0xFF);
        }
	}
	SetPos(0,0);
}

void Init_GLCD(void)
{
    unsigned char i;

    b_TRIS_GCS1=0;
    b_TRIS_GCS2=0;
    b_TRIS_RS=0;
    b_TRIS_RW=0;
    b_TRIS_E=0;
    b_TRIS_On=0;
//    b_TRIS_BL=0;

    b_GLCD_On=1;
	b_GLCD_GCS1=1;
	b_GLCD_GCS2=1;
//    b_GLCD_BL=1;
	GLCD_Write_Cmd(0x3f);	//display on
	GLCD_Write_Cmd(0xc0);	//z=0
	ClearScreen();
}

void PutChar(unsigned char data)
{
    unsigned char i,d;
	if(data<32)
    {
		switch(data)
        {
			case 13:
				XPos=0;
			case 10:
				XPos=0;
				YPos+=8;
				YPos=YPos&63;
		}
		WritePosition();
	}
	else
    {
		for(i=0;i<7;i++)
        {
			d=Font[data-32][i];
			if(d!=0x55)
            {
				GLCD_Write_Data(d);
				MoveRight();
			}
		}
		GLCD_Write_Data(0xff);
		MoveRight();
	}
}

void PutMessage(unsigned char const *Message)
{
	while(*Message!=0) 
		if(*Message==0x16)
        {
			*Message++;
			XPos=*Message++;
			YPos=*Message++;
			WritePosition();
		}
		else
			PutChar(*Message++);
}	

void PutLogo(unsigned char const *logo)
{
    unsigned char i;
    unsigned char w,h,bitcount,Byte;
	w=*logo++;
	h=*logo++;
	bitcount=0;
	do{
		for(i=0;i<w;i++)
        {
			if(bitcount==0)
            {
				bitcount=8;
				Byte=*logo++;
			}
			if(Byte&1) plot(XPos,YPos);
			XPos++;
			Byte/=2;
			bitcount--;
		}
		YPos++;
		XPos-=w;
	}while(--h);
}

void SetPos(unsigned char x,unsigned char y)
{
	XPos=x;
	YPos=y;
	WritePosition();
}