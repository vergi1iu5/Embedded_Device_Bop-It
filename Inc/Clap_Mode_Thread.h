#ifndef __CLAP_MODE_THREAD_H
#define __CLAP_MODE_THREAD_H

#include "cmsis_os2.h"
#include "DFSDM_Handler.h"
#include "Thread_Message_Queue.h"

osThreadId_t Init_Clap_Mode_Thread (void);

#endif