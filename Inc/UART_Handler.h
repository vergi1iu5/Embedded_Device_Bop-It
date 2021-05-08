#ifndef __UART_HANDLER_H
#define __UART_HANDLER_H

#include "stm32l4xx_hal.h"
#include <stdint.h>


static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void UART_Handler_Init();
void UART_Handler_Receive(uint8_t * rxBuffer, uint32_t timeOut);
void UART_Handler_Transmit(uint8_t);

#endif