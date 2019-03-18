<<<<<<< HEAD
/*
 * Light.c
 *
 * Created: 18-Mar-19 16:57:43
 *  Author: josef
 */ 
=======
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

>>>>>>> 2f9841fc8eb7f427341c5246be3e9d6f5d958cc1
