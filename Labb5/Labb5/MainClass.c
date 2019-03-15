#include "MainClass.h"
#include "LCD.h"
#include "Serial.h"



void run(MainClass* self){
	Serial serial = INIT_SERIAL;
	
	
	writeChar('H',0);
	
}
int checkSensor(Serial *serial){
	char availabel = 0;
	serialAvailable(serial, availabel);
	if(availabel){
		return 1;
	}
}

int checkCarSensor(Serial *serial){
	char output;	
	read(serial, &output);	
	
	//Northbound car arrival sensor activated
	if(output & (1<<0)){
		
	}
	
	
}
