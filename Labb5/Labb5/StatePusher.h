#ifndef STATEPUSHER_H_
#define STATEPUSHER_H_
#include "TinyTimber.h"
#include "Serial.h"

#define INIT_STATEPUSHER {initObject(), (unsigned char)0b0000} 

typedef struct{

	Object super;
	Serial* serial;
	unsigned char state;
	
} StatePusher;

void initStatePusher(StatePusher* self, Serial* serial);
void setState(StatePusher* self, int state);


#endif /* STATEPUSHER_H_ */