#ifndef __GYRO_HANDLER_H
#define __GYRO_HANDLER_H

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#define ABS(x)                    (x < 0) ? (-x) : x
#define GYRO_THRESHOLD_DETECTION 40000
#include "stm32l476g_discovery_gyroscope.h"

uint8_t GYRO_Handler_Init();
uint8_t GYRO_Handler_MovementDetected();

#endif