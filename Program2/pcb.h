#ifndef PCB_H
#define PCB_H

struct pcb
{
    uint32_t esp;
    uint32_t ss;
};
typedef struct pcb pcb_t;

pcb_t *currPCB;
int pcb_next = 0;

#endif
