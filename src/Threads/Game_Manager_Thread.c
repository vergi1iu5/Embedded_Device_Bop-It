
#include "Game_Manager_Thread.h"                          // CMSIS RTOS header file
#include <stdlib.h>

extern USART_HandleTypeDef huart2;

static void display_GameMode(uint8_t);

extern void Input_Manager_Thread(void *argument);

static const uint8_t CHANGE_GAME_PERIOD = 4;
static uint8_t gameCount = 0;
static uint16_t gameModeTarget = MATH_MODE_THREAD_MSG_ID;

osThreadId_t mathMode_ThreadId;
osThreadId_t shakeMode_ThreadId;
osThreadId_t joyStick_ThreadId;
osThreadId_t clapMode_ThreadId;

uint8_t mathMode_display[] = {'M','A','T','H'};
uint8_t shkeMode_display[] = {'S','H','A','K','E'};
uint8_t joyMode_display[] =  {'J','O','Y','S','T','K'};
uint8_t clapMode_display[] = {'C','L','A','P'};

uint8_t JoyStick_Mode_TargetButton = 0;

uint16_t lfsrGame = 0x1;

uint16_t randWrdGame(){
	uint16_t bit = ((lfsrGame >> 0) ^ (lfsrGame >> 2) ^ (lfsrGame >> 3) ^ (lfsrGame >> 5));
	lfsrGame = (lfsrGame >> 1) | (bit << 15);
	return (bit);
}

const osThreadAttr_t thread1_attr = {
  .attr_bits = osThreadJoinable                        // Create the thread stack with a size of 1024 bytes
};

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Game_Manager_Thread (void *argument);                   // thread function
 
osThreadId_t Init_Game_Manager_Thread (void) {
 
  return osThreadNew(Game_Manager_Thread, NULL, NULL);

}
 
void Game_Manager_Thread (void *argument) {
	
	initQueue();
	initSoundQueue();
	
  while (1) {
    //Start and join thread for inputs
		osThreadId_t startMode_Thread = osThreadNew(Input_Manager_Thread, NULL, &thread1_attr);
		osThreadJoin(startMode_Thread);
		
		MSGQUEUE_OBJ_t inputMsg;
		inputMsg.Idx = INPT_MODE_THREAD_MSG_ID;
		//Get Dificulty and GameTime from queue
		getFromQueue(&inputMsg);
		uint32_t gameDuration = getRemainingTime(inputMsg.Buf);
		getFromQueue(&inputMsg);
		uint8_t difficulty = inputMsg.Buf[0];
		//Start timer
		osTimerId_t gameTimerId = Init_Timer(gameDuration);
		//Start sound manager
		osThreadId_t soundManagerThreadId = Init_Sound_Manager_Thread();
		
		while(Game_Timer_GetTimeLeft() > 0)
		{
				//make into a function to calculate next game mode
				if(gameCount < CHANGE_GAME_PERIOD){
					//Do 4 runs of regular math modes
					gameModeTarget = MATH_MODE_THREAD_MSG_ID;
					gameCount++;
				}
				else
				{
					//Generate random next game mode
					gameModeTarget = (randWrdGame() % 5) + 2;
					gameCount = 0;
					//Generate random joystick target
					if(gameModeTarget == JOYS_MODE_THREAD_MSG_ID)
					{
						JoyStick_Mode_TargetButton = randWrdGame() % 5;
					}
				}
				//Show target game mode in LCD
				display_GameMode(gameModeTarget);
				
				//Same with this, say, Start all Threads and make it return a threadId Array
				mathMode_ThreadId = Init_Math_Mode_Thread(difficulty);
				shakeMode_ThreadId = Init_Shake_Mode_Thread();
				joyStick_ThreadId = Init_JoyStk_Mode_Thread(JoyStick_Mode_TargetButton);
				clapMode_ThreadId = Init_Clap_Mode_Thread();
				
				MSGQUEUE_OBJ_t AnyMsg;
				getFromQueueWait(&AnyMsg, Game_Timer_GetTimeLeft());
				
				//Make into a function called "TerminateAllThreads" or something
				osThreadTerminate(mathMode_ThreadId);
				osThreadTerminate(shakeMode_ThreadId);
				osThreadTerminate(joyStick_ThreadId);
				osThreadTerminate(clapMode_ThreadId);
				
				
				if(clearMessageQueue() == osError)
				{
					while(1){}; //Debugging pourposes
				}
				//Check if correct answer and correct thread	
				if(AnyMsg.Idx == gameModeTarget && AnyMsg.Buf[0] == GAME_MSG_RIGHT_ANSWER)
				{
					putOnSoundQueue(RIGHT_ANSWER_SOUND_F, (uint8_t) 250);
					Game_Timer_IncreaseTimer(10);
				}
				else
				{
					putOnSoundQueue(WRONG_ANSWER_SOUND_F, (uint8_t) 250);
				}
				
				osDelay(250);
				
		}
		
		osThreadTerminate(soundManagerThreadId);
		
    osThreadYield();         
  }
}

void display_GameMode(uint8_t gameMode)
{
	switch(gameMode)
	{
		case MATH_MODE_THREAD_MSG_ID:
			LCD_Handler_displayString(4, mathMode_display);
			break;
		case CLAP_MODE_THREAD_MSG_ID:
			LCD_Handler_displayString(4, clapMode_display);
			break;
		case JOYS_MODE_THREAD_MSG_ID:
			LCD_Handler_displayString(6, joyMode_display);
			break;
		case SHKE_MODE_THREAD_MSG_ID:
			LCD_Handler_displayString(5, shkeMode_display);
			break;
		default:
			break;
	}
}
