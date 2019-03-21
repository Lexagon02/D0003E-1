#include "LightHandler.h"

void cyckleLightState(LightHandler* self);

int counter;
void initLightHandler(LightHandler *self, Serial *serial){
	
	counter = 0;
	self->serial = serial;
	cyckleLightState(self);

}

void delayedLightStateReaction(LightHandler *self, int direction){
	
	
	if(self->activePassingSemaphore[direction] == 1) {
		self->lightState[direction == NORTH ? SOUTH : NORTH] = GREEN;
		//onLightChange(self);
	}
	
	if(self->activePassingSemaphore[direction] > 0){
		self->activePassingSemaphore[direction]--;
	}
	
}

void pushLightState(LightHandler* self, int direction){
		
	self->activePassingSemaphore[direction]++;
	
	self->lightState[direction] = GREEN;
	self->lightState[direction == NORTH ? SOUTH : NORTH] = RED;
	SEND(MSEC(CARPASSINGTIME), MSEC(CARPASSINGTIME + 100), self, &delayedLightStateReaction, direction);
	
	ASYNC(self, &onLightChange, NULL);
	
}

void getLightState(LightHandler* self, int* arg){
	
	*arg = self->lightState[*arg];
	
}

void cyckleLightState(LightHandler* self){
	
	ASYNC(self, &onLightChange, NULL);
	SEND(MSEC(100), MSEC(200), self, &cyckleLightState, NULL);
	
}

void onLightChange(LightHandler* self){
	
	int parsedValue = 0;
	
	for(int i = 0; i < 2; i++){
		
		if(self->lightState[i] == GREEN){
			parsedValue |= (1 << (i * 2));
		}
		else{
			parsedValue |= (2 << (i * 2));
		}
		
	}
	
	writeChar('0' + self->activePassingSemaphore[0], 1);
	writeChar((self->lightState[0] == RED ? 'R' : 'G'), 2);
	
	writeChar((self->lightState[1] == RED ? 'R' : 'G'), 3);
	writeChar('0' + self->activePassingSemaphore[1], 4);
	
	
	SYNC(self->serial, &send, parsedValue);
}