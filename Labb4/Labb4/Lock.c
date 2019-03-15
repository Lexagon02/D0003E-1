#include "Lock.h"
#include "TinyTimber.h"

#define TIMEOUT 40

void unlockState(Lock *self){
	
	self->state = 0;
}

void lockState(Lock *self){
	
	self->state = 1;
	SEND(MSEC(TIMEOUT), MSEC(TIMEOUT + 10), self, &unlockState, NULL);
	
}