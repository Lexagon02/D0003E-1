#include "Clock.h"
#include <avr/io.h>
#include <stdint-gcc.h>

void initClock(){
	
	// Runs the internal clock
	TCCR1B = TCCR1B | (1<<CS12);
	
}

// If the clock (TCNT1) is higher than the CYCLE value, resets the clock and returns wheter
// the clock has changed
int clockCycle(){
	
	if(TCNT1 > CYCLE){
		TCNT1 = 0;
		return 1;
	}
	return 0;
	
}