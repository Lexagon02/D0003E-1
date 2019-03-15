#ifndef SERIAL_H_
#define SERIAL_H_

#include "TinyTimber.h"

#define INIT_SERIAL {initObject()}

typedef struct {
	Object super;
} Serial;

void initSerial(Serial* self);
void send(Serial* self, unsigned char input);
void read(Serial* self, int* output);


#endif /* SERIAL_H_ */