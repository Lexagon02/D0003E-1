#ifndef MAINCLASS_H_
#define MAINCLASS_H_
#define INIT_MAIN_CLASS(northQueue,southQueue) {initObject(), northQueue, southQueue}

#include "TinyTimber.h"

typedef struct{
	
	Object super;
	int* northQueue;
	int* southQueue;
} MainClass;

void run(MainClass* self);
void onSensorRead(MainClass* self, unsigned char input);

#endif /* MAINCLASS_H_ */
