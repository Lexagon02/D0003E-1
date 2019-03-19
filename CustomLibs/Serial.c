#include "Serial.h"
#include <avr/io.h>

#define FOSC 8000000 // Clock speed
#define BAUD 9600
#define MYUBER FOSC/16/BAUD-1

unsigned int uber = MYUBER;

void read(Serial* self);

void initSerial(Serial* self, Object* onReadObject, void (*onReadFunction)(unsigned char)){
	
	self->onReadObject = onReadObject;
	self->onReadFunction = onReadFunction;
	
	// Sets baud rate
	UBRR0H = (unsigned char)(uber >> 8);
	UBRR0L = (unsigned char)(uber);
	
	
	
	// Enable receive and transmit, and enable and transmit interrupts
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
	
	// Set frame format: 8data, 1stop bit
	UCSR0C = (3 << UCSZ00) & ~(1 << USBS0);
	
	INSTALL(self, &read, IRQ_USART0_RX);
	writeChar('J', 0);
}

void send(Serial* self, unsigned char input){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = input;
	
}

void read(Serial* self){
	
	while(!(UCSR0A & (1<<RXC0)));
	
	unsigned char temp = UDR0;
	
	if(temp == 10) return;
	
	ASYNC(self->onReadObject, self->onReadFunction, temp);

}

void serialAvailable(Serial* self, int* available){
	
	*available = (UCSR0A & (1<<RXC0));
	
}
