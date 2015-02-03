#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <mpi.h>

using namespace std;

char* createMatrix(int rows, int cols);
void  populateMatrix(char* matrix, int rows, int cols);
int   countNeighbors(char* matrix, int rows, int cols, int r, int c);
void  swap(void* item1, void* item2);

const int GENERATIONS = 100;

int main()
{

	int rows = 40000;
	int cols = 40000;

	int my_rank;
	int comm_size;

	MPI_Init(NULL, NULL); 
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

	char* home_grid;
	char* mat1;
	char* mat2;

	int num_rows;

	double time_total = 0;
	double time_processing = 0;

	if(my_rank == 0)
		time_total = MPI_Wtime();

	int* distro = (int*) malloc(comm_size*sizeof(int));
	int* displacement = (int*) malloc(comm_size*sizeof(int));

	if(my_rank == 0)
	{
		//cout << "Creating matrix" << endl;
		home_grid = createMatrix(rows, cols);

		//cout << "Matrix made" << endl;
		populateMatrix(home_grid, rows, cols);

	}

	//int rowsPerThread = ceiling(rows/comm_size)
	int rowsPerThread = 1 + ((rows - 1) / comm_size);	

	//cout << rowsPerThread << " rows per process" << endl;

	//delegate number of rows for each process 0 through comm_size - 2
	for(int i = 0; i < comm_size - 1; i++)
	{
		distro[i] = rowsPerThread*cols;
		displacement[i] = distro[i]*i;

		/*if(i == my_rank)
		{
			cout << distro[i] << " elements for process " << i << endl;
			cout << displacement[i] << " element offset for process " << i << endl;
		}*/

	}

	//delegate the rest of the rows to process comm_size - 1
	distro[comm_size - 1] = (rows - rowsPerThread * (comm_size - 1)) * cols;
	displacement[comm_size - 1] = distro[comm_size - 1] * (comm_size - 1);

	//cout << distro[comm_size-1]/cols << " rows for the last process " << comm_size-1 << endl;
	//cout << distro[comm_size-1] << " elements for process " << comm_size-1 << endl;
	//cout << displacement[comm_size-1] << " element offset for process " << comm_size-1 << endl;

	num_rows = distro[my_rank]/cols;

	//cout << "Process " << my_rank << " has " << num_rows << " rows" << endl;

	mat1 = createMatrix(num_rows + 2, cols);
	mat2 = createMatrix(num_rows, cols);

	MPI_Scatterv(home_grid, distro, displacement, MPI_CHAR, mat2, distro[my_rank], MPI_CHAR, 0, MPI_COMM_WORLD);

	//cout << "Scatter complete" << endl;

	for(int r = 1; r <= num_rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			mat1[r*cols + c] = mat2[(r - 1)*cols + c];
		}
	}

	char* send_to_prev = createMatrix(1, cols);
	char* send_to_next = createMatrix(1, cols);

	char* from_prev = createMatrix(1,cols);
	char* from_next = createMatrix(1,cols);

	if(my_rank == 0)
		time_processing = MPI_Wtime();

	for(int gen = 0; gen < GENERATIONS; gen++)
	{

		//prep to send 1st row to my_rank - 1
		for(int c = 0; c < cols; c++)
			send_to_prev[c] = mat1[cols + c];

		//prep to send last row to my_rank + 1
		for(int c = 0; c < cols; c++)
			send_to_next[c] = mat1[(num_rows+1)*cols + c];


		int next_neighbor = my_rank + 1;
		int prev_neighbor = my_rank - 1;

		if(my_rank == comm_size - 1)
		{
			next_neighbor = 0;
		}

		else if(my_rank == 0)
		{
			prev_neighbor = comm_size - 1;
		}

		if(my_rank%2 == 0)
		{

			MPI_Send(send_to_prev, cols, MPI_CHAR, prev_neighbor, 0, MPI_COMM_WORLD);
			MPI_Recv(from_prev, cols, MPI_CHAR, prev_neighbor, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
			MPI_Recv(from_next, cols, MPI_CHAR, next_neighbor, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(send_to_next, cols, MPI_CHAR, next_neighbor, 0, MPI_COMM_WORLD);

		}

		else
		{


			MPI_Recv(from_next, cols, MPI_CHAR, next_neighbor, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(send_to_next, cols, MPI_CHAR, next_neighbor, 0, MPI_COMM_WORLD);

			MPI_Send(send_to_prev, cols, MPI_CHAR, prev_neighbor, 0, MPI_COMM_WORLD);
			MPI_Recv(from_prev, cols, MPI_CHAR, prev_neighbor, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		}

		for(int i = 0; i < cols; i++)
			mat1[i] = from_prev[i];

		for(int i = 0; i < cols; i++)
			mat1[num_rows + i] = from_next[i];

		//if(my_rank == 0)
			//printMatrix(mat1, rows, cols);

		for(int r = 1; r <= num_rows; r++)
		{

			for(int c = 0; c < cols; c++)
			{

				//cout << "Counting neighbors for cell (" << r << "," << c << ")" << endl;

				int numNeighbors = countNeighbors(mat1, num_rows, cols, r, c);

				mat2[r * num_rows + c] = false;

				//Already lrving cells survive
				if(numNeighbors == 2)
				{

					if(mat1[r * num_rows + c] == true)
					{				
						mat2[r * num_rows + c] = true;

					}

					else
					{
						mat2[r * num_rows + c] = false;
					}

				}

				//cell either lives if alive, or becomes alive if dead
				else if(numNeighbors == 3)
				{
					mat2[r * num_rows + c] = true;
				}

				//cell dies from starvation (numNeighbors < 2) or overcrowding (numNeighbors > 3)
				else
				{
					mat2[r * num_rows + c] = false;
				}

			}

		}

		
		swap(mat1, mat2);

	}

	if(my_rank == 0)
		time_processing = MPI_Wtime() - time_processing;

	free(mat2);

	mat2 = createMatrix(num_rows, cols);

	if(my_rank == 0)
	{	
		free(home_grid);
		home_grid = createMatrix(rows,cols);
	}

	for(int r = 1; r <= num_rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			mat2[(r - 1) * cols + c] = mat1[r * cols + c];
		}
	}

	MPI_Gatherv(mat2, distro[my_rank], MPI_CHAR, home_grid, distro, displacement, MPI_CHAR, 0, MPI_COMM_WORLD);

	if(my_rank == 0)
	{
		time_total = MPI_Wtime() - time_total;

	
		cout << "It took " << time_processing << " seconds to compute " << GENERATIONS << " generations with " << comm_size << " Processes" << endl;
		cout << "It took " << time_total << " seconds overall" << endl << endl;

	
		/**FILE* file_csv;
		file_csv  = fopen("results.csv", "a");

		cout << "It took " << time_processing << " seconds to compute " << GENERATIONS << " generations with " << comm_size << " Processes" << endl;
		cout << "It took " << time_total << " seconds overall" << endl << endl;

		fprintf(file_csv, "%d x %d,%d,%d,%f,%f,\n", rows, cols, comm_size,, generations time_processing, time_total);

		fflush(file_csv);

		fclose(file_csv);**/

	}

	MPI_Finalize();

}

char* createMatrix(int rows, int cols)
{

	return (char*) calloc(rows,cols*sizeof(char));

}

void  populateMatrix(char* matrix, int rows, int cols)
{

	srand(time(NULL));

	int length = rows * cols;

	int random;

	for(int i = 0; i < length; i++)
	{

		random = rand()%10;

		if(random < 2)
			matrix[i] = true;

		else
			matrix[i] = false;

		//matrix[i] = rand()%10;

	}

}

int countNeighbors(char* matrix, int rows, int cols, int r, int c)
{

	int numNeighbors = 0;
	int up = r - 1;
	int down = r + 1;
	int left = c - 1;
	int right = c + 1;

	//check for wrap conditions

	if(c == 0)
		left = cols - 1;
	
	else if(c == cols - 1)
		right = 0;

	//check for wrap conditions


	//check above
	if(matrix[up * cols + c] == true)
		numNeighbors++;

	//check above right
	if(matrix[up * cols + right] == true)
		numNeighbors++;

	//check right
	if(matrix[r * cols + right] == true)
		numNeighbors++;

	//check below right
	if(matrix[down * cols + right] == true)
		numNeighbors++;

	//check below
	if(matrix[down * cols + c] == true)
		numNeighbors++;

	//check below left
	if(matrix[down * cols + left] == true)
		numNeighbors++;

	//check left
	if(matrix[r * cols + left] == true)
		numNeighbors++;

	//check above left
	if(matrix[up * cols + left] == true)
		numNeighbors++;

	return numNeighbors;

}

void swap(void* item1, void* item2)
{

	void* temp = item1;

	item1 = item2;

	item2 = temp;

	return;

}
