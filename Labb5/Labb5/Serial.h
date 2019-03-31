#ifndef SERIAL_H_
#define SERIAL_H_

#include "TinyTimber.h"
#include "LCD.h"
#define BUFFERSIZE 100
#define INIT_SERIAL {initObject(), NULL, NULL, 0, 0}

typedef struct {
	Object super;
	Object* onReadObject;
	void (*onReadFunction)(unsigned char);
	int input;
	int output;
	
} Serial;


void initSerial(Serial* self, Object* onReadObject, void (*onReadFunction)(unsigned char));
void send(Serial* self, unsigned char output);
void serialAvailable(Serial* self, int* available);



#endif /* SERIAL_H_ */