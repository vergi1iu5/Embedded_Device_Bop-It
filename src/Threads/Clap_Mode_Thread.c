#include "Clap_Mode_Thread.h"

void Clap_Mode_Thread(void * arguments);

osThreadId_t Init_Clap_Mode_Thread(void)
{
	return osThreadNew(Clap_Mode_Thread, NULL, NULL);
}

void Clap_Mode_Thread(void * arguments)
{
	while(1)
	{
		uint8_t soundDetected = 0;
		
		DFSDM_Handler_clearBuffer();
		DFSDM_Handler_StartRecording();
		osDelay(2); //allow for buffer to start being populated
		// Wait for sound to pass threshold
		while(soundDetected != 0xFF)
		{
			soundDetected = DFSDM_Handler_SoundPassedThreshold();
		}
			
		DFSDM_Handler_StopRecording();
		
		putOnQueue((uint8_t *) GAME_MSG_RIGHT_ANSWER, 1, CLAP_MODE_THREAD_MSG_ID);
		
		osThreadExit();
	}
	
}