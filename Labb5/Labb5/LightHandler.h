/*
 * LightHandler.h
 *
 * Created: 20-Mar-19 23:21:57
 *  Author: josef
 */ 


#ifndef LIGHTHANDLER_H_
#define LIGHTHANDLER_H_

#include "TinyTimber.h"
#include "Serial.h"

#define NORTH 0
#define SOUTH 1
#define GREEN 1
#define RED 0
#define CARPASSINGTIME 5000

#define INIT_LIGHTHANDLER {initObject(), NULL, {0, 0}, {GREEN, GREEN}}

typedef struct{
	
	Object super;
	Serial *serial;
	int activePassingSemaphore[2];
	int lightState[2];
	
} LightHandler;

void initLightHandler(LightHandler *self, Serial *serial);
void getLightState(LightHandler* self, int* arg);
void pushLightState(LightHandler* self, int direction);

void onLightChange(LightHandler* self);
#endif /* LIGHTHANDLER_H_ */