#include    "system.h" 
#include <stdio.h>
#include <stdlib.h>
#include "spi_pic.h"
#include "ili9341.h"
//#include "font.h"
//#include "bitmap.h"

void main(void)
{
    Init();
    int i;
    char buffer1[20];
//ADCON1 = 15;
    SPI1_Close();
    SPI1_Init();
    TFT_Init();

    TFT_SetDotSize(1);
    TFT_RectangleRound(5, 115, 234, 314, 10, BLACK);
//    TFT_SetFont(Courier_New_Bold_20, 1);
/*    TFT_ConstText("TFT 240x320", 20, 10, BLACK, WHITE);
    TFT_ConstText("Driver ILI9341", 20, 34, BLACK, WHITE);
    TFT_ConstText("Interface: SPI", 20, 58, BLACK, WHITE);
    TFT_ConstText("Version",20, 82, BLACK, WHITE);
    __delay_ms(1000);
    TFT_WriteChar('>', 0, 10, BLACK, WHITE); TFT_ConstText("TFT 240x320", 20, 10, WHITE, BLACK); __delay_ms(800);
    TFT_WriteChar('>', 0, 10, WHITE, WHITE); TFT_ConstText("TFT 240x320", 20, 10, BLACK, WHITE); 
    TFT_WriteChar('>', 0, 34, BLACK, WHITE); TFT_ConstText("Driver ILI9341", 20, 34, WHITE, BLACK); __delay_ms(800);
    TFT_WriteChar('>', 0, 34, WHITE, WHITE); TFT_ConstText("Driver ILI9341", 20, 34, BLACK, WHITE);
    TFT_WriteChar('>', 0, 58, BLACK, WHITE); TFT_ConstText("Interface: SPI", 20, 58, WHITE, BLACK); __delay_ms(800);
    TFT_WriteChar('>', 0, 58, WHITE, WHITE); TFT_ConstText("Interface: SPI", 20, 58, BLACK, WHITE);
    TFT_WriteChar('>', 0, 82, BLACK, WHITE); TFT_ConstText("Version", 20, 82, WHITE, BLACK); __delay_ms(800);
    
    for(i = 31; i > 1; i--)
       {
        sprintf(buffer1, "Version%3d ", i);
        TFT_Text(buffer1, 20, 82, WHITE, BLACK);
        __delay_ms(200);
    }
*/
    TFT_Box(33, 150, 63, 180, RED);
    TFT_Box(103, 150, 133, 180, GREEN);
    TFT_Box(173, 150, 203, 180, BLUE);

    TFT_Circle(48, 165, 26, BLACK);
    TFT_RectangleRound(93, 140, 143, 190, 10, BLACK);
    TFT_Rectangle(163, 140, 213, 190, BLACK);

//    TFT_Icon(icon1, 20, 220, 64, 64);

    TFT_SetDotSize(3);
    TFT_RectangleRound(93, 210, 213, 300, 10, BLACK);

    TFT_SetDotSize(0);
    TFT_Line(93, 255, 213, 255, BLACK);
    TFT_Line(153, 210, 153, 300, BLACK);

    while(1)
    {
    }
}