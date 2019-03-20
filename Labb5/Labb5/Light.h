#ifndef LIGHT_H_
#define LIGHT_H_

#include "TinyTimber.h"
#include "Serial.h"
#define INIT_LIGHT(instance) {initObject(), NULL, NULL, instance, 0, 5, 0}

typedef struct{
	Object super;
	Serial* serial;
	Object* mainClass;
	int instance;
	int currentTime;
	int time;
	int state;
} Light;

void initLight(Light* self, Serial* serial, Object* mainClass);
int getCurrentTime(Light* self);
void setTime(Light* self, int time);
int getTime(Light* self);
int getState(Light* self);


#endif