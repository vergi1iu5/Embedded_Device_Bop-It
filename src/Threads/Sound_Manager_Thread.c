#include "Sound_Manager_Thread.h"                          // CMSIS RTOS header file
 
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/

void Sound_Manager_Thread (void *argument);                   // thread function
 
osThreadId_t Init_Sound_Manager_Thread (void) {
 
  return osThreadNew(Sound_Manager_Thread, NULL, NULL);

}
 
void Sound_Manager_Thread (void *argument) {
	
	SOUNDMSG_OBJ_t soundToPlay; 
	osStatus_t status;
	
  while (1) {
    //Wait until a sound request is put into the queue
		status = getFromSoundQueueWait(&soundToPlay, osWaitForever);
		
		if(status == osOK)
		{
			//Change frequnecy if new one does not match previous one
			if(SAI_Handler_GetSoundFrequency() != soundToPlay.Frequency)
			{
				SAI_Handler_SetFrequency(soundToPlay.Frequency);
			}
			//Play sound and start sound timer
			SAI_Handler_Play();
			status = Init_Sound_Timer(soundToPlay.duration);
			//Wait for timer to expire
			if(status == osOK)
			{
				while(Sound_TimerIsRunning()){};
			}
			//Stop sound
			SAI_Handler_Stop();
		}
		
    //osThreadExit();           
  }
}
