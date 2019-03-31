#include "Serial.h"
#include <avr/io.h>

#define FOSC 8000000 // Clock speed
#define BAUD 9600
#define MYUBER FOSC/16/BAUD-1

unsigned int uber = MYUBER;

void pullFromSerial(Serial* self);
void pushToSerial(Serial* self);

void initSerial(Serial* self, Object* onReadObject, void (*onReadFunction)(unsigned char)){
	
	initLCD();
	self->onReadObject = onReadObject;
	self->onReadFunction = onReadFunction;
	
	// Sets baud rate
	UBRR0H = (unsigned char)(uber >> 8);
	UBRR0L = (unsigned char)(uber);
	
	// Enable receive and transmit, and enable and transmit interrupts
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
	
	// Set frame format: 8data, 1stop bit
	UCSR0C = (3 << UCSZ00) & ~(1 << USBS0);
	
	//INSTALL(self, &pullFromSerial, IRQ_USART0_RX);
	SEND(MSEC(100), MSEC(110), self, &pushToSerial, NULL);
		
}

void pushToSerial(Serial* self){
	
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = self->output;
		
	//writeChar('0' + (self->output % 10), 5);
	ASYNC(self, &pullFromSerial, NULL);

}

void pullFromSerial(Serial* self){
	
	LCDDR0 ^= (1 << 1);
	
	while(!(UCSR0A & (1<<RXC0)));
	
	self->input = UDR0;
	
	//if(self->input) writeChar('0' + self->input, 5);
	
	SYNC(self->onReadObject, self->onReadFunction, self->input);	
			
}

void send(Serial* self, unsigned char output){
	
	self->output = output;
	SEND(MSEC(100), MSEC(110), self, &pushToSerial, NULL);
	
}

void serialAvailable(Serial* self, int* available){
	
	*available = (UCSR0A & (1<<RXC0));
	
}