#include "GYRO_Handler.h"

float buffer[3] = {0,0,0};
int32_t xval = 0;
int32_t yval = 0;
int32_t zval = 0;
uint32_t xvalabs = 0;
uint32_t yvalabs = 0;
uint32_t zvalabs = 0;

uint8_t GYRO_Handler_Init()
{
	return BSP_GYRO_Init();
}
//Wait for movement to pass threshol
uint8_t GYRO_Handler_MovementDetected()
{
	uint8_t ret = 0;
	
	BSP_GYRO_GetXYZ(buffer);
	xval = (int32_t) buffer[0];
	yval = (int32_t) buffer[1];
	zval = (int32_t) buffer[2];
	//Take absolute value of all axis
  xvalabs = ABS(xval);
	yvalabs = ABS(yval);
	zvalabs = ABS(zval);
	//Only act if significant movement has occured (determined by threshold value)
	if((xvalabs > GYRO_THRESHOLD_DETECTION) || (yvalabs > GYRO_THRESHOLD_DETECTION) ||
      (zvalabs > GYRO_THRESHOLD_DETECTION))
	{
		ret = 1; //movement detected
	}
	
	return ret;
}