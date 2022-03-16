/***************************** C SOURCE FILE *********************************
**
**  Project:    Board Support Package for CL2bm1
*   @file:      bsp_cl2.c
**  Version:    1.2a
*   @date:      05-03-2022
*   @author:    Rafael Oliva
**
******************************************************************************
**
**
******************************************************************************
**
**  VERSION HISTORY:
**  ----------------
**  initial Version:    1.1
**  current Version:    1.2a
**  Date:       30-01-2022 revised 05-03-22
**  Revised by: R.Oliva
*   @brief filemodel for CL2 projects on Codevision
**  Description:
**      - Function renaming for LyR-IHCR
**      
**
**
**
*****************************************************************************/

#include "..\inc\bsp_cl2.h"


/*****************************************************************************
**
** DEFINITIONS
**
*****************************************************************************/

// Default BaudRates for Simple INIT
#define BAUD_RATE_DEFAULT 19200
#define BAUD_INIT (_MCU_CLOCK_FREQUENCY_/(BAUD_RATE_DEFAULT*16L)-1)

/*****************************************************************************
**
** Global Variables declared in .h
** MEMORY IS ASSIGNED
** HERE FOLLOWING RULE #5
**
*****************************************************************************/
// Variable for comport value
// comport_t cl2_boardComport;

/*****************************************************************************
**
** LOCAL FUNCTIONS 
**
*****************************************************************************/
void Initialize_CL2_simple(void);      // 19.11.2017 Simple CL2bm1 
                                       // initialize (Test_UART) with 1284P
void Initialize_CL2(void);             // PWRC2 12.9.2010 CL2bm1 initialize
                                       // with 1284P

/*****************************************************************************
**
** EXPORTED FUNCTIONS 
**
*****************************************************************************/

/****************************************************************************
** Generalized Board initialization - parameter example PWRC2 
** to use Doxygen
**
  * @brief  Initializes the Board
  * @param  uint8_t boardConfig
  * @retval None 
  * void CL2Board_init(systemtype_t boardConfig);  
*****************************************************************************/

void CL2Board_init(systemtype_t boardConfig){
	switch(boardConfig){
				 case CL2BOARD_SIMPLE:
				  Initialize_CL2_simple();
				  break;
				 case CL2BOARD_PWRC2:
				  Initialize_CL2();
				  break; 
	}
}

/****************************************************************************
** Generalized UART Selector Wrapper added 13-12-2021
** Calls low level /uart0 and /uart1 driver init functions
** to use Doxygen
**
  * @brief  Initializes a UART
  * @param  comport_t comport
  * @param  uint16_t baud
  * @retval None                                                               
  * void CL2Board_uartConfig(comport_t comport, uint16_t baud);
*****************************************************************************/

#ifdef CL2_BOARD_COM_CFG_DEFINED

void CL2Board_uartConfig(comport_t comport, baud_t baud)
{
  // comport = comport;
  // baud    = baud;
  if (UART0_TER == comport){ 
        USART0_Init();     
        }
  else if (UART1_485 == comport){
      switch (baud)
             {
             case UART_BAUD9600:
             USART1_Init(PBAUD_9600);
             break;
             case UART_BAUD19200:
             USART1_Init(PBAUD_19200);
             break;                   
             case UART_BAUD38400:
             USART1_Init(PBAUD_38400);
             break;                   
             } // end switch     
  }            // end else
}


#endif


/****************************************************************************
** One-time Blink OLED for startout,also tests Backlight on/off
** to use Doxygen
**
  * @brief  Blinks LED and Backlight LCD once (use with Display)
  * @param  none
  * @retval None
*****************************************************************************/

#ifdef CL2BOARD_INIT_BLINK_OLED_CFG_DEFINED
void CL2Board_blinkOLED(void){
    // from main1284.c
    BACK_LIGHT = LOGIC_ON;
    OLED = LOGIC_ON;
    delay_ms(500); // milliseconds
    OLED = LOGIC_OFF;
    // Turnoff backlight too
    BACK_LIGHT = LOGIC_OFF;
}
#endif

