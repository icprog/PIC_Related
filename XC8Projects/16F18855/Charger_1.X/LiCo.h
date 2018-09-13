/*****************************************************************************
*                           LiCo.h
*
* Description: Lithium Cobalt specific parameters
*
* Hardware:  Synchronous Inverse SEPIC (Zeta) Converter + Battery Charging Library
*
* Resources: PICC 9.83 / MPLAB 8.80
*
* CODE OWNERSHIP AND DISCLAIMER OF LIABILITY
*
* Microchip Technology Incorporated ("Microchip") retains all ownership and
* intellectual property rights in the code accompanying this message and in
* all derivatives hereto.  You may use this code, and any derivatives created
* by any person or entity by or on your behalf, exclusively with Microchips
* proprietary products.  Your acceptance and/or use of this code constitutes
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT
* LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND
* FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH
* MICROCHIPS PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
* APPLICATION.
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE,
* WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF
* STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE,
* FOR ANY INDIRECT, SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL
* LOSS, DAMAGE, FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
* CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE
* BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY
* TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
* Author            Date		Ver		Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Mihnea            Oct 2012 	1.00	Release
* Rosu-Hamzescu
******************************************************************************/

// LiCo battery parameters

#define PRESET1
//define PRESET2

//	3.00V per cell cutoff voltage
// 	3.70V+ per cell charged OCV voltage
//	4.20V per cell charging voltage

#ifdef PRESET1
	#define CAPACITY 				1800
	#define CHARGING_VOLTAGE		3400		//4.15V
	#define TOPPING_VOLTAGE			3112		//4.00V
	#define	CUTOFF_VOLTAGE			2457		//3.00V

	#define	ILIM_PRECHARGE			141		//100mA
	#define	ILIM					1415	//1000mA, C/2
	#define ISTOP					71		//55mA, C/33 (3%) minimum charging current				

#endif

#ifdef PRESET2
	#define CAPACITY 				3000
	#define CHARGING_VOLTAGE		3400		//4.15V
	#define TOPPING_VOLTAGE			3112		//4.00V
	#define	CUTOFF_VOLTAGE			2457		//3.00V

	#define	ILIM_PRECHARGE			141		//100mA
	#define	ILIM					1904	//1500mA, C/2
	#define ISTOP					115		//90mA, C/33 (3%) minimum charging current				

#endif

#define	BATTERY_STANDBY_MODE
	
#define	PRECHARGE_TIME		600

#define IFLAT_COUNT		600
