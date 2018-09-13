/*****************************************************************************
*                           Hardware.h
*
* Description: Hardware related definitions
*
* Hardware:  Synchronous Inverse SEPIC (Zeta) Converter + Battery Charging Library
*
* Resources: PICC 9.83 / MPLAB 8.80
*
******************************************************************************/

#include <xc.h>

#define _XTAL_FREQ 				16000000

#ifndef HARDWARE_H
	#define HARDWARE_H
	enum LED_MODES { LED_OFF = 100, LED_ON = 101, BLINK_05HZ = 16, BLINK_2HZ = 4 };
#endif

#define		IOUT				RA1
#define		VIN					RA2
#define		IIN					RC2
#define		VOUT				RC3

#define		LED					RC5

//								  76543210
#define		ADCON0_INIT 		0b10000001
#define		ADCON1_INIT  		0b11010000

#define		IOUT_SENSE_CHAN			0x01
#define		VIN_CHAN				0x02
#define		IIN_SENSE_CHAN			0x06
#define		VOUT_CHAN				0x07

#define		FVR_CHAN				0x1F
#define		FVR_MAX					932

#define		SHUNT_VALUE						5		//mOhms
#define		SHUNT_AMPLIFICATION_OUT			106		// should be 101
#define		VOUT_DIVIDER					4
#define		VDD_VAL							5037	//mVolts

#define		NCO_MIN				1
#define		NCO_START			1

#define		NCO_MAX				29500			//app. 450k

#define		NCO_16P				0x80
#define		NCO_32P				0xA0

#define		WARMUP_TIME			64
#define		CURRENT_MODE		4
#define		ERR_MAX				4095
#define		ERR_MIN				-4095

//	For this demo board VDD is 5037mV, IOUT shunt is 5mOhm, IOUT amplification 106, VOUT divider is 4

#define		AD_SAMPLES			4
#define		SAMPLES_AVG			16

#define		AD_SET_CHAN(x)		{ ADCON0 = ADCON0_INIT | (x << 2); }
#define		AD_CONVERT()		{ GO_nDONE = 1; while(GO_nDONE); }
#define		VREF_COMP(x)		{ x = (unsigned int)x * VREF_VDD_MAX / vref; }

#define		STOP_CONVERTER()	{ increment = 0; set_NCO(); TRIS_NCO = 1; }
#define  	START_CONVERTER()	{ warmup = WARMUP_TIME; TRIS_NCO = 0; }

#define		ISENSE		iout
#define		VSENSE		vout

#define		SET_VOLTAGE(x)		{ vref = x; }
#define		SET_CURRENT(x)		{ iref = x; }
#define		SET_LED_BLINK(x)	{ led_state = x; }

#define		CONSTANT_VOLTAGE	(!cmode)
#define		I_BAT_DETECT		16 

#define		STOUS(x)		{ x -= 1; x = ~x; }
#define		USTOS(x)		{ x = ~x; x += 1; }

#define		BUTTON				RA3

#define		NCO					RA4
#define		TRIS_NCO			TRISA4

#define 	BUTTON_COUNT			61

#define		SECOND_COUNT			976
#define 	SECOND_COUNT_START		999

extern unsigned char temp;
extern unsigned int ad_res;
extern unsigned int iout;
extern unsigned int vout;

extern unsigned char lbut, led_state;
extern unsigned char but_cnt, led_cnt;

extern int increment;

extern unsigned int vref;
extern unsigned int iref;
extern unsigned int warmup;
extern char cmode;
extern unsigned char cc_cv;
extern unsigned int second;

extern int	pp,pi;
extern int er;

void Initialize_Hardware(void);
void Init_Registers(void);
void Shutdown_Peripherals(void);
void Measure_Impedance(void);
void Blink(unsigned char num);
void Delay_ms(unsigned int msec);
void pid(unsigned int feedback, unsigned int setpoint);
void set_NCO(void);
void read_ADC(void);
void cc_cv_mode(void);
unsigned char button_scheme(void);
void led_blink(void);