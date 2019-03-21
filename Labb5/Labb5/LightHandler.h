/*
 * LightHandler.h
 *
 * Created: 20-Mar-19 23:21:57
 *  Author: josef
 */ 


#ifndef LIGHTHANDLER_H_
#define LIGHTHANDLER_H_

#include "TinyTimber.h"
#include "Light.h"
#include "StatePusher.h"

#define NORTH 0
#define SOUTH 1
#define INIT_LIGHTHANDLER {initObject(), NULL, {INIT_LIGHT, INIT_LIGHT}}

typedef struct{
	
	Object super;
	StatePusher* statePusher;
	Light light[2];
	
} LightHandler;

void initLightHandler(LightHandler *self, StatePusher *statePusher);
void setLightPassingDirection(LightHandler *self, int direction);


void onLightChange(LightHandler* self);
#endif /* LIGHTHANDLER_H_ */