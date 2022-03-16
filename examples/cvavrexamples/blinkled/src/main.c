/***************************** C SOURCE FILE *********************************
**
**  Project:   Example Blinkled on CL2bm1 on Codevision
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
* @brief main Blink OLED file for Codevision
**  Description:
**      - Simple OLED Blink using bsp_cl2.c/.h driver
**      - version 1.1 uses new naming following IHRC
**
**
**
*****************************************************************************/

#include "../inc/main.h"

/*****************************************************************************
**
** DEFINITIONS
**
*****************************************************************************/

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
  * @brief  main() function **  Version 1.2 5.03.22
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

    // Simple OLED blink with blocking delays
    for(;;){
        // in /drivers/BSP
        CL2Board_setOLED();
        CL2Board_delay_ms(ONE_SEC_DELAY_MS);
        CL2Board_clearOLED();
        CL2Board_delay_ms(HALF_SEC_DELAY_MS);
    }

}







/*****************************************************************************
**
** EOF
**
*****************************************************************************/
