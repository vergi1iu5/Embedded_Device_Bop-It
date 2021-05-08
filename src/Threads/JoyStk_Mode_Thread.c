#include "JoyStk_Mode_Thread.h"

void JoyStk_Mode_Thread (void *argument);                   // thread function
static uint32_t targetButton;

osThreadId_t Init_JoyStk_Mode_Thread (uint32_t _targetButton) {
 
  targetButton = _targetButton;
	return osThreadNew(JoyStk_Mode_Thread, NULL, NULL);

}
 
void JoyStk_Mode_Thread (void *argument) {
	
	JOY_Handler_ClearLastPressed();
	//Wait for a single button to be pressed
	while(JOY_Handler_GetLastButtonPressed() == -1){};
	
	uint32_t buttonPressed = JOY_Handler_GetLastButtonPressed();
	//Check if correct joystick was pressed
	uint32_t response = buttonPressed == targetButton? GAME_MSG_RIGHT_ANSWER : GAME_MSG_WRONG_ANSWER;
	//Push result into queue	
	putOnQueue((uint8_t *) response, 1, JOYS_MODE_THREAD_MSG_ID);
		
	osThreadExit();	
}