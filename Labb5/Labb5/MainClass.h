#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#define NORTH 0
#define SOUTH 1

#define INIT_MAIN_CLASS {initObject(), INIT_SERIAL, INIT_STATEPUSHER, {INIT_LIGHT(NORTH), INIT_LIGHT(SOUTH)}, {0, 0}}

#include "TinyTimber.h"
#include "Serial.h"
#include "Light.h"
#include "StatePusher.h"

typedef struct{
	
	Object super;
	Serial serial;
	StatePusher statePusher;
	Light lights[2];
	int queue[2];
	
} MainClass;

void runMain(MainClass* self);
void onSensorRead(MainClass* self, unsigned char input);
void sendLightData(MainClass* self);
#endif /* MAINCLASS_H_ */
