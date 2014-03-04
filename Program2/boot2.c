//boot2.c is the c driver for our first project
//Created 2.3.2014 by Daniel Brown 
//CSC 4100 - Operating Systems for Professor Mike Rogers
#include <stdio.h>
#include "gdt.h"
//Directives for external data and functions

//Forward declartions
void clearScr();
void writeScr( char *string, int row, int col);
void kWriteScr(char *string, int row, int col);
void segLoad(uint32_t code, uint32_t data, uint32_t stack, uint32_t video);
void lgdtLoader(gdt_ptr_t *pgdt);

//Global
gdt_entry_t gdt[5];
gdt_ptr_t gdtPointer;

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

    while(1);
   
}

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

