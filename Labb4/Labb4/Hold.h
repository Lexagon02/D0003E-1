#ifndef HOLD_H_
#define HOLD_H_

#define HOLD_INIT(gui) {initObject(), gui}

#include "TinyTimber.h"
#include "GUI.h"
#include "pwmGenerator.h"


// Works separately from the gui and starts the hold to fast
// increments function after a given time
typedef struct {
	
	Object super;
	GUI* gui;
	int state;
	
} Hold;

void parseHold(Hold* self);



#endif /* HOLD_H_ */