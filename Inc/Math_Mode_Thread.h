#ifndef __MATH_MODE_THREAD_H
#define __MATH_MODE_THREAD_H

#include "cmsis_os2.h"
#include "UART_Handler.h"
#include "Thread_Message_Queue.h"

osThreadId_t Init_Math_Mode_Thread (uint8_t);

#endif