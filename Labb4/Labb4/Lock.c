#include "Lock.h"
#include "TinyTimber.h"

#define TIMEOUT 10

void unlockState(Lock *self){
	self->state = 0;
}

void lockState(Lock *self){
	self->state = 1;
	BEFORE(MSEC(TIMEOUT), self, &unlockState, NULL);
	
}