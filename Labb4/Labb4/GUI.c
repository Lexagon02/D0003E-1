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

	return 1;
}


void writeAt(int pos, int value){
	
	writeChar('0' + (value % 100) / 10, pos);
	writeChar('0' + (value % 10), ++pos);
	
}

// Renders the LCD
void render(GUI* self){
	
	writeAt(0,self->pwmGenerators[0]->active ? self->pwmGenerators[0]->step : 0);
	writeAt(4,self->pwmGenerators[1]->active ? self->pwmGenerators[1]->step : 0);
		
	if(self->currentChannel){
		LCDLINE2REG &= ~(1 << LCDLINE2BIT);
		LCDLINE4REG |= (1 << LCDLINE4BIT);
	}
	else{
		LCDLINE4REG &= ~(1 << LCDLINE4BIT);
		LCDLINE2REG |= (1 << LCDLINE2BIT);
	}
	
}

// Parses the gui upon joystick interrupts. Reads the joystick state,
// increments/decrements the pwm signal speed on up/down, changes the
// current pwm chanel on left/right and activates/deactivates the pwm
// on input push

void parseGUI(GUI *self){
	
	if(self->lock.state) return;
	
	switch (readJoystick()) {
		
		// 0 = Center, 1 = Upp, 2 = Down, 3 = Left, 4 = Right, 5 = Center Down
		case 1:
			if(self->debounce || !self->pwmGenerators[self->currentChannel]->active) return;
			
			SYNC(self->pwmGenerators[self->currentChannel], &incrementStep, NULL);
			self->debounce = 1;
			
		break;
		
		case 2:
			if(self->debounce || !self->pwmGenerators[self->currentChannel]->active) return;
			
			SYNC(self->pwmGenerators[self->currentChannel], &decrementStep, NULL);
			self->debounce = 1;
			
		break;
		
		case 3:
			if(self->debounce) return;	
			self->currentChannel = 0;
			self->debounce = 1;
		break;
		
		case 4:
			if(self->debounce) return;
			self->currentChannel = 1;
			self->debounce = 1;
		break;
		
		case 5:
			if(self->debounce || !self->pwmGenerators[self->currentChannel]->step) return;
			
			if(self->pwmGenerators[self->currentChannel]->active){
				deactivate(self->pwmGenerators[self->currentChannel]);
			}
			else{
				activate(self->pwmGenerators[self->currentChannel]);
			}
			self->debounce = 1;
		break;
		
		case 0:
			self->debounce = 0;
			self->hold = 0;
		break;
		
		default:
		break;
		
	}
	
	render(self);
	SYNC(&(self->lock), &lockState, NULL);

}

void setPwmGenerators(GUI* self, PwmGenerator* pwmGenerator1, PwmGenerator* pwmGenerator2){
	self->pwmGenerators[0] = pwmGenerator1;
	self->pwmGenerators[1] = pwmGenerator2;
}
