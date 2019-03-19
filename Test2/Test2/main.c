#include <avr/io.h>
#include "TinyTimber.h"
#include "LCD.h"
#include "Serial.h"

#define INIT_MAIN_OBJ {initObject(), INIT_SERIAL};

typedef struct {
	
	Object super;
	Serial serial;
	
} MainObj;

void run(MainObj* self);
void write(MainObj* self, unsigned char arg);

int ehh;
int main(void){

	MainObj mainObj = INIT_MAIN_OBJ;
	
	TINYTIMBER(&mainObj, &run, NULL);	

}

void run(MainObj* self){
	
	ehh = 0;
	
	initLCD();
	initSerial(&(self->serial), self, &write);

}


void write(MainObj* self, unsigned char arg){
	
	
	writeChar(arg, ehh++);
	
	//writeChar('H', 0);
	
	/*
	int temp = (int)arg;
	
	for(int i = 5; i >= 1; i-- ){
		
		writeChar('0' + (temp % 10), i);
		temp = temp / 10;
		
	}
	*/
}