#define F_CPU 10000000

#define JOYUP 6
#define JOYDOWN 7

#include <avr/io.h>
#include <util/delay.h>

#include "LCD.h"

int read();
void writeInt8(uint8_t val);

int main(void)
{
	
	initLCD();
	
	DDRB = 0x0;
	PORTB = 0x0 | (1 << JOYDOWN) | (1 <<  JOYUP);
	
	uint8_t ch = 'A';
	int state = 1;
	while(1){
		
		writeChar(ch, 0);
		writeInt8(ch);
		
		
		while(read(JOYUP) && read(JOYDOWN)){
			
			if(!read(JOYUP) && state){
				state = 0;
				ch -= 1;
			}
			else if(state){
				state = 0;
				ch += 1;
			}
		}
		while(!(read(JOYUP) && read(JOYDOWN))){
			clear();
		}
		state = 1;
		
		
	}
}

int read(int bit){
	
	return PINB & (1 << bit) ? 1 : 0;
}

void writeInt8(uint8_t val){
	
	for(int i = 0; i < 3; i++ ){
		
		writeChar('0' + val % 10, 5 - i);
		val /= 10;
		
	}
	
}