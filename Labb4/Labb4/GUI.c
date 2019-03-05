#include "GUI.h"
#include "LCD.h"
#include "Joystick.h"

int initGUI(GUI* self){
	initLCD();
	//initJoystick();
	
	writeAt(0, 0);
	writeAt(3, 0);
	return 1;
}


void writeAt(int pos, int value){
	
	writeChar('0' + (value % 100) / 10, pos);
	writeChar('0' + (value % 10), ++pos);
	
}