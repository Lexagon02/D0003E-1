#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#define INIT_MAIN_CLASS {initObject(), INIT_SERIAL, INIT_LIGHTHANDLER, {0, 0}, {0, 0}}

#include "TinyTimber.h"
#include "Serial.h"
#include "LightHandler.h"

typedef struct{
	
	Object super;
	Serial serial;
	LightHandler lightHandler;
	int queue[2];
	int passedSinceChange[2];
	
} MainClass;

void runMain(MainClass* self);
void onSensorRead(MainClass* self, int input);
void sendLightData(MainClass* self);
#endif /* MAINCLASS_H_ */
