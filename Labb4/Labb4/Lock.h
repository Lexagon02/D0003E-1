#ifndef LOCK_H_
#define LOCK_H_

#include "TinyTimber.h"

#define LOCK_INIT {initObject(), 0}

typedef struct {
	
	Object super;
	int state;
		
} Lock;

void lockState(Lock* self);


#endif /* LOCK_H_ */