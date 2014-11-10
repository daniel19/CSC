This project simulates James Conway's Game of Life Theory using parallelization techniques.
'
To compile and run the programs do the following.

Compile the pthread program using the following command:
    g++ -g -Wall -lpthread -o GOL_pthread GOL_Pthread.cpp [number of threads] [matrix size]

Compile the omp program usin the following command:
    g++ -g -Wall -fopenmp -o GOL_omp GOL_omp.cpp [number of threads] [matrix size]
   
To run and compile MPI use the following commands:
    mpicc -g -Wall -o mpiGOL GOL_MPI.cpp 
    mpiexec -n [number of process] ./mipGOL 
