#include "Thread_Message_Queue.h"

osMessageQueueId_t MessageQueue = NULL;

osMessageQueueId_t initQueue()
{
	MessageQueue = osMessageQueueNew(QUEUE_SIZE, sizeof(MSGQUEUE_OBJ_t), NULL);
	
	if(MessageQueue == NULL)
	{	
			MessageQueue = NULL;
	}
	
	return MessageQueue;
}

osStatus_t putOnQueue(uint8_t * bytes, uint8_t count, uint8_t index){
	MSGQUEUE_OBJ_t msg;
	osStatus_t status;
	
	if(count > QUEUE_BYTES_PER_MESSAGE){
		status = osError;
		return status;
	}
	
	for(int i = 0; i < count; i++)
	{
		msg.Buf[i] = *(bytes + i);
	}
	
	msg.Idx = index;
	
	status = osMessageQueuePut(MessageQueue, &msg, 0u, 0u);
	
	return status;
}

osStatus_t getFromQueue(MSGQUEUE_OBJ_t * msg)
{
	osStatus_t status = osError;
	
	MSGQUEUE_OBJ_t testMsg;
	
	uint8_t messagesOnQueue;
	
	messagesOnQueue = osMessageQueueGetCount(MessageQueue);
	
	for(int messegeIndex = 0; messegeIndex < messagesOnQueue; messegeIndex++)
	{
		osMessageQueueGet(MessageQueue, &testMsg, NULL, osWaitForever);
		if(testMsg.Idx == msg->Idx){
			for(int byte; byte < QUEUE_BYTES_PER_MESSAGE; byte++)
			{
				msg->Buf[byte] = testMsg.Buf[byte];
			}
			status = osOK;
			break;
		}
		else{
			osMessageQueuePut(MessageQueue, &msg, 0U, 0U);
		}
	}
	
	return status;
}

osStatus_t getFromQueueWait(MSGQUEUE_OBJ_t * msg, uint32_t gameDuration)
{
	osStatus_t status = osError;
	
	MSGQUEUE_OBJ_t testMsg;
	
	uint8_t messagesOnQueue;
	
	messagesOnQueue = osMessageQueueGetCount(MessageQueue);
	
	osMessageQueueGet(MessageQueue, &testMsg, NULL, gameDuration * 1000);
	
	for(int byte; byte < QUEUE_BYTES_PER_MESSAGE; byte++)
	{
				msg->Buf[byte] = testMsg.Buf[byte];
	}
	
	msg->Idx = testMsg.Idx;
	
	status = osOK;
	
	return status;
}

osStatus_t clearMessageQueue()
{
	return osMessageQueueReset(MessageQueue);
}