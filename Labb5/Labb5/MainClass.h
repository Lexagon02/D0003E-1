#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#define INIT_MAIN_CLASS {initObject(), INIT_SERIAL, INIT_STATEPUSHER, INIT_LIGHTHANDLER, {0, 0}}

#include "TinyTimber.h"
#include "Serial.h"
#include "LightHandler.h"
#include "StatePusher.h"

typedef struct{
	
	Object super;
	Serial serial;
	StatePusher statePusher;
	LightHandler lightHandler;
	int queue[2];
	
} MainClass;

void runMain(MainClass* self);
void onSensorRead(MainClass* self, unsigned char input);
void sendLightData(MainClass* self);
#endif /* MAINCLASS_H_ */
