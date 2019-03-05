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

static void initButtonInterrupt();
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
	initButtonInterrupt();
	initClockInterrupt();
	
	spawn(flipClock, 0);
	yield();
	spawn(checkJoystick, 0);
	yield();
	
    countPrime(0);
}


void checkJoystick(int arg){
	int counter = 0;
	
	while(1){
		
		printAt(counter++, 4);
		
		lock(getJoystickMutex());
		
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
		lock(getFlashMutex());
		
		LCDWritePackage(2, state ? 0b0100 : 0x00, 0x00, 0x00, 0x00);
		state = !state;
		
	}
}


static void initButtonInterrupt(){

	// Button stuff
	// Makes the downbit input pullup
	DDRB &= ~(1 << 7);
	PORTB |= (1 << 7);

	// Enables external interrupt and sets the interrupt to PCINT15..8
	EIMSK |= (1 << PCIE1);

	// Enables interrupt on PCINT15
	PCMSK1 |= (1 << PCINT15);

	// Sets interrupt control to generate an interruption on a falling edge
	EICRA |= (1 << ISC01);

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

