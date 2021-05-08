
#include "JOY_Handler.h"

uint32_t buttonPressed = -1;

void JOY_Handler_Init(uint32_t JOY_mode){
	 
	if(JOY_mode == JOY_INTERRUPT){
		BSP_JOY_Init(JOY_MODE_EXTI);
	}
	if(JOY_mode == JOY_GPIO){
		BSP_JOY_Init(JOY_MODE_GPIO);
	}

}

void JOY_Handler_ClearLastPressed(){
	buttonPressed = -1;
}

uint32_t JOY_Handler_GetLastButtonPressed(){
	return buttonPressed;
}

/*
	Interrupt for center button on joystick. This function
	toggles timer 2 on and off to enable blinking feature.
*/
void EXTI0_IRQHandler()
{
	
	buttonPressed = JOY_SEL;
	
	EXTI->PR1 |= EXTI_PR1_PIF0;
	NVIC_ClearPendingIRQ(SEL_JOY_EXTI_IRQn);
}
/*
	Interrupt for left button on joystick. This function
	takes no inputs and turns red LED off and green LED on.
*/
void EXTI1_IRQHandler()
{
	buttonPressed = JOY_LEFT;
	
	EXTI->PR1 |= EXTI_PR1_PIF1;
	NVIC_ClearPendingIRQ(LEFT_JOY_EXTI_IRQn);
}
/*
	Interrupt for right button on joystick. This function
	takes no inputs and turns red LED on and green LED off.
*/
void EXTI2_IRQHandler(){
	
	buttonPressed = JOY_RIGHT;
	
	EXTI->PR1 |= EXTI_PR1_PIF2;
	NVIC_ClearPendingIRQ(RIGHT_JOY_EXTI_IRQn);
}
/*
	Interrupt for up button on joystick. This function
	takes no inputs and toggles red LED.
*/
void EXTI3_IRQHandler(){
	
	buttonPressed = JOY_UP;
	
	EXTI->PR1 |= EXTI_PR1_PIF3;
	NVIC_ClearPendingIRQ(UP_JOY_EXTI_IRQn);
}
/*
	Interrupt for down button on joystick. This function
	takes no inputs and toggles Green LED.
*/
void EXTI9_5_IRQHandler(){
	
	buttonPressed = JOY_DOWN;
	
	EXTI->PR1 |= EXTI_PR1_PIF5;
	NVIC_ClearPendingIRQ(DOWN_JOY_EXTI_IRQn);
}