
#include "LCD_Handler.h"

LCD_HandleTypeDef hlcd;

void LCD_Handler_Init()
{
	BSP_LCD_GLASS_Init();
}
//Display a single string into LCD
void LCD_Handler_displayString(uint8_t stringLength, uint8_t * stringToDisplay){
	
	LCD_Handler_Clear();
	
	for(int i = 0; i < stringLength; i++){
		BSP_LCD_GLASS_DisplayChar(&stringToDisplay[i],POINT_OFF,DOUBLEPOINT_OFF, i);
	}

}
//Display time (tailed for special format input)
void LCD_Handler_displayTime(uint8_t * time){
	
	LCD_Handler_Clear();
	
	uint8_t label_1 = 'T';
	uint8_t label_2 = 'M';
	BSP_LCD_GLASS_DisplayChar(&time[0],POINT_OFF,DOUBLEPOINT_OFF, LCD_DIGIT_POSITION_6);
	BSP_LCD_GLASS_DisplayChar(&time[1],POINT_OFF,DOUBLEPOINT_OFF, LCD_DIGIT_POSITION_5);
	BSP_LCD_GLASS_DisplayChar(&time[2],POINT_ON,DOUBLEPOINT_OFF, LCD_DIGIT_POSITION_4);
	BSP_LCD_GLASS_DisplayChar(&time[3],POINT_OFF,DOUBLEPOINT_OFF, LCD_DIGIT_POSITION_3);
	BSP_LCD_GLASS_DisplayChar(&label_2,POINT_OFF,DOUBLEPOINT_OFF, LCD_DIGIT_POSITION_2);
	BSP_LCD_GLASS_DisplayChar(&label_1,POINT_OFF,DOUBLEPOINT_OFF, LCD_DIGIT_POSITION_1);
}
//Clear LCD
void LCD_Handler_Clear(){
	BSP_LCD_GLASS_Clear();
}