/****************************************************************************
** Set OLED to ON 
** to use Doxygen
**
  * @brief  Turns on OLED on CL2
  * @param  none
  * @retval None
*****************************************************************************/
void CL2Board_setOLED(void){
    OLED = LOGIC_ON;
}

/****************************************************************************
** Clear OLED to OFF 
** to use Doxygen
**
  * @brief  Turns off OLED on CL2
  * @param  none
  * @retval None
*****************************************************************************/
void CL2Board_clearOLED(void){
    OLED = LOGIC_OFF;
}

/****************************************************************************
** Simple blocking delay 
** to use Doxygen
**
  * @brief  Sets delay in milliseconds, uses internal CVAVR function
  * @param  none
  * @retval None
*****************************************************************************/
// 
void CL2Board_delay_ms(uint16_t millis){
    delay_ms(millis);
}

/*****************************************************************************
**
**  Initialize_CL2_simple() Depends on processor used and board.
**  Simple Version TAKES AWAY Interrupts /  modified 19.11.2017
**  For LCD and RTC testing..
**  Current for Mega1284 uses AtMega1284P and CL2bm1
**  COM0 at 19200,N,8,1 - traditional
**  COM1 not used
**  Port C and one pin PortD used for LCD.
**  Timer0 not used, 
**  Timer1 not used
**  ADC not set
**
*****************************************************************************/

void Initialize_CL2_simple(void)
{
  CLI();      /* disable all interrupts */


 // Input/Output Ports initialization

  // Port A initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  PORTA=0x00;
  DDRA=0x00;

  // Port B initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  PORTB=0x00;
  DDRB=0x00;

  // Port C initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  // Debug: set Bit C.7 to 1 3.2.09
  // v0.3 6-2-09 Set PC.2-7 as outputs - For LCD..
  PORTC=0x00;
  DDRC=0xFC;

  // Port D initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  // v0.3 6-2-09 Set Pd.7 as output - For LCD 0x80
  // V1284p-7 Set Pd.5./.6 to outputs too for OLED and BacklightLCD 24.7.10 0xE0
  PORTD=0x00;
  //DDRD=0x80;
  DDRD=0xE0;

// Following from SDCard4.c initialization..19.11.2017

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=(0<<EXCLK) | (0<<AS2);
TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
TCCR2B=(0<<WGM22) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// Timer/Counter 3 initialization
// Clock source: System Clock
// Clock value: Timer3 Stopped
// Mode: Normal top=0xFFFF
// OC3A output: Disconnected
// OC3B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer3 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR3A=(0<<COM3A1) | (0<<COM3A0) | (0<<COM3B1) | (0<<COM3B0) | (0<<WGM31) | (0<<WGM30);
TCCR3B=(0<<ICNC3) | (0<<ICES3) | (0<<WGM33) | (0<<WGM32) | (0<<CS32) | (0<<CS31) | (0<<CS30);
TCNT3H=0x00;
TCNT3L=0x00;
ICR3H=0x00;
ICR3L=0x00;
OCR3AH=0x00;
OCR3AL=0x00;
OCR3BH=0x00;
OCR3BL=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);

// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2);

