#include "MainClass.h"
#include "Serial.h"

int checkCarArrival(char input, int instance);
int checkCarCrossing(MainClass* self, char input, int instance);
void letCarCross(MainClass* self, int instance);
int checkCollision(MainClass* self, int input);

void addCar(MainClass* self, int direction);
void removeCar(MainClass* self, int direction);

void writeHere(MainClass* self){
	int temp[2] = {(int)'H', 3};
	SYNC(&(self->serial.lcd), &writeChar, temp);
	while(1);
}

void runMain(MainClass* self){
	
	initSerial(&(self->serial), (Object*)(self), (void*)&onSensorRead);
	initStatePusher(&(self->statePusher), &(self->serial));
	initLightHandler(&(self->lightHandler), &(self->statePusher));
	//self->lightHandler.light[NORTH].state = RED;
	
	SYNC(&(self->lightHandler), &onLightChange, NULL);
}

void onSensorRead(MainClass* self, unsigned char input){
	
	//Northbound car arrival sensor activated
	if(checkCarArrival(input, NORTH)){
		addCar(self, NORTH);
	}
	if(checkCarArrival(input, SOUTH)){
		addCar(self, SOUTH);
	}
	
	if(checkCarCrossing(self, input, NORTH)){
		letCarCross(self, NORTH);
	}
	if(checkCarCrossing(self, input, SOUTH)){
		letCarCross(self, SOUTH);
	}
	
	SYNC(&(self->lightHandler), &onLightChange, NULL);
	
}

int checkCarArrival(char input, int instance){
	return (input & (1 << (instance == NORTH ? 0 : 2)));
}

int checkCarCrossing(MainClass* self, char input, int instance){
	
	int state;
	SYNC(&(self->lightHandler.light[instance]), &getLightState, &state);
	
	return (input & (1 << (instance == NORTH ? 1 : 3))) && state == GREEN;
}

void letCarCross(MainClass* self, int instance){
	
	SYNC(&(self->lightHandler), &setLightPassingDirection, instance);
	
	removeCar(self, instance);
}

int checkCollision(MainClass* self, int input){
	
	return input == 0b1010;
}

void addCar(MainClass* self, int direction){
	self->queue[direction]++;
}

void removeCar(MainClass* self, int direction){
	self->queue[direction]--;
}
