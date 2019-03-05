#ifndef GUI_H_
#define GUI_H_

#define GUI_INIT(self) {initObject(), initGUI(self)}

#include "TinyTimber.h"

typedef struct {
	Object super;
	int initialized;
	
} GUI;

int initGUI(GUI* self);
void writeAt(int pos, int value);


#endif