// Timer/Counter 3 Interrupt(s) initialization
TIMSK3=(0<<ICIE3) | (0<<OCIE3B) | (0<<OCIE3A) | (0<<TOIE3);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-15: Off
// Interrupt on any change on pins PCINT16-23: Off
// Interrupt on any change on pins PCINT24-31: Off
EICRA=(0<<ISC21) | (0<<ISC20) | (0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
EIMSK=(0<<INT2) | (0<<INT1) | (0<<INT0);
PCICR=(0<<PCIE3) | (0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);

// USART0 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART0 Receiver: On
// USART0 Transmitter: On
// USART0 Mode: Asynchronous
// USART0 Baud Rate: 19200
UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
UBRR0H=0x00;
UBRR0L=0x2F;

/* initialize the USART0 TX, 8N1, Baud rate: 19200 */
UCSR0A=0;
UCSR0B=1<<TXEN0;
UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
UBRR0H=BAUD_INIT>>8;
UBRR0L=BAUD_INIT&0xFF;

// USART1 initialization
// USART1 disabled
UCSR1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (0<<RXEN1) | (0<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
ADCSRB=(0<<ACME);
// Digital input buffer on AIN0: On
// Digital input buffer on AIN1: On
DIDR1=(0<<AIN0D) | (0<<AIN1D);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);


// This kept from old Initialize_CL2() function..
  // ********************************
  // Two Wire Bus initialization
  // Bit Rate:
  // 17.2.09 Changed TWBR to 0x0c for 184kHz..
  // if XTAL = 7.3728e6 means:
  // Bit Rate: 184.320 kHz
  // ** NOTE: For Bit Rate: 115.200 kHz
  // ** then CV-Wiz selectede TWBR=0x18;
  // TWBR=0x0C;
  // Two Wire Bus Slave Address: 0h
  // General Call Recognition: Off
  // TWAR=0x00;
  // Generate Acknowledge Pulse: Off
  // TWI Interrupt:  OFF
  // TWCR=0x05 - would be for TWI IRQ ON;
  // TWCR=0x04; // Same as v32..
  // TWSR=0x00;

  // Two Wire Bus initialization for XTal 14.756MHz 22.3.2012
  // Bit Rate: 184.320 kHz
  TWBR=0x20;
  // Two Wire Bus Slave Address: 0h
  // General Call Recognition: Off
  TWAR=0x00;
  // Generate Acknowledge Pulse: Off
  // TWI Interrupt: Off
  TWCR=0x04;
  TWSR=0x00;


  // Watchdog Timer initialization - CV-Wiz (07.2010)
  // Watchdog Timer Prescaler: OSC/2k
  // Watchdog Timer interrupt: Off
  // Re-eanble 30-9-2010
  // b4 WDCE, b3 WDE
  // b5 b2 b1 b0 WDP3-WDP0 Prescaler
  #pragma optsize-
  #asm("wdr")
  WDTCSR=0x18;    // 0001 1000
  //WDTCSR=0x08;    // 0000 1000  -- Prescaler in 16ms
  WDTCSR=0x28;    // 0010 1000  -- Prescaler in 1000 = 4sec
  #ifdef _OPTIMIZE_SIZE_
  #pragma optsize+
  #endif

  // Global enable interrupts
   SEI();      /* re-enable interrupts 19.11.2017 */

}

/*****************************************************************************
**
**  Initialize_CL2() Depends on processor used and board.
**  Vesion 22.03.2012
**  Current for Mega1284 uses AtMega1284P and CL2bm1, connected to M4/E board
**  with TRIADC via I2C at 184.32 kHz - COM0 at 9600,8,N,1
**  COM1 at 38400,8,N,1
**  Port C and one pin PortD used for LCD.
**  Timer0 used, rest not yet.
**  ADC set for Free-Running at 912kHz, new option in Mega1284P - must be tested.
**  from: main1284.c PWRC2 used in v9G2 2020
*****************************************************************************/

