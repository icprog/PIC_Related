/*
Name                  : lcd_ks108.c
Funktionsumfang       : Funktionen zum Zugriff auf ein LC-Display mit einem
                        Samsung KS0108-Controller
*/
#include <string.h>
#include "lcd_ks108.h"
#include "f5x8.h"

unsigned char uchMarker = 0x00; //Position des Tastenmarkers fuer die 4 Hauptpunkte (Betrieb,Diagnose...)

/*
Name         :  LcdSetCS1
Beschreibung :  Steuerung der CS1 (linke Haelfte Display)
Parameter    :  ucLevel - 0 LOW / 1 HIGH (Leitung ist Low-Aktiv)
Rueckgabe    :  keine
*/
void LcdSetCS1(unsigned char ucLevel)
{
  if(ucLevel == TRUE)
    LCD_CTRL |= 0x10;
  else
    LCD_CTRL &= 0xEF;
}

/*
Name         :  LcdSetCS2
Beschreibung :  Steuerung der CS2 (rechte Haelfte Display)
Parameter    :  ucLevel - 0 LOW / 1 HIGH (Leitung ist Low-Aktiv)
Rueckgabe    :  keine
*/
void LcdSetCS2(unsigned char ucLevel)
{
  if(ucLevel == TRUE)
    LCD_CTRL |= 0x08;
  else
    LCD_CTRL &= 0xF7;
}

/*
Name         :  LcdSetE
Beschreibung :  Steuerung der E-Leitung
Parameter    :  ucLevel - 0 LOW / 1 HIGH (Leitung ist High-Aktiv)
Rueckgabe    :  keine
*/
void LcdSetE(unsigned char ucLevel)
{
  if(ucLevel == TRUE)
    LCD_CTRL |= 0x80;
  else
    LCD_CTRL &= 0x7F;
}

/*
Name         :  LcdSetRS
Beschreibung :  Steuerung der RS-Leitung
Parameter    :  ucLevel - 0 LOW / 1 HIGH (0 - Daten / 1 - Kommando)
Rueckgabe    :  keine
*/
void LcdSetRS (unsigned char ucLevel)
{
  if(ucLevel == TRUE)
    LCD_CTRL |= 0x20;
  else
    LCD_CTRL &= 0xDF;
}

/*
Name         :  LcdSetRW
Beschreibung :  Steuerung der RW-Leitung
Parameter    :  ucLevel - 0 LOW / 1 HIGH (0 - Schreiben / 1 - Lesen)
Rueckgabe    :  keine
*/
void LcdSetRW (unsigned char ucLevel)
{
  if(ucLevel == TRUE)
    LCD_CTRL |= 0x40;
  else
    LCD_CTRL &= 0xBF;
}

/*
Name         :  LcdReadStatus
Beschreibung :  Lesen des Statusbyte aus dem Display
Parameter    :  keine
Rueckgabe    :  Statusbyte (Bit 7 - BUSY / Bit 5 - ON/OFF / Bit 4 - RESET)
*/
unsigned char LcdReadStatus(void)
{
  unsigned char ucData = 0x00;

  LCD_DATA_DIR = INPUT;   //Datenleitungen auf Input
  LcdSetRW(HIGH);

  LcdSetRS(LOW);
  LcdSetE(HIGH);
  ucData = LCD_DATA;      //Status vom Bus lesen
  LcdSetE(LOW);
  LCD_DATA_DIR = OUTPUT;  //Datenleitungen auf Output
  return(ucData);
}

/*
Name         :  LcdWaitReady
Beschreibung :  Wartet bis im Statusbyte Bit 7 (BUSY) == 0 ist
Parameter    :  keine
Rueckgabe    :  keine
*/
void LcdWaitReady(void)
{
  while(LcdReadStatus() & 0x80 != 0);
}

/*
Name         :  LcdExec
Beschreibung :  Ausfuehren eines Schreib-Kommandos
Parameter    :  keine
Rueckgabe    :  keine
*/
void LcdExec(void)
{
  LcdSetRW(LOW);
  LcdSetE(HIGH);
  LcdSetE(LOW);
  LcdSetRW(HIGH);
}

/*
Name         :  LcdOnOff
Beschreibung :  Ein-/Ausschalten des Display
Parameter    :  ucLevel - 0 OFF / 1 ON
Rueckgabe    :  keine
*/
void LcdOnOff (unsigned char ucLevel)
{
  LcdWaitReady();

  if(ucLevel == TRUE)
    LCD_DATA = 0x3F;  //0b00111111
  else
    LCD_DATA = 0x3E;  //0b00111110

  LcdSetRS(INST);
  LcdExec();
}

