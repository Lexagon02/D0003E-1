#include <avr/io.h>
#include "TinyTimber.h"
#include "MainClass.h"
#include "Serial.h"

#define F_CPU 8000000
#include <util/delay.h>

int main(void){
	
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	Serial serial = INIT_SERIAL;
	
	initSerial(&serial);
	
    while (1) {
		send(&serial, 'H');
		_delay_ms(1000);
    }
}

