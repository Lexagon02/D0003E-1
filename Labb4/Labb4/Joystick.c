#include "Joystick.h"
#include <avr/io.h>

void initJoystick() {


	//upp = b6, down = b7, center = b4, left = e2, right = e3
	
	DDRB = DDRB & ~((1 << 7) | (1 << 6) |(1 << 4));
	DDRE = DDRE & ~( ( 1 << 2) | (1 << 3));
	PORTB = PORTB | ((1 << 7)| (1 << 6 ) | (1 << 4));
	PORTE = PORTE | ( (1 << 2) | ( 1 << 3));
	
	
	// Enables external interrupt and sets the interrupt to PCINT15..8
	EIMSK |= (1 << PCIE1) | (1 << PCIE0);
	
	// Enables interrupt on PCINT15
	PCMSK1 |= (1 << PCINT15)|(1 << PCINT14)|(1 << PCINT12);
	PCMSK0 |= (1 << PCINT3)|(1 << PCINT2);
	
	// Sets interrupt control to generate an interruption on a falling edge
	EICRA |= (1 << ISC01);
	
}



// 0 = Center Upp, 1 = Upp, 2 = Down, 3 = Left, 4 = Right, 5 = Center Down
int readJoystick()  {

	//Right
	if(~PINE & (1 << 3)){
		return 4;
	}

	//Left
	if(~PINE & (1 << 2)){
		return 3;
	}

	//Center Down
	if(~PINB & ( 1 << 4)){
		return 5;
	}
		
	//Upp
	if(~PINB & ( 1 << 6)){
		return 1;
	}

	//Down
	if(~PINB & ( 1 << 7 )){
		return 2;
	}
	//Center
	return 0;

}