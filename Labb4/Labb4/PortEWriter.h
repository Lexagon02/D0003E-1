#ifndef PORTEWRITER_H_
#define PORTEWRITER_H_

#include "TinyTimber.h"

#define PORTEWRITER_INIT {initObject()}

typedef struct{

	Object super;
	
}PortEWriter;

void write(PortEWriter* self, int* arg);

#endif /* PORTEWRITER_H_ */