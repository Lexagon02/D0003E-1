/*
 * Labb3_2.c
 *
 * Created: 23-Feb-19 17:41:16
 * Author : josef
 */ 

#include <avr/io.h>
#include "tinythreads.h"
#include "LCD.h"

int readJoystick();
int isPrime(long i);
void countPrime(int arg);
void checkClock(int arg);

int main(void){
	
	CLKPR = 0x80;
	CLKPR = 0x0;
	
	initLCD();
	initButtonInterrupt();
	initClockInterrupt();
	
	ENABLE();
    countPrime(0);
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

// Checks wheter a number is a prime number by brute force
int isPrime(long i) {

	for (int j = 2; j < i; j++) {

		if (!(i % j)) {

			return 0;

		}

	}

	return 1;

}

