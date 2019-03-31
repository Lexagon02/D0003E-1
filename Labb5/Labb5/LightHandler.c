#include "LightHandler.h"

int counter;

void initLightHandler(LightHandler *self, Serial *serial){
	
	counter = 0;
	self->serial = serial;
}

void lightCycler(LightHandler *self){
	
	SEND(MSEC(100), MSEC(110), self, &lightCycler, NULL);
}

void carOffBridge(LightHandler* self){
	
	self->carsOnBridge--;
	
	if(!self->carsOnBridge){
		self->lightState[NORTH] = RED;
		self->lightState[SOUTH] = RED;
		SYNC(self, &onLightChange, NULL);

	}
	
}

void pushLightState(LightHandler* self, int direction){
	
	if(self->lightState[direction] == RED && !self->carsOnBridge){
		self->lightState[direction] = GREEN;
	}
}
	
void pushCarToBridge(LightHandler* self, int direction){

	self->carsOnBridge++;
	SEND(MSEC(CARPASSINGTIME), MSEC(CARPASSINGTIME + 100), self, &carOffBridge, NULL);
	
}

void getCarsOnBridge(LightHandler* self, int* output){
	
	*output = self->carsOnBridge;
	
}

void getLightState(LightHandler* self, int* arg){
	
	*arg = self->lightState[*arg];
	
}

void setLightStateRed(LightHandler* self, int direction){
	self->lightState[direction] = RED;
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
		
	writeChar(((self->lightState[NORTH] == GREEN) ? 'G' : 'R'), 1);
	writeChar(((self->lightState[SOUTH] == GREEN) ? 'G' : 'R'), 3);
	writeChar('0' + (self->carsOnBridge % 10), 2);
	
	SEND(MSEC(100), MSEC(150), self->serial, &send, parsedValue);
}