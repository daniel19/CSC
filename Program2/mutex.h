#ifndef MUTEX_H
#define MUTEX_H

#include "queue.h"
#define true    1
#define false   0
typedef uint32_t bool;
void unlock(uint32_t *);

struct mutex
{
    bool locked;        //keep track if mutex is locked
    uint32_t bolt;      //mutual exclusion
    queue_t waitQueue;  //process queue
} __attribute__((packed));

typedef struct mutex mutex_t;

mutex_t m;

void mutex_init(mutex_t *m)
{
    m->waitQueue.head = 0;
    m->waitQueue.tail = 0;
    m->locked = false;
    m->bolt = 0;
}

void mutex_lock(mutex_t *m)
{
    //turn off interrupts
    //asm("cli");

    if(m->locked == 1)
    {
        mutexSchedule(m);
    }
    else
    {
        m->locked = true;
        unlock(&(m->bolt));
     }

    //turn on interrupts
    //asm("sti");
}

void mutex_unlock(mutex_t *m)
{
    // turn off interrupts
    //asm("cli");

    if(m->waitQueue.head == m->waitQueue.tail)
    {
        m->locked = false;
    }
    else
    {
        pcb_t* temp = genDequeue(&(m->waitQueue));
        genEnqueue(&queues, temp);
    }
    unlock(&(m->bolt));

    //turn on interrupts
    //asm("sti");
}

#endif
