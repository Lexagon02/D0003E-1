/*
 * Labb3_2.c
 *
 * Created: 23-Feb-19 17:41:16
 * Author : josef
 */ 

#include <avr/io.h>
#include "tinythreads.h"
#include "LCD.h"

int state;

void initJoystick();
int readJoystick();
int isPrime(long i);
void countPrime(int arg);
static void initClockInterrupt();
void flipClock(int arg);
void checkJoystick(int arg);
void checkClock(int arg);

int main(void){
	
	CLKPR = 0x80;
	CLKPR = 0x0;
	
	state = 0;
	
	initLCD();
	initJoystick();
	initClockInterrupt();
	
	spawn(flipClock, 0);
	yield();
	
    countPrime(0);
}


void checkJoystick(int arg){
	initJoystick();
	int counter = 0;
	int state = !readJoystick();
	
	while(1){
		if(state != readJoystick()){
			
			if(!state){
				// lock(&ppMutex);
				printAt(counter++, 4);
				// unlock(&ppMutex);
			}
			
			state = !state;
			
		}
	}
	
}

void countPrime(int arg){
	int currentPrime = 2;
	while(1){
		if(isPrime(currentPrime)){
			// lock(&ppMutex);
			printAt(currentPrime,0);
			// unlock(&ppMutex);
			
		}
		currentPrime++;
	}
	
	
}

static void initClockInterrupt(){
	
	// Sets OC1A/PCINT13 to compare and interrupt
	PORTB |= (1 << PB7) | (1 << PB5);
	
	// Clock stuff
	// Set OC1A/OC1B on Compare Match (Set output to high level)
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);

	// Sets the timer to CTC mode
	TCCR1B |= (1 << WGM12);

	// Sets the clock select to internal clock with a prescale of 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);

	//
	TIMSK1 |= (1 << OCIE1A);

	// Sets the compare register
	OCR1A = DELAY;

	// Clears the timer
	TCNT1 = 0;
	
}

void flipClock(int arg){
	
	while(1){
		lock(flashMutex);
		
		writeChar('H', 0);
		while(1);
		
		LCDWritePackage(2, state ? 0b0100 : 0x00, 0x00, 0x00, 0x00);
		state = !state;
	}
}

// Sets the joystick i/o pins to input_pullup and sets a start state that will
// activate the button the first cycle
void initJoystick() {

	DDRB = DDRB & ~(1 << 7);
	PORTB = PORTB | (1 << 7);
	//state = !readJoystick();
}

// Reads the joystick
int readJoystick() {
	return (PINB & (1 << 7)) ? 1 : 0;

}



// Checks wheter a number is a prime number by brute force
int isPrime(long i) {

	for (int j = 2; j < i; j++) {

		if (!(i % j)) {

			return 0;

		}

	}

	return 1;

}


void printAt(int num, int pos) {
	int pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}

