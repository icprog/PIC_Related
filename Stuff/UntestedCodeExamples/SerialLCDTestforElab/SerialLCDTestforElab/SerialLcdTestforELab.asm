
_Delay_50ms:
;SerialLcdTestforELab.c,12 :: 		void Delay_50ms(){
;SerialLcdTestforELab.c,13 :: 		Delay_ms(50);
	MOVLW      65
	MOVWF      R12+0
	MOVLW      238
	MOVWF      R13+0
L_Delay_50ms0:
	DECFSZ     R13+0, 1
	GOTO       L_Delay_50ms0
	DECFSZ     R12+0, 1
	GOTO       L_Delay_50ms0
	NOP
;SerialLcdTestforELab.c,14 :: 		}
	RETURN
; end of _Delay_50ms

_Write_LCD_Nibble:
;SerialLcdTestforELab.c,16 :: 		void Write_LCD_Nibble(unsigned short N){
;SerialLcdTestforELab.c,17 :: 		Enable_Pin = 0;
	BCF        GP2_bit+0, 2
;SerialLcdTestforELab.c,19 :: 		Clk_Pin = 0;
	BCF        GP1_bit+0, 1
;SerialLcdTestforELab.c,20 :: 		Data_Pin = RS;
	BTFSC      _RS+0, 0
	GOTO       L__Write_LCD_Nibble14
	BCF        GP5_bit+0, 5
	GOTO       L__Write_LCD_Nibble15
L__Write_LCD_Nibble14:
	BSF        GP5_bit+0, 5
L__Write_LCD_Nibble15:
;SerialLcdTestforELab.c,21 :: 		Clk_Pin = 1;
	BSF        GP1_bit+0, 1
;SerialLcdTestforELab.c,22 :: 		Clk_Pin = 0;
	BCF        GP1_bit+0, 1
;SerialLcdTestforELab.c,26 :: 		Mask = 8;
	MOVLW      8
	MOVWF      _Mask+0
;SerialLcdTestforELab.c,27 :: 		for (t=0; t<4; t++){
	CLRF       _t+0
L_Write_LCD_Nibble1:
	MOVLW      4
	SUBWF      _t+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_Write_LCD_Nibble2
;SerialLcdTestforELab.c,28 :: 		Flag = N & Mask;
	MOVF       _Mask+0, 0
	ANDWF      FARG_Write_LCD_Nibble_N+0, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	MOVWF      _Flag+0
;SerialLcdTestforELab.c,29 :: 		if(Flag==0) Data_Pin = 0;
	MOVF       R1+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_Write_LCD_Nibble4
	BCF        GP5_bit+0, 5
	GOTO       L_Write_LCD_Nibble5
L_Write_LCD_Nibble4:
;SerialLcdTestforELab.c,30 :: 		else Data_Pin = 1;
	BSF        GP5_bit+0, 5
L_Write_LCD_Nibble5:
;SerialLcdTestforELab.c,31 :: 		Clk_Pin = 1;
	BSF        GP1_bit+0, 1
;SerialLcdTestforELab.c,32 :: 		Clk_Pin = 0;
	BCF        GP1_bit+0, 1
;SerialLcdTestforELab.c,33 :: 		Mask = Mask >> 1;
	RRF        _Mask+0, 1
	BCF        _Mask+0, 7
;SerialLcdTestforELab.c,27 :: 		for (t=0; t<4; t++){
	INCF       _t+0, 1
;SerialLcdTestforELab.c,34 :: 		}
	GOTO       L_Write_LCD_Nibble1
L_Write_LCD_Nibble2:
;SerialLcdTestforELab.c,36 :: 		Clk_Pin = 1;
	BSF        GP1_bit+0, 1
;SerialLcdTestforELab.c,37 :: 		Clk_Pin = 0;
	BCF        GP1_bit+0, 1
;SerialLcdTestforELab.c,38 :: 		Data_Pin = 0;
	BCF        GP5_bit+0, 5
;SerialLcdTestforELab.c,39 :: 		Enable_Pin = 1;
	BSF        GP2_bit+0, 2
;SerialLcdTestforELab.c,40 :: 		Enable_Pin = 0;
	BCF        GP2_bit+0, 2
;SerialLcdTestforELab.c,41 :: 		}
	RETURN
; end of _Write_LCD_Nibble

_Write_LCD_Data:
;SerialLcdTestforELab.c,44 :: 		void Write_LCD_Data(unsigned short D){
;SerialLcdTestforELab.c,45 :: 		RS = 1; // It is Data, not command
	MOVLW      1
	MOVWF      _RS+0
;SerialLcdTestforELab.c,46 :: 		Low_Nibble = D & 15;
	MOVLW      15
	ANDWF      FARG_Write_LCD_Data_D+0, 0
	MOVWF      _Low_Nibble+0
;SerialLcdTestforELab.c,47 :: 		High_Nibble = D/16;
	MOVF       FARG_Write_LCD_Data_D+0, 0
	MOVWF      R0+0
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	MOVF       R0+0, 0
	MOVWF      _High_Nibble+0
;SerialLcdTestforELab.c,48 :: 		Write_LCD_Nibble(High_Nibble);
	MOVF       R0+0, 0
	MOVWF      FARG_Write_LCD_Nibble_N+0
	CALL       _Write_LCD_Nibble+0
;SerialLcdTestforELab.c,49 :: 		Write_LCD_Nibble(Low_Nibble);
	MOVF       _Low_Nibble+0, 0
	MOVWF      FARG_Write_LCD_Nibble_N+0
	CALL       _Write_LCD_Nibble+0
;SerialLcdTestforELab.c,50 :: 		}
	RETURN
; end of _Write_LCD_Data

_Write_LCD_Cmd:
;SerialLcdTestforELab.c,52 :: 		void Write_LCD_Cmd(unsigned short C){
;SerialLcdTestforELab.c,53 :: 		RS = 0; // It is command, not data
	CLRF       _RS+0
;SerialLcdTestforELab.c,54 :: 		Low_Nibble = C & 15;
	MOVLW      15
	ANDWF      FARG_Write_LCD_Cmd_C+0, 0
	MOVWF      _Low_Nibble+0
;SerialLcdTestforELab.c,55 :: 		High_Nibble = C/16;
	MOVF       FARG_Write_LCD_Cmd_C+0, 0
	MOVWF      R0+0
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	MOVF       R0+0, 0
	MOVWF      _High_Nibble+0
;SerialLcdTestforELab.c,56 :: 		Write_LCD_Nibble(High_Nibble);
	MOVF       R0+0, 0
	MOVWF      FARG_Write_LCD_Nibble_N+0
	CALL       _Write_LCD_Nibble+0
;SerialLcdTestforELab.c,57 :: 		Write_LCD_Nibble(Low_Nibble);
	MOVF       _Low_Nibble+0, 0
	MOVWF      FARG_Write_LCD_Nibble_N+0
	CALL       _Write_LCD_Nibble+0
;SerialLcdTestforELab.c,58 :: 		}
	RETURN
; end of _Write_LCD_Cmd

_Initialize_LCD:
;SerialLcdTestforELab.c,60 :: 		void Initialize_LCD(){
;SerialLcdTestforELab.c,61 :: 		Delay_50ms();
	CALL       _Delay_50ms+0
;SerialLcdTestforELab.c,62 :: 		Write_LCD_Cmd(0x20); // Wake-Up Sequence
	MOVLW      32
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,63 :: 		Delay_50ms();
	CALL       _Delay_50ms+0
;SerialLcdTestforELab.c,64 :: 		Write_LCD_Cmd(0x20);
	MOVLW      32
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,65 :: 		Delay_50ms();
	CALL       _Delay_50ms+0
;SerialLcdTestforELab.c,66 :: 		Write_LCD_Cmd(0x20);
	MOVLW      32
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,67 :: 		Delay_50ms();
	CALL       _Delay_50ms+0
;SerialLcdTestforELab.c,68 :: 		Write_LCD_Cmd(0x28); // 4-bits, 2 lines, 5x7 font
	MOVLW      40
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,69 :: 		Delay_50ms();
	CALL       _Delay_50ms+0
;SerialLcdTestforELab.c,70 :: 		Write_LCD_Cmd(0x0C); // Display ON, No cursors
	MOVLW      12
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,71 :: 		Delay_50ms();
	CALL       _Delay_50ms+0
;SerialLcdTestforELab.c,72 :: 		Write_LCD_Cmd(0x06); // Entry mode- Auto-increment, No Display shifting
	MOVLW      6
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,73 :: 		Delay_50ms();
	CALL       _Delay_50ms+0
;SerialLcdTestforELab.c,74 :: 		Write_LCD_Cmd(0x01);
	MOVLW      1
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,75 :: 		Delay_50ms();
	CALL       _Delay_50ms+0
;SerialLcdTestforELab.c,76 :: 		}
	RETURN
; end of _Initialize_LCD

_Position_LCD:
;SerialLcdTestforELab.c,78 :: 		void Position_LCD(unsigned short x, unsigned short y){
;SerialLcdTestforELab.c,79 :: 		temp = 127 + y;
	MOVF       FARG_Position_LCD_y+0, 0
	ADDLW      127
	MOVWF      _temp+0
;SerialLcdTestforELab.c,80 :: 		if (x == 2) temp = temp + 64;
	MOVF       FARG_Position_LCD_x+0, 0
	XORLW      2
	BTFSS      STATUS+0, 2
	GOTO       L_Position_LCD6
	MOVLW      64
	ADDWF      _temp+0, 1
L_Position_LCD6:
;SerialLcdTestforELab.c,81 :: 		Write_LCD_Cmd(temp);
	MOVF       _temp+0, 0
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,82 :: 		}
	RETURN
; end of _Position_LCD

_Write_LCD_Text:
;SerialLcdTestforELab.c,84 :: 		void Write_LCD_Text(char *StrData){
;SerialLcdTestforELab.c,85 :: 		q = strlen(StrData);
	MOVF       FARG_Write_LCD_Text_StrData+0, 0
	MOVWF      FARG_strlen_s+0
	CALL       _strlen+0
	MOVF       R0+0, 0
	MOVWF      _q+0
;SerialLcdTestforELab.c,86 :: 		for (p = 0; p<q; p++){
	CLRF       _p+0
L_Write_LCD_Text7:
	MOVF       _q+0, 0
	SUBWF      _p+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_Write_LCD_Text8
;SerialLcdTestforELab.c,87 :: 		temp = StrData[p];
	MOVF       _p+0, 0
	ADDWF      FARG_Write_LCD_Text_StrData+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      _temp+0
;SerialLcdTestforELab.c,88 :: 		Write_LCD_Data(temp);
	MOVF       R0+0, 0
	MOVWF      FARG_Write_LCD_Data_D+0
	CALL       _Write_LCD_Data+0
;SerialLcdTestforELab.c,86 :: 		for (p = 0; p<q; p++){
	INCF       _p+0, 1
;SerialLcdTestforELab.c,89 :: 		}
	GOTO       L_Write_LCD_Text7
L_Write_LCD_Text8:
;SerialLcdTestforELab.c,91 :: 		}
	RETURN
; end of _Write_LCD_Text

_main:
;SerialLcdTestforELab.c,96 :: 		void main() {
;SerialLcdTestforELab.c,97 :: 		CMCON0 = 7;  // Disable Comparators
	MOVLW      7
	MOVWF      CMCON0+0
;SerialLcdTestforELab.c,98 :: 		TRISIO = 0b00001000;  // All Outputs except GP3
	MOVLW      8
	MOVWF      TRISIO+0
;SerialLcdTestforELab.c,99 :: 		ANSEL = 0x00; // No analog i/p
	CLRF       ANSEL+0
;SerialLcdTestforELab.c,101 :: 		Initialize_LCD();
	CALL       _Initialize_LCD+0
;SerialLcdTestforELab.c,103 :: 		do {
L_main10:
;SerialLcdTestforELab.c,104 :: 		Position_LCD(1,4);
	MOVLW      1
	MOVWF      FARG_Position_LCD_x+0
	MOVLW      4
	MOVWF      FARG_Position_LCD_y+0
	CALL       _Position_LCD+0
;SerialLcdTestforELab.c,105 :: 		Write_LCD_Text(Message1);
	MOVLW      _Message1+0
	MOVWF      FARG_Write_LCD_Text_StrData+0
	CALL       _Write_LCD_Text+0
;SerialLcdTestforELab.c,106 :: 		Position_LCD(2,2);
	MOVLW      2
	MOVWF      FARG_Position_LCD_x+0
	MOVLW      2
	MOVWF      FARG_Position_LCD_y+0
	CALL       _Position_LCD+0
;SerialLcdTestforELab.c,107 :: 		Write_LCD_Text(Message2);
	MOVLW      _Message2+0
	MOVWF      FARG_Write_LCD_Text_StrData+0
	CALL       _Write_LCD_Text+0
;SerialLcdTestforELab.c,108 :: 		Delay_ms(1500);
	MOVLW      8
	MOVWF      R11+0
	MOVLW      157
	MOVWF      R12+0
	MOVLW      5
	MOVWF      R13+0
L_main12:
	DECFSZ     R13+0, 1
	GOTO       L_main12
	DECFSZ     R12+0, 1
	GOTO       L_main12
	DECFSZ     R11+0, 1
	GOTO       L_main12
	NOP
	NOP
;SerialLcdTestforELab.c,109 :: 		Write_LCD_Cmd(0x01);  // Clear LCD
	MOVLW      1
	MOVWF      FARG_Write_LCD_Cmd_C+0
	CALL       _Write_LCD_Cmd+0
;SerialLcdTestforELab.c,110 :: 		delay_ms(1000);
	MOVLW      6
	MOVWF      R11+0
	MOVLW      19
	MOVWF      R12+0
	MOVLW      173
	MOVWF      R13+0
L_main13:
	DECFSZ     R13+0, 1
	GOTO       L_main13
	DECFSZ     R12+0, 1
	GOTO       L_main13
	DECFSZ     R11+0, 1
	GOTO       L_main13
	NOP
	NOP
;SerialLcdTestforELab.c,111 :: 		} while(1);
	GOTO       L_main10
;SerialLcdTestforELab.c,113 :: 		}
	GOTO       $+0
; end of _main