/*
Name         :  LcdSetAdrY
Beschreibung :  Setzen der Y-Adresse
Parameter    :  uchAdrY - 0-63 (entspricht Display-Spalte)
Rueckgabe    :  keine
*/
void LcdSetAdrY(unsigned char uchAdrY)
{
  LcdWaitReady();
  //0x40 SetAdrY (s. KS0108-Datenblatt Display Control Instruction)
  //&0x2F ausmaskieren der unteren 6 Bit
  LCD_DATA = 0x40 | (uchAdrY & 0x3F);
  LcdSetRS(INST);
  LcdExec();
}

/*
Name         :  LcdSetAdrX
Beschreibung :  Setzen der aktiven Display-Page
Parameter    :  uchAdrX - 0-7 (entspricht Display-Zeile)
Rueckgabe    :  keine
*/
void LcdSetAdrX(unsigned char uchAdrX)
{
  LcdWaitReady();
  //0xB8 SetAdrX (s. KS0108-Datenblatt Display Control Instruction)
  //%0x07 ausmaskieren der unteren 3 Bit
  LCD_DATA = 0xB8 | (uchAdrX & 0x07);
  LcdSetRS(INST);
  LcdExec();
}

/*

Name         :  LcdSetAdrZ
Beschreibung :  Setzen der Z-Adresse (Startzeile)
Parameter    :  uchAdrZ - 0-63 (entspricht Zeile im Display)
Rueckgabe    :  keine
*/
void LcdSetAdrZ(unsigned char uchAdrZ)
{
  LcdWaitReady();

  //0xC0 SetAdrZ (s. KS0108-Datenblatt Display Control Instruction)
  //&0x3F ausmaskieren der unteren 6 Bit
  LCD_DATA = 0xC0 | (uchAdrZ & 0x3F);
  LcdSetRS(INST);
  LcdExec();
}

/*
Name         :  LcdWriteData
Beschreibung :  Schreiben eines Datenbytes an die aktuelle Adresse
                im Display-Ram
Parameter    :  ucData
Rueckgabe    :  keine
*/
void LcdWriteData(unsigned char uchData)
{
  LcdWaitReady();
  LCD_DATA = uchData;
  LcdSetRS(DATA);
  LcdExec();
}

/*
Name         :  LcdReadData
Beschreibung :  Lesen eines Datenbytes ab der aktuellen Adresse
                aus dem Display-Ram
Parameter    :  keine
Rueckgabe    :  gelesenes Datenbyte
*/
unsigned char LcdReadData(void)
{
  unsigned char uchData;

  LcdWaitReady();
  LCD_DATA_DIR = INPUT;
  LcdSetRW(HIGH);
  LcdSetRS(HIGH);
  //dummy read s. KS0108-Datenblatt 'Operation Principles & Methods 3. Output register
  LcdSetE(HIGH);
  LcdSetE(LOW);
  LCD_DATA_DIR = OUTPUT;

  LcdWaitReady();
  LCD_DATA_DIR = INPUT;
  LcdSetRW(HIGH);
  LcdSetRS(HIGH);
  //dummy read s. KS0108-Datenblatt 'Operation Principles & Methods 3. Output register
  LcdSetE(HIGH);
  uchData = LCD_DATA;
  LcdSetE(LOW);
  LCD_DATA_DIR = OUTPUT;
  return(uchData);
}

/*
Name         :  LcdClear
Beschreibung :  Loeschen des Display-Ram (leeren der Anzeige)
Parameter    :  keine
Rueckgabe    :  keine
*/
void LcdClear(void)
{
  unsigned int i,j;

  LcdWaitReady();
  LcdSetCS1(LOW); //aktivieren beider Display-Haelften
  LcdSetCS2(LOW);
  LcdSetAdrY(0x00);
  LcdSetAdrX(0x00);
  LcdSetAdrZ(0x00);
  for(j=0;j<8;j++)  //8 Zeilen
  {
    LcdSetAdrX(j);
    for(i=0;i<64;i++) //64 Spalten
      LcdWriteData(0x00);
  }
}

