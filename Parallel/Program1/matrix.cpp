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
void printVector(vector< vector<int> > A);
const int MAX_THREADS = 10;


/*
 * Measure the time for the serial portion.
 *  *Variable declaration and thread declaration
 * Then measure running threads.
*/
vector< vector<int> > A;
vector< vector<int> > B;
vector< vector<int> > C; 

int thread_count;
int DIM;
void *multiply(void* rank);
int main(int argc, char* argv[]){
  
  //Error check command line arguments
  if(argc < 3){
   fprintf(stderr, "Usage: ./matrix [# of threads] [matrix dimensions]");
   exit(1);
  }
   float start_seq;
   float end_seq;
   float start_par;
   float end_par;
   start_seq = (float)clock()/CLOCKS_PER_SEC;
   DIM = atoi(argv[2]);
   thread_count = atoi(argv[1]);
  
   //thread declaration
   pthread_t* thread_handles;
   long thread;

   thread_handles =(pthread_t*) malloc(thread_count*sizeof(pthread_t)); // May or may not need this


   if(thread_count > MAX_THREADS){
       thread_count = MAX_THREADS;
   }
  
   
      
   
   //Generate random numbers into matrix A and matrix B
   for(int i =0; i< DIM; i++){
       vector<int> row;
       vector<int> row2;
      for(int j=0; j< DIM; j++){
          row.push_back(2);
          row2.push_back(0);
      }
     A.push_back(row);
     B.push_back(row); 
     C.push_back(row2);
   }
   end_seq = (float) clock()/CLOCKS_PER_SEC;
  // printf("Sequential Time Difference: %f", difftime(end_seq,start_seq));
   
    start_par = (float)clock()/CLOCKS_PER_SEC;
    for(thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, multiply,(void*) thread);
    }

    for(thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }
    end_par=(float) clock()/CLOCKS_PER_SEC;

  
   //Calculate Speedup
   float diff_seq = end_seq - start_seq;
   float diff_par = end_par - start_par;
   float speedup = diff_seq/diff_par;
   float efficiency = speedup/thread_count;

   printf("Difference sequential %f; Difference parallel %f \n", diff_seq, diff_par);
   printf("Speedup of %d threads is %f \n", thread_count, speedup);
   printf("Efficiency is %f \n", efficiency);
   printf("\n");
   printVector(C);
    return 0;
}

void printVector(vector< vector<int> > A){
    for(int i =0; i < DIM;i++){
        printf("-");
    }
    printf("\n");
    for(int k=0; k < DIM; k++){
       for(int j=0; j < DIM; j++){
          printf("| %d | ", A[k][j]);
       }
       printf("\n");
    }
}
void* multiply(void* rank){
    //printf("Thread %ld \n", (long) rank);
    long myrank = (long) rank;
    int first_row, local, last_row;

    local = DIM/thread_count;
    first_row = myrank*local;
    last_row = (myrank+1)*local - 1;
    
    for(int i = first_row; i <= last_row; i++){
        for(int j =0; j < DIM; j++){
           for( int k=0; k < DIM; k++){
            C[i][j] = C[i][k] + A[i][j]*B[j][k];
           } 
        }
    }    
    printf("local %d: first: %d last: %d rank: %ld \n", local, first_row, last_row, myrank);
    return NULL;
}

