//Dog.bmp, Font Table in 8 Font.
//72 x 64 matrix
//Is different from normal bmp hex data dump, this array runs
//in 8 font cells, with convenience for CG RAM character def.
//Data converted by shareware FastLCD designer by Bojan I. MICRODESIGN, version 1.2.0

const UCHAR Dog_row1[72]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//1st CG character, 0 row, 0 col 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//2nd CG character, 0 row, 1 col
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//3rd
0x01,0x03,0x06,0x0C,0x38,0x79,0x78,0xF8,	//4th
0xF8,0xCF,0x07,0x03,0xC7,0xE6,0xC3,0x06,	//5
0x70,0xFC,0x8E,0x07,0x01,0x31,0x79,0x31,	//6
0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,	//7
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//8
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00		//9th CG character, 0 row, 8 col
};

const UCHAR Dog_row2[72]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//10th CG Character, 1 row, 0 col
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x03,0x07,0x07,0x0F,0x3F,0x3F,0x7E,0x7E,
0xF8,0xFC,0xE7,0xF7,0xC1,0x03,0x23,0x61,
0x1F,0x1F,0xFF,0xFF,0x83,0xFF,0xFF,0xFF,
0x01,0x81,0x81,0xE3,0x9C,0xE7,0xE1,0xC4,
0xF8,0xF8,0xFC,0xFC,0x7F,0x7F,0xBF,0xBF,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const UCHAR Dog_row3[72]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x01,0x03,0x03,0x03,0x03,0x03,
0xFC,0xFC,0xFC,0xFE,0xFF,0xFF,0xEF,0xEF,
0x08,0x00,0x20,0x04,0x00,0x80,0xE0,0x7F,
0xFF,0x08,0x00,0x00,0x00,0x00,0x00,0xF8,
0x80,0x08,0x02,0x10,0x01,0x01,0x03,0xFF,
0x5F,0x5F,0x5F,0x5F,0xDE,0x9E,0x9E,0x1E,
0xF0,0xF0,0xF8,0xFC,0x7E,0x3E,0x3F,0x3F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const UCHAR Dog_row4[72]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x03,0x03,0x03,0x03,0x03,0x01,0x00,0x00,
0xE7,0xE7,0xE7,0xF7,0xFF,0xFF,0xFF,0xFE,
0x84,0x84,0x84,0x84,0x88,0x08,0x08,0x08,
0x07,0x07,0x06,0x02,0x06,0x06,0x06,0x06,
0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x1E,0x1E,0x1E,0x1E,0x1F,0x1F,0x0F,0x0F,
0x1F,0x1F,0x1F,0x1F,0x7F,0xFF,0xFF,0xFF,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00
};

const UCHAR Dog_row5[72]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x03,
0x10,0x10,0x30,0xB0,0x80,0x00,0x00,0x60,
0x04,0x04,0x04,0x07,0x01,0x00,0x06,0x07,
0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xC0,
0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0xFE,0xFC,0xF8,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const UCHAR Dog_row6[72]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x03,0x07,0x06,0x06,0x06,
0x02,0x02,0xC6,0xFC,0x06,0x03,0x01,0x00,
0x60,0x63,0xCF,0xFC,0xC0,0x80,0x80,0x80,
0x01,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,
0xC3,0xC7,0xCC,0xE8,0x30,0x30,0x10,0x00,
0xFC,0x06,0x06,0x02,0x01,0x01,0x03,0x02,
0x00,0x0F,0x1F,0x72,0xCF,0x9F,0x1F,0x1F,
0x00,0xC0,0xE0,0x30,0x50,0xF8,0xF8,0xF8
};

const UCHAR Dog_row7[72]=
{
0x00,0x03,0x0F,0x3D,0x77,0x67,0x6F,0x6F,
0x06,0xFA,0xFF,0xE7,0xF8,0xF8,0xF8,0x0F,
0x00,0x00,0x00,0x80,0x21,0x01,0x00,0xC0,
0x00,0x00,0x00,0x0F,0x7F,0xE0,0x80,0x80,
0x00,0x00,0x20,0xB0,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0xF0,0x0F,0x01,0x00,0x00,
0x04,0x04,0x00,0x08,0x80,0xC0,0x70,0x38,
0x0F,0x1F,0x3F,0x3F,0x7F,0x7E,0x7E,0x7C,
0xF8,0xF0,0x90,0x10,0x20,0x60,0xC0,0xC0
};

const UCHAR Dog_row8[72]=
{
0x3F,0x1F,0x0F,0x06,0x01,0x00,0x00,0x00,
0x9F,0x9F,0x9F,0x0F,0xE1,0x78,0x1F,0x07,
0xF8,0xFC,0xFE,0xFE,0xFC,0x10,0x01,0xFF,
0x60,0x20,0x30,0x30,0x30,0x70,0xE0,0xC0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x06,0x03,0x01,0x00,0x00,0x00,0x00,0x00,
0x13,0xEE,0xFC,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
