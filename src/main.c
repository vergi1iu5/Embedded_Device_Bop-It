#include "main.h"

void Playback_Update(uint32_t);


int main(void)
{
	
	Hardware_Init();
	
	osKernelInitialize();
	
	osThreadId_t gameManager_ThreadId = Init_Game_Manager_Thread();
	
	//osThreadId_t inputManager_ThreadId = Init_Input_Manager_Thread();
	
	osKernelStart();
	
	for(;;);
	
}
