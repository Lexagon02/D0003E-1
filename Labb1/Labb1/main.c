			/*
 * Labb1.c
 *
 * Created: 28-Jan-19 15:12:34
 * Author : Josef Utbult, Samuel Gratäng
 */ 

#define CYCLE 18519
#define BLINKBIT 3
#define STARTPRIME 2

#include <avr/io.h>
#include <stdint-gcc.h>

long currentPrime;
int state;

void initJoystick();
int readJoystick();
void joystickSimple();
void joystickConcurrent();

void initLCD();
void LCDWritePackage();
void writeLong(long i);
void writeChar(char ch, int pos);
void clear();


void blinkSimple();
void blinkSimpleConcurrent();
void primesSimple();
void primesConcurrent();
int isPrime(long i);
void initClock();
int clockCycle();


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
		
		blinkSimpleConcurrent();
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
void blinkSimpleConcurrent(){
	
	if(clockCycle()){
		LCDDR18 = !LCDDR18;
	}
	
}

void initClock(){
	
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


// Hacks up a long and writes them as chars to the screen

void writeLong(long i){

	int pos = 5;

	while(i > 0){
	
		writeChar((i % 10) + '0', pos-- );
		i = i / 10;
	}

}

// Writes a char to the screen on a given possition

void writeChar(char ch, int pos){
	
	if (pos >= 0 && pos <= 5){
	
			switch (ch){
				
				case '0':
				
				LCDWritePackage(pos, 0b1001, 0b0101, 0b0101, 0b0101);
				
				break;
				
				case '1':
				
				LCDWritePackage(pos, 0b0000, 0b0001, 0b0001, 0b0000);
				
				break;
				
				case '2':
				
				LCDWritePackage(pos, 0b0001, 0b0001, 0b1000, 0b0101);
				
				break;
				
				case '3':
				
				LCDWritePackage(pos, 0b0001, 0b0001, 0b1011, 0b0001);
				
				break;
				
				case '4':
				
				LCDWritePackage(pos, 0b0000, 0b0101, 0b1011, 0b0000);
				
				break;
				
				case '5':
				
				LCDWritePackage(pos, 0b0001, 0b0100, 0b1011, 0b0001);
				
				break;
				
				case '6':
				
				LCDWritePackage(pos, 0b0001, 0b0100, 0b1111, 0b0001);
				
				break;
				
				case '7':
				
				LCDWritePackage(pos, 0b1001, 0b0000, 0b0000, 0b0100);
				
				break;
				
				case '8':
				
				LCDWritePackage(pos, 0b0001, 0b0101, 0b1111, 0b0001);
				
				break;
				
				case '9':
				
				LCDWritePackage(pos, 0b0001, 0b0101, 0b1011, 0b0001);
				
				break;
				
				
				default:
				
				LCDWritePackage(pos, 0b0001, 0b0001, 0b1000, 0b0010);	//Questionmark
				
				break;
			}
	
	}
	
}

// Takes 4 nibbles and masks them in on there corresponding possitions registers

void LCDWritePackage(int offcet, uint16_t pos0, uint16_t pos1, uint16_t pos2, uint16_t pos3){

	if(offcet < 0){
		
		return;
		
	}
	// Digit 0 and 1 on the display
	else if(offcet < 2){
		
		// Shifts the nibbles up to the second part of the byte if the position is the
		// second one in the digit-pair
		
		LCDDR0  = (LCDDR0  & (offcet == 1 ? 0x0F : 0xF0)) | ((uint32_t)pos0 << (offcet == 1 ? 4 : 0));
		LCDDR5  = (LCDDR5  & (offcet == 1 ? 0x0F : 0xF0)) | ((uint32_t)pos1 << (offcet == 1 ? 4 : 0));
		LCDDR10 = (LCDDR10 & (offcet == 1 ? 0x0F : 0xF0)) | ((uint32_t)pos2 << (offcet == 1 ? 4 : 0));
		LCDDR15 = (LCDDR15 & (offcet == 1 ? 0x0F : 0xF0)) | ((uint32_t)pos3 << (offcet == 1 ? 4 : 0));

	}
	
	// Digit 2 and 3 on the display
	else if(offcet < 4){
		
		LCDDR1  = (LCDDR1  & (offcet == 3 ? 0x0F : 0xF0)) | ((uint32_t)pos0 << (offcet == 3 ? 4 : 0));
		LCDDR6  = (LCDDR6  & (offcet == 3 ? 0x0F : 0xF0)) | ((uint32_t)pos1 << (offcet == 3 ? 4 : 0));
		LCDDR11 = (LCDDR11 & (offcet == 3 ? 0x0F : 0xF0)) | ((uint32_t)pos2 << (offcet == 3 ? 4 : 0));
		LCDDR16 = (LCDDR16 & (offcet == 3 ? 0x0F : 0xF0)) | ((uint32_t)pos3 << (offcet == 3 ? 4 : 0));

	}
	
	// Digit 4 and 5 on the display
	else if(offcet < 6){
		
		LCDDR2  = (LCDDR2  & (offcet == 5 ? 0x0F : 0xF0)) | ((uint32_t)pos0 << (offcet == 5 ? 4 : 0));
		LCDDR7  = (LCDDR7  & (offcet == 5 ? 0x0F : 0xF0)) | ((uint32_t)pos1 << (offcet == 5 ? 4 : 0));
		LCDDR12 = (LCDDR12 & (offcet == 5 ? 0x0F : 0xF0)) | ((uint32_t)pos2 << (offcet == 5 ? 4 : 0));
		LCDDR17 = (LCDDR17 & (offcet == 5 ? 0x0F : 0xF0)) | ((uint32_t)pos3 << (offcet == 5 ? 4 : 0));

	}
	
	// The Different symbols on the screen that is not included in the digits bytes
	
	else if(offcet < 8){
		
		LCDDR3  = (LCDDR3  & (offcet == 7 ? 0x0F : 0xF0)) | ((uint32_t)pos0 << (offcet == 7 ? 4 : 0));
		LCDDR7  = (LCDDR7  & (offcet == 7 ? 0x0F : 0xF0)) | ((uint32_t)pos1 << (offcet == 7 ? 4 : 0));
		LCDDR13 = (LCDDR13 & (offcet == 7 ? 0x0F : 0xF0)) | ((uint32_t)pos2 << (offcet == 7 ? 4 : 0));
		LCDDR18 = (LCDDR18 & (offcet == 7 ? 0x0F : 0xF0)) | ((uint32_t)pos3 << (offcet == 7 ? 4 : 0));

	}

	
}

// Clears the screen

void clear(){
	
	LCDDR0 = 0x00;
	LCDDR1 = 0x00;
	LCDDR2 = 0x00;
	LCDDR3 = 0x00;

	LCDDR5 = 0x00;
	LCDDR6 = 0x00;
	LCDDR7 = 0x00;
	LCDDR8 = 0x00;

	LCDDR10 = 0x00;
	LCDDR11 = 0x00;
	LCDDR12 = 0x00;
	LCDDR13 = 0x00;
	
	LCDDR15 = 0x00;
	LCDDR16 = 0x00;
	LCDDR17 = 0x00;
	LCDDR18 = 0x00;
	
}

// Inits the LCD by using some magic

void initLCD(){
	
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
	LCDFRR = (0<<LCDPS2) | (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
	LCDCCR = (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);
	LCDCRA = (1<<LCDEN);
	
}
