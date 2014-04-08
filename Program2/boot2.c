#include "gdt.h"
#include "queue.h"
#include "pcb.h"

void clearScr();
void writeScr(char *string, int row, int col);
void protectedWrite(char *string, int row, int col);
void segLoader(uint32_t code, uint32_t data, uint32_t stack, 
        uint32_t video);
void lgdtLoad(gdt_ptr_t *pgdt);
void protectedClear();
void p1();
void p2();
void p3();
void p4();
void p5();
void p6();
void p7();
void p8();
void p9();
void p10();
int createProcess(uint32_t ds, uint32_t ss, uint32_t topOfStack, uint32_t cs, uint32_t processEntry);
int* allocStack();


/*Global variables*/
int STACK_SIZE = 1024;
gdt_entry_t gdt[5]; //Global descriptor table
gdt_ptr_t prgLgdt; //pointer to  ^
int stacks[10][1024];
int nextStack = 0;

int main()
{
    clearScr();
    writeScr("Initializing OS", 0, 0);
    writeScr("Setting up OS descriptors...", 1, 0);
    
    //Set up the GDT
    initGDTEntry(&gdt[0], 0, 0, 0, 0);                  //NULL
    initGDTEntry(&gdt[1], 0, 640*1024-1, 0x9A, 0x40);   //Code
    initGDTEntry(&gdt[2], 0, 640*1024-1, 0x92, 0x40);   //Data
    initGDTEntry(&gdt[3], 0, 640*1024-1, 0x92, 0x40);   //Stack
    initGDTEntry(&gdt[4], 0xB8000, 80*25*2-1, 0x92, 0x40); //Video

    prgLgdt.lim = sizeof(gdt) - 1;
    prgLgdt.base = (uint32_t)gdt;

    lgdtLoad(/*(gdt_entry_t*)*/ &prgLgdt);
    
    //Load the segment registers
    segLoader(8, 16, 24, 32);

    //write to the screen in protected mode
    protectedWrite("done.", 2, 28);
    int i;
    int j;
    for(i = 3; i < 25; i++)
    {
        for(j = 0; j < 80; j++)
        {
            protectedWrite("*", i, j);
        }
    }
    protectedClear();
    protectedWrite("Running ten processes. . .",0,0);
    
    //initialize queue for use
    queues.head = 0;
    queues.tail = 9;

    int *s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p1);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p2);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p3);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p4);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p5);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p6);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p7);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p8);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p9);

    s = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (s + STACK_SIZE), (uint32_t) 8, (uint32_t) p10);

    go();
    while(1);
}

void clearScr()
{
    int i, j;
    for(i = 0; i < 25; i++)
    {
        for(j = 0; j < 80; j++)
        {
            writeScr(" ", i, j);
        }
    }
}


void protectedClear()
{
    int i, j;
    for(i = 0; i < 25; i++)
    {
        for(j = 0; j < 80; j++)
        {
            protectedWrite(" ", i, j);
        }
    }
}

//Processes
void p1()
{
    int i = 0;
    char msg[] = "Process p01:  ";
    while(1)
    {
        msg[13] =  (i + '0');
        protectedWrite(msg, 5, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p2()
{
    int i = 0;
    char msg[] = "Process p02:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 6, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p3()
{
    int i = 0;
    char msg[] = "Process p03:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 7, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p4()
{
    int i = 0;
    char msg[] = "Process p04:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 8, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p5()
{
    int i = 0;
    char msg[] = "Process p05:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 9, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p6()
{
    int i = 0;
    char msg[] = "Process p06:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 10, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p7()
{
    int i = 0;
    char msg[] = "Process p07:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 11, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p8()
{
    int i = 0;
    char msg[] = "Process p08:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 12, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p9()
{
    int i = 0;
    char msg[] = "Process p09:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 13, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

void p10()
{
    int i = 0;
    char msg[] = "Process p10:  ";
    while(1)
    {
        msg[13] = (i + '0');
        protectedWrite(msg, 14, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

int* allocStack()
{
    nextStack++;
    return stacks[nextStack-1];
}

int createProcess(uint32_t ds, uint32_t ss, uint32_t topOfStack, uint32_t cs, uint32_t processEntry)
{
    uint32_t *st = (uint32_t *)topOfStack;
    st--;
    *st = 0;
    st--;
    *st = cs;
    st--;
    *st = processEntry;
    st--;
    *st = 0;    //ebp
    st--;
    *st = 0;    //esp
    st--;
    *st = 0;    //edi
    st--;
    *st = 0;    //esi
    st--;
    *st = 0;    //edx
    st--;
    *st = 0;    //ecx
    st--;
    *st = 0;    //ebx
    st--;
    *st = 0;    //eax
    st--;
    *st = ds;   //ds
    st--;
    *st = ds;   //es
    st--;
    *st = ds;   //fs
    st--;
    *st = ds;   //gs

    pcb_t *pcb = allocatePCB();
    pcb->ss = ss;
    pcb->esp = (uint32_t)st;
    enqueue(pcb);   //add pointer to queue
}
