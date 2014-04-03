//boot2.c is the c driver for our first project
//Created 2.3.2014 by Daniel Brown 
//CSC 4100 - Operating Systems for Professor Mike Rogers
#include <stdio.h>
#include "gdt.h"
#include "queue.h"
#include "pcb.h"

//Forward declartions
void clearScr();
void writeScr( char *string, int row, int col);
void kWriteScr(char *string, int row, int col);
void segLoad(uint32_t code, uint32_t data, uint32_t stack, uint32_t video);
void lgdtLoader(gdt_ptr_t *pgdt);
void kClearScr();

//processor funtions for Program 3 submission
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

//Global
gdt_entry_t gdt[5];
gdt_ptr_t gdtPointer;

//Global variables for Program 3 submission
int STACK_SIZE = 1024;
int stacks[10][1024];
int nextStack =0;

int main(){
    //Main function that calls clearScr() and writeScr() functions 
    clearScr(); 
    writeScr("Initialiazing Operating System", 0, 0);//Prints string onto screen after booting up
    writeScr("Setting up Operating System Descriptors....", 1,0);

    initGDTEntry(&gdt[0],0,0,0,0); //Null
    initGDTEntry(&gdt[1], 0, 640*1024-1, 0x9A, 0x40);   //Code
    initGDTEntry(&gdt[2], 0, 640*1024-1, 0x92, 0x40);   //Data
    initGDTEntry(&gdt[3], 0, 640*1024-1, 0x92, 0x40);   //Stack
    initGDTEntry(&gdt[4], 0xB8000, 80*25*2-1, 0x92, 0x40); //Video
	
    gdtPointer.lim = sizeof(gdt) - 1;
    gdtPointer.base = (uint32_t)gdt;

    lgdtLoad((gdt_entry_t*) &gdtPointer);
    
    //Load the segment registers
    segLoader(8, 16, 24, 32);

    //write to the screen in protected mode
    kWriteScr("DONE", 2, 28);
    int i;
    int j;
    int k;

    for(i = 3; i < 25; i++)
    {   
        for( k=0; k < 624000; k++){
        }
        for(j = 0; j < 80; j++)
        {
            kWriteScr("*", i, j);
        }
    }
    kClearScr();
    kWriteScr("Running ten processess..............",0,0);



    //queues
    queues.head = 0;
    queues.tail = 9;

    int *newStack = allocStack();
    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p1);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p2);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p3);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p4);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p5);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p6);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p7);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p8);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p9);

    createProcess((uint32_t) 16, (uint32_t) 24, (uint32_t) (newStack + STACK_SIZE), (uint32_t) 8, (uint32_t) p10);


    go();

    while(1);
   
}


//Protyped Methods
void clearScr()
{
    int i;
    int j;
    for(i = 0; i < 25; i++)
    {
        for(j = 0; j < 80; j++)
        {
            writeScr(" ", i, j);
        }
    }
}

void kClearScr()
{
	int i,j;
	for(i = 0; i <25; i++)
	{
		for(j=0; j<80; j++)
		{
			kwriteScr(" ",i,j);
		}
	}
}

//Process functions
void p1()
{
    int i = 0;
    char msg[] = "Process p01:  ";
    while(1)
    {
        msg[13] =  (i + '0');
        kWritesScr(msg, 5, 0);
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
        kWritesScr(msg, 6, 0);
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
        kWritesScr(msg, 7, 0);
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
        kWritesScr(msg, 8, 0);
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
        kWritesScr(msg, 9, 0);
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
        kWritesScr(msg, 10, 0);
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
        kWritesScr(msg, 11, 0);
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
        kWritesScr(msg, 12, 0);
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
        kWritesScr(msg, 13, 0);
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
        kWritesScr(msg, 14, 0);
        i = (i + 1) % 10;
        schedule();
    }
}

int createProcess(uint32_t ds, uint32_t ss, uint32_t topOfStack, uint32_t cs, uint32_t processEntry)
{
	uint32_t *stack = (uint32_t *) topOfStack;
	stack --;
	
	*stack = 0;
	stack --;

	
	*stack = cs;
	stack --;

	
	*stack = processEntry;
	stack --;
	int i,j;
	for(i = 0; i< 9; i++)
	{	
		*stack = 0;
		stack --;
	}

	for(j= 0; j <3; j++)
	{
		*stack = ds;
		stack --;
	}

	pcb_t *pcb = allocatePCB();
	pcb->ss = ss;
	pcb->esp = (uint32_t)stack;
	enqueue(pcb);
}


