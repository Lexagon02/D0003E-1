#include "pwmGenerator.h"
#include "TinyTimber.h"

#include <avr/io.h>
#include <stdint-gcc.h>

#define OFFCET 10
#define WRITEREGISTER PORTE
#define SETUPREGISTER DDRE


int initPwmGenerator(PwmGenerator* self, int outputBit, int step){

	self->initialized = 1;	
	self->outputBit = outputBit;
	self->step = step;
	self->state = 0;
	self->active = 0;
	
	SETUPREGISTER |= (1 << outputBit);
	
	return 1;
	
}

// Converts the current step that is outputed on the LCD to a 
// half period of the pwm signal
int stepToHalfPeriod(int step){
	
	return (100 - step);
	
}

// Flips the outputbit and starts an avalanche effect that reqursevly 
// calls itself after the currently stored half period
void cycle(PwmGenerator* self){
	
	if(self->active){
		
		int arg[2] = { self->outputBit, self->state };
		SYNC(self->portEWriter, &write, arg);
		
		self->state = !self->state;
		
		SEND(MSEC(stepToHalfPeriod(self->step)), MSEC(stepToHalfPeriod(self->step) + OFFCET), self, &cycle, NULL);
	}
	else{
		
		int arg[2] = { self->outputBit, 0 };
		SYNC(self->portEWriter, &write, arg);
	}
	
}

void activate(PwmGenerator* self){
	
	self->active = 1;
	cycle(self);

}

void deactivate(PwmGenerator* self){
	self->active = 0;
}

void incrementStep(PwmGenerator* self){
	if(self->step < 99){
		self->step++;
		
	}
}

void decrementStep(PwmGenerator* self){
	if(self->step > 0){
		self->step--;
		
	}
}

void setStep(PwmGenerator* self, int* step){
	
	self->step = *step;
}

void getStep(PwmGenerator* self, int* step){
	
	*step = self->step;
	
}