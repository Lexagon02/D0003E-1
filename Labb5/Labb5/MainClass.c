#include "MainClass.h"
#include "Serial.h"

#define MAXCARS 10

void checkCarArrived(MainClass* self, int* input, int direction);
void tryToPass(MainClass* self, int* input, int direction);
void checkBridgeState(MainClass* self, int* input, int direction);


void runMain(MainClass* self){
	
	initSerial(&(self->serial), (Object*)(self), (void*)&onSensorRead);
	initLightHandler(&(self->lightHandler), &(self->serial));
	
	SEND(MSEC(100), MSEC(200), self, &onSensorRead, 0b0000);
	SEND(MSEC(100), MSEC(200), &(self->lightHandler), &onLightChange, NULL);

}

void onSensorRead(MainClass* self, int input){
		
	checkCarArrived(self, &input, NORTH);
	checkCarArrived(self, &input, SOUTH);
	
	checkBridgeState(self, &input, NORTH);
	checkBridgeState(self, &input, SOUTH);
	
	tryToPass(self, &input, NORTH);
	tryToPass(self, &input, SOUTH);
	
	writeChar('0' + (self->queue[NORTH] % 10), 0);
	writeChar('0' + (self->queue[SOUTH] % 10), 4);
	
	SYNC(&(self->lightHandler), &onLightChange, NULL);
}

void checkCarArrived(MainClass* self, int* input, int direction){

	if((*input) & (1 << (direction == NORTH ? 0 : 2))){
	
		self->queue[direction]++;
	
	}

}

void tryToPass(MainClass* self, int* input, int direction){
	
	if(*input & (1 << (direction == NORTH ? 1 : 3))){
		
		SYNC(&(self->lightHandler), &pushCarToBridge, direction);
		
		self->passedSinceChange[direction == NORTH ? SOUTH : NORTH] = 0;
		self->passedSinceChange[direction]++;
		
		self->queue[direction]--;
	}
	
	
}

void checkBridgeState(MainClass* self, int* input, int direction){

	int lightThis = direction;
	SYNC(&(self->lightHandler), &getLightState, &lightThis);
	
	int lightOther = ((direction == NORTH) ? SOUTH : NORTH);
	SYNC(&(self->lightHandler), &getLightState, &lightOther);
	
	
	if((self->passedSinceChange[direction] >= MAXCARS) && self->queue[((direction == NORTH) ? SOUTH : NORTH)]){
		SYNC(&(self->lightHandler), &setLightStateRed, direction);
		SYNC(&(self->lightHandler), &pushLightState, direction == NORTH ? SOUTH : NORTH);
	}
	else if(self->queue[direction] && (lightOther == RED)){
		SYNC(&(self->lightHandler), &pushLightState, direction);
	}
	
}