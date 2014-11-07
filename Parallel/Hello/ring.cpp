#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char* argv[]){
    char message[100];
    int commsize, my_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
    MPI_Request request; 
    //for(int i =0; i < commsize; i++){
        if(my_rank == 0){
            //read then send message
            printf("Enter your secure message: ");
            scanf("%99s", message);
            printf("\n");
            MPI_Send(message, strlen(message)+1, MPI_CHAR, my_rank+1,0, MPI_COMM_WORLD);
            MPI_Recv(message, 100, MPI_CHAR,commsize-1,0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);  
        }else{
          printf("Greetings from process %d of %d!\n", my_rank, commsize);
          MPI_Irecv(message, 100, MPI_CHAR,my_rank-1,0, MPI_COMM_WORLD,&request);  
        }
    //}

    MPI_Finalize(); 
    return 0;
}

