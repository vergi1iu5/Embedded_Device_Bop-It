#ifndef JOY_HANDLER_H
#define JOY_HANDLER_H

#include "stm32l476g_discovery.h"

#define JOY_SEL 0
#define JOY_DOWN 1
#define JOY_LEFT 2
#define JOY_UP 3
#define JOY_RIGHT 3

#define JOY_INTERRUPT 0
#define JOY_GPIO 1

extern uint32_t buttonPressed;

uint32_t JOY_Handler_GetLastButtonPressed();
void JOY_Handler_Init(uint32_t);
void JOY_Handler_ClearLastPressed();

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

#endif