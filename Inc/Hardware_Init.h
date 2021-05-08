#ifndef HARDWARE_INIT_H
#define HARDWARE_INIT_H

#include "stm32l4xx_hal.h"
//#include "Thread_Message_Queue.h"
#include "JOY_Handler.h"
#include "LCD_Handler.h"
#include "UART_Handler.h"
#include "SAI_Handler.h"
//#include "Math_Mode_Thread.h"
#include "GYRO_Handler.h"
#include "DFSDM_Handler.h"

void Hardware_Init(void);

static void SystemClock_Config(void);

#endif