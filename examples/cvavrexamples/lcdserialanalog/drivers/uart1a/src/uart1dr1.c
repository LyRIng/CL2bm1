/***************************** C SOURCE FILE *********************************
**
**  Project:    UART1 Driver for CL2bm1 (UART1A) 
**  Filename:   Uart1_dr1.c
**  Date:       21.02.2018 - refactored 30.01.2022
**  Version:    1.2A
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
**  Date:       21.02.2018
**  current Version:    1.2A
**  Date:       30.01.2022
**  Revised by: R.Oliva
**  Description:
**      - 2022 only filename/path changes
** 
**              
**
*****************************************************************************/

#include "../inc/uart1dr1.h" 

/*****************************************************************************
**
** DEFINITIONS
**
*****************************************************************************/



/*****************************************************************************
**
** UART1 Global Variables declared in uart1dr1.h
** only filename changes
** MEMORY IS ASSIGNED
** HERE FOLLOWING RULE #5
**
*****************************************************************************/

char rx_buffer1[RX_BUFFER_SIZE1];

#if RX_BUFFER_SIZE1 <= 256
unsigned char rx_wr_index1,rx_rd_index1,rx_counter1;
#else
unsigned int rx_wr_index1,rx_rd_index1,rx_counter1;
#endif

// This flag is set on USART1 Receiver buffer overflow
bit rx_buffer_overflow1;

char tx_buffer1[TX_BUFFER_SIZE1];

#if TX_BUFFER_SIZE1 <= 256
unsigned char tx_wr_index1,tx_rd_index1,tx_counter1;
#else
unsigned int tx_wr_index1,tx_rd_index1,tx_counter1;
#endif

/*****************************************************************************
**
** EXPORTED FUNCTIONS 
**
*****************************************************************************/

/****************************************************************************
**
** Initializes the UART1 - version UART1A with parameter
**
** Parameters: uint8_t pbaud, can take values:
** #define PBAUD_9600  0
** #define PBAUD_19200 1
** #define PBAUD_38400 2
** Then for each option, considering CLK=14.7456E06 Hz
**	38400 -> u2x=0 ->UBRR=23dec = 0x17
**  19200 -> u2x=0 ->UBRR=47dec = 0x2F
**	9600  -> u2x=0 ->UBRR=95dec = 0x5F
**
** Returns: NONE
** -2022 no changes
****************************************************************************/

// USART1_Init modified for pbaud parameter
void USART1_Init(uint8_t pbaud)
{
  switch(pbaud){
	case PBAUD_9600:	  
		// USART1 initialization 9600 baud 
		// Communication Parameters: 8 Data, 1 Stop, No Parity
		// USART1 Receiver: On
		// USART1 Transmitter: On
		// USART1 Mode: Asynchronous
		// USART1 Baud Rate: 9600
		UCSR1A=0x00;
		UCSR1B=0xD8;
		UCSR1C=0x06;
		UBRR1H=0x00;
		UBRR1L=0x5F; // ==95 dec for 9600, U2X=0
		break;
	case PBAUD_19200:	  
		// USART1 initialization 19200
		// Communication Parameters: 8 Data, 1 Stop, No Parity
		// USART1 Receiver: On
		// USART1 Transmitter: On
		// USART1 Mode: Asynchronous
		// USART1 Baud Rate: 19200
		UCSR1A=0x00;
		UCSR1B=0xD8;
		UCSR1C=0x06;
		UBRR1H=0x00;
		UBRR1L=0x2F; // ==47 dec for 19200, U2X=0
		break;
	case PBAUD_38400:	  
		// USART1 initialization 38400 baud (PWRC2 - V22.3.2012)
		// Communication Parameters: 8 Data, 1 Stop, No Parity
		// USART1 Receiver: On
		// USART1 Transmitter: On
		// USART1 Mode: Asynchronous
		// USART1 Baud Rate: 38400
		UCSR1A=0x00;
		UCSR1B=0xD8;
		UCSR1C=0x06;
		UBRR1H=0x00;
		UBRR1L=0x17; // ==23 dec for 38400, U2X=0
		break;
	default:
        printf("\n\r Parametro COM1 Incorrecto! (9600, 19200 o 38400)");
        break;		 
	}
}

/*****************************************************************************
**
** USART1 Receiver interrupt service routine
** Buffer Size 256 not considered..30.1.18 - -2022 no changes
*****************************************************************************/

interrupt [USART1_RXC] void usart1_rx_isr(void)
{
char status,data;
status=UCSR1A;
data=UDR1;
if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
   rx_buffer1[rx_wr_index1++]=data;
   // #if RX_BUFFER_SIZE1 == 256
   // special case for receiver buffer size=256
   // if (++rx_counter1 == 0)
   //    {
   // #else
   if (rx_wr_index1 == RX_BUFFER_SIZE1) rx_wr_index1=0;
   if (++rx_counter1 == RX_BUFFER_SIZE1)
      {
      rx_counter1=0;
   //#endif
      rx_buffer_overflow1=1;
      }
   }
}


/*****************************************************************************
**
** Creates an Alternat Getchar1() function using the USART1 ISR
** 30.1.18 -2022 no changes
*****************************************************************************/

// Get a character from the USART1 Receiver buffer
#pragma used+
char getchar1(void)
{
char data;
while (rx_counter1==0);
data=rx_buffer1[rx_rd_index1++];
#if RX_BUFFER_SIZE1 != 256
if (rx_rd_index1 == RX_BUFFER_SIZE1) rx_rd_index1=0;
#endif
#asm("cli")
--rx_counter1;
#asm("sei")
return data;
}
#pragma used-



/*****************************************************************************
**
** USART1 Transmitter interrupt service routine -2022 no changes
**
*****************************************************************************/

interrupt [USART1_TXC] void usart1_tx_isr(void)
{
if (tx_counter1)
   {
   --tx_counter1;
   UDR1=tx_buffer1[tx_rd_index1++];
#if TX_BUFFER_SIZE1 != 256
   if (tx_rd_index1 == TX_BUFFER_SIZE1) tx_rd_index1=0;
#endif
   }
}
/*****************************************************************************
**
** Creates an Alternate putchar1() function using the USART1 ISR
** 30.1.18 -2022 no changes
*****************************************************************************/

// Write a character to the USART1 Transmitter buffer
#pragma used+
void putchar1(char c)
{
while (tx_counter1 == TX_BUFFER_SIZE1);
#asm("cli")
if (tx_counter1 || ((UCSR1A & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer1[tx_wr_index1++]=c;
#if TX_BUFFER_SIZE1 != 256
   if (tx_wr_index1 == TX_BUFFER_SIZE1) tx_wr_index1=0;
#endif
   ++tx_counter1;
   }
else
   UDR1=c;
#asm("sei")
}
#pragma used-



/*****************************************************************************
**
** EOF 
**
*****************************************************************************/

