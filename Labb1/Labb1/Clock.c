#include "Clock.h"
#include <avr/io.h>
#include <stdint-gcc.h>

int lastVal;
int currentVal;

void initClock(){
	
	// Runs the internal clock
	TCCR1B = TCCR1B | (1<<CS12);
	lastVal = TCCR1B;
}

// If the clock (TCNT1) is higher than the CYCLE value, resets the clock and returns whether
// the clock has changed
int clockCycle(){

    currentVal = TCNT1 - lastVal;
    while (currentVal < 0){
        currentVal += CYCLE;
    }

	if(currentVal > CYCLE){
		lastVal = TCNT1;
		return 1;
	}
	return 0;
	
}