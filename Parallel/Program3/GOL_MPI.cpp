#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//Forward Declaration
void printRow(int* a);
int* createGeneration(int dimensions);
int* createSpare(int row, int columns);
void copyGeneration(int *arr1, int *arr2);
void printArray(int** A);
void update(int nr, int *sendOne, int *sendTwo, int *recvOne, int *recvTwo, int *spareOne, int *spareTwo, int DIM, int rank, int thread_count);
int rule(int numberOfLiveNeighbors, int cellState, int row, int column);
int neighbors(int row, int column, int *currentGen, int DIM);

int main(int argc, char* argv[]){
    int DIM;
    int rank;
    int thread_count;

    int* currentGen;
    int* spareOne;
    int* spareTwo;
    int* distribution;
    int* displacement;
    int* sendOne;
    int* sendTwo; 
    int* recvOne;
    int* recvTwo;
    
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
    double total_time = 0;
    double processing = 0;
    if(rank == 0){
        total_time = MPI_Wtime();
        currentGen = createGeneration(DIM);
    }

    distribution = (int*) malloc(thread_count*sizeof(int));
    displacement = (int*) malloc(thread_count*sizeof(int));

    int rp = 1 + ((DIM-1)/thread_count);
    //cerr << "Rows per thread: " << rp << endl << endl;
    for(int i =0; i < thread_count-1; i++){
        distribution[i] = rp*DIM;
        displacement[i] = distribution[i]*i;

		if(i == rank)
		{
//			cerr << distribution[i] << " elements for process " << i << endl;
//			cerr << displacement[i] << " element offset for process " << i << endl;
		}
    }

    distribution[thread_count-1] = (DIM - rp*(thread_count-1))*DIM;
    displacement[thread_count -1] = distribution[thread_count-1]*(thread_count-1);

    int nr = distribution[rank]/DIM;
	//cerr << "Process " << rank << " has " << nr << " rows" << endl;
    spareOne = createSpare(nr+2, DIM);
    spareTwo = createSpare(nr, DIM); 

    
    MPI_Scatterv(currentGen, distribution, displacement, MPI_INT, spareTwo, distribution[rank], MPI_INT, 0, MPI_COMM_WORLD);

    for(int row = 1; row <= nr; row++){
        for(int column = 0; column<DIM; column++){
            spareOne[row*DIM + column] = spareTwo[(row-1)*DIM + column];
        }
    }

    sendOne = createSpare(1, DIM); 
    sendTwo = createSpare(1, DIM); 
    recvTwo = createSpare(1, DIM); 
    recvOne = createSpare(1, DIM); 
    //update after each generation
   if(rank ==0){
        processing = MPI_Wtime();
   }
   for(int iter =0; iter < GEN; iter++){
            for(int columns = 0; columns<DIM; columns++){
            sendOne[columns] = spareOne[columns+DIM];
            sendTwo[columns] = spareOne[(nr+1)*DIM+columns];
        } 

        
        int next = rank+1;
        int previous = rank-1; 
        if(rank == thread_count-1) next =0;
        if(rank == 0) previous = thread_count-1;

        if(rank%2 == 0){
            MPI_Send(sendOne, DIM, MPI_INT, previous, 0, MPI_COMM_WORLD);
            MPI_Recv(recvOne, DIM, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(recvTwo, DIM, MPI_INT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(sendTwo, DIM, MPI_INT, next, 0, MPI_COMM_WORLD);
        }else{
            MPI_Recv(recvTwo, DIM, MPI_INT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(sendTwo, DIM, MPI_INT, next, 0, MPI_COMM_WORLD);
            MPI_Send(sendOne, DIM, MPI_INT, previous, 0, MPI_COMM_WORLD);
            MPI_Recv(recvOne, DIM, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        
        for(int i =0; i < DIM; i++){
            spareOne[i] = recvOne[i];
        }
        
        for(int i =0; i < DIM; i++){
            spareOne[i+nr] = recvTwo[i];
        }
        
        for(int i = 0; i <= nr; i++){
            for(int j = 0; j < DIM; j++){
                spareTwo[i*DIM+j] = rule(neighbors(i,j, spareOne, DIM), spareOne[i*DIM+j], i,j);
            }
        }
  
      copyGeneration(spareOne, spareTwo); 
   }
   
   if(rank ==0){
       processing = MPI_Wtime()-processing;
       free(currentGen);
       currentGen = createSpare(DIM, DIM);
   }
   free(spareTwo);
   spareTwo = createSpare(nr, DIM); 
  for(int r = 1; r<= nr; r++){
    for(int c = 0; c<DIM; c++){
        spareTwo[(r-1)*DIM +c] = spareOne[r*DIM+c];
    }
  }

 MPI_Gatherv(spareTwo, distribution[rank], MPI_INT, currentGen, distribution, displacement, MPI_INT,0, MPI_COMM_WORLD);
    
    if(rank==0){
       total_time = MPI_Wtime() - total_time;
       cout << "For square matrix size: " << DIM << " with thread count: " << thread_count << endl;
       cout << "Total Time to process: " << processing<<endl; 
       cout << "Total Time to run: " << total_time << endl << endl;
    } 
   MPI_Finalize();
   return 0;
}

void update(int nr, int *sendOne, int *sendTwo, int *recvOne, int *recvTwo, int *spareOne, int *spareTwo, int DIM, int rank, int thread_count){
    for(int columns = 0; columns<DIM; columns++){
        sendOne[columns] = spareOne[columns+DIM];
        sendTwo[columns] = spareOne[(nr+1)*DIM+columns];
    } 

    
    int next = rank+1;
    int previous = rank-1; 
    if(rank == thread_count-1) next =0;
    if(rank == 0) previous = thread_count-1;

    if(rank%2 == 0){
        MPI_Send(sendOne, DIM, MPI_INT, previous, 0, MPI_COMM_WORLD);
        MPI_Recv(recvOne, DIM, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(recvTwo, DIM, MPI_INT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(sendTwo, DIM, MPI_INT, next, 0, MPI_COMM_WORLD);
    }else{
        MPI_Recv(recvTwo, DIM, MPI_INT, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(sendTwo, DIM, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Send(sendOne, DIM, MPI_INT, previous, 0, MPI_COMM_WORLD);
        MPI_Recv(recvOne, DIM, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    for(int i =0; i < DIM; i++){
        spareOne[i] = recvOne[i];
    }
    
    for(int i =0; i < DIM; i++){
        spareOne[i+nr] = recvTwo[i];
    }
    
    for(int i = 0; i <= nr; i++){
        for(int j = 0; j < DIM; j++){
            spareTwo[i*DIM+j] = rule(neighbors(i,j, spareOne, DIM), spareOne[i*DIM+j], i,j);
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
int neighbors(int row, int column, int *currentGen, int DIM){
    int left, right, top, bottom;
    left = column-1;
    right = column+1;
    top = row-1;
    bottom = row+1;
    if(column == 0) left = DIM-1;
    if(column == DIM-1) right=0;

    int result =0;
    result += currentGen[top*DIM + column]; //above
    result += currentGen[top*DIM + right];//above right
    result += currentGen[top*DIM + left];//above left
    result += currentGen[bottom*DIM + column];//below
    result += currentGen[bottom*DIM + right]; //below right
    result += currentGen[bottom*DIM + left]; //below left
    result += currentGen[row*DIM + left];//left
    result += currentGen[row*DIM + right];//right
    return result;
}

void copyGeneration(int *arr1, int *arr2){
    int* temp = arr1;
    arr1 = arr2;
    arr2 = temp;
}

 /*Separate matrix based on the number of processes created.
 */
int* createGeneration(int dimensions){
    srand(time(NULL));
    int length = dimensions*dimensions;
    int *a = (int*)calloc(dimensions, dimensions* sizeof(int)); 
    
    //fill partitioned matrix with random 0s and 1s
    for(int k=0; k < length; k++){
        a[k] = rand() %2;
    }
    return a;
}
void printVec(int* a, int DIM){
    for(int i=0; i < DIM; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}
void printArray(int** a, int DIM){
    for(int k=0; k < DIM; k++){
       for(int j=0; j < DIM; j++){
          printf("| %d | ", a[k][j]);
       }
       printf("\n");
    }
}

int* createSpare(int row, int columns){
    return (int*) calloc(row, columns*sizeof(int));
}
