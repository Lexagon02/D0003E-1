#ifndef SERIAL_H_
#define SERIAL_H_

#include "TinyTimber.h"
#include "LCD.h"
#define BUFFERSIZE 100
#define INIT_SERIAL {initObject(), INIT_LCD, NULL, NULL}

typedef struct {
	Object super;
	Lcd lcd;
	Object* onReadObject;
	void (*onReadFunction)(unsigned char);
	
} Serial;


void initSerial(Serial* self, Object* onReadObject, void (*onReadFunction)(unsigned char));
void send(Serial* self, unsigned char input);
void serialAvailable(Serial* self, int* available);



#endif /* SERIAL_H_ */