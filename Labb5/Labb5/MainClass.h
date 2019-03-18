#ifndef MAINCLASS_H_
#define MAINCLASS_H_
#define INIT_MAIN_CLASS(northQueue,southQueue) {initObject(),INIT_SERIAL,INIT_LIGHT, INIT_LIGHT, northQueue, southQueue}

#include "TinyTimber.h"
#include "Serial.h"
#include "Light.h"

typedef struct{
	
	Object super;
	Serial serial;
	Light north;
	Light south;
	int* northQueue;
	int* southQueue;
} MainClass;

void run(MainClass* self);
void onSensorRead(MainClass* self, unsigned char input);

#endif /* MAINCLASS_H_ */
