/***************************** C HEADER FILE *********************************
**
**  Project:    UART1 Driver for CL2bm1 (UART1A) 
**  Filename:   uart1dr1.h
**  Date:       30.01.2022
**
**  Modified    R.Oliva  - Include interrupt routines in C separate file (test)
**              UART1A with selectable BaudRate INIT
**              Refactored - filename and path + minimal changes 01.2022
**  
******************************************************************************
**
**
******************************************************************************
**
**  VERSION HISTORY:
**  ----------------
**  initial Version:    1.0
**  Date:       21.02.2018
**  Current version:    1.2A 
**  Date:       30.01.2022
**  Revised by: R.Oliva
**  Description:
**      - 2022 only filename/path changes
**      - Add stdint.h to avoid compilation errors        
**
*****************************************************************************/

#ifndef UART1_INCLUDED
#define UART1_INCLUDED

/****************************************************************************
**
**    MODULES USED 
**
****************************************************************************/
#include <stdio.h>
#include <stdint.h>

/****************************************************************************
**
**    DEFINITIONS AND MACROS
**
****************************************************************************/


//#define UART_485   1
#define BAUD_38400 38400

#ifndef RXB8
#define RXB8 1
#endif

#ifndef TXB8
#define TXB8 0
#endif

#ifndef UPE
#define UPE 2
#endif

#ifndef DOR
#define DOR 3
#endif

#ifndef FE
#define FE 4
#endif

#ifndef UDRE
#define UDRE 5
#endif

#ifndef RXC
#define RXC 7
#endif

#ifndef FRAMING_ERROR 
#define FRAMING_ERROR (1<<FE)
#endif

#ifndef PARITY_ERROR 
#define PARITY_ERROR (1<<UPE)
#endif

#ifndef DATA_OVERRUN 
#define DATA_OVERRUN (1<<DOR)
#endif

#ifndef DATA_REGISTER_EMPTY 
#define DATA_REGISTER_EMPTY (1<<UDRE)
#endif

#ifndef RX_COMPLETE 
#define RX_COMPLETE (1<<RXC)
#endif

// USART1 Receiver buffer
// New Value 22.3.2012 - works at 38400baud
// #define RX_BUFFER_SIZE1 8
#define RX_BUFFER_SIZE1 96

// USART1 Transmitter buffer
// 22.3.2012 New Value
// #define TX_BUFFER_SIZE1 8
#define TX_BUFFER_SIZE1 24

// UART1A - Init Baud Rate param 21.2.2018
#define PBAUD_9600  0
#define PBAUD_19200 1
#define PBAUD_38400 2



/****************************************************************************
** 
**    EXPORTED VARIABLES
**    declared here, but defined in .c file for global access.. 30.01.2018
**
****************************************************************************/

extern char rx_buffer1[RX_BUFFER_SIZE1];


#if RX_BUFFER_SIZE1 <= 256
extern unsigned char rx_wr_index1,rx_rd_index1,rx_counter1;
#else
extern unsigned int rx_wr_index1,rx_rd_index1,rx_counter1;
#endif

// This flag is set on USART1 Receiver buffer overflow
extern bit rx_buffer_overflow1;

extern char tx_buffer1[TX_BUFFER_SIZE1];

#if TX_BUFFER_SIZE1 <= 256
extern unsigned char tx_wr_index1,tx_rd_index1,tx_counter1;
#else
extern unsigned int tx_wr_index1,tx_rd_index1,tx_counter1;
#endif
 
/****************************************************************************
**
**    EXPORTED FUNCTIONS
**    functions public to rest of program 30.01.2018
**
****************************************************************************/

// Interrupt routines
interrupt [USART1_RXC] void usart1_rx_isr(void);
interrupt [USART1_TXC] void usart1_tx_isr(void);

// Alternate getchar1() defined with ISR Rx support
char getchar1(void);

// Alternate putchar1() defined with ISR Tx support
void putchar1(char c);

// USART1_Init modified (UART1A) for pbaud parameter 21.2.18
void USART1_Init(uint8_t pbaud);


#endif
/****************************************************************************
**
**    EOF 
**
****************************************************************************/
