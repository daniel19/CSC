/**
 *matrix.cpp
 *Pthread application that computes matrix multiplication using
 *  threading applications.
 *@author Daniel Brown
 *@version 1.0 9/16/2014
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <vector>
using namespace std;

#define MAX_THREADS = 10;


/*
 * Measure the time for the serial portion.
 *  *Variable declaration and thread declaration
 * Then measure running threads.
*/
vector< vector<int> > A;
vector< vector<int> > B;
   

int thread_count;
void *multiply(void* rank);
int main(int argc, char* argv[]){
  
  //Error check command line arguments
  if(argc < 3){
   fprintf(stderr, "Usage: ./matrix [# of threads] [matrix dimensions]");
   exit(1);
  }
   time_t start_seq;
   time_t end_seq;
   time_t start_par;
   time_t end_par;
   time(&start_seq);
   const int DIM = atoi(argv[2]);
   thread_count = atoi(argv[1]);
  
   //thread declaration
   pthread_t* thread_handles;
   long thread;

   thread_handles =(pthread_t*) malloc(thread_count*sizeof(pthread_t)); // May or may not need this


/*   if(thread_count > MAX_THREADS){
       thread_count = MAX_THREADS;
   }
  */
   
      
   
   //Generate random numbers into matrix A and matrix B
   for(int i =0; i< DIM; i++){
       vector<int> row;
      for(int j=0; j< DIM; j++){
          row.push_back(3 *i + j);
      }
     A.push_back(row);
     B.push_back(row); 
   }
   time(&end_seq);
  // printf("Sequential Time Difference: %f", difftime(end_seq,start_seq));
   
    time(&start_par);
    for(thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, multiply,(void*) thread);
    }

    for(thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }
    time(&end_par);

   
   return 0;
}


void* multiply(void* rank){
    //printf("Thread %ld \n", (long) rank);
    return NULL;
}

