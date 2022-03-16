/***************************** C HEADER FILE *********************************
**
**  Project:    LCD Display Functions Driver for CL2bm1
**  Filename:   lcdcl2_3.h
**  Date:       17.12.2017 modified 26.01.2022
**
**  Modified    R.Oliva 
**  
******************************************************************************
**
**
******************************************************************************
**
**  VERSION HISTORY:
**  ----------------
**  initial Version:    1.1 
**  current version:    1.2A
**  Date:       28.01.2022
**  Revised by: R.Oliva
**  Description:
**  - v1.2A 01.22 name files all lowercase and underscore, 8.3 format
**  --- LCD Display Functions for CL2-R.OLIVA 2009
**  Adapted from indoor.c & Other.. 6.02.2009 
**   Hardware supposed for CL2bm1:
**   PC.4-PC.7 LCDDATA
**   PD.7 LCD_E
**   PC.3 LCD_RW
**   PC.2 LCD_RS
**   VCL2bm1 - ATMega644P/1284P - Convert to LCD 4x20
**   Rev 4.11.2017 after KIERAS Rule compliance analysis in:
**   C:\cvavr328\Work3\CL2\CL2_Drivers\LCD\LCD4x20(2010)\DOC
**        \LCD_4x20(2010)_TESTING FOR HEADER RULES COMPLIANCE(1stIteration)_v04-11-2017.docx
**   Rule #5 & #6 violations: Local functions and variables should be kept visible only to .c file,
**   not exposed in .h, and defined as static.
**              
**
*****************************************************************************/

#ifndef LCD_DRIVER_H

#define LCD_DRIVER_H
/****************************************************************************
**
**    MODULES USED 
**    13.12.21 Include stdint.h for normalized types
****************************************************************************/

#include <mega1284p.h>
#include <delay.h>
#include <stdint.h>

/****************************************************************************
**
**    DEFINITIONS AND MACROS / 
**
****************************************************************************/
// #define   20 since 3.5.2010 
#define MAX_LCD_COL 20

#define LCD_E       PORTD.7		/* LCD Control Lines */
#define LCD_RS      PORTC.2	    // Different from INDOOR.C!!! 14.3.2006
#define LCD_RW      PORTC.3

// Bit structure typedef for LCD - access on upper PortC 6.2.09
// In O'Cull book, p63, bit_x undefined ->compiler complains!
// Rule #13 (IHCR v2022) type names finish in "_t" --> added to bits
// replaced by bits_t
typedef struct {
   unsigned int bit_0:1;
   unsigned int bit_1:1;
   unsigned int bit_2:1;
   unsigned int bit_3:1;
   unsigned int bit_4:1;
   unsigned int bit_5:1;
   unsigned int bit_6:1;
   unsigned int bit_7:1;      
} bits_t;                                   

// LCD Port defines
#define LCD_DB0 PORTC.4
#define LCD_DB1 PORTC.5
#define LCD_DB2 PORTC.6
#define LCD_DB3 PORTC.7

/****************************************************************************
** 
**    EXPORTED VARIABLES
**    No Externaly accessible variables here..
**
****************************************************************************/


/****************************************************************************
**
**    EXPORTED FUNCTIONS
**    functions public to rest of program 18.12.2017
**    LCD Function Definitions - same as lcd1.c/.h in Mega128DEV2a
**    4.11.2017 - Local functions wr_half, wr_disp, line() declaration
**    moved to start of .c file
**    28.1.22 Naming rule #14 --> global functions preceded by module name 
**    "LCD_" prefix added
**
****************************************************************************/// *************************************************************


void LCD_init_display(void);
void LCD_clear_display(void);
void LCD_set_LCD_cur(char LCDrow, char LCDcol);
void LCD_disp_char(unsigned char c);
void LCD_disp_str(unsigned char *sa);	                  // display string from RAM 
void LCD_disp_cstr(unsigned char flash *sa);	          // display string from ROM 


#endif