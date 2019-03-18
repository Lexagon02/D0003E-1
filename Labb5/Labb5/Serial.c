#include "Serial.h"
#include <avr/io.h>

#define FOSC 8000000 // Clock speed
#define BAUD 9600
#define MYUBER FOSC/16/BAUD-1

unsigned int uber = MYUBER;

void pullSerialData(Serial* self);
void pushSerialData(Serial* self);

void initSerial(Serial* self){
	
	// Sets baud rate
	UBRR0H = (unsigned char)(uber >> 8);
	UBRR0L = (unsigned char)(uber);
	
	// Enable receive and transmit
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	// Set frame format: 8data, 1stop bit
	UCSR0C = (3 << UCSZ00) & ~(1 << USBS0);

}


void send(Serial* self, unsigned char input){

	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = input;
	
}

void read(Serial* self, unsigned char* output){
	
	while(!(UCSR0A & (1<<UDRE0)));
	*output = UDR0;
	
}

void serialAvailable(Serial* self, int* available){
	
	*available = (UCSR0A & (1<<UDRE0));
	
}