void Initialize_CL2(void)
{
  CLI();      /* disable all interrupts */


 // Input/Output Ports initialization

  // Port A initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  PORTA=0x00;
  DDRA=0x00;

  // Port B initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  PORTB=0x00;
  DDRB=0x00;

  // Port C initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  // Debug: set Bit C.7 to 1 3.2.09
  // v0.3 6-2-09 Set PC.2-7 as outputs - For LCD..
  PORTC=0x00;
  DDRC=0xFC;

  // Port D initialization
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
  // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
  // v0.3 6-2-09 Set Pd.7 as output - For LCD 0x80
  // V1284p-7 Set Pd.5./.6 to outputs too for OLED and BacklightLCD 24.7.10 0xE0
  PORTD=0x00;
  //DDRD=0x80;
  DDRD=0xE0;


  // Timer/Counter 0 initialization - 14.76MHz (22.3.2012) AtMega1284P
  // Clock source: System Clock
  // Clock value: 14.400 kHz
  // Mode: Normal top=FFh
  // OC0A output: Disconnected
  // OC0B output: Disconnected
  TCCR0A=0x00;
  TCCR0B=0x05;
  TCNT0=0x00;
  OCR0A=0x00;
  OCR0B=0x00;

  #ifdef XTAL_732MHZ
  // Timer/Counter 0 initialization
  // Clock source: System Clock
  // Clock value: 7.2kHz = CK/1024 (TCCR0B = 0x05)
  // Mode: Normal top=FFh
  // OC0A output: Disconnected
  // OC0B output: Disconnected
  TCCR0A=0x00;
  TCCR0B=0x05;
  TCNT0=0x00;
  OCR0A=0x00;
  OCR0B=0x00;
  #endif


  // Timer/Counter 1 initialization
  // Clock source: System Clock
  // Clock value: Timer1 Stopped
  // Mode: Normal top=FFFFh
  // OC1A output: Discon.
  // OC1B output: Discon.
  // Noise Canceler: Off
  // Input Capture on Falling Edge
  // Timer1 Overflow Interrupt: Off
  // Input Capture Interrupt: Off
  // Compare A Match Interrupt: Off
  // Compare B Match Interrupt: Off
  TCCR1A=0x00;
  TCCR1B=0x00;
  TCNT1H=0x00;
  TCNT1L=0x00;
  ICR1H=0x00;
  ICR1L=0x00;
  OCR1AH=0x00;
  OCR1AL=0x00;
  OCR1BH=0x00;
  OCR1BL=0x00;

  // Timer/Counter 2 initialization
  // Clock source: System Clock
  // Clock value: Timer2 Stopped
  // Mode: Normal top=FFh
  // OC2A output: Disconnected
  // OC2B output: Disconnected
  ASSR=0x00;
  TCCR2A=0x00;
  TCCR2B=0x00;
  TCNT2=0x00;
  OCR2A=0x00;
  OCR2B=0x00;

  // New in 1284P - 23.7.2010
  // Timer/Counter 3 initialization
  // Clock source: System Clock
  // Clock value: Timer3 Stopped
  // Mode: Normal top=FFFFh
  // OC3A output: Discon.
  // OC3B output: Discon.
  // Noise Canceler: Off
  // Input Capture on Falling Edge
  // Timer3 Overflow Interrupt: Off
  // Input Capture Interrupt: Off
  // Compare A Match Interrupt: Off
  // Compare B Match Interrupt: Off
  TCCR3A=0x00;
  TCCR3B=0x00;
  TCNT3H=0x00;
  TCNT3L=0x00;
  ICR3H=0x00;
  ICR3L=0x00;
  OCR3AH=0x00;
  OCR3AL=0x00;
  OCR3BH=0x00;
  OCR3BL=0x00;

// Conditional EXT_IRQ init, added 24-10-2012
#ifdef NO_OSCOUT_INTERRUPT
  // External Interrupt(s) initialization
  // INT0: Off
  // INT1: Off
  // INT2: Off
  // Interrupt on any change on pins PCINT0-7: Off
  // Interrupt on any change on pins PCINT8-15: Off
  // Interrupt on any change on pins PCINT16-23: Off
  // Interrupt on any change on pins PCINT24-31: Off
  EICRA=0x00;
  EIMSK=0x00;
  PCICR=0x00;
#else
  // External Interrupt(s) initialization
  // INT0: Off
  // INT1: Off
  // INT2: Off
  // Interrupt on any change on pins PCINT0-7: Off
  // Interrupt on any change on pins PCINT8-15: Off
  // Interrupt on any change on pins PCINT16-23: Off
  // Interrupt on any change on pins PCINT24-31: On
  EICRA=0x00;
  EIMSK=0x00;
  PCMSK3=0x10;
  PCICR=0x08;
  PCIFR=0x08;
#endif

  // Timer/Counter 0 Interrupt(s) initialization
  // Timer(s)/Counter(s) Interrupt(s) initialization
  TIMSK0=0x01;

  // Timer/Counter 1 Interrupt(s) initialization
  TIMSK1=0x00;
  // Timer/Counter 2 Interrupt(s) initialization
  TIMSK2=0x00;
  // New in 1284P - 23.7.2010
  // Timer/Counter 3 Interrupt(s) initialization
  TIMSK3=0x00;

  // USART0 initialization
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


/* En PWRC / 12
      // USART0 initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART0 Receiver: On
    // USART0 Transmitter: On
    // USART0 Mode: Asynchronous
    UCSR0A=0x00;
    UCSR0B=0xD8;
    UCSR0C=0x06;
    UBRR0H=0x00;
    // USART0 Baud rate: 19200 - changed 08.04.06
     UBRR0L=0x2F;
     baud1 = 19200;

     */

  #ifdef UNI_TEST1
  // USART1 initialization - 9600 Unitest1
  // Communication Parameters: 8 Data, 1 Stop, No Parity
  // USART1 Receiver: On
  // USART1 Transmitter: On
  // USART1 Mode: Asynchronous
  // USART1 Baud Rate: 9600
  UCSR1A=0x00;
  UCSR1B=0xD8;
  UCSR1C=0x06;
  UBRR1H=0x00;
  UBRR1L=0x2F;
  #endif

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
  UBRR1L=0x17;

  // Analog Comparator initialization
  // Analog Comparator: Off
  // Analog Comparator Input Capture by Timer/Counter 1: Off
  ACSR=0x80;
  ADCSRB=0x00;

  // ADC initialization v128-1 / Leave as proposed by CV-Wiz 23.7.10
  // ADC Clock frequency: 921.600 kHz
  // ADC Voltage Reference: AREF pin
  // ADC Auto Trigger Source: Free Running
  // Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
  // ADC4: On, ADC5: On, ADC6: On, ADC7: On
  // DIDR0=0x00;
  // ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
  // ADCSRA=0xEB;
  // ADCSRB&=0xF8;
  // ***** Replace 2-10-2010 ***************************************
  // ADC initialization - Rev 12D (slower) 2-10-2010
  // ADC Clock frequency: 115.200 kHz - dont work, 460.8kHz = 0xEC in ADCSRA
  // ADC Voltage Reference: AREF pin
  // ADC Auto Trigger Source: Free Running
  // Digital input buffers on ADC0: Off, ADC1: Off, ADC2: Off, ADC3: Off
  // ADC4: Off, ADC5: Off, ADC6: Off, ADC7: Off
  // DIDR0=0xFF;
  // ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
  // ADCSRA=0xEB;     // Try Back with 921.6kHz..
  // ADCSRA=0xEC;     // Try 460.8kHz.. - No va..
  // ADCSRB&=0xF8;
                                      
  #ifdef ADC_FREE_RUNNING_PWRC2
  // Only if traditional ADC (old) 12.3.2022
  // ADC initialization - XTAL 14.76MHz 22-3-2012
  // ADC Clock frequency: 921.600 kHz
  // ADC Voltage Reference: AREF pin
  // ADC Auto Trigger Source: Free Running
  // Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
  // ADC4: On, ADC5: On, ADC6: On, ADC7: On
  DIDR0=0x00;
  ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
  ADCSRA=0xEC;
  ADCSRB&=0xF8;
  #endif

  // ADC initialization v64-6 - Older not used..
  // ADC Clock frequency: 115.200 kHz
  // ADC Voltage Reference: AREF pin
  // ADC Auto Trigger Source: ADC Stopped
  // Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
  // ADC4: On, ADC5: On, ADC6: On, ADC7: On
  // DIDR0=0x00;
  // ADMUX=FIRST_ADC_INPUT | (ADC_VREF_TYPE & 0xff);
  // ADCSRA=0xCE;


  // ********************************
  // Two Wire Bus initialization
  // Bit Rate:
  // 17.2.09 Changed TWBR to 0x0c for 184kHz..
  // if XTAL = 7.3728e6 means:
  // Bit Rate: 184.320 kHz
  // ** NOTE: For Bit Rate: 115.200 kHz
  // ** then CV-Wiz selectede TWBR=0x18;
  // TWBR=0x0C;
  // Two Wire Bus Slave Address: 0h
  // General Call Recognition: Off
  // TWAR=0x00;
  // Generate Acknowledge Pulse: Off
  // TWI Interrupt:  OFF
  // TWCR=0x05 - would be for TWI IRQ ON;
  // TWCR=0x04; // Same as v32..
  // TWSR=0x00;

  // Two Wire Bus initialization for XTal 14.756MHz 22.3.2012
  // Bit Rate: 184.320 kHz
  TWBR=0x20;
  // Two Wire Bus Slave Address: 0h
  // General Call Recognition: Off
  TWAR=0x00;
  // Generate Acknowledge Pulse: Off
  // TWI Interrupt: Off
  TWCR=0x04;
  TWSR=0x00;


  // Watchdog Timer initialization - CV-Wiz (07.2010)
  // Watchdog Timer Prescaler: OSC/2k
  // Watchdog Timer interrupt: Off
  // Re-eanble 30-9-2010
  // b4 WDCE, b3 WDE
  // b5 b2 b1 b0 WDP3-WDP0 Prescaler
  #pragma optsize-
  #asm("wdr")
  WDTCSR=0x18;    // 0001 1000
  //WDTCSR=0x08;    // 0000 1000  -- Prescaler in 16ms
  WDTCSR=0x28;    // 0010 1000  -- Prescaler in 1000 = 4sec
  #ifdef _OPTIMIZE_SIZE_
  #pragma optsize+
  #endif

  // Global enable interrupts
  // #asm("sei")

  // Old Watchdog Timer initialization 20.11.2006  - From PWRC12dv - version 'e'
  // Watchdog Timer Prescaler: OSC/2048 - 1.8sec aprox.
  // WDTCR=0x0F; no va
  // 17.3.07 Revisited --
  // According to Avr freaks, Topic Mega128 Watchdog? Aug 04 2006
  // Setting Wdog for MEga64, at OSC /1024
  // WDTCR = 0x1E;  // 00011110 WDCE = 1
  // WDTCR = 0x0E;  // 00001110 inmediately after, WDCE=0;
  // So for OSC/2048..
  // WDTCR = 0x1F;  // 00011111 WDCE = 1
  // WDTCR = 0x0F;  // 00001111 inmediately after, WDCE=0;


   SEI();      /* re-enable interrupts */

}

