#ifndef LIGHT_H_
#define LIGHT_H_

#include "TinyTimber.h"
//Buffer?

typedef struct{
	Object super;
	int currentTime;
	int time;
	int state;
} Light;

void tick();
void getCurrentTime();
void setTime(int time);
void getTIme();


