#ifndef PWMGENERATOR_H_
#define PWMGENERATOR_H_

#define PWMGENERATOR_INIT(portEWriter) {initObject(), portEWriter, 0, 0, 0, 0, 0}
	
#include "TinyTimber.h"
#include "PortEWriter.h"

// Takes care of the pwm generation and stores state and speed of
// one pwm instance
typedef struct {
	Object super;
	PortEWriter* portEWriter;
	int initialized;
	int outputBit;
	int step;
	int state;
	int active;
	
	
} PwmGenerator;

int initPwmGenerator(PwmGenerator* self, int outputBit, int step);

void activate(PwmGenerator* self);
void deactivate(PwmGenerator* self);
void incrementStep(PwmGenerator* self);
void decrementStep(PwmGenerator* self);
void setStep(PwmGenerator* self, int* step);
void getStep(PwmGenerator* self, int* step);

#endif /* PWMGENERATOR_H_ */