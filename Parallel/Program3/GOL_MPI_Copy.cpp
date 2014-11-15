#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int** currentGen;
int** nextGen;
int DIM;
int rank;
int count;
int thread_count;

//Forward Declaration
void printRow(int* a);
void createGeneration(int dimensions);
void duplicateGeneration();
void copyGeneration();
void printArray(int** A);
void update();
int rule(int numberOfLiveNeighbors, int cellState, int row, int column);
int neighbors(int row, int column); 

int main(int argc, char* argv[]){
    count = 0;
    const int GEN = 100;
    if(argc < 2){
      fprintf(stderr, "Usage: ./mpiGOL [matrix dimensions]");
      exit(1);
     }
    DIM = atoi(argv[1]);
    //Setup MPI configuration
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &thread_count); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    
    float start_seq;
    float end_seq;
    float start_par;
    float end_par;
    start_seq = (float)clock()/CLOCKS_PER_SEC;
    
    createGeneration(DIM);
    //Make copy of initial generation 
    duplicateGeneration();
    
    end_seq = (float) clock()/CLOCKS_PER_SEC;
    
    //run sequentially Conway's rules for the Game of Life
    start_par = (float)clock()/CLOCKS_PER_SEC;
    //update after each generation
    for(int iter =0; iter < GEN; iter++){
       update();
       copyGeneration(); 
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

    MPI_Finalize();
    return 0;
}

void update(){
    int* topRow;
    int* bottomRow;
    MPI_Status status;
    MPI_Request req_recvAbove, req_recvBelow, req_sendAbove, req_sendBelow;
    //Send and Receive rows to other processes
    if(rank != 0){
        //Receive bottom row from neighbor above
        printf("Receiving bottom row from rank %d",rank);
        MPI_Irecv(&bottomRow, DIM, MPI_INT, rank-1, NULL, MPI_COMM_WORLD, &req_recvAbove);
    }
    if(rank != thread_count-1){
        //Receive top row from neighbor below
        MPI_Irecv(&topRow, DIM, MPI_INT, rank+1, NULL, MPI_COMM_WORLD, &req_recvBelow);
    }

    if(rank !=0){
        //Send top row to neighbor above
        MPI_Isend(currentGen[0], DIM, MPI_INT, rank-1, NULL, MPI_COMM_WORLD, &req_sendAbove);
    }

    if(rank != thread_count-1){
        //Send bottom row to neighbor below
        printf("Sending bottom row from rank %d: ", rank);
        MPI_Isend(currentGen[DIM-1], DIM, MPI_INT, rank+1, NULL, MPI_COMM_WORLD, &req_sendBelow);
    }
    
    //wait for send and receives 
    if(rank != 0) {
      // receive bottom row from neighbor "above" 
      MPI_Wait(&req_recvAbove, &status);
    }
    if (rank != (thread_count-1)) {
     //receive top row from neighbor "below"
     MPI_Wait(&req_recvBelow, &status);
    }
    if (rank != 0) {
        // send top row to neighbor "above"
        MPI_Wait(&req_sendAbove, &status);
   }
   if (rank != (thread_count-1)) {
       // send bottom row to neighbor "below"
       MPI_Wait(&req_sendBelow, &status);
   } 

    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            nextGen[i][j] = rule(neighbors(i,j), currentGen[i][j], i,j);
        }
    }
  
}

int rule(int numberOfLiveNeighbors, int cellState, int row, int column){
    //Check for the correct response to the number of neighbors and current state of cell
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
    for(int i = 0; i < DIM; i++){
        nextGen[i] = currentGen[i];
    }
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
/*
 *Separate matrix based on the number of processes created.
 */
void createGeneration(int dimensions){
    int first_row, last_row, local;
    
    local = dimensions/thread_count;
    first_row = rank*local;
    last_row = (rank+1)*local - 1; 
    currentGen = new int* [dimensions];
    for(int i=0; i < dimensions; i++)
        currentGen[i] = new int[dimensions];

 
    srand(time(NULL));
    //fill partitioned matrix with random 0s and 1s
    for(int i = first_row; i < last_row; i++){
        for(int k=0; k < dimensions; k++){
            currentGen[i][k] = rand() %2;
        }
    }
}
void printVec(int* a){
    for(int i=0; i < DIM; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}
void printArray(int** a){
    for(int k=0; k < DIM; k++){
       for(int j=0; j < DIM; j++){
          printf("| %d | ", a[k][j]);
       }
       printf("\n");
    }
}