/*
Name         :  LcdInit
Beschreibung :  Initialisieren des Display
Parameter    :  keine
Rueckgabe    :  keine
*/
void LcdInit(void)
{
  LCD_DATA_DIR = OUTPUT;    //Datenport fuer Datenleitungen auf Output
  LCD_DATA_PULL = INACTIVE; //keine Pullup-Wiederstaende aktivieren

  LCD_CTRL_DIR = OUTPUT;    //Datenport fuer Steuerleitungen
  LCD_CTRL = 0x00;          //??alle Datenleitgunen auf LOW

  LcdClear();               //Anzeige loeschen
  LcdOnOff(ON);             //Display einschalten
}

/*
Name         :  LcdWriteString
Beschreibung :  Ausgabe eines Textstring in einer Displayzeile
Parameter    :  uchPosX - X-Position ab der die Ausgabe erfolgen soll (0-127)
                uchPosY - Y-Position ab der die Ausgabe erfolgen soll (0-7)
                *uchText - Zeiger auf den auszugebenden Textstring (nullterminiert)
Rueckgabe    :  keine
*/
void LcdWriteString(unsigned char uchPosX,unsigned char uchPosY,unsigned char *puchText,unsigned char uchXMax,unsigned char uchStyle)
{
  unsigned char auchTemp[30];
  unsigned char uchHalf = 0x00;
  unsigned char uchLine = 0x00;
  unsigned char i,j;
    
  LcdSetCS1(LOW);
  LcdSetCS2(HIGH);
  LcdSetAdrX(uchPosY);
  LcdSetAdrY(uchPosX);
  LcdSetAdrZ(0x00);    

  strncpy(auchTemp,puchText,29);
  auchTemp[29]='\0';
  for(i=strlen(auchTemp);i<29;i++)
    strcat(auchTemp," ");
    
  if(uchStyle == INVERS)
    LcdWriteData(0xFF);
  else
    LcdWriteData(0x00);
  
  uchHalf = 0x00;
  for(i=0;i<strlen(auchTemp);i++)
  {
    for(j=0;j<=5;j++)
    {
      if(uchPosX+i*6+j+1 >= 0x40 && uchHalf == 0x00)  //Cursorposition in der Mitte ?
      {
        uchHalf = 0x01; //Flag fuer Anzeigenhaelfte auf rechte Haelfte
        LcdSetCS1(HIGH);  //Chip-Select auf rechte Haelfte wechseln
        LcdSetCS2(LOW);
        LcdSetAdrX(uchPosY); 
        LcdSetAdrY(uchPosX+i*6+j+1-0x40); //Cursorposition in rechter Haelfte anpassen
      }

      if(uchXMax >= 0x40)
      {
        if(uchPosX+i*6+j+1 > uchXMax && uchHalf == 0x01)  //Cursorposition am Ende rechte Haelfte ?
          return; //keine Daten mehr schreiben
      }
      else
      {
        if(uchPosX+i*6+j+1 > uchXMax && uchHalf == 0x00)  //Cursorposition am Ende linke Haelfte ?
          return;  //keine Daten mehr schreiben
      }

      if(uchStyle != INVERS)
        LcdWriteData(font[auchTemp[i]-0x1B][j]);
      else
        LcdWriteData(~font[auchTemp[i]-0x1B][j]); //fuer inverse Darstellung Grafikdaten negieren
    }
  }  
}

/*
Name         :  LcdSetPoint
Beschreibung :  Setzen eines Pixels im Display
Parameter    :  uchPosX - X-Position an der der Punkt gesetzt werden soll (0-128)
                uchPosY - Y-Position an der der Punkt gesetzt werden soll (0-63)
Rueckgabe    :  keine
*/
void LcdSetPoint(unsigned char uchPosX,unsigned char uchPosY)
{
  unsigned char uchData;

  if(uchPosX >= 0x80 || uchPosY >= 0x40)
    return;  
  if(uchPosX >= 0x40) //X-Position in der zweiten Anzeigehaelfte
  {
    LcdSetCS1(HIGH);
    LcdSetCS2(LOW);
    uchPosX -= 0x40;  //X-Position korregieren
  }
  else
  {
    LcdSetCS1(LOW);
    LcdSetCS2(HIGH);
  }
  
  LcdSetAdrZ(0x00);
  LcdSetAdrY(uchPosX);
  LcdSetAdrX(uchPosY / 8);
  uchData = LcdReadData() | (1 << (uchPosY % 8)); //aktuelle Daten aus Display lesen

  LcdSetAdrZ(0x00);
  LcdSetAdrY(uchPosX);
  LcdSetAdrX(uchPosY / 8);
  LcdWriteData(uchData);
}

