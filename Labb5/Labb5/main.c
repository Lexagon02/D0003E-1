#include <avr/io.h>
#include "TinyTimber.h"
#include "MainClass.h"
#include "Serial.h"
#include "LCD.h"

#define F_CPU 8000000
#include <util/delay.h>

int main(void){
	
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	MainClass mainClass = INIT_MAIN_CLASS;
	TINYTIMBER(&mainClass, &runMain, NULL);
}

