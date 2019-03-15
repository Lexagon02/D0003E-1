#include "CircularBuffer.h"
#include "LCD.h"

writeBufferToLCD(CircularBuffer* self){
	writeChar('0' + (self->head % 100) / 10, 0);
	writeChar('0' + (self->head % 10), 1);
	
	writeChar('0' + (self->tail % 100) / 10, 2);
	writeChar('0' + (self->tail % 10), 3);
}

void bufferEmpty(CircularBuffer* self, int* output){
	
	*output = ((self->tail + 1) % BUFFERLENGTH == self->head);
	writeBufferToLCD(self);
	
}
	
void bufferFull(CircularBuffer* self, int* output){
	
	*output = (self->head == self->tail);
	writeBufferToLCD(self);
	
}

void bufferPull(CircularBuffer* self, unsigned char* output){
	
	int temp;
	bufferEmpty(self, &temp);
	
	if(temp){
		*output = 0;
		writeBufferToLCD(self);
		return;
	}
	
	writeChar('H', 5);
	
	*output = self->data[self->tail];
	self->tail = (self->tail + 1) % BUFFERLENGTH;
	writeBufferToLCD(self);
	
}
void bufferPush(CircularBuffer* self, unsigned char* output){
	
	int temp;
	bufferFull(self, &temp);
	
	writeBufferToLCD(self);
	
	if(temp) return;
	
	self->data[self->head] = *output;
	self->head = (self->head + 1) % BUFFERLENGTH;
	writeBufferToLCD(self);

	
}