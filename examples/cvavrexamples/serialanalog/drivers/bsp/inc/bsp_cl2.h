/***************************** C HEADER FILE *********************************
**
**  Project:    Board Support Package for CL2bm1
* @file:        bsp_cl2.h
* @date:        30.01.2022
**
* @author:     Rafael Oliva
**
******************************************************************************
**
**
******************************************************************************
**
**  VERSION HISTORY:
**  ----------------
**  initial Version:    1.0
**  current Version:    1.2
**  Date:
**  Revised by: R.Oliva
* @brief BSP for CL2 projects on Codevision
**  Description:
**      - Change naming global functions to CL2Board_xxx()   
**      - Newer versions see top.
**
**
**
*****************************************************************************/

#ifndef CL2BSP_INCLUDED
#define CL2BSP_INCLUDED

/****************************************************************************
**
**    MODULES USED
**
****************************************************************************/
#include <stdio.h>
#include <delay.h>
#include <mega1284p.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

// UART0 Driver in CL2 -updated 2021
#include "..\..\drivers\uart0\inc\uart0dr1.h"
// UART1A Driver in CL2 -updated 2021
#include "..\..\drivers\uart1a\inc\uart1dr1.h"


/****************************************************************************
**
**    DEFINITIONS AND MACROS
**
****************************************************************************/

// CL2BOARD Configuration #defines
// Uncomment to use COMs CL2 board configuration
#define CL2_BOARD_COM_CFG_DEFINED

// Uncomment to Blink OLED + Display BL once
// #define CL2BOARD_INIT_BLINK_OLED_CFG_DEFINED

// Uncomment to Use Timer1 / ADC 115 kHz Mode
#define CL2_BOARD_ANALOG_TIMER_1_ENABLED

typedef enum comport_en{
    UART0_TER = 0,
    UART1_485 = 1
}comport_t;

typedef enum baud_en
             {
             UART_BAUD9600,
             UART_BAUD19200,
             UART_BAUD38400
             }baud_t;

typedef enum systemtype_en{
    CL2BOARD_SIMPLE = 0,
    CL2BOARD_PWRC2 = 1
}systemtype_t;

// Ports in CL2 board 1284P Refactored 01.22
#define     OLED        PORTD.5
#define     BACK_LIGHT  PORTD.6
// For LEDs / Lighting
#define     LOGIC_ON    1
#define     LOGIC_OFF   0

#define     SEI()           #asm("sei")
#define     CLI()           #asm("cli")

#ifdef ADC_FREE_RUNNING_PWRC2
 #define FIRST_ADC_INPUT 0
 #define LAST_ADC_INPUT 7
 // Voltage Reference: AREF pin
 #define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))
#endif

/****************************************************************************
**
**    EXPORTED VARIABLES
**    declared here, but defined in .c file for global access.. 18.12.2017
**
****************************************************************************/


/****************************************************************************
**
**    EXPORTED FUNCTIONS
**    functions public to rest of program 18.12.2017
**
****************************************************************************/

// parameter example PWRC2
void CL2Board_init(systemtype_t boardConfig);

// Added 2021 - CL2 Terminal @COM0 19200 configuration 
// in /drivers/UART0 or @COM1 in /drivers/UART1A wrapper      
// Remember to #include stdint.h or won't compile! 31.1.22
#ifdef CL2_BOARD_COM_CFG_DEFINED
    void CL2Board_uartConfig(comport_t comport, baud_t baud);
#endif


#ifdef CL2_BOARD_ANALOG_TIMER_1_ENABLED
    void CL2Board_Timer1_Initialize(void);
#endif	

// One-time blink OLED - Board LED with Display
#ifdef CL2_BOARD_INIT_BLINK_OLED_CFG_DEFINED
    void CL2Board_blinkOLED(void);
#endif

// Set OLED on 
void CL2Board_setOLED(void);
// Set OLED off
void CL2Board_clearOLED(void);
// Simple blocking delay
void CL2Board_delay_ms(uint16_t millis);

#endif
/****************************************************************************
**
**    EOF
**
****************************************************************************/
