
/*
 * Light.c
 *
 * Created: 18-Mar-19 16:57:43
 *  Author: Ya boi Asmongold
 */ 
#include "Light.h"
#include "LCD.h"
#include "TinyTimber.h"



void run(Light* self){
	tick();
}


void tick(){

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

