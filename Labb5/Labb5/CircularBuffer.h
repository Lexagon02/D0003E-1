#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#define BUFFERLENGTH 100
#define INIT_CIRCULAR_BUFFER {{}, 1, 0}

typedef struct {
	unsigned char data[BUFFERLENGTH];
	int head;
	int tail;
} CircularBuffer;

void bufferEmpty(CircularBuffer* self, int* output);
void bufferFull(CircularBuffer* self, int* output);

void bufferPull(CircularBuffer* self, unsigned char* output);
void bufferPush(CircularBuffer* self, unsigned char* output);

#endif /* CIRCULARBUFFER_H_ */