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
#include <random>
#include <version>
using namespace std;

/*
 * Measure the time for the serial portion.
 *  *Variable declaration and thread declaration
 * Then measure running threads.
*/
int main(int argc, char* argv[]){
  
  //Error check command line arguments
  if(argc < 3){
   fprintf(stderr, "Usage: ./matrix [# of threads] [matrix dimensions]");
   exit(1);
  }
   time_t start_seq;
   time_t end_seq;
   //time(&start_seq);
   default_random_engine generator;
   geometric_distribution <int> distribution(0.3);

   const int DIM = atoi(argv[2]);
   vector< vector<int> > A;
   vector< vector<int> > B;
   //Generate random numbers into matrix A and matrix B
   for(int i =0; i< DIM; i++){
       vector<int> row;
      for(int j=0; j< DIM; j++){
      //  A[i][j] = rand() % 100;
      //  B[i][j] = rand() % 100;
          row.push_back(distribution(generator));
      }
     A.push_back(row);
     B.push_back(row); 
   }
  // time(&end_seq);
  // printf("Sequential Time Difference: %f", difftime(end_seq,start_seq));
    
   printf("Value A: %d \n Value B: %d \n", A[DIM][0], B[DIM][0]);
   
   return 0;
}
