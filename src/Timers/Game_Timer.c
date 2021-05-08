#include "Game_Timer.h"                         // CMSIS RTOS header file
 
/*----------------------------------------------------------------------------
 *      Timer: Sample timer functions
 *---------------------------------------------------------------------------*/
 
/*----- One-Shoot Timer Example -----*/
osTimerId_t tim_id1;                            // timer id
static uint32_t exec1;                          // argument for the timer call back function
static int32_t secondsLeft;
uint32_t beepFrequency = 24;

// One-Shoot Timer Function
static void Timer1_Callback (void const *arg) {
	beepFrequency = beepFrequency > 40? 17 : beepFrequency + 1;
	secondsLeft--;
	if(secondsLeft <= 0)
	{
		osTimerStop(tim_id1);
		secondsLeft = 0;
	}
	else
	{
		putOnSoundQueue(beepFrequency, (uint8_t) 250);
	}
}
 
// Example: Create and Start timers
osTimerId_t Init_Timer (uint32_t gameDuration) {
  osStatus_t status;                            // function return status
	
	secondsLeft = gameDuration;
  
  exec1 = 1U;
  tim_id1 = osTimerNew((osTimerFunc_t)&Timer1_Callback, osTimerPeriodic, &exec1, NULL);
  if (tim_id1 != NULL) {  // One-shot timer created
    // start timer with delay 1s
    status = osTimerStart(tim_id1, 1000); 
    if (status != osOK) {
      return NULL;
    }
  }
	
  return tim_id1;
}

int32_t Game_Timer_GetTimeLeft()
{
	return secondsLeft;
}

osStatus_t Game_Timer_IncreaseTimer(int32_t increase)
{
	osStatus_t status = osOK;
	
	secondsLeft += increase;
	
	return status;
}
