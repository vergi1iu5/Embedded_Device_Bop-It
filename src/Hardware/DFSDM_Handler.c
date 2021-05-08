#include "DFSDM_Handler.h"


DFSDM_Channel_HandleTypeDef  DfsdmChannelHandle;
DFSDM_Filter_HandleTypeDef   DfsdmFilterHandle;
DMA_HandleTypeDef            hDfsdmDma;

int32_t                      RecBuff[2048];
uint32_t                     DmaRecHalfBuffCplt  = 0;
uint32_t                     DmaRecBuffCplt      = 0;
uint32_t										 max;
void DFSDM_Init(void);

void DFSDM_Init(void)
{
  /* Initialize channel 2 */
  __HAL_DFSDM_CHANNEL_RESET_HANDLE_STATE(&DfsdmChannelHandle);
  DfsdmChannelHandle.Instance                      = DFSDM1_Channel2;
  DfsdmChannelHandle.Init.OutputClock.Activation   = ENABLE;
  DfsdmChannelHandle.Init.OutputClock.Selection    = DFSDM_CHANNEL_OUTPUT_CLOCK_AUDIO;
  DfsdmChannelHandle.Init.OutputClock.Divider      = 4; /* 11.294MHz/4 = 2.82MHz */
  DfsdmChannelHandle.Init.Input.Multiplexer        = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  DfsdmChannelHandle.Init.Input.DataPacking        = DFSDM_CHANNEL_STANDARD_MODE; /* N.U. */
  DfsdmChannelHandle.Init.Input.Pins               = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
  DfsdmChannelHandle.Init.SerialInterface.Type     = DFSDM_CHANNEL_SPI_RISING;
  DfsdmChannelHandle.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  DfsdmChannelHandle.Init.Awd.FilterOrder          = DFSDM_CHANNEL_FASTSINC_ORDER; /* N.U. */
  DfsdmChannelHandle.Init.Awd.Oversampling         = 10; /* N.U. */
  DfsdmChannelHandle.Init.Offset                   = 0;
  DfsdmChannelHandle.Init.RightBitShift            = 2;
  if(HAL_OK != HAL_DFSDM_ChannelInit(&DfsdmChannelHandle))
  {
    //Error_Handler();
  }

  /* Initialize filter 0 */
  __HAL_DFSDM_FILTER_RESET_HANDLE_STATE(&DfsdmFilterHandle);
  DfsdmFilterHandle.Instance                          = DFSDM1_Filter0;
  DfsdmFilterHandle.Init.RegularParam.Trigger         = DFSDM_FILTER_SW_TRIGGER;
  DfsdmFilterHandle.Init.RegularParam.FastMode        = ENABLE;
  DfsdmFilterHandle.Init.RegularParam.DmaMode         = ENABLE;
  DfsdmFilterHandle.Init.InjectedParam.Trigger        = DFSDM_FILTER_SW_TRIGGER; /* N.U. */
  DfsdmFilterHandle.Init.InjectedParam.ScanMode       = ENABLE; /* N.U. */
  DfsdmFilterHandle.Init.InjectedParam.DmaMode        = DISABLE; /* N.U. */
  DfsdmFilterHandle.Init.InjectedParam.ExtTrigger     = DFSDM_FILTER_EXT_TRIG_TIM1_TRGO; /* N.U. */
  DfsdmFilterHandle.Init.InjectedParam.ExtTriggerEdge = DFSDM_FILTER_EXT_TRIG_RISING_EDGE; /* N.U. */
  DfsdmFilterHandle.Init.FilterParam.SincOrder        = DFSDM_FILTER_SINC3_ORDER;
  DfsdmFilterHandle.Init.FilterParam.Oversampling     = 64; /* 11.294MHz/(4*64) = 44.1KHz */
  DfsdmFilterHandle.Init.FilterParam.IntOversampling  = 1;
  if(HAL_OK != HAL_DFSDM_FilterInit(&DfsdmFilterHandle))
  {
    //Error_Handler();
  }

  /* Configure regular channel and continuous mode for filter 0 */
  if(HAL_OK != HAL_DFSDM_FilterConfigRegChannel(&DfsdmFilterHandle, DFSDM_CHANNEL_2, DFSDM_CONTINUOUS_CONV_ON))
  {
    //Error_Handler();
  }
}

