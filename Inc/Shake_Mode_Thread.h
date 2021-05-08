#ifndef __SHAKE_MODE_THREAD_H
#define __SHAKE_MODE_THREAD_H

#include "cmsis_os2.h"
#include "Thread_Message_Queue.h"
#include "GYRO_Handler.h"

osThreadId_t Init_Shake_Mode_Thread (void);

#endif