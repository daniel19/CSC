#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
void  printGrid(float* grid, int rows, int cols);
/**
 *Kernel will update the matrix to keep the heater cells constant.
 */
__global__ void copyHeaters(float* stateGrid, float* heaterGrid, int nRows, int nCols, int iteration) {
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            float heatValue = heaterGrid[i*nCols +j];
            if(heatValue != 0)
                stateGrid[i*nCols + j] =heatValue;
        }
    }
    printf("\n FOR ITERATION %d \n\n", iteration);
    printGrid(stateGrid, nRows, nCols);
}

__global__ void updateGrid(float* inGrid, float* outGrid, float k, int nRows, int nCols) {
    dim3 gIdx;
    gIdx.y = blockIdx.y * blockDim.y + threadIdx.y;
    gIdx.x = blockIdx.x * blockDim.x + threadIdx.x;

   //Find these values from the inGrid
    int Tlft, Trite, Tup, Tdown;
    for(int i=0; i < nRows; ++i){
       for(int j=0; j < nCols; ++j){
           int currentPosition = i*nCols+j;
           Tlft = currentPosition -1;
           Trite = currentPosition +1;
           Tup = currentPosition -nCols;
           Tdown = currentPosition +nCols;
           float Tnew = inGrid[currentPosition];
           float Top, Tbottom, Tleft, Tright;
           Tbottom = (Tdown < 0) ? 0 : inGrid[Tdown];
           Top = (Tup > nCols) ? 0 : inGrid[Tup];
           Tright = (Trite > nCols) ?  0 : inGrid[Trite];
           Tleft = (Tlft < 0) ? 0 : inGrid[Tlft]; 
           
           Tnew = Tnew + k*(Top + Tbottom + Tleft + Tright - (4*Tnew));

           outGrid[currentPosition] = Tnew;
       }
   }
}

/*------------------------------------------------------------------------------
readHeaterFile

Assumes heaterGrid points to a flattened 2d array of size [rows,cols]
Fille heaterGrid with heaters from the heater file
------------------------------------------------------------------------------*/
void readHeaterFile(const char* fileName, float* heaterGrid, int rows, int cols) {
    std::ifstream inFile(fileName); 

    int numHeaters;
    inFile >> numHeaters;

    for(int i = 0; i < numHeaters; ++i) {
        int hRow, hCol;
        inFile >> hRow;
        inFile >> hCol;
        
        float temp;
        inFile >> temp; 

        heaterGrid[hRow * cols + hCol] = temp;
    }

    inFile.close();
}


/*------------------------------------------------------------------------------
printGrid
------------------------------------------------------------------------------*/
__device__ void printGrid(float* grid, int rows, int cols) {
    //std::cout << std::fixed << std::setprecision(2);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
     //       std::cout << std::setw(6) << grid[i*cols+j] << " ";
            printf("%f ", grid[i*cols+j]);
        }
        //std::cout << std::endl;
        printf("\n");
    }
}

/*------------------------------------------------------------------------------
printGridToFile
------------------------------------------------------------------------------*/
void printGridToFile(float* grid, int rows, int cols, char* fileName) {
    std::ofstream outFile(fileName);
    outFile << std::fixed << std::setprecision(2);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            outFile << std::setw(6) << grid[i*cols+j] << " ";
        }
        outFile<< std::endl;
    }
    outFile.close();
}

/*------------------------------------------------------------------------------
main
------------------------------------------------------------------------------*/
int main(int argc, char** argv) {
    if(argc != 6) {
        std::cout << "Usage: " << argv[0] << 
            " <numRows> <numCols> <k> <timesteps> <heaterFileName>" << std::endl;

        return 0;
    }

    //Input arguments
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    float k = atof(argv[3]);
    int timeSteps = atoi(argv[4]);

    //Allocate heater grid
    int gridSize = rows * cols * sizeof(float);
    float* heaterGrid_h = (float*)malloc(gridSize);

    //Read in heater file
    readHeaterFile(argv[5], heaterGrid_h, rows, cols); 

    float* heaterGrid_d; //device pointer
    //TODO Copy heater grid to device
    cudaMalloc(&heaterGrid_d, gridSize);
    cudaMemcpy(heaterGrid_d, heaterGrid_h, gridSize, cudaMemcpyHostToDevice);


    //Input grid
    float* inGrid_h = (float*)malloc(gridSize);
    memset(inGrid_h, 0, gridSize);
    float* inGrid_d; //device pointer
    //TODO Allocate and copy inGrid to device
    cudaMalloc(&inGrid_d, gridSize);
    cudaMemcpy(inGrid_d, inGrid_h, gridSize, cudaMemcpyHostToDevice);

    //Output grid
    float* outGrid_h = (float*)malloc(gridSize);
    memset(outGrid_h, 0, gridSize);
    float* outGrid_d; //device pointer
    //TODO Allocate and copy outGrid to device
    cudaMalloc(&outGrid_d, gridSize);
    cudaMemcpy(outGrid_d, outGrid_h, gridSize, cudaMemcpyHostToDevice);

    dim3 bDim(16, 16);
    dim3 gDim;
    gDim.x = (rows + 16 - 1) / 16; //ceil(num_rows/16)
    gDim.y = (rows + 16 - 1) / 16;


    //TODO fill in update loop
    for(int i = 0; i < timeSteps; ++i) {
        //copy heater temps to inGrid_d (kernel call)
        copyHeaters<<<gDim, bDim>>>(inGrid_d, heaterGrid_d, rows, cols, i);
        //update outGrid_d based on inGrid_d (kernel call)
        updateGrid<<<gDim, bDim>>>(inGrid_d, outGrid_d, k, rows, cols);
        //swap pointers inGrid_d and outGrid_d
        float* temp = inGrid_d;
        inGrid_d = outGrid_d;
        outGrid_d = temp;
    }
    
    //TODO copy inGrid_d back to host (to inGrid_h)
    cudaMemcpy(inGrid_h, inGrid_d, gridSize, cudaMemcpyDeviceToHost); 
    printGridToFile(inGrid_h, rows, cols, "output_two.txt");

    return 0;
}
