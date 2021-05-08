#ifndef __GAME_TIMER_H
#define __GAME_TIMER_H

#include "cmsis_os2.h" 
#include "Sound_Message_Queue.h"

osTimerId_t Init_Timer (uint32_t gameDuration);
int32_t Game_Timer_GetTimeLeft();
osStatus_t Game_Timer_IncreaseTimer(int32_t increase);


#endif