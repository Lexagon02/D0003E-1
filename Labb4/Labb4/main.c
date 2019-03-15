#include <avr/io.h>
#include "GUI.h"
#include "pwmGenerator.h"
#include "TinyTimber.h"
#include "Hold.h"
#include "PortEWriter.h"

// Main object that holds all the other objects and exicutes them
typedef struct{
	
	Object super;
	GUI *gui;
	PwmGenerator* pwmGenerator1;
	PwmGenerator* pwmGenerator2;
	Hold* hold;
	
} MainObj;

void run(MainObj *self);

// Inits objects and runs the tinyTimber kernel

int main(void)
{
	
	PortEWriter portEWriter = PORTEWRITER_INIT;
	
	PwmGenerator pwmGenerators[2] = {PWMGENERATOR_INIT(&portEWriter), PWMGENERATOR_INIT(&portEWriter)};
	initPwmGenerator(&(pwmGenerators[0]), 4, 99);
	initPwmGenerator(&(pwmGenerators[1]), 6, 80);
	
	GUI gui = GUI_INIT;
	setPwmGenerators(&gui, &(pwmGenerators[0]), &(pwmGenerators[1]));
	
	Hold hold = HOLD_INIT(&gui);
	
	initGUI(&gui);
	MainObj mainObj = {initObject(), &gui, &(pwmGenerators[0]), &(pwmGenerators[1]), &hold};
	
	return TINYTIMBER(&mainObj, &run, NULL);
}

// Runs the parsers for the concerning objects
void parseJoystickData(MainObj *self){
	
	ASYNC(self->gui, &parseGUI, NULL);
	ASYNC(self->hold, &parseHold, NULL);
	
}

// Attatches the interrupts in the Kernal and 
// activates the PWM generators
void run(MainObj *self){
	
	INSTALL(self, &parseJoystickData, IRQ_PCINT0);
	INSTALL(self, &parseJoystickData, IRQ_PCINT1);
	
	SYNC(self->pwmGenerator1, &activate, NULL);
	SYNC(self->pwmGenerator2, &activate, NULL);

}