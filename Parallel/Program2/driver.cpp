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
    printArray(currentGen);
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
            printf("Value of (%d, %d) : %d\n",i, j, nextGen[i][j]); 
        }
    }    
}

int rule(int numberOfLiveNeighbors, int cellState, int row, int column){
    //Check for the correct response to the number of neighbors and current state of cell
    if(numberOfLiveNeighbors > 2 && cellState ==1){
        return 0;
    }else if((numberOfLiveNeighbors == 2 || numberOfLiveNeighbors == 3) && cellState ==1){
        return 1;
    }else if(numberOfLiveNeighbors > 3 && cellState ==1){
        return 0;
    }else if(numberOfLiveNeighbors ==3 && cellState ==0){
        return 1;
    }

}
int neighbors(int row, int column){
    int count = 0;
    //check the edge case neighbors next to cell
    if(row == 0 || column == 0){//first row or first column
        if(row == 0 && column > 0){
            //get top
            if(currentGen[DIM -1][column] ==1)
                count++;
            //check bottom
            if(currentGen[row+1][column] == 1)
                count++;
            //check left
            if(currentGen[row][column-1] == 1)
                count++;
            //check right
            if(currentGen[row][column+1] == 1)
               count++;
            //check left top corner
            if(currentGen[DIM-1][column-1] == 1)
              count++;
           //check left bottom corner
            if(currentGen[row+1][column-1] == 1)
              count++;
            //check right top corner
            if(currentGen[DIM-1][column+1] == 1)
              count++;
           //check left bottom corner
            if(currentGen[row+1][column+1] == 1)
              count++;

       }else if( row > 0 && row < DIM-1 && column == 0){
            //get top
            if(currentGen[row -1][column] ==1)
                count++;
            //check bottom
            if(currentGen[row+1][column] == 1)
                count++;
            //check left
            if(currentGen[row][DIM-1] == 1)
                count++;
            //check right
            if(currentGen[row][column+1] == 1)
               count++;
            //check left top corner
            if(currentGen[row-1][DIM-1] == 1)
              count++;
           //check left bottom corner
            if(currentGen[row+1][DIM-1] == 1)
              count++;
            //check right top corner
            if(currentGen[row-1][column+1] == 1)
              count++;
           //check right bottom corner
            if(currentGen[row+1][column+1] == 1)
              count++;
        }

    }else if( (row > 0 || column > 0) && (row < DIM-1 && column < DIM -1)){//regular cases
        //check left
        if(currentGen[row][column-1] == 1)
           count++;
       //check right
       if(currentGen[row][column+1] == 1)
          count++;
       //check up
       if(currentGen[row-1][column] == 1)
          count++;
       //check down
       if(currentGen[row+1][column] == 1)
          count++;
       //check left top corner
        if(currentGen[row-1][column-1] == 1)
          count++;
       //check left bottom corner
        if(currentGen[row+1][column-1] == 1)
          count++;
        //check right top corner
        if(currentGen[row-1][column+1] == 1)
          count++;
       //check left bottom corner
        if(currentGen[row+1][column+1] == 1)
          count++;
    }else if(row == DIM-1 || column == DIM-1){
        if(row == DIM-1 && column < DIM){
            //check left
            if(currentGen[row][column-1] == 1)
               count++;
           //check right
           if(currentGen[row][column+1] == 1)
              count++;
           //check up
           if(currentGen[row-1][column] == 1)
              count++;
           //check down
           if(currentGen[0][column] == 1)
              count++;
           //check left top corner
            if(currentGen[row-1][column-1] == 1)
              count++;
           //check left bottom corner
            if(currentGen[0][column-1] == 1)
              count++;
            //check right top corner
            if(currentGen[row-1][column+1] == 1)
              count++;
           //check left bottom corner
            if(currentGen[0][column+1] == 1)
              count++;
        }else if( row < DIM && column == DIM-1){
            //check left
            if(currentGen[row][column-1] == 1)
               count++;
           //check right
           if(currentGen[row][0] == 1)
              count++;
           //check up
           if(currentGen[row-1][column] == 1)
              count++;
           //check down
           if(currentGen[row+1][column] == 1)
              count++;
           //check left top corner
            if(currentGen[row-1][column-1] == 1)
              count++;
           //check left bottom corner
            if(currentGen[row+1][column-1] == 1)
              count++;
            //check right top corner
            if(currentGen[row-1][0] == 1)
              count++;
           //check left bottom corner
            if(currentGen[row+1][0] == 1)
              count++;
        }
    }
    return count;
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
