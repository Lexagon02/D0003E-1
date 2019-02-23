#ifndef CYCLE
#define CYCLE 15625		// 8000000 / (2 * 256)			Clock frequency / (freq * prescaler)
#endif

void initClock();
int clockCycle();