/*
Name         :  LcdClearPoint
Beschreibung :  Loeschen eines Pixels im Display
Parameter    :  uchPosX - X-Position an der der Punkt gesetzt werden soll (0-128)
                uchPosY - Y-Position an der der Punkt gesetzt werden soll (0-63)
Rueckgabe    :  keine
*/
void LcdClearPoint(unsigned char uchPosX,unsigned char uchPosY)
{
  unsigned char uchData;

  if(uchPosX >= 0x80 || uchPosY >= 0x40)
    return;  
  if(uchPosX >= 0x40) //X-Position in der zweiten Anzeigehaelfte
  {
    LcdSetCS1(HIGH);
    LcdSetCS2(LOW);
    uchPosX -= 0x40;  //X-Position korregieren
  }
  else
  {
    LcdSetCS1(LOW);
    LcdSetCS2(HIGH);
  }
  
  LcdSetAdrZ(0x00);
  LcdSetAdrY(uchPosX);
  LcdSetAdrX(uchPosY / 8);
  uchData = LcdReadData() & ~(1 << (uchPosY % 8)); //aktuelle Daten aus Display lesen

  LcdSetAdrZ(0x00);
  LcdSetAdrY(uchPosX);
  LcdSetAdrX(uchPosY / 8);
  LcdWriteData(uchData);
}

/*
Name         :  LcdSetLine
Beschreibung :  Setzen einer Linie im Display
Parameter    :  uchPosStartX - Start X-Position an der der Punkt gesetzt werden soll (0-128)
                uchPosStartY - Start Y-Position an der der Punkt gesetzt werden soll (0-63)
                uchPosEndX   - Start X-Position an der der Punkt gesetzt werden soll (0-128)
                uchPosEndY   - Start Y-Position an der der Punkt gesetzt werden soll (0-63)
Rueckgabe    :  keine
Kommentar    :  Nur senkrechte oder waagerechte Linien
                StartX bzw. StartY muss kleiner sein als EndX bzw. EndY
*/
void LcdSetLine(unsigned char uchPosStartX,unsigned char uchPosStartY,unsigned char uchPosEndX,unsigned char uchPosEndY)
{
  if(uchPosStartX == uchPosEndX)
  {
    for(;uchPosStartY<=uchPosEndY;uchPosStartY++)
      LcdSetPoint(uchPosStartX,uchPosStartY);
  }
  else
  {
    for(;uchPosStartX<=uchPosEndX;uchPosStartX++)
      LcdSetPoint(uchPosStartX,uchPosStartY);
  }
}

/*
Name         :  LcdClearLine
Beschreibung :  Loeschen einer Linie im Display
Parameter    :  uchPosStartX - Start X-Position an der der Punkt gesetzt werden soll (0-128)
                uchPosStartY - Start Y-Position an der der Punkt gesetzt werden soll (0-63)
                uchPosEndX   - Start X-Position an der der Punkt gesetzt werden soll (0-128)
                uchPosEndY   - Start Y-Position an der der Punkt gesetzt werden soll (0-63)
Rueckgabe    :  keine
Kommentar    :  Nur senkrechte oder waagerechte Linien
                StartX bzw. StartY muss kleiner sein als EndX bzw. EndY
*/
void LcdClearLine(unsigned char uchPosStartX,unsigned char uchPosStartY,unsigned char uchPosEndX,unsigned char uchPosEndY)
{
  if(uchPosStartX == uchPosEndX)
  {
    for(;uchPosStartY<=uchPosEndY;uchPosStartY++)
      LcdClearPoint(uchPosStartX,uchPosStartY);
  }
  else
  {
    for(;uchPosStartX<=uchPosEndX;uchPosStartX++)
      LcdClearPoint(uchPosStartX,uchPosStartY);
  }
}

void LcdSetByte(unsigned char uchPosX,unsigned char uchPosY,unsigned char uchData)
{
  if(uchPosX >= 0x80 || uchPosY >= 0x40)
    return;  

  if(uchPosX >= 0x40) //X-Position in der zweiten Anzeigehaelfte
  {
    LcdSetCS1(HIGH);
    LcdSetCS2(LOW);
    uchPosX -= 0x40;  //X-Position korregieren
  }
  else
  {
    LcdSetCS1(LOW);
    LcdSetCS2(HIGH);
  }
  
  LcdSetAdrZ(0x00);
  LcdSetAdrY(uchPosX);
  LcdSetAdrX(uchPosY / 8);

  LcdWriteData(uchData);
}
