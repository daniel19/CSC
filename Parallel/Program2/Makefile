threads := 5
matrix := 1000

omp: GOL_omp.cpp
	g++-5 -g -Wall -fopenmp -o GOL_omp GOL_omp.cpp

run:
	./GOL_omp $(threads) $(matrix)
