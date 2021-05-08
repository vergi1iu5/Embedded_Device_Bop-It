#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "Input_Manager_Thread.h" 

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
static uint8_t displayEasy[4] = {'E','A','S','Y'};
static uint8_t displayMedium[3] = {'M','E','D'};
static uint8_t displayHard[4] = {'H','A','R','D'};
static uint8_t updateNeeded = 0;

uint8_t mode = EASY_MODE;
extern uint8_t gameTime[4];

void Input_Manager_Thread (void *argument);                   // thread function

osThreadId_t Init_Input_Manager_Thread (void) {
 
  return osThreadNew(Input_Manager_Thread, NULL, NULL);
	
}
 
void Input_Manager_Thread (void *argument) {
	
	JOY_Handler_ClearLastPressed();
  LCD_Handler_Clear();
	LCD_Handler_displayString(4 , displayEasy);
	
	while (1) {
		
		while(JOY_Handler_GetLastButtonPressed() != JOY_SEL){
			//Cycle from Easy -> Med -> Hard and back to Easy
			if(JOY_Handler_GetLastButtonPressed() == JOY_UP){
				mode++;
				if(mode > HARD_MODE){mode = EASY_MODE;}
				JOY_Handler_ClearLastPressed();
				updateNeeded = 1;
			}

			if(JOY_Handler_GetLastButtonPressed() == JOY_DOWN){
				mode--;
				if(mode < EASY_MODE){mode = HARD_MODE;}
				JOY_Handler_ClearLastPressed();
				updateNeeded = 1;
			}	
			//Update LCD only if Mode changed
			if(updateNeeded)
			{
				switch(mode){
					case EASY_MODE:
						LCD_Handler_displayString(4 , displayEasy);
						break;
					case MED_MODE:
						LCD_Handler_displayString(3 , displayMedium);
						break;
					case HARD_MODE:
						LCD_Handler_displayString(4 , displayHard);
						break;
					default:
						break;
				}
				
				updateNeeded = 0;
				
			}
		}
		
		JOY_Handler_ClearLastPressed();
		//Get game time target
		while(JOY_Handler_GetLastButtonPressed() != JOY_SEL){
			
			if(JOY_Handler_GetLastButtonPressed() == JOY_UP){
				increaseTimer(gameTime,ONE_SEC);
				LCD_Handler_displayTime(gameTime);
				JOY_Handler_ClearLastPressed();
			}

			if(JOY_Handler_GetLastButtonPressed() == JOY_DOWN){
				decreaseTimer(gameTime,ONE_SEC);
				LCD_Handler_displayTime(gameTime);
				JOY_Handler_ClearLastPressed();
			}	
			
		}
		
		putOnQueue(gameTime, 4, INPT_MODE_THREAD_MSG_ID);
		putOnQueue(&mode, 1, INPT_MODE_THREAD_MSG_ID);
		
		
		osThreadExit();                            // suspend thread
  }
}
