#include "Light.h"


void initLight(Light* self, Object* onStateChangeObject, void (*onStateChangeFunction)(int)){
	self->onStateChangeObject = onStateChangeObject;
	self->onStateChangeFunction = onStateChangeFunction;
}

void getLightState(Light* self, int* state){
	*state = self->state;
}

void setLight(Light* self, int state){
	
	self->state = state;

}