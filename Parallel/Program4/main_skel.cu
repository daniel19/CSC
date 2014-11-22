#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>

/**
 *Kernel will update the matrix to keep the heater cells constant.
 */
__global__ void copyHeaters(float* stateGrid, float* heaterGrid, int nRows, int nCols) {
   //TODO 
}

__global__ void updateGrid(float* inGrid, float* outGrid, float k, int nRows, int nCols) {
   //TODO 
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
void printGrid(float* grid, int rows, int cols) {
    std::cout << std::fixed << std::setprecision(2);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            std::cout << std::setw(6) << grid[i*cols+j] << " ";
        }
        std::cout << std::endl;
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

    //Input grid
    float* inGrid_h = (float*)malloc(gridSize);
    memset(inGrid_h, 0, gridSize);
    float* inGrid_d; //device pointer
    //TODO Allocate and copy inGrid to device

    //Output grid
    float* outGrid_h = (float*)malloc(gridSize);
    memset(outGrid_h, 0, gridSize);
    float* outGrid_d; //device pointer
    //TODO Allocate and copy outGrid to device

    //TODO fill in update loop
    for(int i = 0; i < timeSteps; ++i) {
        //copy heater temps to inGrid_d (kernel call)
        //update outGrid_d based on inGrid_d (kernel call)
        //swap pointers inGrid_d and outGrid_d
    }
    
    //TODO copy inGrid_d back to host (to inGrid_h)
    
    printGridToFile(inGrid_h, rows, cols, "output.txt");

    return 0;
}
