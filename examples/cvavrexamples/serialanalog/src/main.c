/***************************** C SOURCE FILE *********************************
**
**  Project:   Example serialanalog for CL2bm1 on Codevision
* @file:       main.c
* @author      R.Oliva
**  Date:      05.03.2022
**  Modified
**
******************************************************************************
**
**
******************************************************************************
**
**  VERSION HISTORY:
**  ----------------
**  initial Version: 1.1    
**  Date:       08.02.2022
**  Version 1.2 5.03.22
**  Revised by: R.Oliva
* @brief Example serialanalog for CL2bm1 on Codevision
**  Description:
**      - Simple serialanalog for CL2bm1 on Codevision, prints out ADC readings
**      - version 1.1 uses new naming following IHRC
**
**
**
*****************************************************************************/

#include "../inc/main.h"

/*****************************************************************************
**
** DEFINITIONS / VARIABLES
**
*****************************************************************************/

char s[25];
uint8_t j_1 = 0;

/*****************************************************************************
**
** See higher level functions grouped
** in /modules
** and low level in /drivers
** declared in main.h
**
*****************************************************************************/


/****************************************************************************
**
** to use Doxygen
**
  * @brief  main() serialanalog function **  Version 1.2 5.03.22
  * @param  None
  * @retval none
  *
**
**/

void main(void)
{
    // CL2 board configuration
    // in /drivers/bsp
    CL2Board_init(CL2BOARD_SIMPLE);
	
    // CL2 BSP Terminal @COM0 19200 configuration
    // uses function in /drivers/uart0
    CL2Board_uartConfig(UART0_TER, UART_BAUD19200);
	
    // ADC_Init standard configurable Parameter
    // Parameters for ADC_param in ADC_Init() 
    // Select (A) FreeRunning or (B) Timer1OVF as trigger,
    // ADC clock is 115.2 kHz @ 14.7456 MHz Clk
    // (A)#define ADC_INIT_FR_115K2   0
    // (B)#define ADC_INIT_TMR1_115K2 1
    // REMEMBER to set correct Parameter..(B here)
    ADC_Init(ADC_INIT_TMR1_115K2);

    // *************************************************
    // 10.2.2018 - Added - Timer1 Use - Renamed 2022
    CL2Board_Timer1_Initialize();	

    // Start interrupts
    SEI();
    printf(CRLF);
    printf(MAIN_VER);        
    printf(COM_MSG1);
    // Analog Read, printout + simple OLED blink with blocking delays
    for(;;){
        // in /drivers/BSP
        if (adc_vector_completed == 1){
            ADC_Copy_Vector();
        }
        sprintf (s,"\n\r ADC Read:  ");
        printf("%s",s);  
        for(j_1=0; j_1<(LAST_ADC_INPUT-FIRST_ADC_INPUT+1); j_1++){
             sprintf (s,"Ch(%d):%04d ", j_1, adc_FPSChannel[j_1]);
             printf("%s",s);
             }		
        CL2Board_setOLED();
        CL2Board_delay_ms(HALF_SEC_DELAY_MS);
        CL2Board_clearOLED();
        CL2Board_delay_ms(HALF_SEC_DELAY_MS);
    }

}







/*****************************************************************************
**
** EOF
**
*****************************************************************************/
