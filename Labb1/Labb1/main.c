			/*
 * Labb1.c
 *
 * Created: 28-Jan-19 15:12:34
 * Author : Josef Utbult, Samuel Gratäng
 */ 

#define BLINKBIT 3
#define STARTPRIME 2

#include <avr/io.h>
#include <stdint-gcc.h>
#include "LCD.h"
#include "Clock.h"

long currentPrime;
int state;

void initJoystick();
int readJoystick();
void joystickSimple();
void joystickConcurrent();

void blinkSimple();
void blinkConcurrent();
void primesSimple();
void primesConcurrent();
int isPrime(long i);


int main(void){

	// Inits some stuff
	initJoystick();
	initLCD();
	initClock();
	
	currentPrime = STARTPRIME;
	

	//primesSimple();
	//blinkSimple();
	//joystickSimple();

	while(1){
		
		blinkConcurrent();
		primesConcurrent();
		joystickConcurrent();
	}
}

// Sets the joystick i/o pins to input_pullup and sets a start state that will 
// activate the button the first cycle
void initJoystick(){
	
	DDRB = DDRB & ~(1 << 7);
	PORTB = PORTB | (1 << 7);
	state = !readJoystick();
}

// Reads the joystick
int readJoystick(){
	return (PINB & ( 1 << 7)) ? 1 : 0;
		
}

// Runs an infinity loop and writes the toggeling of the joystick to the screen
void joystickSimple(){

	state = !readJoystick();
	while(1){
	
		// Checks if the state of the joystick has changed since the last cycle
		if(readJoystick() != state){
			
			// Flips the register if the state went from false to true
			state = !state;
			if(state){
				LCDDR3 = !LCDDR3;
			}
		
		}
	
	}

}

// Does the same as joystickSimple, but dosn't require an infinity-loop
void joystickConcurrent(){

	if(readJoystick() != state){
		
		state = !state;
		if(state){
			LCDDR3 = !LCDDR3;
		}
		
	}

}

// Waits for the clock to hit the threashold and flips the register
void blinkSimple(){

	while(1){	
		while(!clockCycle()){
		
		}
	
		LCDDR18 = !LCDDR18;
	}	
	
}


// Checks if the clock has hit the threashold and flips it if so
void blinkConcurrent(){
	
	if(clockCycle()){
		LCDDR18 = !LCDDR18;
	}
	
}

// Increments a variable, checks wheter it is a prime number and writes it to the screen if so
void primesSimple(){

	long i = STARTPRIME;
	do{
		
		if(isPrime(i)){
			//clear();
			writeLong(i);
						
		
		}

	} while(++i);

}

// Same as primesSimple, but only generates one prime at the time
void primesConcurrent(){
	
	while(1){
		if(isPrime(currentPrime)){
			writeLong(currentPrime++);
			return;
		}
		currentPrime++;
	}
	
}

// Checks wheter a number is a prime number by brute force
int isPrime(long i){

	for(int j = 2; j < i; j++ ){
	
		if(!(i % j)){
		
			return 0;
		
		}
	
	}

	return 1;

}
