#ifndef SERIAL_H_
#define SERIAL_H_

#include "TinyTimber.h"
#include "CircularBuffer.h"

#define INIT_SERIAL {initObject(), INIT_CIRCULAR_BUFFER, INIT_CIRCULAR_BUFFER}

typedef struct {
	Object super;
	CircularBuffer writeBuffer;
	CircularBuffer readBuffer;
	
} Serial;


void initSerial(Serial* self);
void send(Serial* self, unsigned char input);
void read(Serial* self, unsigned char* output);
void serialAvailable(Serial* self, int* available);

void writeToSerial(Serial* self);


#endif /* SERIAL_H_ */