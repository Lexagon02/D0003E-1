#include <setjmp.h>
#include <avr/io.h>
#include "tinythreads.h"
#include "LCD.h"

#ifndef PORTB
#include "src/iom169.h"
#endif

#define DOWNBIT         7
#define NULL            0
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

int initialized = 0;

void flipClock(int arg){
	
	LCDWritePackage(2, state ? 0b0100 : 0x00, 0x00, 0x00, 0x00);
	state = !state;

}

ISR(TIMER1_COMPA_vect){
	
	DISABLE();
	spawn(flipClock, 0);
	yield();
	ENABLE();
		
}

void checkJoystick(int arg){
	DISABLE();
	if(!(PINB & (1 << 7))){
		
		printAt(counter++, 4);
		
	}
	ENABLE();
}

ISR(PCINT1_vect){
	
	spawn(checkJoystick, 0);
	yield();
}

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

    initialized = 1;
}

static void enqueue(thread p, thread *queue) {
    p->next = *queue;
	*queue = p;
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

	thread temp = dequeue(&readyQ);
	enqueue(current, &readyQ);
	dispatch(temp);

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

void printAt(int num, int pos) {
	int pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}


void initClockInterrupt(){
	
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
	
	state = 0;
	
	
	
}


void initButtonInterrupt(){

	// Button stuff
	// Makes the downbit input pullup
	DDRB &= ~(1 << 7);
	PORTB |= (1 << 7);

	// Enables external interrupt and sets the interrupt to PCINT15..8
	EIMSK |= (1 << PCIE1);

	// Enables interrupt on PCINT15
	PCMSK1 |= (1 << PCINT15);

	// Sets interrupt control to generate an interruption on a falling edge
	EICRA |= (1 << ISC01);
	
	counter = 1;

}	