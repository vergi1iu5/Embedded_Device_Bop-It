#include "Shake_Mode_Thread.h"                          // CMSIS RTOS header file
 
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Shake_Mode_Thread (void *argument);                   // thread function

osThreadId_t Init_Shake_Mode_Thread (void) {
 
  return osThreadNew(Shake_Mode_Thread, NULL, NULL);
  
}
 
void Shake_Mode_Thread (void *argument) {
	
	uint8_t movementDetected = 0;
	    
	while(movementDetected != 1)
	{
		movementDetected = GYRO_Handler_MovementDetected();
	}
		
		
	putOnQueue((uint8_t *) GAME_MSG_RIGHT_ANSWER, 1, SHKE_MODE_THREAD_MSG_ID);
		
  osThreadExit(); 
		

}
