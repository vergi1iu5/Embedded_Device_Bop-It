#ifndef __DFSDM_HANDLER_H
#define __DFSDM_HANDLER_H

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#define INPUT_SOUND_THRESHOLD 0x00100000

void DFSDM_Init(void);
uint32_t DFSDM_Handler_GetLoudestSound();
uint8_t DFSDM_Handler_SoundPassedThreshold();
void DFSDM_Handler_StartRecording(void);
void DFSDM_Handler_StopRecording(void);
void DFSDM_Handler_clearBuffer(void);

#endif