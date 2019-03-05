#ifndef PWMGENERATOR_H_
#define PWMGENERATOR_H_

#define PWMGENERATOR_INIT() (initObject(), 0)

#include "TinyTimber.h"

typedef struct {
	Object super;
	int initialized;
	
} PwmGenerator;

void initPwmGenerator(PwmGenerator* self);

#endif /* PWMGENERATOR_H_ */