#ifdef CL2_BOARD_ANALOG_TIMER_1_ENABLED
/********************************************************************************
**
**  Initialize Timer1 for overflow interrupt - 
**  for Version Timer1_115_2  10.2.2018
**
**  Timer/Counter 1 initialization
**  Clock source: System Clock
**  Clock value: 1843,200 kHz  (in TCCR1B, CS12:CS10 = 010 -> CLK/8) 
**  Mode: Normal top=0xFFFF
**  OC1A output: Disconnected
**  OC1B output: Disconnected
**  Noise Canceler: Off
**  Input Capture on Falling Edge
**  Timer Period: 10 ms
**  Timer1 Overflow Interrupt: On
**  Input Capture Interrupt: Off
**  Compare A Match Interrupt: Off
**  Compare B Match Interrupt: Off
**  In ELM_FFS Timer1 initialization value after overflow (equiv. to 0x00FF70 )
**    #define T1_INIT (0x10000L-(_MCU_CLOCK_FREQUENCY_/(T1_PRESC*T1_OVF_FREQ)))
**    ..BUT! in TCCR1B, CS12:CS10 = 101 (-> CLK/1024 = 14.4kHz..-> T=69.44us)
**    .. so 0x10000-0xff70 = 0x090 (144 dec)-> 144*T = 10ms, ->fT1= 1/10ms=100Hz
********************************************************************************/

void CL2Board_Timer1_Initialize(void){
    TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
    TCNT1H=0xB8;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;
    // Timer/Counter 1 Interrupt(s) initialization
    TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (1<<TOIE1);
}

/*****************************************************************************
**
**  Timer1 overflow interrupt service routine - from Wizard
**  for Version Timer1_115_2  10.2.2018 of ADC
**
*****************************************************************************/
 
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Reinitialize Timer1 value
TCNT1H=0xB800 >> 8;
TCNT1L=0xB800 & 0xff;
// Place your code here
}

#endif


/*****************************************************************************
**
** EOF
**
*****************************************************************************/

