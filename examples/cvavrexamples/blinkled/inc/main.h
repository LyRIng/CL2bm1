/***************************** C HEADER FILE *********************************
**
**  Project:   PWRC2 v10a for CL2bm1
* @file:     main.h
* @date:     13.12.21
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
* @brief Example Blinkled CL2bm1 on Codevision
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

// Uncomment to use COMs CL2 board configuration
// #define COM_CFG_DEFINED

// Uncomment to Blink OLED + Display BL once
// #define INIT_BLINK_OLED_CFG_DEFINED


// Modules



/****************************************************************************
**
**    DEFINITIONS AND MACROS
**
****************************************************************************/

#define SUCCESS 1
#define ONE_SEC_DELAY_MS  1000
#define HALF_SEC_DELAY_MS 500

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



#endif
/****************************************************************************
**
**    EOF
**
****************************************************************************/
