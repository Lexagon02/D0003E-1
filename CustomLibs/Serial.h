#ifndef SERIAL_H_
#define SERIAL_H_

#include "TinyTimber.h"
#define BUFFERSIZE 100
#define INIT_SERIAL {initObject(), NULL, NULL}

typedef struct {
	Object super;
	Object* onReadObject;
	void (*onReadFunction)(unsigned char);
	
} Serial;


void initSerial(Serial* self, Object* onReadObject, void (*onReadFunction)(unsigned char));
void send(Serial* self, unsigned char input);
void serialAvailable(Serial* self, int* available);



#endif /* SERIAL_H_ */