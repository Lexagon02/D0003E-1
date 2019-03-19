#include "MainClass.h"
#include "LCD.h"
#include "Serial.h"
#include "Light.h"
//LightObject
//Time =  will start at 0
//CurrentTime = 0; Will increment with '1',
//State, 0 = Red, 1 = Green.
//Tick() Each second the time will decrese by '1' to '0'
//
//
// if time goes upp to 20 sec, force change lights


void addSouthCar(MainClass* self);
void addNorthCar(MainClass* self);

void removeNorthCar(MainClass* self);
void removeSouthCar(MainClass* self);

void runMain(MainClass* self){


	initSerial(&(self->serial), self, &onSensorRead);
	SYNC(&(self->north), &initLight, NULL);
	SYNC(&(self->south), &initLight, NULL);
	
}

void onSensorRead(MainClass* self, unsigned char input){
	// TODO: Remove
	writeChar('0' + (input % 10), 5);
	
	checkCarSensor(self, input);
	//checkQueue(self);
	//checkStarvation();
	//sendLight(self);
	
	
}

void checkCarSensor(MainClass* self, char output){
	
	//Northbound car arrival sensor activated
	if(output & (1 << 0)){
		addNorthCar(self);
	}
	if(output & (1 << 1)){
		setSouthLight(5);
		removeNorthCar(self);
		//NorraBroSensor
	}
	if(output & (1 << 2)){
		addSouthCar(self);
	}
		
	if(output & (1 << 3)){
		setNorthLight(5);
		removeSouthCar(self);
		//södrabroskit
	}
}

void checkQueue(MainClass* self){

	if(*(self->northQueue) == 0){
		setSouthLight(10);
	}

	if(self->southQueue == 0){
		setNorthLight(10);
	}
}

void checkStarvation(MainClass* self){						//Fråga Josef of Jag får värdet eller bara pekaren
	if((SYNC(&(self->south), &getCurrentTime, NULL) >= 20) && ( *(self->northQueue) > 0 )){
		setSouthLight(6);//Jag tror det borde funka	
	}
	if((SYNC(&(self->north), &getCurrentTime, NULL) >= 20) && ( *(self->southQueue) > 0)){
		setNorthLight(6);
	}
}

void sendLight(MainClass* self){
	int input = 0;
	
	if(SYNC(&(self->north), &getState, NULL) == 0){
		input = input | (1 << 1);	
	}else{
		input = input | 1;
	}
	if(SYNC(&(self->north), &getState, NULL) == 0){
		input = input | (1 << 3);
	}
	else{
		input = input | (1 << 2);
	}
	ASYNC(&(self->serial), &send, 'H');
}


void addSouthCar(MainClass* self){
	*(self->southQueue) = *(self->southQueue) + 1;
	
}

void addNorthCar(MainClass* self){
	*(self->northQueue) = *(self->northQueue) + 1;
}

void removeNorthCar(MainClass* self){
	 *(self->northQueue) = *(self->northQueue) - 1;
}
void removeSouthCar(MainClass* self){
	*(self->southQueue) = *(self->southQueue) - 1;
}

int northLightRed(MainClass* self){
	if(SYNC(&(self->north), &getState, NULL) == 0){
		return 1;
	
	}
	return 0;
}
void setNorthLight(MainClass* self, int time){
	SYNC(&(self->north), &setTime, time);
}
void setSouthLight(MainClass* self, int time){
	SYNC(&(self->south), &setTime,time);
		
}

