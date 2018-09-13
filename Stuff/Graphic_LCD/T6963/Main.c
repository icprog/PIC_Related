#include "build/board.h"
#include "T6963C.h"
#include "graph.h"

extern void Init(void);

int main(void)
{
int i;
Init();

GLCD_Initalize();
GLCD_Clear_Graphic();
GLCD_Clear_Text();
GLCD_Clear_CG();

GLCD_Line(0,0, 239, 0);
GLCD_Line(0,0,0,63);
GLCD_Line(239,0, 239, 63);
GLCD_Line(239, 63, 0, 63);

GLCD_Circle(30,30,20);
GLCD_Line(30, 10, 30, 20);

GLCD_Circle(209,30,20);
GLCD_Line(209, 10, 209, 20);

GLCD_Rectangle(60, 6, 120, 48);

GLCD_Text_GoTo(13,1);
GLCD_Write_String("radzio.dxp.pl");

GLCD_Text_GoTo(13,3);
GLCD_Write_String("TOSHIBA T6963C");

GLCD_Text_GoTo(11,5);
GLCD_Write_String("AT91SAM7 & arm-gcc");

while(1);
return 0;
}