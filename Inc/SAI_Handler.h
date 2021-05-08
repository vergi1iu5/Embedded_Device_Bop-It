#ifndef SAI_HANDLER_H
#define SAI_HANDLER_H

#include <stdint.h>
#include "stm32l476g_discovery.h"
//#include "stm32l476g_discovery_audio.h"
#include "audio.h"
#include "../Components/cs43l22/cs43l22.h"

#define AUDIO_FILE_SIZE      (100)
#define PLAY_HEADER          0x0
#define PLAY_BUFF_SIZE       50

/* SAI peripheral configuration defines */
#define AUDIO_SAIx                           SAI1_Block_A
#define AUDIO_SAIx_CLK_ENABLE()              __HAL_RCC_SAI1_CLK_ENABLE()

#define AUDIO_SAIx_FS_GPIO_PORT              GPIOE
#define AUDIO_SAIx_FS_AF                     GPIO_AF13_SAI1
#define AUDIO_SAIx_FS_PIN                    GPIO_PIN_4
#define AUDIO_SAIx_SCK_GPIO_PORT             GPIOE
#define AUDIO_SAIx_SCK_AF                    GPIO_AF13_SAI1
#define AUDIO_SAIx_SCK_PIN                   GPIO_PIN_5
#define AUDIO_SAIx_SD_GPIO_PORT              GPIOE
#define AUDIO_SAIx_SD_AF                     GPIO_AF13_SAI1
#define AUDIO_SAIx_SD_PIN                    GPIO_PIN_6
#define AUDIO_SAIx_MCLK_GPIO_PORT            GPIOE
#define AUDIO_SAIx_MCLK_AF                   GPIO_AF13_SAI1
#define AUDIO_SAIx_MCLK_PIN                  GPIO_PIN_2
   
#define AUDIO_SAIx_MCLK_ENABLE()             __HAL_RCC_GPIOE_CLK_ENABLE()
#define AUDIO_SAIx_SCK_ENABLE()              __HAL_RCC_GPIOE_CLK_ENABLE()
#define AUDIO_SAIx_FS_ENABLE()               __HAL_RCC_GPIOE_CLK_ENABLE()
#define AUDIO_SAIx_SD_ENABLE()               __HAL_RCC_GPIOE_CLK_ENABLE()

static uint32_t soundVolume = 70;
static uint32_t soundDuration = 0;
static uint32_t soundFrequency_N = 24;

void SAI_Handler_Play();
void SAI_Handler_Stop();
void SAI_Handler_Init();
void SAI_Handler_DeInit();
void SAI_Handler_SetSoundDuration(uint32_t);
void SAI_Handler_SetFrequency(uint32_t);
void SAI_Handler_SetVolume(uint32_t);
uint32_t SAI_Handler_GetSoundDuration();
uint32_t SAI_Handler_GetSoundFrequency();
void SAI_Handler_Start();

//static void TIM2_Setup(uint32_t);
//void TIM2_IRQHandler();

#endif