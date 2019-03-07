#ifndef PWMGENERATOR_H_
#define PWMGENERATOR_H_

#define PWMGENERATOR_INIT {initObject(), 0, 0, 0, 0, 0}
	
#include "TinyTimber.h"
#include <stdint-gcc.h>

typedef struct {
	Object super;
	int initialized;
	int outputBit;
	int step;
	int state;
	int active;
	
} PwmGenerator;

int initPwmGenerator(PwmGenerator* self, int outputBit, int step);

void activate(PwmGenerator* self);
void deactivate(PwmGenerator* self);
void setStep(PwmGenerator* self, int* step);
void getStep(PwmGenerator* self, int* step);

#endif /* PWMGENERATOR_H_ */