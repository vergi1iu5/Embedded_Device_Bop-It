#ifndef __COFFE_TIMER_H
#define __COFFE_TIMER_H

#include <stdint.h>
#include "stm32l476g_discovery.h"

#define ONE_SEC 1
#define TEN_SEC 10
#define ONE_MIN 60

extern void increaseTimer(uint8_t*, uint8_t);
void decreaseTimer(uint8_t*, uint8_t);
void setTimer(uint8_t*, uint8_t);
extern void getInputTime(uint8_t *);
uint32_t getRemainingTime(uint8_t *);
#endif