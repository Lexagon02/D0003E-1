#include <avr/io.h>
#include "tinythreads.h"
#include "LCD.h"

#define CYCLE 20

// mutex ppMutex = MUTEX_INIT;
// int pp;

void initJoystick();

int readJoystick();

int isPrime(long i);

void countPrime(int arg);

void checkJoystick();

void checkClock(int arg);

int main(void)
{
	CLKPR = 0x80;
	CLKPR = 0x0;
		
	initLCD();
	
	spawn(countPrime, 0);
	spawn(checkClock, 0);
	checkJoystick();
}

void checkJoystick(){
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

void checkClock(int arg){
	
	int state = 0;
	
	while(1){
		if(interruptCounter >= CYCLE){
			interruptCounter = 0;
			
			LCDWritePackage(2, state ? 0b0100 : 0x00, 0x00, 0x00, 0x00);
			state = !state;
		}
		yield();
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