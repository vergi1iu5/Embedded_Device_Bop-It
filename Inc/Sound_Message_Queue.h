#ifndef __SOUND_MESSAGE_QUEUE_H
#define __SOUND_MESSAGE_QUEUE_H

#include "cmsis_os2.h"

#define QUEUE_SIZE 5
#define QUEUE_BYTES_PER_MESSAGE 2 //First 5 byte is frequency and second is duration
//Message IDs for pushing and pulling messages from queue
#define RIGHT_ANSWER_SOUND_F 24
#define WRONG_ANSWER_SOUND_F  12

#define GAME_MSG_RIGHT_ANSWER 0xFF

typedef struct {                                // object data type
  uint8_t Frequency;
	uint8_t duration;
} SOUNDMSG_OBJ_t;

osMessageQueueId_t initSoundQueue(void);
osStatus_t putOnSoundQueue(uint32_t, uint8_t);
osStatus_t getFromSoundQueue(SOUNDMSG_OBJ_t * msg);
osStatus_t getFromSoundQueueWait(SOUNDMSG_OBJ_t * msg, uint32_t);

#endif