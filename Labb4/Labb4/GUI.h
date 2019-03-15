#ifndef GUI_H_
#define GUI_H_

#define GUI_INIT {initObject(), 0, 0, {NULL, NULL}, {initObject(), 0},0,0}

#include "TinyTimber.h"
#include "pwmGenerator.h"
#include "Lock.h"

// An objects that takes care of joystick inputs, and the screen
typedef struct {
	Object super;
	int initialized;
	int currentChannel;
	PwmGenerator* pwmGenerators[2];
	Lock lock;
	int debounce;
	int hold;
	
} GUI;

int initGUI(GUI* self);
void writeAt(int pos, int value);
void render(GUI* self);
void parseGUI(GUI *self);
void setPwmGenerators(GUI* self, PwmGenerator* pwmGenerator1, PwmGenerator* pwmGenerator2);
void activateHold(GUI* self);


#endif