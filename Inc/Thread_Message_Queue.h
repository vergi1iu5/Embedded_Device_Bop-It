#ifndef THREAD_MESSAGE_QUEUE_H
#define THREAD_MESSAGE_QUEUE_H

#include "cmsis_os2.h"

extern osMessageQueueId_t MessageQueue;

#define QUEUE_SIZE 4
#define QUEUE_BYTES_PER_MESSAGE 4
//Message IDs for pushing and pulling messages from queue
#define INPT_MODE_THREAD_MSG_ID 0
#define MATH_MODE_THREAD_MSG_ID 1
#define CLAP_MODE_THREAD_MSG_ID 2
#define JOYS_MODE_THREAD_MSG_ID 3
#define SHKE_MODE_THREAD_MSG_ID 4

#define GAME_MSG_RIGHT_ANSWER 0xFF
#define GAME_MSG_WRONG_ANSWER 0x00

typedef struct {                                // object data type
  uint8_t Buf[QUEUE_BYTES_PER_MESSAGE];
  uint8_t Idx;
} MSGQUEUE_OBJ_t;

osMessageQueueId_t initQueue(void);
osStatus_t putOnQueue(uint8_t * bytes, uint8_t count, uint8_t index);
osStatus_t getFromQueue(MSGQUEUE_OBJ_t * msg);
osStatus_t getFromQueueWait(MSGQUEUE_OBJ_t * msg, uint32_t);
osStatus_t clearMessageQueue();

#endif