#include <iostream>
#include <ctime>

__global__ void matMulKernel(float* matA, float* matB, float* matC, int rows, int cols)
{
    dim3 gIdx;
    gIdx.y = blockIdx.y * blockDim.y + threadIdx.y;
    gIdx.x = blockIdx.x * blockDim.x + threadIdx.x;

    float sum = 0;
    if(gIdx.x < cols && gIdx.y < rows)
    {
        for(int i = 0; i < rows; ++i)
        {
             sum += matA[gIdx.y * cols + i] * matB[i * cols + gIdx.x];
        }
        
        matC[gIdx.y * cols + gIdx.x] = sum;
    }
}

void printMat(float* mat, int rows, int cols)
{
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            int index = i * cols + j;
            std::cout << mat[index] << " "; 
        }
        std::cout << "\n";
    }
}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <DIM>" << std::endl;
        exit(1);
    }

    int matDim = atoi(argv[1]);
    const int NUM_COLS = matDim;
    const int NUM_ROWS = matDim;

    //allocate host mem for input matrices
    float* matA_h = new float[NUM_ROWS * NUM_COLS];
    float* matB_h = new float[NUM_ROWS * NUM_COLS];

    //fill input matrices
    for(int i = 0; i < NUM_ROWS; ++i)
    {
        for(int j = 0; j < NUM_COLS; ++j)
        {
            int index = i * NUM_COLS + j; 
            matA_h[index] = index;
            
            //scale matrix (factor 2)
            matB_h[index] = (i == j) ? 2 : 0;
        }
    }   

    //allocate dev mem for input matrices
    float* matA_d;
    float* matB_d;
    int matSize = NUM_ROWS * NUM_COLS * sizeof(float);
    cudaMalloc(&matA_d, matSize);
    cudaMalloc(&matB_d, matSize);

    //copy input matrices to device
    cudaMemcpy(matA_d, matA_h, matSize, cudaMemcpyHostToDevice); 
    cudaMemcpy(matB_d, matB_h, matSize, cudaMemcpyHostToDevice);

    //allocate dev mem for output matrix
    float* matC_d;
    cudaMalloc(&matC_d, matSize);
    cudaMemset(matC_d, 0, matSize);
    
    //determine block and grid size
    dim3 bDim(16, 16);
    dim3 gDim;
    gDim.x = (NUM_ROWS + 16 - 1) / 16; //ceil(num_rows/16)
    gDim.y = (NUM_ROWS + 16 - 1) / 16;

    cudaEvent_t start, stop;

    //record start event
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    //launch kernel
    matMulKernel<<<gDim, bDim>>>(matA_d, matB_d, matC_d, NUM_ROWS, NUM_COLS);
    
    //record stop event
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    float elapsed;
    cudaEventElapsedTime(&elapsed, start, stop);

    //allocate host mem for output matrix
    float* matC_h = new float[NUM_ROWS * NUM_COLS];

    //copy output matrix from dev to host
    cudaMemcpy(matC_h, matC_d, matSize, cudaMemcpyDeviceToHost);

    //print output matrix
    printMat(matC_h, NUM_ROWS, NUM_COLS); 

    std::cout << std::endl << "Compute time: " << elapsed << "ms" << std::endl;
}
