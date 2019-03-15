#include "Hold.h"
#include "Joystick.h"

#define DELAY 1000
#define STEPDELAY 100


// Cycles and increments/decrements the pwm step counter if the 
// joystick still has the correct input. Starts itself again after
// a defined time
void cycleUp(Hold* self){
	
	if(readJoystick() == 1 && self->gui->pwmGenerators[self->gui->currentChannel]->active){
		
		SYNC(self->gui->pwmGenerators[self->gui->currentChannel], &incrementStep, NULL);
		SYNC(self->gui, &render, NULL);
		SEND(MSEC(STEPDELAY), MSEC(STEPDELAY + 10), self, &cycleUp, NULL);
		
	}
	else{
		self->state = 0;
	}
	
}

void cycleDown(Hold* self){
	
	if(readJoystick() == 2 && self->gui->pwmGenerators[self->gui->currentChannel]->active){
		
		SYNC(self->gui->pwmGenerators[self->gui->currentChannel], &decrementStep, NULL);
		SYNC(self->gui, &render, NULL);
		SEND(MSEC(STEPDELAY), MSEC(STEPDELAY + 10), self, &cycleDown, NULL);
		
	}
	else{
		self->state = 0;
	}
	
}


// Checks the state of the joystick and starts a cycle up/down after 
// a given delay time
void parseHold(Hold* self){
	
	if(self->state) return;
	
	switch (readJoystick()) {
		
		case 1:
			self->state = 1;
			SEND(MSEC(DELAY), MSEC(DELAY + 10), self, &cycleUp, NULL);
			break;
			
		case 2:
			self->state = 1;
			SEND(MSEC(DELAY), MSEC(DELAY + 10), self, &cycleDown, NULL);
			break;
		
		default:
			self->state = 0;
			break;
		
	}
	
}
