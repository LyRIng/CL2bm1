/***************************** C SOURCE FILE *********************************
**
**  Project:    UART0 Driver for CL2bm1
* @file:        uart0_dr1.c
**  Version:    1.2A
**  Date:       v18.02.2019 / rev26.01.2022
**  Modified    R.Oliva  - Include interrupt routines in C separate file (test)
**  
******************************************************************************
**
**
******************************************************************************
**
**  VERSION HISTORY:
**  ----------------
**  initial Version:    1.1 (2017)
**  current version:    1.2A
**  Date:       27.01.2022
**  Revised by: R.Oliva
* @brief UART0 Driver for CL2bm1 boards - 2022
**  Description:
**      - v1.2A 01.22 name files all lowercase and underscore, 8.3 format
**      - change #include to reflect new name
**      - REVERTED local data, buffers and defines moved to .c file
**      - REVERTED , buffers declared as static in .c file
**      - Only public definitions and functions left in .h
**      - GetByte() and PutByte() renamed to USART0_GetByte(),USART0_PutByte()
**         
**              
**
*****************************************************************************/

#include "../inc/uart0dr1.h" 

/*****************************************************************************
**
** DEFINITIONS  
**
*****************************************************************************/


/*****************************************************************************
**
** UART0 Reverted to global variables 27.1.22
**
*****************************************************************************/

char rx_buffer0[RX_BUFFER_SIZE0];

#if RX_BUFFER_SIZE0 <= 256
unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
#else
unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
#endif

// This flag is set on USART0 Receiver buffer overflow
bit rx_buffer_overflow0;


char tx_buffer0[TX_BUFFER_SIZE0];

#if TX_BUFFER_SIZE0 <= 256
unsigned char tx_wr_index0,tx_rd_index0,tx_counter0;
#else
unsigned int tx_wr_index0,tx_rd_index0,tx_counter0;
#endif


/*****************************************************************************
**
** EXPORTED FUNCTIONS 
**
*****************************************************************************/

/****************************************************************************
** 1.USART0_Init()
** Initializes the UART0
**
** Parameters: NONE
**
** Returns: NONE
**
****************************************************************************/



// USART0_Init standard 19200,N,8,1 TxRx ISR support
void USART0_Init(void)
{
  // USART0 initialization - PWRC2
  // Communication Parameters: 8 Data, 1 Stop, No Parity
  // USART0 Receiver: On
  // USART0 Transmitter: On
  // USART0 Mode: Asynchronous
  // USART0 Baud Rate: 19200!
  UCSR0A=0x00;
  UCSR0B=0xD8;
  UCSR0C=0x06;
  UBRR0H=0x00;
  UBRR0L=0x2F;
}


/*****************************************************************************
** 2. RX ISR
** USART0 Receiver interrupt service routine
** Buffer Size 256 not considered..18.12.2017
*****************************************************************************/

interrupt [USART0_RXC] void usart0_rx_isr(void)
{
 char status,data;
 status=UCSR0A;
 data=UDR0;
 if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
  {
   rx_buffer0[rx_wr_index0++]=data;
   //#if RX_BUFFER_SIZE0 == 256     (commented out 18.12.2017)
   // special case for receiver buffer size=256
   // if (++rx_counter0 == 0)
   //   {
   //#else
   if (rx_wr_index0 == RX_BUFFER_SIZE0) rx_wr_index0=0;
   if (++rx_counter0 == RX_BUFFER_SIZE0)
      {
      rx_counter0=0;
   //#endif
      rx_buffer_overflow0=1;
      }
   }
  }


/*****************************************************************************
** 3. Alternate getchar
** Creates an Alternat Getchar() function using the USART0 ISR
** 18.12.2017
*****************************************************************************/

// Internal CVAVR compiler commands:
#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART0 Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter0==0);
data=rx_buffer0[rx_rd_index0++];
#if RX_BUFFER_SIZE0 != 256
if (rx_rd_index0 == RX_BUFFER_SIZE0) rx_rd_index0=0;
#endif
#asm("cli")
--rx_counter0;
#asm("sei")
return data;
}
#pragma used-
#endif

// *******************************************************************
// ** 4.USART0_GetByte() Add Modbus Input transfer Bytes not chars..**
// ** v1.0 30-05-2012 - Used by MB_Serial() FromModbusTest2()       **
// *******************************************************************
unsigned char USART0_GetByte(void)
{
unsigned char data;
while (rx_counter0==0);
data=rx_buffer0[rx_rd_index0++];
#if RX_BUFFER_SIZE0 != 256
if (rx_rd_index0 == RX_BUFFER_SIZE0) rx_rd_index0=0;
#endif
#asm("cli")
--rx_counter0;
#asm("sei")
return data;
}


/*****************************************************************************
** 5. TX ISR
** USART0 Transmitter interrupt service routine
**
*****************************************************************************/

interrupt [USART0_TXC] void usart0_tx_isr(void)
{
if (tx_counter0)
   {
   --tx_counter0;
   UDR0=tx_buffer0[tx_rd_index0++];
#if TX_BUFFER_SIZE0 != 256
   if (tx_rd_index0 == TX_BUFFER_SIZE0) tx_rd_index0=0;
#endif
   }
}

/*****************************************************************************
** 6. Alternate putchar()
** Creates an Alternate putchar() function using the USART0 ISR
** 18.12.2017
*****************************************************************************/

// Internal CVAVR compiler commands:
#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART0 Transmitter buffer
#define _ALTERNATE_PUTCHAR_
#pragma used+
void putchar(char c)
{
while (tx_counter0 == TX_BUFFER_SIZE0);
#asm("cli")
if (tx_counter0 || ((UCSR0A & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer0[tx_wr_index0++]=c;
#if TX_BUFFER_SIZE0 != 256
   if (tx_wr_index0 == TX_BUFFER_SIZE0) tx_wr_index0=0;
#endif
   ++tx_counter0;
   }
else
   UDR0=c;
#asm("sei")
}
#pragma used-
#endif

// *******************************************************************
// ** 7. USART0_PutByte() Added f/Modbus output-tx  Bytes not chars.**
// ** v1.2 renamed  - Used by FinaliseTransmit and ExceptionResp()  **
// *******************************************************************
void USART0_PutByte(unsigned char txbyte)
{
while (tx_counter0 == TX_BUFFER_SIZE0);
#asm("cli")
if (tx_counter0 || ((UCSR0A & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer0[tx_wr_index0++]=txbyte;
#if TX_BUFFER_SIZE0 != 256
   if (tx_wr_index0 == TX_BUFFER_SIZE0) tx_wr_index0=0;
#endif
   ++tx_counter0;
   }
else
   UDR0=txbyte;
#asm("sei")
}



/*****************************************************************************
**
** EOF 
**
*****************************************************************************/

