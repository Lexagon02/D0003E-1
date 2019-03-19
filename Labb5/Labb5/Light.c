
/*
 * Light.c
 *
 * Created: 18-Mar-19 16:57:43
 *  Author: Ya boi Asmongold
 */ 
#include "Light.h"
#include "LCD.h"
#include "TinyTimber.h"

void initLight(Light* self){
	self -> currentTime = 0;
	self -> time = 5; 
	self -> state = 0;
	tick(self);
}



void tick(Light* self){
	writeChar('0' + (self->time % 10), 3);
	if(self->time > 0){
		self->time = self->time -1;
	}
	if((self->time) <= 5){
		self->state = 0;
	}
	else{
		self->state = 1;
		
	}
	
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

