#include "MainClass.h"
#include "LCD.h"
#include "Serial.h"

//LightObject
//Time =  will start at 0
//CurrentTime = 0; Will increment with '1',
//State, 0 = Red, 1 = Green.
//Tick() Each second the time will decrese by '1' to '0'
//
//
// if time goes upp to 20 sec, force change lights


int northQueue = 0;
int southQueue = 0;


void run(MainClass* self){
	Serial serial = INIT_SERIAL;

	writeChar('H',0);
	//SKAPA TVÅ TRÅDAR AV TYPEN LIGHT, EN NORTH, EN SOUTH
	//KÖR DEM
	
	while(1){
		if(checkSensor){

			checkCarSensor(&serial);

			checkQueue();

			checkStarvation();

			sendLight();
			
		}
	}

}
int checkSensor(Serial *serial){
	char availabel = 0;
	serialAvailable(serial, &availabel);
	if(availabel){
		return 1;
	}
}

void checkCarSensor(Serial *serial){
	char output;	
	read(serial, &output);	
	
	//Northbound car arrival sensor activated
	if(output & (1 << 0)){
		addCar(northCar);
	}
	if(output & (1 << 1)){
		setSouthLight(5);
		removeCar(northQueue);
		//NorraBroSensor
	}
	if(output & (1 << 2)){
		addCar(southCar)
	}
		
	if(output & (1 << 3)){
		setNorthLight(5);
		removeCar(southQueue);
		//södrabroskit
	}
}

void checkQueue(){

	if(northQueue == 0){
		setNorthLight(10);
	}

	if(southQueue == 0){
		setSouthLight(10);
	}
}

void checkStarvation(){
	if((southLight->getCurrentTime => 20) && (northQueue < 1)){
		setSouthLight(6);//Jag tror det borde funka	
	}
	if((northLight->getCurrentTime => 20) && (southQueue < 1)){
		setNorthLight(6);
	}

}

void sendLights(){

		int

}

void addCar(int queue){
	queue = queue + 1;
}

void removeCar(int queue){
	queue = queue - 1;
}

int northLightRed(){
	if( 0 == northLight->getLight()){
		return 1;				
	}
	return 0;
}
void setNorthLight(int time){
	northLight -> setTime(Time);
}
void setSouthLight(int time){
	southLight -> setTime(Time);
		
}

