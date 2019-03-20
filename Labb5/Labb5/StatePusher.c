#include "StatePusher.h"

void cycleStatePusher(StatePusher* self);

void initStatePusher(StatePusher* self, Serial* serial){
	self->serial = serial;
	SYNC(self, &cycleStatePusher, NULL);
	
}

void setState(StatePusher* self, int state){
	
	self->state = state;
	SYNC(self, &cycleStatePusher, NULL);
	
}
void cycleStatePusher(StatePusher* self){
	
	ASYNC(self->serial, &send, self->state);
	SEND(MSEC(100), MSEC(110), self, &cycleStatePusher, NULL);
	
}