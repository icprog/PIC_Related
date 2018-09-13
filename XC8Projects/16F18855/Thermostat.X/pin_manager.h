/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.1
        Device            :  PIC16F18855
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set D2 aliases
#define D2_TRIS               TRISAbits.TRISA0
#define D2_LAT                LATAbits.LATA0
#define D2_PORT               PORTAbits.RA0
#define D2_WPU                WPUAbits.WPUA0
#define D2_OD                ODCONAbits.ODCA0
#define D2_ANS                ANSELAbits.ANSA0
#define D2_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define D2_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define D2_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define D2_GetValue()           PORTAbits.RA0
#define D2_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define D2_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define D2_SetPullup()      do { WPUAbits.WPUA0 = 1; } while(0)
#define D2_ResetPullup()    do { WPUAbits.WPUA0 = 0; } while(0)
#define D2_SetPushPull()    do { ODCONAbits.ODCA0 = 1; } while(0)
#define D2_SetOpenDrain()   do { ODCONAbits.ODCA0 = 0; } while(0)
#define D2_SetAnalogMode()  do { ANSELAbits.ANSA0 = 1; } while(0)
#define D2_SetDigitalMode() do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set DP aliases
#define DP_TRIS               TRISAbits.TRISA1
#define DP_LAT                LATAbits.LATA1
#define DP_PORT               PORTAbits.RA1
#define DP_WPU                WPUAbits.WPUA1
#define DP_OD                ODCONAbits.ODCA1
#define DP_ANS                ANSELAbits.ANSA1
#define DP_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DP_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DP_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DP_GetValue()           PORTAbits.RA1
#define DP_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DP_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DP_SetPullup()      do { WPUAbits.WPUA1 = 1; } while(0)
#define DP_ResetPullup()    do { WPUAbits.WPUA1 = 0; } while(0)
#define DP_SetPushPull()    do { ODCONAbits.ODCA1 = 1; } while(0)
#define DP_SetOpenDrain()   do { ODCONAbits.ODCA1 = 0; } while(0)
#define DP_SetAnalogMode()  do { ANSELAbits.ANSA1 = 1; } while(0)
#define DP_SetDigitalMode() do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set G_seg aliases
#define G_seg_TRIS               TRISAbits.TRISA2
#define G_seg_LAT                LATAbits.LATA2
#define G_seg_PORT               PORTAbits.RA2
#define G_seg_WPU                WPUAbits.WPUA2
#define G_seg_OD                ODCONAbits.ODCA2
#define G_seg_ANS                ANSELAbits.ANSA2
#define G_seg_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define G_seg_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define G_seg_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define G_seg_GetValue()           PORTAbits.RA2
#define G_seg_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define G_seg_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define G_seg_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define G_seg_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define G_seg_SetPushPull()    do { ODCONAbits.ODCA2 = 1; } while(0)
#define G_seg_SetOpenDrain()   do { ODCONAbits.ODCA2 = 0; } while(0)
#define G_seg_SetAnalogMode()  do { ANSELAbits.ANSA2 = 1; } while(0)
#define G_seg_SetDigitalMode() do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set F_seg aliases
#define F_seg_TRIS               TRISAbits.TRISA3
#define F_seg_LAT                LATAbits.LATA3
#define F_seg_PORT               PORTAbits.RA3
#define F_seg_WPU                WPUAbits.WPUA3
#define F_seg_OD                ODCONAbits.ODCA3
#define F_seg_ANS                ANSELAbits.ANSA3
#define F_seg_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define F_seg_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define F_seg_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define F_seg_GetValue()           PORTAbits.RA3
#define F_seg_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define F_seg_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define F_seg_SetPullup()      do { WPUAbits.WPUA3 = 1; } while(0)
#define F_seg_ResetPullup()    do { WPUAbits.WPUA3 = 0; } while(0)
#define F_seg_SetPushPull()    do { ODCONAbits.ODCA3 = 1; } while(0)
#define F_seg_SetOpenDrain()   do { ODCONAbits.ODCA3 = 0; } while(0)
#define F_seg_SetAnalogMode()  do { ANSELAbits.ANSA3 = 1; } while(0)
#define F_seg_SetDigitalMode() do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set E_seg aliases
#define E_seg_TRIS               TRISAbits.TRISA4
#define E_seg_LAT                LATAbits.LATA4
#define E_seg_PORT               PORTAbits.RA4
#define E_seg_WPU                WPUAbits.WPUA4
#define E_seg_OD                ODCONAbits.ODCA4
#define E_seg_ANS                ANSELAbits.ANSA4
#define E_seg_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define E_seg_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define E_seg_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define E_seg_GetValue()           PORTAbits.RA4
#define E_seg_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define E_seg_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define E_seg_SetPullup()      do { WPUAbits.WPUA4 = 1; } while(0)
#define E_seg_ResetPullup()    do { WPUAbits.WPUA4 = 0; } while(0)
#define E_seg_SetPushPull()    do { ODCONAbits.ODCA4 = 1; } while(0)
#define E_seg_SetOpenDrain()   do { ODCONAbits.ODCA4 = 0; } while(0)
#define E_seg_SetAnalogMode()  do { ANSELAbits.ANSA4 = 1; } while(0)
#define E_seg_SetDigitalMode() do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set D_seg aliases
#define D_seg_TRIS               TRISAbits.TRISA5
#define D_seg_LAT                LATAbits.LATA5
#define D_seg_PORT               PORTAbits.RA5
#define D_seg_WPU                WPUAbits.WPUA5
#define D_seg_OD                ODCONAbits.ODCA5
#define D_seg_ANS                ANSELAbits.ANSA5
#define D_seg_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define D_seg_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define D_seg_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define D_seg_GetValue()           PORTAbits.RA5
#define D_seg_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define D_seg_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define D_seg_SetPullup()      do { WPUAbits.WPUA5 = 1; } while(0)
#define D_seg_ResetPullup()    do { WPUAbits.WPUA5 = 0; } while(0)
#define D_seg_SetPushPull()    do { ODCONAbits.ODCA5 = 1; } while(0)
#define D_seg_SetOpenDrain()   do { ODCONAbits.ODCA5 = 0; } while(0)
#define D_seg_SetAnalogMode()  do { ANSELAbits.ANSA5 = 1; } while(0)
#define D_seg_SetDigitalMode() do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set B_seg aliases
#define B_seg_TRIS               TRISAbits.TRISA6
#define B_seg_LAT                LATAbits.LATA6
#define B_seg_PORT               PORTAbits.RA6
#define B_seg_WPU                WPUAbits.WPUA6
#define B_seg_OD                ODCONAbits.ODCA6
#define B_seg_ANS                ANSELAbits.ANSA6
#define B_seg_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define B_seg_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define B_seg_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define B_seg_GetValue()           PORTAbits.RA6
#define B_seg_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define B_seg_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define B_seg_SetPullup()      do { WPUAbits.WPUA6 = 1; } while(0)
#define B_seg_ResetPullup()    do { WPUAbits.WPUA6 = 0; } while(0)
#define B_seg_SetPushPull()    do { ODCONAbits.ODCA6 = 1; } while(0)
#define B_seg_SetOpenDrain()   do { ODCONAbits.ODCA6 = 0; } while(0)
#define B_seg_SetAnalogMode()  do { ANSELAbits.ANSA6 = 1; } while(0)
#define B_seg_SetDigitalMode() do { ANSELAbits.ANSA6 = 0; } while(0)

