#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//Global variables
int** currentGen;
int** nextGen;
int thread_count;
int DIM;

//Forward Declaration
void createGeneration(int dimensions);
void duplicateGeneration();
void printArray(int** a);
void update();
int rule(int numberOfLiveNeighbors, int cellState, int row, int column);
int neighbors(int row, int column); 

int main(int argc, char* argv[]){
    if(argc < 3){
      fprintf(stderr, "Usage: ./matrix [# of threads] [matrix dimensions]");
      exit(1);
     }

    thread_count = atoi(argv[1]);
    float start_seq;
    float end_seq;
    float start_par;
    float end_par;
    start_seq = (float)clock()/CLOCKS_PER_SEC;
    createGeneration(atoi(argv[2]));
    printArray(currentGen);
    printf("\n");
    //Make copy of initial generation 
    duplicateGeneration();
    
    //run sequentially Conway's rules for the Game of Life
    update();

    end_seq = (float) clock()/CLOCKS_PER_SEC;
    float diff_seq = end_seq - start_seq;
    float diff_par = end_par - start_par;
    float speedup = diff_seq/diff_par;
    float efficiency = speedup/thread_count;

    printf("Difference sequential %f; Difference parallel %f \n", diff_seq, diff_par);
    printf("Speedup of %d threads is %f \n", thread_count, speedup);
    printf("Efficiency is %f \n", efficiency);
    printf("\n");
    printArray(nextGen);
    delete currentGen;
    delete nextGen;
    return 0;
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
            printf("Rule at (%d, %d) : numberOfLiveNeighbors: %d , cellState: %d \n",row, column,numberOfLiveNeighbors, cellState);
    if(numberOfLiveNeighbors > 2 && cellState ==1){
        return 0;
    }else if((numberOfLiveNeighbors == 2 || numberOfLiveNeighbors == 3) && cellState ==1){
        return 1;
    }else if(numberOfLiveNeighbors > 3 && cellState ==1){
        return 0;
    }else if(numberOfLiveNeighbors ==3 && cellState ==0){
        return 1;
    }else{
        return 0;
    }

}
int neighbors(int row, int column){
    int result=0;
    
    if(row==0 || row == DIM-1 || column ==0 || column == DIM-1){
         for(int i=row-1; i < row+2; i++){
            for(int j=column-1; j< column+2; j++){
                if(i==row && j == column){
                    continue;
                }
                if(i < 0){//on the first row check the last row to wrap around 
                    if(j <0){//on the first column check the last column to wrap around
                        result += currentGen[DIM-1][DIM-1];
                    }else{
                        result += currentGen[DIM-1][j];
                    }
                }else if(j<0 && !(i==DIM)){
                    result+= currentGen[i][DIM-1];
                }else if(i == DIM-1){
                    if(j == DIM-1){
                        result += currentGen[0][0];
                    }else{
                        result += currentGen[0][j];
                    }
                }else if(j == DIM-1 && !(i == DIM)){
                    result += currentGen[i][0];
                }                
            }
         }
    }else{//for general cases not on the first or last row and columns
        for(int i=row-1; i < row+2; i++){
            for(int j=column-1; j< column+2; j++){
                if(i==row && j == column){
                    continue;
                }
                if(i > -1 && j > -1 && i < DIM && j < DIM ){
                    result += currentGen[i][j];
                }
            }
        }
    }
    return result;
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
