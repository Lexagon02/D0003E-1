
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
}

void run(Light* self){
	tick(self);
}


void tick(Light* self){
	if(En secund har paserat){
		self -> time = self -> time + 1
	}
}

int getTime(Light* self){
	return self -> time;

}

int getCurrentTime(Light* self){
	return self -> currentTime;
}

void setTime(Light* self,int time){
	self -> time = time;
}

