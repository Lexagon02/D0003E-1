#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "tinythreads.h"

#ifndef PORTB
#include "src/iom169.h"
#endif

#ifndef F_CPU
#define F_CPU 8000000
#endif

// (Freq * ms) / (prescaler * seconds to ms)
// (8000000 * 50 / (1024 * 1000)
#define DELAY 391

#define DOWNBIT         7
#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4

struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int interruptCounter;

static void initClockInterrupt(){
	
	// Sets OC1A/PCINT13 to compare and interrupt
	PORTB |= (1 << PB7) | (1 << PB5);
	
	// Clock stuff
	// Set OC1A/OC1B on Compare Match (Set output to high level)
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);

	// Sets the timer to CTC mode
	TCCR1B |= (1 << WGM12);

	// Sets the clock select to internal clock with a prescale of 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);

	//
	TIMSK1 |= (1 << OCIE1A);

	// Sets the compare register
	OCR1A = DELAY;

	// Clears the timer
	TCNT1 = 0;
	
}


int initialized = 0;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

	interruptCounter = 0;
	
	initClockInterrupt();
	
    initialized = 1;
}

ISR(TIMER1_COMPA_vect){
	
	interruptCounter++;
	
    yield();
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
		writeChar('E', 2);
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
    ENABLE();
}

void yield(void) {

	DISABLE();
	enqueue(current, &readyQ);
	dispatch(dequeue(&readyQ));
	ENABLE();
}

void lock(mutex *m) {

	DISABLE();
	if(!m->locked){
		m->locked = 1;
	}
	else{
		enqueue(current, &(m->waitQ));
		dispatch(dequeue(&readyQ));
	}
	ENABLE();

}

void unlock(mutex *m) {

	DISABLE();
	if(m->waitQ){
		enqueue(current, &readyQ);
		dispatch(dequeue(&(m->waitQ)));
	}
	else{
		m->locked = 0;
	}
	ENABLE();
	

}


int getCounter(){
	return interruptCounter;
}

void setCounter(int val){
	interruptCounter = val;
}