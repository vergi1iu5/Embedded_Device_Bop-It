#include "SAI_Handler_Mutex.h"                          // CMSIS RTOS header file
 
/*----------------------------------------------------------------------------
 *      Mutex creation & usage
 *---------------------------------------------------------------------------*/
 
osMutexId_t SAI_Manager_Mutex;                          // mutex id

const osMutexAttr_t Thread_Mutex_attr = {
  "SAI_Handler_Mutex", // human readable mutex name
  osMutexRobust,  		 // attr_bits
  NULL,                // memory for control block   
  0U                   // size for control block
};

osStatus_t Init_SAI_Mutex (void)
{	
	osStatus_t status = osOK;
		
	SAI_Manager_Mutex = osMutexNew(&Thread_Mutex_attr);
	
	if(SAI_Manager_Mutex == NULL){status = osError;}
		
	return status;	
}

osStatus_t SAI_Mutex_Aquire(uint32_t timeout)
{
	return osMutexAcquire(SAI_Manager_Mutex, timeout); //timeout specified in seconds
}

osStatus_t SAI_Mutex_Release()
{
	return osMutexRelease(SAI_Manager_Mutex);
}