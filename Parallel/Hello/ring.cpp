#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char* argv[]){
    int commsize, my_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_Comm_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
}

