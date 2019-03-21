#include "MainClass.h"
#include "Serial.h"

void checkCarArrived(MainClass* self, int* input, int direction);
void parseLightStatus(MainClass* self, int* input, int direction);
void cycleSensorRead(MainClass* self);

void runMain(MainClass* self){
	
	initSerial(&(self->serial), (Object*)(self), (void*)&onSensorRead);
	initLightHandler(&(self->lightHandler), &(self->serial));
	
	SYNC(self, &cycleSensorRead, NULL);
}

void cycleSensorRead(MainClass* self){
	
	onSensorRead(self, 0b0000);
	
	SEND(MSEC(1000), MSEC(2000), self, &cycleSensorRead, NULL);
	
}

void onSensorRead(MainClass* self, int input){
		
	checkCarArrived(self, &input, NORTH);
	checkCarArrived(self, &input, SOUTH);
	
	parseLightStatus(self, &input, NORTH);
	parseLightStatus(self, &input, SOUTH);
	
	writeChar('0' + self->queue[0], 0);
	writeChar('0' + self->queue[1], 5);
	
}

void checkCarArrived(MainClass* self, int* input, int direction){

	if((*input) & (1 << (direction == NORTH ? 0 : 2))){
	
		self->queue[direction]++;
	
	}

}

void parseLightStatus(MainClass* self, int* input, int direction){
	
	int arg = direction;
	SYNC(&(self->lightHandler), &getLightState, &arg);
	
	if(self->queue[direction] && arg == GREEN){
		self->queue[direction]--;
		SYNC(&(self->lightHandler), &pushLightState, direction);
	}
	
}