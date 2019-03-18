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
void write(unsigned char arg);

int main(void){

	MainObj mainObj = INIT_MAIN_OBJ;
	
	TINYTIMBER(&mainObj, &run, NULL);	

}

void run(MainObj* self){

	initLCD();
	initSerial(&(self->serial), self, &write);

	while(1){
		writeChar('0' + ((UCSR0A & (1<<UDRE0)) ? 1 : 0), 5);
	}

}

void write(unsigned char arg){
	
	writeChar(arg, 0);
	
}