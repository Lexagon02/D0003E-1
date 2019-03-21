#define CROSSINGTIME 5000

#include "LightHandler.h"

void initLightHandler(LightHandler *self, StatePusher *statePusher){

	self->statePusher = statePusher;
	int temp;
	
	for(int i = 0; i < 2; i++ ){
		initLight(&(self->light[i]), (Object*)self, (void*)&onLightChange);

	}

}


void setDelayedLight(LightHandler *self, int direction){
	
	SYNC(&(self->light[direction]), &setLight, GREEN);
	ASYNC(self, &onLightChange, NULL);
	
}


void setLightPassingDirection(LightHandler *self, int direction){
	
	SYNC(&(self->light[direction]), &setLight, RED);
	SYNC(&(self->light[direction == NORTH ? SOUTH : NORTH]), &setLight, RED);
	SEND(MSEC(CROSSINGTIME), MSEC(CROSSINGTIME + 10), self, &setDelayedLight, direction);
	
	SYNC(self, &onLightChange, NULL);

}

void onLightChange(LightHandler* self){
	
	int parsedValue = 0;
	int temp;
	
	for(int i = 0; i < 2; i++){
		
		SYNC(&(self->light[i]), &getLightState, &temp);
		
		if(temp == GREEN){
			parsedValue |= (1 << (i * 2));
		}
		else{
			parsedValue |= (1 << (1 + i * 2));
		}
		
	}
	
	
	SYNC(&(self->light[0]), &getLightState, &temp);
	int temp2[2] = {(int)(temp == RED ? 'R' : 'G'), 2};
	SYNC(&(self->statePusher->serial->lcd), &writeChar, temp2);
	
	SYNC(&(self->light[1]), &getLightState, &temp);
	int temp3[2] = {(int)(temp == RED ? 'R' : 'G'), 3};
	SYNC(&(self->statePusher->serial->lcd), &writeChar, temp3);
	
	ASYNC(self->statePusher, &setState, (unsigned char)parsedValue);
	
	
}