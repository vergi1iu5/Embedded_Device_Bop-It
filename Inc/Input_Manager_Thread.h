#ifndef INPUT_MANAGER_THREAD_H
#define INPUT_MANAGER_THREAD_H

#include "JOY_Handler.h"
#include "LCD_Handler.h"
#include "stm32l476g_discovery_glass_lcd.h"
#include "coffeTimer.h"
#include "Thread_Message_Queue.h"

osThreadId_t Init_Input_Manager_Thread (void);


#endif