// get/set C_seg aliases
#define C_seg_TRIS               TRISAbits.TRISA7
#define C_seg_LAT                LATAbits.LATA7
#define C_seg_PORT               PORTAbits.RA7
#define C_seg_WPU                WPUAbits.WPUA7
#define C_seg_OD                ODCONAbits.ODCA7
#define C_seg_ANS                ANSELAbits.ANSA7
#define C_seg_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define C_seg_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define C_seg_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define C_seg_GetValue()           PORTAbits.RA7
#define C_seg_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define C_seg_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define C_seg_SetPullup()      do { WPUAbits.WPUA7 = 1; } while(0)
#define C_seg_ResetPullup()    do { WPUAbits.WPUA7 = 0; } while(0)
#define C_seg_SetPushPull()    do { ODCONAbits.ODCA7 = 1; } while(0)
#define C_seg_SetOpenDrain()   do { ODCONAbits.ODCA7 = 0; } while(0)
#define C_seg_SetAnalogMode()  do { ANSELAbits.ANSA7 = 1; } while(0)
#define C_seg_SetDigitalMode() do { ANSELAbits.ANSA7 = 0; } while(0)

// get/set MCP9700A aliases
#define MCP9700A_TRIS               TRISBbits.TRISB5
#define MCP9700A_LAT                LATBbits.LATB5
#define MCP9700A_PORT               PORTBbits.RB5
#define MCP9700A_WPU                WPUBbits.WPUB5
#define MCP9700A_OD                ODCONBbits.ODCB5
#define MCP9700A_ANS                ANSELBbits.ANSB5
#define MCP9700A_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define MCP9700A_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define MCP9700A_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define MCP9700A_GetValue()           PORTBbits.RB5
#define MCP9700A_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define MCP9700A_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define MCP9700A_SetPullup()      do { WPUBbits.WPUB5 = 1; } while(0)
#define MCP9700A_ResetPullup()    do { WPUBbits.WPUB5 = 0; } while(0)
#define MCP9700A_SetPushPull()    do { ODCONBbits.ODCB5 = 1; } while(0)
#define MCP9700A_SetOpenDrain()   do { ODCONBbits.ODCB5 = 0; } while(0)
#define MCP9700A_SetAnalogMode()  do { ANSELBbits.ANSB5 = 1; } while(0)
#define MCP9700A_SetDigitalMode() do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set A_seg aliases
#define A_seg_TRIS               TRISCbits.TRISC0
#define A_seg_LAT                LATCbits.LATC0
#define A_seg_PORT               PORTCbits.RC0
#define A_seg_WPU                WPUCbits.WPUC0
#define A_seg_OD                ODCONCbits.ODCC0
#define A_seg_ANS                ANSELCbits.ANSC0
#define A_seg_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define A_seg_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define A_seg_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define A_seg_GetValue()           PORTCbits.RC0
#define A_seg_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define A_seg_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define A_seg_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define A_seg_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define A_seg_SetPushPull()    do { ODCONCbits.ODCC0 = 1; } while(0)
#define A_seg_SetOpenDrain()   do { ODCONCbits.ODCC0 = 0; } while(0)
#define A_seg_SetAnalogMode()  do { ANSELCbits.ANSC0 = 1; } while(0)
#define A_seg_SetDigitalMode() do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set D1 aliases
#define D1_TRIS               TRISCbits.TRISC1
#define D1_LAT                LATCbits.LATC1
#define D1_PORT               PORTCbits.RC1
#define D1_WPU                WPUCbits.WPUC1
#define D1_OD                ODCONCbits.ODCC1
#define D1_ANS                ANSELCbits.ANSC1
#define D1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define D1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define D1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define D1_GetValue()           PORTCbits.RC1
#define D1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define D1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define D1_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define D1_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define D1_SetPushPull()    do { ODCONCbits.ODCC1 = 1; } while(0)
#define D1_SetOpenDrain()   do { ODCONCbits.ODCC1 = 0; } while(0)
#define D1_SetAnalogMode()  do { ANSELCbits.ANSC1 = 1; } while(0)
#define D1_SetDigitalMode() do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SW1_A aliases
#define SW1_A_TRIS               TRISCbits.TRISC2
#define SW1_A_LAT                LATCbits.LATC2
#define SW1_A_PORT               PORTCbits.RC2
#define SW1_A_WPU                WPUCbits.WPUC2
#define SW1_A_OD                ODCONCbits.ODCC2
#define SW1_A_ANS                ANSELCbits.ANSC2
#define SW1_A_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SW1_A_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SW1_A_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SW1_A_GetValue()           PORTCbits.RC2
#define SW1_A_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SW1_A_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SW1_A_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define SW1_A_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define SW1_A_SetPushPull()    do { ODCONCbits.ODCC2 = 1; } while(0)
#define SW1_A_SetOpenDrain()   do { ODCONCbits.ODCC2 = 0; } while(0)
#define SW1_A_SetAnalogMode()  do { ANSELCbits.ANSC2 = 1; } while(0)
#define SW1_A_SetDigitalMode() do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set SW1_D aliases
#define SW1_D_TRIS               TRISCbits.TRISC3
#define SW1_D_LAT                LATCbits.LATC3
#define SW1_D_PORT               PORTCbits.RC3
#define SW1_D_WPU                WPUCbits.WPUC3
#define SW1_D_OD                ODCONCbits.ODCC3
#define SW1_D_ANS                ANSELCbits.ANSC3
#define SW1_D_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SW1_D_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SW1_D_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SW1_D_GetValue()           PORTCbits.RC3
#define SW1_D_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SW1_D_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SW1_D_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define SW1_D_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define SW1_D_SetPushPull()    do { ODCONCbits.ODCC3 = 1; } while(0)
#define SW1_D_SetOpenDrain()   do { ODCONCbits.ODCC3 = 0; } while(0)
#define SW1_D_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define SW1_D_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SW1_B aliases
#define SW1_B_TRIS               TRISCbits.TRISC4
#define SW1_B_LAT                LATCbits.LATC4
#define SW1_B_PORT               PORTCbits.RC4
#define SW1_B_WPU                WPUCbits.WPUC4
#define SW1_B_OD                ODCONCbits.ODCC4
#define SW1_B_ANS                ANSELCbits.ANSC4
#define SW1_B_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SW1_B_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SW1_B_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SW1_B_GetValue()           PORTCbits.RC4
#define SW1_B_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SW1_B_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SW1_B_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define SW1_B_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define SW1_B_SetPushPull()    do { ODCONCbits.ODCC4 = 1; } while(0)
#define SW1_B_SetOpenDrain()   do { ODCONCbits.ODCC4 = 0; } while(0)
#define SW1_B_SetAnalogMode()  do { ANSELCbits.ANSC4 = 1; } while(0)
#define SW1_B_SetDigitalMode() do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RELAY aliases
#define RELAY_TRIS               TRISCbits.TRISC5
#define RELAY_LAT                LATCbits.LATC5
#define RELAY_PORT               PORTCbits.RC5
#define RELAY_WPU                WPUCbits.WPUC5
#define RELAY_OD                ODCONCbits.ODCC5
#define RELAY_ANS                ANSELCbits.ANSC5
#define RELAY_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RELAY_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RELAY_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RELAY_GetValue()           PORTCbits.RC5
#define RELAY_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RELAY_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RELAY_SetPullup()      do { WPUCbits.WPUC5 = 1; } while(0)
#define RELAY_ResetPullup()    do { WPUCbits.WPUC5 = 0; } while(0)
#define RELAY_SetPushPull()    do { ODCONCbits.ODCC5 = 1; } while(0)
#define RELAY_SetOpenDrain()   do { ODCONCbits.ODCC5 = 0; } while(0)
#define RELAY_SetAnalogMode()  do { ANSELCbits.ANSC5 = 1; } while(0)
#define RELAY_SetDigitalMode() do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set LED_blue aliases
#define LED_blue_TRIS               TRISCbits.TRISC6
#define LED_blue_LAT                LATCbits.LATC6
#define LED_blue_PORT               PORTCbits.RC6
#define LED_blue_WPU                WPUCbits.WPUC6
#define LED_blue_OD                ODCONCbits.ODCC6
#define LED_blue_ANS                ANSELCbits.ANSC6
#define LED_blue_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define LED_blue_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define LED_blue_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define LED_blue_GetValue()           PORTCbits.RC6
#define LED_blue_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define LED_blue_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define LED_blue_SetPullup()      do { WPUCbits.WPUC6 = 1; } while(0)
#define LED_blue_ResetPullup()    do { WPUCbits.WPUC6 = 0; } while(0)
#define LED_blue_SetPushPull()    do { ODCONCbits.ODCC6 = 1; } while(0)
#define LED_blue_SetOpenDrain()   do { ODCONCbits.ODCC6 = 0; } while(0)
#define LED_blue_SetAnalogMode()  do { ANSELCbits.ANSC6 = 1; } while(0)
#define LED_blue_SetDigitalMode() do { ANSELCbits.ANSC6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/