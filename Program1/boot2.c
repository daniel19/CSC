//boot2.c is the c driver for our first project
//Created 2.3.2014 by Daniel Brown 
//CSC 4100 - Operating Systems for Professor Mike Rogers
#include <stdio.h>
//#include "boot2.S"
//Directives for external data and functions

//Forward declartions
void clearScr();
void writeScr( char *string, int row, int col);

int main(){
    //Main function that calls clearScr() and writeScr() functions 
    clearScr();
    char string[12]="Hello World"; 
    writeScr(string, 12, 25);//Prints string onto screen after booting up
    //while(1);
    return 0;
}

void clearScr(){
    //Calling writing screen to clear the screen
    int i=0;
    for(i; i<25; i++){
        writeScr("            ",i,0);
    }
}
/*
void writeScr(char *string, int row, int col){
    //calcualte offset into video memory
}
*/
