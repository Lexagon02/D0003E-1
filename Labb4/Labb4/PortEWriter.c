#include "PortEWriter.h"
#include <avr/io.h>
#include <stdint-gcc.h>

void write(PortEWriter* self, int* arg){
	
	if(arg[1]){
		PORTE |= (1 << arg[0]);

	}
	else{
		PORTE &= ~(1 << arg[0]);
	}
	
}