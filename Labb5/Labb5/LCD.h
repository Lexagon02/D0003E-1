#ifndef LCD_H
#define LCD_H

#include "TinyTimber.h"

#define INIT_LCD {initObject()}

typedef struct {

	Object super;
	
} Lcd;

void initLCD(Lcd* self);
void writeChar(Lcd* self, int* arg);
void clear();

#endif 