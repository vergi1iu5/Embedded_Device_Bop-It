#include "Sound_Timer.h"                          // CMSIS RTOS header file
 
/*----------------------------------------------------------------------------
 *      Timer: Sample timer functions
 *---------------------------------------------------------------------------*/
 
/*----- One-Shoot Timer Example -----*/
osTimerId_t soundTimer_Id;                            // timer id
static uint32_t exec1;                          // argument for the timer call back function

// One-Shoot Timer Function
static void SoundTimer_Callback (void const *arg) {

}
 
// Example: Create and Start timers
int Init_Sound_Timer (uint32_t soundDuration) {
  osStatus_t status;                            // function return status
 
  // Create one-shoot timer
  exec1 = 1U;
  soundTimer_Id = osTimerNew((osTimerFunc_t)&SoundTimer_Callback, osTimerOnce, &exec1, NULL);
  if (soundTimer_Id != NULL) {  // One-shot timer created
    // start timer with delay 100ms
    status = osTimerStart(soundTimer_Id, soundDuration); 
    if (status != osOK) {
      return -1;
    }
  }
 
  return NULL;
}

uint32_t Sound_TimerIsRunning()
{
	return osTimerIsRunning(soundTimer_Id);
}