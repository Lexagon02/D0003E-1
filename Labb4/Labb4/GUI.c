#include "GUI.h"
#include "LCD.h"
#include "Joystick.h"
#include <avr/io.h>

#define LCDLINE2REG LCDDR0
#define LCDLINE4REG LCDDR1

#define LCDLINE2BIT 5
#define LCDLINE4BIT 6


int initGUI(GUI* self){
	initLCD();
	initJoystick();
	
	render(self);
	
	return 1;
}


void writeAt(int pos, int value){
	
	writeChar('0' + (value % 100) / 10, pos);
	writeChar('0' + (value % 10), ++pos);
	
}


void render(GUI* self){
	
	writeAt(0, self->pwmGenerators[0]->step);
	writeAt(4, self->pwmGenerators[1]->step);
	
	if(self->currentChannel){
		LCDLINE2REG &= ~(1 << LCDLINE2BIT);
		LCDLINE4REG |= (1 << LCDLINE4BIT);
	}
	else{
		LCDLINE4REG &= ~(1 << LCDLINE4BIT);
		LCDLINE2REG |= (1 << LCDLINE2BIT);
	}
	
}

void run(GUI *self){
	
	INSTALL(self, parseJoystickData, IRQ_PCINT0);
	INSTALL(self, parseJoystickData, IRQ_PCINT1);
	
	SYNC(self->pwmGenerators[0], &activate, NULL);
	SYNC(self->pwmGenerators[1], &activate, NULL);
	
}

void disableInterface(GUI* self){
	
	SYNC(&(self->lock), &lockState, NULL);
	int state = 1;
	int i = 0;
	
	do {
		
		state = self->lock.state;
		writeChar('0' + self->lock.state, 3);
		writeChar('0' + (++i % 10), 2);
		
	} while (state);
	
}

void parseJoystickData(GUI *self){
	
	switch (readJoystick()) {
		
		// 0 = Center, 1 = Upp, 2 = Down, 3 = Left, 4 = Right, 5 = Center Down
		case 1:
		
			if(self->pwmGenerators[self->currentChannel]->step < 100){
				self->pwmGenerators[self->currentChannel]->step++;
				
			}
		
		break;
		
		case 2:
			
			if(self->pwmGenerators[self->currentChannel]->step >= 0){
				self->pwmGenerators[self->currentChannel]->step--;
				
			}
			
		break;
		
		case 3:
		
			self->currentChannel = 0;
		
		break;
		
		case 4:
		
			self->currentChannel = 1;
		
		break;
		
		case 5:
		break;
		
		case 0:
		break;
		
		default:
		break;
		
	}
	
	ASYNC(self, &render, NULL);
	//SYNC(self, &disableInterface, NULL);

}

void setPwmGenerators(GUI* self, PwmGenerator* pwmGenerator1, PwmGenerator* pwmGenerator2){
	self->pwmGenerators[0] = pwmGenerator1;
	self->pwmGenerators[1] = pwmGenerator2;
}
