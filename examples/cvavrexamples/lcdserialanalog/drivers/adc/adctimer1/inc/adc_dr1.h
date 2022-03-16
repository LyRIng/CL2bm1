/***************************** C HEADER FILE *********************************
**
**  Project:    adc_dr1 Driver for CL2bm1
**  Filename:   adc_dr1.h
**  Date:       10.02.2018 renamed 26.1.22
**
**  Modified    R.Oliva  - Include interrupt routine 
**              Version for Timer1 Autotrig + ADC_CK = 115.2 kHz
**  
******************************************************************************
**
**
******************************************************************************
**
**  VERSION HISTORY:
**  ----------------
**  initial Version:    1.0 
**  current version:    1.2a
**  Date:       08.02.2018 current 27.01.2022
**  Revised by: R.Oliva
**  Description:
**      - 
**      - Newer versions see top.
**      - Renaming to LyR-IHCR v1 26.1.22
**      - Changed names and variable 
**              
**
*****************************************************************************/

#ifndef ADC_INCLUDED
#define ADC_INCLUDED

/****************************************************************************
**
**    MODULES USED 
**
****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <delay.h>

/****************************************************************************
**
**    DEFINITIONS AND MACROS
**
****************************************************************************/


#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 7

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))


// Parameters for ADC_param in ADC_Init() 
// Select FreeRunning or Timer1OVF as trigger,
// ADC clock is 115.2 kHz @ 14.7456 MHz Clk
#define ADC_INIT_FR_115K2    0
#define ADC_INIT_TMR1_115K2  1

#ifndef CL2BSP_INCLUDED
// Definitions required. 8.2.2018.
#define     SEI()           #asm("sei")
#define     CLI()           #asm("cli")

// From 1284P testing 8.2.2018
#define OLED        PORTD.5
#define BACK_LIGHT  PORTD.6
#endif


/****************************************************************************
** 
**    EXPORTED VARIABLES
**    declared here, but defined in .c file for global access..
**    v26.1.22 (Rule#6 violation undetected)..
**    removed internal adc_data, buffer and flag completed
**    rule #15 -->renamed FPSChannel to adc_FPSChannel[], 
**    now the single globally accessible vector
**
****************************************************************************/


// Vector buffer
extern uint16_t adc_FPSChannel[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
// completion Flag set by ISR, protected reset by ADC_Copy_Vector() 27.1.22 
extern uint8_t adc_vector_completed;
 
/****************************************************************************
**
**    EXPORTED FUNCTIONS
**    functions public to rest of program 18.12.2017
**
****************************************************************************/

// Interrupt routines
interrupt [ADC_INT] void adc_isr(void);

// If  ADC_INIT_TMR1_115K2 == ADC_param in ADC_Init(),
// then definition of Timer1 OVF ISR (used by ElmChanFFS)
// will be required, at 100Hz by default.

// ADC_Init standard configurable Parameter
// Parameters for ADC_param in ADC_Init() 
// Select (A) FreeRunning or (B) Timer1OVF as trigger,
// ADC clock is 115.2 kHz @ 14.7456 MHz Clk
// (A)#define ADC_INIT_FR_115K2   0
// (B)#define ADC_INIT_TMR1_115K2 1
// (here use (B)) 10.2.2018
void ADC_Init(uint8_t ADC_param);

/************************************************************* 
** Protected Copy of ADC Buffer to Vector Buffer FPSChannel[] 
** ADC_Copy_Vector() - 8.2.2018
**************************************************************/
void ADC_Copy_Vector(void);

#endif
/****************************************************************************
**
**    EOF 
**
****************************************************************************/
