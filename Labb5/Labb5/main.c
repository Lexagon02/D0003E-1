#include <avr/io.h>
#include "TinyTimber.h"
#include "MainClass.h"
#include "Serial.h"
#include "LCD.h"

#define F_CPU 8000000
#include <util/delay.h>

int main(void){
	
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	initLCD();
	
	Serial serial = INIT_SERIAL;
	initSerial(&serial);
	
    while (1) {
		
		send(&serial, 'H');
		send(&serial, 'E');
		send(&serial, 'L');
		send(&serial, 'L');
		send(&serial, 'O');
		send(&serial, 'W');
		send(&serial, 'O');
		send(&serial, 'R');
		send(&serial, 'L');
		send(&serial, 'D');
		
		for(int i = 0; i < 10; i++ ){
			writeToSerial(&serial);
		}
		
		_delay_ms(1000);
    }
}

