To run and compile omp threads use the following commands:
    gcc/g++ -g -Wall -fopenmp 

To run and compile pthread threads use the following commands:
    gcc/g++ -g -Wall -lpthread
    
To run and compile MPI use the following commands:
    mpicc -g -Wall -o mpiGOL 
    mpiexec -n <number of process> ./mipGOL 
