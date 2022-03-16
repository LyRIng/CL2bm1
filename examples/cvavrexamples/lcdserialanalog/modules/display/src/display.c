/***************************** C SOURCE FILE *********************************
**
**  Project:   PWRC2 CL2bm1
* @file:       display.c
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
**  initial Version:    1.1 
**  Date:       14.12.21
**  Revised by: R.Oliva
* @brief display module CL2 projects on Codevision
**  Description:
**      - 
**      - Newer versions see top. 
** 
**              
**
*****************************************************************************/

#include "..\inc\display.h" 

/*****************************************************************************
**
** DEFINITIONS
**
*****************************************************************************/

#define MAX_LCD_ROW   4
#define MAX_LCD_ROW2  2
#define MAX_LCD_COL16 16

flash char WELCOME_LINE0_16[] = "*** Welcome! ***";      //   v1a 08-02-2022
flash char WELCOME_LINE1_16[] = "** CL2b Board **";      //   v1a 08-02-2022
flash char WELCOME_LINE0_20[] = "***** Welcome! *****";  //   v1a 08-02-2022
flash char WELCOME_LINE1_20[] = "**** CL2b Board ****";  //   v1a 08-02-2022
flash char WELCOME_LINE2_20[] = "*                  *";  //   v1a 08-02-2022
flash char WELCOME_LINE3_20[] = "********************";  //   v1a 08-02-2022

/*****************************************************************************
**
** LOCAL VARIABLES
**
*****************************************************************************/

static uint8_t display_max_col;
static uint8_t display_max_row;
static uint8_t display_type_user;

/*****************************************************************************
**
** Global Variables declared in filemodel.h
** MEMORY IS ASSIGNED
** HERE FOLLOWING RULE #5
**
*****************************************************************************/

/*****************************************************************************
**
** EXPORTED FUNCTIONS 
**
*****************************************************************************/

/****************************************************************************
** Display_Init(type) 
** to use Doxygen
**
  * @brief  Initializes LCD display 
  * @param  disptype
  * @retval None, but sets local variables 
           display_type_user
           display_max_col
           display_max_row
*****************************************************************************/
void Display_Init(displaytype_t disptype){
    LCD_init_display();
    LCD_clear_display();
    display_type_user = disptype;
    switch(disptype){
				 case LCD4X20:
                  display_max_col = MAX_LCD_COL;
                  display_max_row = MAX_LCD_ROW;
				  break;
				 case LCD2X16:
                  display_max_col = MAX_LCD_COL16;
                  display_max_row = MAX_LCD_ROW2;				  
				  break; 
	}

}

/****************************************************************************
** Display_Screen(param) 
** to use Doxygen
**
  * @brief  Displays LCD with Welcome message or other 
  * @param  dispParam
  * @retval None
*****************************************************************************/
void Display_Screen(uint8_t dispParam){
    if(DISPLAY_WELCOME == dispParam){
        LCD_set_LCD_cur(0, 0);      // Origin
        switch(display_type_user){
				 case LCD4X20:
                    LCD_disp_cstr(WELCOME_LINE0_20); 
                    LCD_set_LCD_cur(1, 0);          
                    LCD_disp_cstr(WELCOME_LINE1_20);
                    LCD_set_LCD_cur(2, 0);          
                    LCD_disp_cstr(WELCOME_LINE2_20);                    
                    LCD_set_LCD_cur(3, 0);          
                    LCD_disp_cstr(WELCOME_LINE3_20);                    
				    break;
				 case LCD2X16:
                    LCD_disp_cstr(WELCOME_LINE0_16); 
                    LCD_set_LCD_cur(1, 0);          
                    LCD_disp_cstr(WELCOME_LINE1_16);
                    break; 
    	}
    }    
}

/****************************************************************************
** Display_Line(line, *buffer) 
** to use Doxygen
**
  * @brief  Displays a buffer in Ram at start of line 
  * @param  line, Display_buffer1
  * @retval None, but uses local variables set in Display_Init 
           display_max_col
           display_max_row
*****************************************************************************/
void Display_Line(uint8_t line,char *Display_buffer1){
                    printf("\n\r Disp line:%d, bufferlen: %d",line,strlen(Display_buffer1));
                    if (line < display_max_row){
                        if (strlen(Display_buffer1) <= display_max_col){
                            LCD_set_LCD_cur(line, 0);          
                            LCD_disp_str(Display_buffer1);
                            //Debug
                            printf("\n\r DispOk");
                        }
                	}
                    else {         
                        // Debug 
                        printf("\n\r ErrDisp line:%d, bufferlen: %d",line,strlen(Display_buffer1));
                    }
}


void Display_RTC(void){
}

void Display_Update(void){
}

/*****************************************************************************
**
** EOF 
**
*****************************************************************************/

