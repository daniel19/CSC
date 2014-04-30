#ifndef QUEUE
#define QUEUE

#include "pcb.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#define QUEUE_SIZE 10

struct queue
{
    uint32_t head;
    uint32_t tail;
    pcb_t pcbs[QUEUE_SIZE];
};

typedef struct queue queue_t;

queue_t queues;

pcb_t* allocatePCB(void)
{
    pcb_next++;
    return &(queues.pcbs[pcb_next-1]);
}

void enqueue(pcb_t *currPCB)
{
    queues.tail = (queues.tail+1) % QUEUE_SIZE;
    queues.pcbs[queues.tail] = *currPCB;
}

pcb_t* dequeue(void)
{
    int temp = queues.head;
    queues.head = (queues.head+1) % QUEUE_SIZE;
    return &(queues.pcbs[temp]);
}

pcb_t* genDequeue(queue_t *q)
{
    int temp = q->head;
    q->head = (q->head+1) % QUEUE_SIZE;
    return &(q->pcbs[temp]);
}

void genEnqueue(queue_t* q, pcb_t* currPCB)
{
    int temp = q->tail;
    q->tail = (q->tail+1) % QUEUE_SIZE;
    q->pcbs[temp] = *currPCB;
}
#endif
