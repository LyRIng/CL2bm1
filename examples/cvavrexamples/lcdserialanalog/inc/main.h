/***************************** C HEADER FILE *********************************
**
**  Project:   Serialanalog example for CL2bm1
* @file:     main.h
* @date:     03.03.22
**
**  Modified    R.Oliva  -
**
******************************************************************************
**
**
******************************************************************************
**
**  VERSION HISTORY:
**  ----------------
**  initial Version:    1.0
**  Date:
**  Revised by: R.Oliva
* @brief Example serialanalog CL2bm1 on Codevision
**  Description:
**      -
**      - Newer versions see top.
**
**
**
*****************************************************************************/

#ifndef MAIN_INCLUDED
#define MAIN_INCLUDED

/****************************************************************************
**
**    MODULES USED
**
****************************************************************************/
#include <stdio.h>
#include <mega1284p.h>
#include <delay.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <io.h>

// Drivers
// Board Support Package Driver
#include "..\drivers\bsp\inc\bsp_cl2.h"

// UART0, UART1 to bsp_cl2.h - Driver in CL2 -updated 2021

// ADC Driver / Timer1 triggered in CL2 -updated 2021
#include "..\drivers\adc\adctimer1\inc\adc_dr1.h"

// CL2_BOARD DEFINEs MOVED TO bsp_cl2.h

// Modules
// Hilevel Display in CL2 -updated 2022
#include "..\modules\display\inc\display.h"


/****************************************************************************
**
**    DEFINITIONS AND MACROS
**
****************************************************************************/

#define SUCCESS 1
#define ONE_SEC_DELAY_MS  1000
#define HALF_SEC_DELAY_MS 500
flash char CRLF[] = "\n\r";
flash char MAIN_VER[] = "SerialAnalog v1a 2022";      //   v1a 08-02-2022
flash char COM_MSG1[] = "\n\rProbando SerialAnalog v1a 11-03-2022\n\r";

/****************************************************************************
**
**    EXPORTED VARIABLES
**    declared here, but defined in .c file for global access.. 18.12.2017
**
****************************************************************************/
extern char s[25];
extern uint8_t j_1;

/****************************************************************************
**
**    EXPORTED FUNCTIONS
**    functions public to rest of program 18.12.2017
**
****************************************************************************/



#endif
/****************************************************************************
**
**    EOF
**
****************************************************************************/