void DFSDM_Handler_StartRecording()
{
	if(HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&DfsdmFilterHandle, RecBuff, 2048))
  {
    //Error_Handler();
  }
}

void DFSDM_Handler_StopRecording()
{
	if(HAL_OK != HAL_DFSDM_FilterRegularStop_DMA(&DfsdmFilterHandle))
  {
    //Error_Handler();
  }
}

void DFSDM_Handler_clearBuffer()
{
	for(int i = 0; i < 2048; i++)
	{
		RecBuff[i] = 0;
	}
}

uint32_t DFSDM_Handler_GetLoudestSound()
{
	
	max = RecBuff[0];
	for(int i = 1; i < 2048; i++)
	{
		if(max < (RecBuff[i] >> 8))
		{
			max = RecBuff[i];
		}
	}

	return max;
}

uint8_t DFSDM_Handler_SoundPassedThreshold()
{
	if(DFSDM_Handler_GetLoudestSound() >= INPUT_SOUND_THRESHOLD)
	{
		return 0xFF;
	}
	else
	{
		return 0x00;
	}
}

void HAL_DFSDM_ChannelMspInit(DFSDM_Channel_HandleTypeDef *hdfsdm_channel)
{
  /* Init of clock, gpio and PLLSAI1 clock */
  GPIO_InitTypeDef GPIO_Init;
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;
  
  /* Enable DFSDM clock */
  __HAL_RCC_DFSDM1_CLK_ENABLE();
  
  /* Configure PE9 for DFSDM_CKOUT and PE7 for DFSDM_DATIN2 */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  GPIO_Init.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init.Pull      = GPIO_PULLDOWN;
  GPIO_Init.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_Init.Alternate = GPIO_AF6_DFSDM1;
  GPIO_Init.Pin = GPIO_PIN_9;
  HAL_GPIO_Init(GPIOE, &GPIO_Init);
  GPIO_Init.Pin = GPIO_PIN_7;
  HAL_GPIO_Init(GPIOE, &GPIO_Init);
  
  /* Configure and enable PLLSAI1 clock to generate 11.294MHz */
  RCC_PeriphCLKInitStruct.PeriphClockSelection    = RCC_PERIPHCLK_SAI1;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1Source   = RCC_PLLSOURCE_MSI;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1M        = 1;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1N        = 48;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1P        = 17;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK;
  RCC_PeriphCLKInitStruct.Sai1ClockSelection      = RCC_SAI1CLKSOURCE_PLLSAI1;
  if(HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct) != HAL_OK)
  {
    //Error_Handler();
  }
}

/**
  * @brief  Initializes the DFSDM filter MSP.
  * @param  hdfsdm_filter : DFSDM filter handle.
  * @retval None
  */
void HAL_DFSDM_FilterMspInit(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
  /* Configure DMA1_Channel4 */
  __HAL_RCC_DMA1_CLK_ENABLE();
  hDfsdmDma.Init.Request             = DMA_REQUEST_0;
  hDfsdmDma.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hDfsdmDma.Init.PeriphInc           = DMA_PINC_DISABLE;
  hDfsdmDma.Init.MemInc              = DMA_MINC_ENABLE;
  hDfsdmDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hDfsdmDma.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  hDfsdmDma.Init.Mode                = DMA_CIRCULAR;
  hDfsdmDma.Init.Priority            = DMA_PRIORITY_HIGH;
  hDfsdmDma.Instance                 = DMA1_Channel4;
  __HAL_LINKDMA(hdfsdm_filter, hdmaReg, hDfsdmDma);
  if (HAL_OK != HAL_DMA_Init(&hDfsdmDma))
  {
    //Error_Handler();
  }
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0x01, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}

void HAL_DFSDM_FilterRegConvHalfCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
  DmaRecHalfBuffCplt = 1;
}

/**
  * @brief  Regular conversion complete callback. 
  * @note   In interrupt mode, user has to read conversion value in this function
            using HAL_DFSDM_FilterGetRegularValue.
  * @param  hdfsdm_filter : DFSDM filter handle.
  * @retval None
  */
void HAL_DFSDM_FilterRegConvCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
  DmaRecBuffCplt = 1;
}

void DMA1_Channel4_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hDfsdmDma);
}