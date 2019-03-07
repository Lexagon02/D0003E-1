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

int stepToHalfPeriod(int step){
	
	return step * 10;
	
}

void cycle(PwmGenerator* self){

	
	if(self->active){
		if(self->state){
			WRITEREGISTER &= ~(1 << self->outputBit);

		}
		else{
			WRITEREGISTER |= (1 << self->outputBit);
		}
		
		self->state = !self->state;
		
		SEND(MSEC(stepToHalfPeriod(self->step) - OFFCET), MSEC(stepToHalfPeriod(self->step) + OFFCET), self, &cycle, NULL);
	}
	else{
		WRITEREGISTER &= ~(1 << self->outputBit);
	}
	
}

void activate(PwmGenerator* self){
	
	self->active = 1;
	cycle(self);

}

void deactivate(PwmGenerator* self){
	self->active = 0;
}

void setStep(PwmGenerator* self, int* step){
	
	self->step = *step;
}

void getStep(PwmGenerator* self, int* step){
	
	*step = self->step;
	
}