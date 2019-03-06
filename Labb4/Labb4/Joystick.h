/*
 * Joystick.h
 *
 * Created: 05-Mar-19 16:48:55
 *  Author: josef
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

void initJoustick() {


	//upp = b6, down = b7, center = b4, left = e2, right = e3
	
	 DDRB = DDRB & ~((1 << 7) | (1 << 6) |(1 << 4));
	 DDRE = DDRE & ~( ( 1 << 2) | (1 << 3));
	 PORTB = PORTB | ((1 << 7)| (1 << 6 ) | (1 << 4));
	 PORTE = PORTE | ( (1 << 2) | ( 1 << 3));



// 0 = Center Upp, 1 = Upp, 2 = Down, 3 = Left, 4 = Right, 5 = Center Down 
int readJoystick()  {
		

	//Right
	if(PINE & (1 << 3)){
		return 4
	}

	//Left
	if(PINE & (1 << 2)){
		return 3
	}

	//Center Down
	if(PINB & ( 1 << 4)){
		return 5
	}
	
	//Upp
	if(PINB & ( 1 << 6)){
		return 1
	}

	//Down
	if(PINB & ( 1 << 7 )){
		return 2
	}
	//Center upp
	return 0

}

#endif /* JOYSTICK_H_ */
