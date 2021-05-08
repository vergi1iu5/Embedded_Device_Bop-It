#ifndef __SOUND_MANAGER_THREAD_H
#define __SOUND_MANAGER_THREAD_H

#include "cmsis_os2.h"
#include "SAI_Handler.h"
#include "Sound_Message_Queue.h"
#include "Sound_Timer.h"

osThreadId_t Init_Sound_Manager_Thread (void);

#endif