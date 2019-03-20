#include "MainClass.h"
#include "LCD.h"
#include "Serial.h"
#include "Light.h"

void checkCarSensor(MainClass* self, char output);
void checkQueue(MainClass* self);
void checkStarvation(MainClass* self);
void addCar(MainClass* self, int direction);
void removeCar(MainClass* self, int direction);
void setLight(MainClass* self, int direction, int time);

void runMain(MainClass* self){
	
	initLCD();
	initSerial(&(self->serial), (Object*)(self), (void*)&onSensorRead);
	SYNC(&(self->lights[NORTH]), &initLight, self);
	SYNC(&(self->lights[SOUTH]), &initLight, self);
	
}

void onSensorRead(MainClass* self, unsigned char input){
	
	checkCarSensor(self, input);
	//checkQueue(self);
	checkStarvation(self);	
	sendLightData(self);
	
}

void checkCarSensor(MainClass* self, char output){
	//Ifall det kommer in två bilar samtidigt så sätts det södra ljuset till rött
	if(output == 5){
		if((self->lights[NORTH].state & self->lights[SOUTH].state) &( (self->queue[NORTH] == 0) & (self->queue[SOUTH] == 0))){
			
			setLight(self,SOUTH, 5);
			
		}
		
	}
	
	//Northbound car arrival sensor activated
	if(output & (1 << 0)){
		addCar(self, NORTH);
	}
	if(output & (1 << 1)){
		setLight(self, SOUTH, 5);
		removeCar(self, NORTH);
		//NorraBroSensor
	}
	if(output & (1 << 2)){
		addCar(self, SOUTH);
	}
		
	if(output & (1 << 3)){
		setLight(self, NORTH, 5);
		removeCar(self, SOUTH);
		//södrabroskit
	}
}

void checkQueue(MainClass* self){

	if(!self->queue[NORTH]){
		setLight(self, SOUTH, 10);
	}

	else if(!self->queue[SOUTH]){
		setLight(self, SOUTH, 10);
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
		
		parsedValue |= (1 << ((i * 2) + (self->lights[i].state ? 0 : 1)));
		
	}
	
	ASYNC(&(self->serial), &send, (unsigned char)parsedValue);
	
}