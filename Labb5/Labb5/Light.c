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

