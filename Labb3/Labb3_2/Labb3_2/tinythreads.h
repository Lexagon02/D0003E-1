/*
 *
 * tinythreads.h
 *
 */

#ifndef TINYTHREADS_H
#define TINYTHREADS_H

// (Freq * ms) / (prescaler * seconds to ms)
// (8000000 * 500 / (1024 * 1000)
#define DELAY 3906

struct thread_block;
typedef struct thread_block *thread;
void spawn(void (*code)(int), int arg);
void yield(void);

struct mutex_block {
    int locked;
    thread waitQ;
};
typedef struct mutex_block mutex;

 
mutex *flashMutex;

void lock(mutex *m);
void unlock(mutex *m);

#endif

