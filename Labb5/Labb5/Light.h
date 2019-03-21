#ifndef LIGHT_H_
#define LIGHT_H_

#include "TinyTimber.h"

#define RED 0
#define GREEN 1

#define INIT_LIGHT {initObject(), GREEN, NULL, NULL}

typedef struct {

	Object super;
	int state;
	Object* onStateChangeObject;
	void (*onStateChangeFunction)(int);
	
} Light;

void initLight(Light* self, Object* onStateChangeObject, void (*onStateChangeFunction)(int));
void getLightState(Light* self, int* state);
void setLight(Light* self, int state);

#endif /* LIGHT_H_ */