/***************************** C HEADER FILE *********************************
**
**  Project:    UART0 Driver for CL2bm1
**  Filename:   uart0_dr1.h
**  Date:       17.12.2017 modified 26.01.2022
**
**  Modified    R.Oliva  - Include interrupt routines in C separate file (test)
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
**  Date:       26.01.2022
**  Revised by: R.Oliva
**  Description:
**      - v1.2A 01.22 name files all lowercase and underscore, 8.3 format
**      - change #include to reflect new name
**      - local data, buffers and defines moved to .c file
**      - local data, buffers declared as static in .c file
**      - Only public definitions and functions left here in .h
**              
**
*****************************************************************************/

#ifndef UART0_INCLUDED
#define UART0_INCLUDED

/****************************************************************************
**
**    MODULES USED 
**    13.12.21 Include stdint.h for normalized types
****************************************************************************/
#include <stdio.h>
#include <stdint.h>

/****************************************************************************
**
**    DEFINITIONS AND MACROS / 
**
****************************************************************************/

#define UART_TER   0
#define BAUD_19200 19200

// Used by global ISR functions

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

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// USART0 Receiver buffer
// #define RX_BUFFER_SIZE0 8
// New value 22.3.2012
#define RX_BUFFER_SIZE0 24

// USART0 Transmitter buffer
// New value 22.3.2012
// #define TX_BUFFER_SIZE0 8
#define TX_BUFFER_SIZE0 24


/****************************************************************************
** 
**    EXPORTED VARIABLES
**    declared here, but defined in .c file for global access.. 18.12.2017
**    At first thought not global-  #reviewed rule 6 - 2022 but CVAVR for 
**    ISR Driven getchar(), putchar() requires these global variables and
**    defines - restore here as extern.
**
****************************************************************************/

extern char rx_buffer0[RX_BUFFER_SIZE0];

#if RX_BUFFER_SIZE0 <= 256
extern unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
#else
extern unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
#endif

// This flag is set on USART0 Receiver buffer overflow
extern bit rx_buffer_overflow0;


extern char tx_buffer0[TX_BUFFER_SIZE0];

#if TX_BUFFER_SIZE0 <= 256
extern unsigned char tx_wr_index0,tx_rd_index0,tx_counter0;
#else
extern unsigned int tx_wr_index0,tx_rd_index0,tx_counter0;
#endif


 
/****************************************************************************
**
**    EXPORTED FUNCTIONS
**    functions public to rest of program 18.12.2017
**
****************************************************************************/

// Interrupt routines
interrupt [USART0_RXC] void usart0_rx_isr(void);
interrupt [USART0_TXC] void usart0_tx_isr(void);

// Alternate getchar() defined with ISR Rx support
char getchar(void);

// *******************************************************************
// ** USART0_GetByte() Add Modbus Input - transfer Bytes not chars..**
// ** v1.2A renamed - Used by MB_Serial() FromModbusTest2()         **
// *******************************************************************
unsigned char USART0_GetByte(void);

// Alternate putchar() defined with ISR Tx support
void putchar(char c);

// *******************************************************************
// ** USART0_PutByte() Add Modbus Input - transfer Bytes not chars..**
// ** v1.2A renamed - Used by MB_Serial() FromModbusTest2()         **
// *******************************************************************
void USART0_PutByte(unsigned char txbyte);

// USART0_Init standard 19200,N,8,1 TxRx ISR support
void USART0_Init(void);



#endif
/****************************************************************************
**
**    EOF 
**
****************************************************************************/
