#ifndef __GAME_MANAGER_THREAD_H
#define __GAME_MANAGER_THREAD_H

#include "cmsis_os2.h"
#include "Input_Manager_Thread.h"
//#include "Hardware_init.h"
#include "Game_Timer.h"
#include "UART_Handler.h"
#include "SAI_Handler.h"
#include "Math_Mode_Thread.h"
#include "Shake_Mode_Thread.h"
#include "LCD_Handler.h"
#include "Sound_Message_Queue.h"
#include "Sound_Manager_Thread.h"
#include "JoyStk_Mode_Thread.h"
#include "Clap_Mode_Thread.h"

osThreadId_t Init_Game_Manager_Thread (void);

#endif