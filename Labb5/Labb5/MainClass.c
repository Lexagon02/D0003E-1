#include "MainClass.h"
#include "LCD.h"
#include "Serial.h"
#include "Light.h"

void checkCarSensor(MainClass* self, char output);
void checkStarvation(MainClass* self);
void addCar(MainClass* self, int direction);
void removeCar(MainClass* self, int direction);
void setLight(MainClass* self, int direction, int time);

void runMain(MainClass* self){
	
	initLCD();
	initSerial(&(self->serial), (Object*)(self), (void*)&onSensorRead);
	initStatePusher(&(self->statePusher), &(self->serial));
	SYNC(&(self->lights[NORTH]), &initLight, self);
	SYNC(&(self->lights[SOUTH]), &initLight, self);
	
}

void onSensorRead(MainClass* self, unsigned char input){
	
	checkCarSensor(self, input);
	//checkStarvation(self);	
	sendLightData(self);
	
}

int checkCarArrival(char input, int instance){
	return (input & (1 << (instance == NORTH ? 0 : 2)));
}

int checkCarCrossing(char input, int instance){
	return (input & (1 << (instance == NORTH ? 1 : 3)));
}

void letCarCross(MainClass* self, int instance){
	setLight(self, (instance == NORTH ? SOUTH : NORTH), 5);
	removeCar(self, instance);
}

int checkCollision(MainClass* self, int input){
	
	return input == 0b1010;
}

void checkCarSensor(MainClass* self, char input){
	
	//Northbound car arrival sensor activated
	if(checkCarArrival(input, NORTH)){
		addCar(self, NORTH);
	}
	if(checkCarArrival(input, SOUTH)){
		addCar(self, SOUTH);
	}
	
	if(checkCarCrossing(input, NORTH)){
		letCarCross(self, NORTH);
	}
	if(checkCarCrossing(input, SOUTH)){
		letCarCross(self, SOUTH);
	}
}

void checkStarvation(MainClass* self){						
	if((SYNC(&(self->lights[SOUTH]), &getCurrentTime, NULL) >= 20) && (self->queue[NORTH] > 0 )){
		setLight(self, SOUTH, 6);
	}
	if((SYNC(&(self->lights[NORTH]), &getCurrentTime, NULL) >= 20) && (self->queue[SOUTH] > 0)){
		setLight(self, NORTH, 6);
	}
}

void addCar(MainClass* self, int direction){
	self->queue[direction]++;
}

void removeCar(MainClass* self, int direction){
	self->queue[direction]--;
}

void setLight(MainClass* self, int direction, int time){
	ASYNC(&(self->lights[direction]), &setTime, time);
}


void sendLightData(MainClass* self){
	
	int parsedValue = 0;
	
	for(int i = 0; i < 2; i++){
		
		if(self->lights[i].state){
			parsedValue |= (1 << (i * 2));
		}
		else{
			parsedValue |= (1 << (1 + i * 2));
		}
		
	}
	
	//parsedValue = 0b1111;
	
	SYNC(&(self->statePusher), &setState, (unsigned char)parsedValue);
	
}