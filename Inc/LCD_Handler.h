#ifndef LCD_HANDLER_H
#define LCD_HANDLER_H

#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_glass_lcd.h"

#define DISPLAY_TIME 1
#define DISPLAY_STRING 2

#define EASY_MODE 0
#define MED_MODE 1
#define HARD_MODE 2

void LCD_Handler_Init(void);
void LCD_Handler_displayTime(uint8_t *);
void LCD_Handler_displayString(uint8_t stringLength, uint8_t * stringToDisplay);
void LCD_Handler_Clear();

#endif