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
#define GREEN 2
#define RED 3
#define CARPASSINGTIME 5000

#define INIT_LIGHTHANDLER {initObject(), NULL, 0, {RED, RED}}

typedef struct{
	
	Object super;
	Serial *serial;
	int carsOnBridge;
	int lightState[2];
	
} LightHandler;

void initLightHandler(LightHandler *self, Serial *serial);
void getLightState(LightHandler* self, int* arg);
void setLightStateRed(LightHandler* self, int direction);
void pushLightState(LightHandler* self, int direction);
void pushCarToBridge(LightHandler* self, int direction);
void getCarsOnBridge(LightHandler* self, int* output);

void onLightChange(LightHandler* self);
#endif /* LIGHTHANDLER_H_ */