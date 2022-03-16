/***************************** C SOURCE FILE *********************************
**
**  Project:    ADC_dr1 Driver for CL2bm1
**  Filename:   ADC_dr1.c
**  Date:       10.02.2018
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
**  Date:       10.2.18 renamed 26.1.22
**  Revised by: R.Oliva
**  Description:
**      - 
**      - Newer versions see top. 
**      - Renaming to LyR-IHCR v1 26.1.22
**              
**
*****************************************************************************/

#include "../inc/adc_dr1.h" 

/*****************************************************************************
**
** DEFINITIONS
**
*****************************************************************************/

// Show timing requirements.. from 2018 tests
// #define ADC_DEBUG_ENABLED

/*****************************************************************************
**
** ADC Global Variables declared in ADC_dr1.h
** MEMORY IS ASSIGNED
** HERE FOLLOWING RULE #5
**
*****************************************************************************/

// Global Vector buffer
uint16_t adc_FPSChannel[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];

// completion Flag set by ISR, protected reset by ADC_Copy_Vector() 27.1.22  
// Boolean support is not very clear in CVAVR, bit is a native form - should
// be bool_t
uint8_t adc_vector_completed = 0;   // Changed from Bit To uint8_t 10.2.2018 


/*****************************************************************************
**
** ADC module local variables declared as static
** Changed 26.1.22 --> rule #6 violation previously undetected
**
*****************************************************************************/

static uint16_t adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
// Inmediate buffer for Data..
static uint16_t adc_buffer[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];

/*****************************************************************************
**
** EXPORTED FUNCTIONS 
**
*****************************************************************************/

/****************************************************************************
**
** Initializes the ADC
** void ADC_Init(uint8_t ADC_param)
** Parameters:  uint8_t ADC_param
** Select (A) FreeRunning or (B) Timer1OVF as trigger,
** ADC clock is 115.2 kHz @ 14.7456 MHz Clk
** (A)#define ADC_INIT_FR_115K2   0
** (B)#define ADC_INIT_TMR1_115K2 1
**
** Returns: NONE
** If  ADC_param == ADC_INIT_TMR1_115K2
** then definition of Timer1 OVF ISR (used by ElmChanFFS)
** will be required, at 100Hz by default.
** (use (B) for this version)
****************************************************************************/

void ADC_Init(uint8_t ADC_param)
{
 switch (ADC_param)
        {
        case ADC_INIT_FR_115K2:
        // ADC initialization Free Running at 115.2 kHz = 14.7456E06 / 128 Hz
        // ADC Clock frequency: 115,200 kHz  -> ADPS = 111
        // ADC Voltage Reference: AREF pin
        // ADC Auto Trigger Source: Free Running  -> ADTS = 000
        // Digital input buffers on ADC0: Off, ADC1: Off, ADC2: Off, ADC3: Off
        // ADC4: Off, ADC5: Off, ADC6: Off, ADC7: Off
        DIDR0=(1<<ADC7D) | (1<<ADC6D) | (1<<ADC5D) | (1<<ADC4D) | (1<<ADC3D) | (1<<ADC2D) | (1<<ADC1D) | (1<<ADC0D);
        ADMUX=FIRST_ADC_INPUT | ADC_VREF_TYPE;
        ADCSRA=(1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (0<<ADIF) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
        ADCSRB=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); // Free Running  -> ADTS = 000
        break;

        case ADC_INIT_TMR1_115K2:
        // ADC initialization for Timer 1 OVF Autotrigger (requires Timer1 ISR)
        // ADC Clock frequency: 115,200 kHz  -> ADPS = 111
        // ADC Voltage Reference: AREF pin
        // ADC Auto Trigger Source: Timer1 Overflow -> ADTS = 110
        // Digital input buffers on ADC0: Off, ADC1: Off, ADC2: Off, ADC3: Off
        // ADC4: Off, ADC5: Off, ADC6: Off, ADC7: Off
        DIDR0=(1<<ADC7D) | (1<<ADC6D) | (1<<ADC5D) | (1<<ADC4D) | (1<<ADC3D) | (1<<ADC2D) | (1<<ADC1D) | (1<<ADC0D);
        ADMUX=FIRST_ADC_INPUT | ADC_VREF_TYPE;
        ADCSRA=(1<<ADEN) | (0<<ADSC) | (1<<ADATE) | (0<<ADIF) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
        ADCSRB=(1<<ADTS2) | (1<<ADTS1) | (0<<ADTS0);   // Timer1_OVF AutoTrigger
        break;
        }
}

/*****************************************************************************
**
** ADC interrupt service routine
** Add a Buffer Vector, and a "Vector complete" bit to signal the main
** program - When this bit is 1, the whole 8-channel vector should
** be copied to an ADProcess variable within main program - 8.2.2018
** 10.2.2018 - Disable the AutoStart at end of routine, controlled by Timer1
** 
*****************************************************************************/

interrupt [ADC_INT] void adc_isr(void)
{
static unsigned char input_index=0;
// Read the AD conversion result
// BACK_LIGHT = 1; // Only for debug..
adc_data[input_index]=ADCW;
// 8.2.2018 Copy to vector_buffer of corresponding channel..
adc_buffer[input_index]=adc_data[input_index]; 
// Select next ADC input
if (++input_index > (LAST_ADC_INPUT-FIRST_ADC_INPUT)){
   adc_vector_completed = 1; // signal main program to copy vector.  
   input_index=0;            // Reset input_index
   // BACK_LIGHT = 1; // Only for debug..
   }
ADMUX=(FIRST_ADC_INPUT | ADC_VREF_TYPE)+input_index;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion - This commented out 10.2.2018 
// ADCSRA|=(1<<ADSC); // not required with Timer1 OVF autotrig..
// BACK_LIGHT = 0; // Only for debug..
}



/*******************************************************************
** Protected Copy of ADC Buffer to Vector Buffer FPSChannel[] 
** 8.2.2018 -Rev 10.2.2018 -Add toggle of BackLight PD.6 (pin20)
** Duration of copy: 26us (scope)
** 26.1.22 renamed global vector adc_FPSChannel[] and
** #ifdef for ADC_DEBUG_ENABLED
*******************************************************************/
void  ADC_Copy_Vector(void)
{
    unsigned char j_cnt;                 
    CLI();
    #ifdef ADC_DEBUG_ENABLED
	BACK_LIGHT = 1; // Only for debug..
	#endif
    for(j_cnt=0; j_cnt<(LAST_ADC_INPUT-FIRST_ADC_INPUT+1); j_cnt++){
             adc_FPSChannel[j_cnt] =  adc_buffer[j_cnt];
             }
    adc_vector_completed = 0; // Reset signal to copy vector..
    #ifdef ADC_DEBUG_ENABLED
    BACK_LIGHT = 0; // Only for debug..         
	#endif	
    SEI();             
}




/*****************************************************************************
**
** EOF 
**
*****************************************************************************/

