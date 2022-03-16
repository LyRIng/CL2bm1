/***************************** C HEADER FILE *********************************
**
**  Project:   PWRC2 CL2bm1
* @file:       display.h
**  Version:    1.1
**  Date:       14.12.21
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
* @brief display header CL2 projects on Codevision
**  Description:
**      - 
**      - Newer versions see top. 
** 
**              
**
*****************************************************************************/

#ifndef DISPLAY_INCLUDED
#define DISPLAY_INCLUDED

/****************************************************************************
**
**    MODULES USED 
**
****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
// LCD Driver in CL2 -updated 2021
#include "..\..\..\drivers\lcd\lcd4x20\inc\lcdcl2_3.h"

/****************************************************************************
**
**    DEFINITIONS AND MACROS
**
****************************************************************************/

#define DISPLAY_WELCOME 1
#define DISPLAY_SD_OK   2





/****************************************************************************
** 
**    EXPORTED VARIABLES
**    declared here, but defined in .c file for global access.. 18.12.2017
**
****************************************************************************/

// Only two main options for this version
typedef enum displaytype_en{
    LCD4X20 = 0,
    LCD2X16 = 1
}displaytype_t;


 
/****************************************************************************
**
**    EXPORTED FUNCTIONS
**    functions public to rest of program 18.12.2017
**
****************************************************************************/

void Display_Init(displaytype_t disptype);

void Display_Screen(uint8_t dispParam);

void Display_RTC(void);

void Display_Update(void);

void Display_Line(uint8_t line,char *Display_buffer1);



#endif
/****************************************************************************
**
**    EOF 
**
****************************************************************************/
