#ifndef __JOYSTK_MODE_THREAD_H
#define __JOYSTK_MODE_THREAD_H

#include "cmsis_os2.h"
#include "Thread_Message_Queue.h"
#include "JOY_Handler.h"

osThreadId_t Init_JoyStk_Mode_Thread (uint32_t _targetButton);


#endif