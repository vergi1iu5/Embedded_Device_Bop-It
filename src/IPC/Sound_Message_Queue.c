#include "Sound_Message_Queue.h"

osMessageQueueId_t Sound_MessageQueue = NULL;

osMessageQueueId_t initSoundQueue()
{
	Sound_MessageQueue = osMessageQueueNew(QUEUE_SIZE, sizeof(SOUNDMSG_OBJ_t), NULL);
	
	if(Sound_MessageQueue == NULL)
	{	
			Sound_MessageQueue = NULL;
	}
	
	return Sound_MessageQueue;
}

osStatus_t putOnSoundQueue(uint32_t Freq, uint8_t durationInSec){
	SOUNDMSG_OBJ_t msg;
	
	osStatus_t status = osOK;
	
	msg.Frequency = Freq;
	msg.duration = durationInSec;
	
	uint32_t count = osMessageQueueGetCount(Sound_MessageQueue);
	
	if(count > QUEUE_BYTES_PER_MESSAGE){
		status = osError;
		return status;
	}
	
	status = osMessageQueuePut(Sound_MessageQueue, &msg, 0u, 0u);
	
	return status;
}

osStatus_t getFromSoundQueue(SOUNDMSG_OBJ_t * msg)
{
	return osMessageQueueGet(Sound_MessageQueue, &msg, NULL, 0u);
}

osStatus_t getFromSoundQueueWait(SOUNDMSG_OBJ_t * msg, uint32_t gameDuration)
{
	return osMessageQueueGet(Sound_MessageQueue, &msg, NULL, gameDuration * 1000);
}