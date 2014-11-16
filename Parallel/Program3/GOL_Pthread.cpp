#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "pthread_barrier.h"
using namespace std;

//Global variables
const int GEN = 100;
int** currentGen;
int** nextGen;
int thread_count;
int DIM;
pthread_barrier_t barrier;

//Forward Declaration
void createGeneration(int dimensions);
void duplicateGeneration();
void copyGeneration();
void printArray(int** a);
int rule(int numberOfLiveNeighbors, int cellState, int row, int column);
void update();
void* parallel_update(void* rank);
int neighbors(int row, int column); 

int main(int argc, char* argv[]){
    if(argc < 3){
      fprintf(stderr, "Usage: ./matrix [# of threads] [matrix dimensions]");
      exit(1);
     }

    thread_count = atoi(argv[1]);
    pthread_barrier_init(&barrier, NULL, thread_count);
    
    float start_seq;
    float end_seq;
    float start_par;
    float end_par;
    start_seq = (float)clock()/CLOCKS_PER_SEC;
    createGeneration(atoi(argv[2]));
    //printArray(currentGen);
    printf("\n");
    //Make copy of initial generation 
    duplicateGeneration();
    //run sequentially Conway's rules for the Game of Life
    
    pthread_t* thread_handles;
    long thread;
    thread_handles = (pthread_t*) malloc(thread_count*sizeof(pthread_t));
    end_seq = (float) clock()/CLOCKS_PER_SEC;
    
    start_par = (float)clock()/CLOCKS_PER_SEC;
    for(thread=0; thread <thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, parallel_update, (void*) thread);
    }

    for(thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }
    end_par=(float) clock()/CLOCKS_PER_SEC;

 
    float diff_seq = end_seq - start_seq;
    float diff_par = end_par - start_par;
    float speedup = diff_seq/diff_par;
    float efficiency = speedup/thread_count;

    printf("Difference sequential %f; Difference parallel %f \n", diff_seq, diff_par);
    printf("Speedup of %d threads is %f \n", thread_count, speedup);
    printf("Efficiency is %f \n", efficiency);
    printf("\n");
    printArray(nextGen);
    for(int i=0; i < DIM; i++){
        delete[] currentGen[i];
        delete[] nextGen[i];
    }
    delete[] currentGen;
    delete[] nextGen;
    return 0;
}

void* parallel_update(void* rank){
    long myrank = (long) rank;
    int first_row, local, last_row;

    local = DIM/thread_count;
    first_row = myrank*local;
    last_row = (myrank+1)*local - 1;
   for(int iter=0; iter < GEN; iter++){
        for(int i= first_row; i < last_row; i++){
            for(int j=0; j < DIM; j++){
               nextGen[i][j] = rule(neighbors(i,j), currentGen[i][j], i,j);
            }
        }
        //Add barrier wait for sync
        pthread_barrier_wait(&barrier);
        if(myrank == 0){
            copyGeneration();
        }
   } 
    return NULL;
}
void update(){
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            nextGen[i][j] = rule(neighbors(i,j), currentGen[i][j], i,j);
        }
    }    
}

int rule(int numberOfLiveNeighbors, int cellState, int row, int column){
    //Check for the correct response to the number of neighbors and current state of cell
    // printf("Rule at (%d, %d) : numberOfLiveNeighbors: %d , cellState: %d \n",row, column,numberOfLiveNeighbors, cellState);
    switch(numberOfLiveNeighbors){
        case 3:
            if(cellState ==1)
                return 1;
            else
                return 0;
        case 2:
            if(cellState == 1)
                return 1;
            else
                return 0;
        default:
            if(numberOfLiveNeighbors > 2 && cellState == 1)
                return 0;
            else
                return 0;

    }

}
int neighbors(int row, int column){
    int left, right, top, bottom;
    left = column-1;
    right = column+1;
    top = row-1;
    bottom = row+1;
    if(left < 0) left+= DIM-1;
    if(right == DIM) right=0;
    if(top < 0) top += DIM-1;
    if(bottom == DIM) bottom = 0;

    int result =0;
    result += currentGen[top][left];
    result += currentGen[top][column];
    result += currentGen[top][right];
    result += currentGen[row][left];
    result += currentGen[row][right];
    result += currentGen[bottom][left];
    result += currentGen[bottom][right];
    result += currentGen[bottom][column];
    return result;
    
}

void copyGeneration(){
    for(int j=0; j < DIM; j++){
        for(int k=0; k < DIM; k++){
            nextGen[j][k] = currentGen[j][k];
        }
    }

}


void duplicateGeneration(){
    nextGen = new int* [DIM];
    for(int i = 0; i < DIM; i++){
        nextGen[i] = new int[DIM];
    }
    for(int j=0; j < DIM; j++){
        for(int k=0; k < DIM; k++){
            nextGen[j][k] = currentGen[j][k];
        }
    }

}
void createGeneration(int dimensions){
    DIM = dimensions;
    srand(time(NULL));
    //fill current Generation matrix with random 0s and 1s
    currentGen = new int* [dimensions];
    for(int i=0; i < dimensions; i++)
        currentGen[i] = new int[dimensions];


    //Fill cells randomly
    for(int j=0; j < dimensions; j++){
        for(int k=0; k < dimensions; k++){
            currentGen[j][k] = rand() % 2;
        }
    }
}

void printArray(int** a){
    for(int k=0; k < DIM; k++){
       for(int j=0; j < DIM; j++){
          printf("| %d | ", a[k][j]);
       }
       printf("\n");
    }
}
