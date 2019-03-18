#ifndef SERIAL_H_
#define SERIAL_H_

#include "TinyTimber.h"

#define INIT_SERIAL {initObject()}

typedef struct {
	Object super;
	
} Serial;


void initSerial(Serial* self);
void send(Serial* self, unsigned char input);
void read(Serial* self, unsigned char* output);
void serialAvailable(Serial* self, int* available);



#endif /* SERIAL_H_ */