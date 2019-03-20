#include "Light.h"
#include "LCD.h"
#include "TinyTimber.h"
#include "MainClass.h"

void tick(Light* self);

void initLight(Light* self, Serial* serial, Object* mainClass){
	self->serial = serial;
	self->mainClass = mainClass;
	tick(self);
}

void tick(Light* self){
	writeChar('0' + (self->state % 10), 3 + self->instance);
	
	if(self->time > 0){
		self->time--;
	}
	
	self->state = (!self->time);
	self->currentTime = (self->state ? self->currentTime + 1 : 0);
	
	ASYNC(self->mainClass, &sendLightData, NULL);
	SEND(MSEC(1000),MSEC(1010),self,tick,NULL);
}

int getTime(Light* self){
	return self -> time;

}

int getCurrentTime(Light* self){
	return self -> currentTime;
}

void setTime(Light* self, int time){
	self -> time = time;
}

int getState(Light* self){
	return self->state;
}

