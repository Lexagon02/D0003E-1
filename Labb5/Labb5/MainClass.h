#ifndef MAINCLASS_H_
#define MAINCLASS_H_
#define INIT_MAIN_CLASS {initObject()}

#include "TinyTimber.h"

typedef struct{
	
	Object super;
	
} MainClass;

void run(MainClass* self);


#endif /* MAINCLASS_H_ */