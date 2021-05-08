#include "Math_Mode_Thread.h"                          // CMSIS RTOS header file
 
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/

uint8_t receiveBuffer[3];

void Math_Mode_Thread (void *argument);                   // thread function
static uint8_t difficulty;
static uint32_t modder;
static uint8_t A[3];
static uint8_t B[3];

static uint16_t DecimalA = 0;
static uint16_t DecimalB = 0;

static const uint8_t EASY = 0;
static const uint8_t MED = 1;
static const uint8_t HARD = 2;
static const uint8_t OPPERANDS[4] = {42,43,45,47};

uint16_t lfsr;

uint16_t randWrd(){
	uint16_t bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5));
	lfsr = (lfsr >> 1) | (bit << 15);
	return (bit);
}

osThreadId_t Init_Math_Mode_Thread (uint8_t _difficulty) {
 
	difficulty = _difficulty;
  return osThreadNew(Math_Mode_Thread, NULL, NULL);
  
}
 
void Math_Mode_Thread (void *argument) {
 
  while (1) {
    
		uint8_t digits = 0;
		//Determine number of digits needed
		if(difficulty == EASY){digits = 1;}
		else if(difficulty == MED){digits = 2;}
		else{digits = 3;}
		//Calculate first operand
		DecimalA = 0;
		for(int i = 0; i < digits; i++)
		{
			A[i] = randWrd() % 9;
			UART_Handler_Transmit(48 + A[i]);
			DecimalA += ((uint16_t) A[i] + 48)*10^i;
		}
		//random operation
		uint8_t opp = randWrd() % 5;
		UART_Handler_Transmit(OPPERANDS[opp]);
		//Calculate second operand
		DecimalB = 0;
		for(int i = 0; i < digits; i++)
		{
			B[i] = randWrd() % 9;
			UART_Handler_Transmit(48 + B[i]);
			DecimalB += ((uint16_t) B[i] + 48)*10^i;
		}
		//Calculate the answer game is looking for
		uint32_t correctAnswer = DecimalA * DecimalB;
		//Clear receiveBuffer
		for(int i = 0; i < 3; i++)
		{
			receiveBuffer[i] = 0;
		}
		//Get all digits needed for correct answer
		for(int i = 0; i < digits; i++)
		{	
			UART_Handler_Receive(&receiveBuffer[i], HAL_MAX_DELAY);
		}
		
    osThreadExit();                            // suspend thread
  }
}
