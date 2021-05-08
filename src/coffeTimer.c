#include "coffeTimer.h"

uint8_t gameTime[4] = {48,48,48,48};
uint8_t button = 0;

void getInputTime(uint8_t * time){

	button = GPIOA->IDR;
	button &= (LEFT_JOY_PIN | UP_JOY_PIN | RIGHT_JOY_PIN | SEL_JOY_PIN | DOWN_JOY_PIN);

	while(button != SEL_JOY_PIN){

		if(button == RIGHT_JOY_PIN){increaseTimer(time, ONE_SEC);}
		if(button == UP_JOY_PIN){increaseTimer(time, TEN_SEC);}
		if(button == DOWN_JOY_PIN){decreaseTimer(time, TEN_SEC);}
		if(button == LEFT_JOY_PIN){decreaseTimer(time, ONE_SEC);}

		//updateLCD( 0, DISPLAY_TIME);

		while(button != 0){
			button = GPIOA->IDR;
			button &= (LEFT_JOY_PIN | UP_JOY_PIN | RIGHT_JOY_PIN | SEL_JOY_PIN | DOWN_JOY_PIN);
		}

		button = GPIOA->IDR;
		button &= (LEFT_JOY_PIN | UP_JOY_PIN | RIGHT_JOY_PIN | SEL_JOY_PIN | DOWN_JOY_PIN);

	}
}

void increaseTimer(uint8_t * time, uint8_t amount){

	uint8_t temp;
	uint8_t index;
	uint8_t maxNum[4] = {9 + 48,6 + 48,9 + 48,6 + 48};
	const uint8_t ONE_SEC_INDEX = 0;
	const uint8_t TEN_SEC_INDEX = 1;
	const uint8_t ONE_MIN_INDEX = 2;
	const uint8_t TEN_MIN_INDEX = 3;

	if(amount == ONE_SEC){index = ONE_SEC_INDEX;}
	else {index = TEN_SEC_INDEX;}

	for(; index <= TEN_MIN_INDEX; index++){
		temp = time[index];

		if(temp + 1 > maxNum[index]){
			if(index + 1 <= TEN_MIN_INDEX && time[index + 1] <= maxNum[index + 1]){
				time[index] = 48;
			}else{
				time[index] = maxNum[index];
			}
		}
		else{
			time[index]++;
			break;
		}
	}
}

void decreaseTimer(uint8_t * time, uint8_t amount){

	int8_t temp;
	uint8_t index;
	uint8_t maxNum[4] = {9 + 48,6 + 48,9 + 48,6 + 48};
	const uint8_t ONE_SEC_INDEX = 0;
	const uint8_t TEN_SEC_INDEX = 1;
	const uint8_t ONE_MIN_INDEX = 2;
	const uint8_t TEN_MIN_INDEX = 3;

	if(amount == ONE_SEC){index = ONE_SEC_INDEX;}
	else {index = TEN_SEC_INDEX;}

	for(; index <= TEN_MIN_INDEX; index++){
		temp = time[index];

		if(temp - 1 < 48){
			if(index + 1 <= TEN_MIN_INDEX && time[index + 1] > 0){
				time[index] = maxNum[index];
			}else{
				time[index] = 48;
			}
		}
		else{
			time[index]--;
			break;
		}
	}
}

void setTimer(uint8_t * time, uint8_t value){
	time[0] = value;
	time[1] = value;
	time[2] = value;
	time[3] = value;
}

uint32_t getRemainingTime(uint8_t * time){
	uint32_t ret;
	
	ret = (uint32_t) time[0] - 48;
	ret += ((uint32_t) time[1] - 48) * 10;
	ret += ((uint32_t) time[2] - 48) * 60;
	ret += ((uint32_t) time[3] - 48) * 600;
	
	return ret;
};