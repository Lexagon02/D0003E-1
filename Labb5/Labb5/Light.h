#ifndef LIGHT_H_
#define LIGHT_H_

#include "TinyTimber.h"
#define INIT_LIGHT {initObject()}

typedef struct{
	Object super;
	int currentTime;
	int time;
	int state;
} Light;

void initLight(Light* self);
int getCurrentTime(Light* self);
void setTime(Light* self, int time);
int getTime(Light* self);
int getState(Light* self);


#endif