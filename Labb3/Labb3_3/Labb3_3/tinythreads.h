/*
 *
 * tinythreads.h
 *
 */

#ifndef TINYTHREADS_H
#define TINYTHREADS_H

#include <avr/interrupt.h>

// (Freq * ms) / (prescaler * seconds to ms)
// (8000000 * 500 / (1024 * 1000)
#define DELAY 3906
#define DISABLE()       cli()
#define ENABLE()        sei()

struct thread_block;
typedef struct thread_block *thread;
void spawn(void (*code)(int), int arg);
void yield(void);

int state;
int counter;

struct mutex_block {
    int locked;
    thread waitQ;
};
typedef struct mutex_block mutex;

void lock(mutex *m);
void unlock(mutex *m);

void printAt(int num, int pos);
void initButtonInterrupt();
void initClockInterrupt();

#endif

