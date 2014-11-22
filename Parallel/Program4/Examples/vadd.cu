/*
	A simple CUDA test program that adds two vectors
*/

#include <iostream>

__global__ void vAdd(int* a, int* b, int* c, int N)
{
	int gIdx = (blockDim.x * blockIdx.x) + threadIdx.x;
	
	if(gIdx < N)
	{
		c[gIdx] = a[gIdx] + b[gIdx];
	}
}

int main(int argc, char** argv)
{
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " <SIZE>" << std::endl;
        exit(1);
    }

	const int N = atoi(argv[1]);;

	//Allocate on host
	int* h_a = new int[N];
	int* h_b = new int[N];
	int* h_c = new int[N];
	
	//Allocate on device
	int* d_a = NULL;
	int* d_b = NULL;
	int* d_c = NULL;
	cudaMalloc(&d_a, sizeof(int) * N);
	cudaMalloc(&d_b, sizeof(int) * N);
	cudaMalloc(&d_c, sizeof(int) * N);
	
	//Fill input vectors
	for(int i = 0; i < N; ++i)
	{
		h_a[i] = i;
		h_b[i] = i;
		h_c[i] = 0;
	}
	
	//Copy vectors to device
	cudaMemcpy(d_a, h_a, sizeof(int) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, h_b, sizeof(int) * N, cudaMemcpyHostToDevice);
	
	//Call kernel
	int threadsPerBlock = 256;
	int numBlocks = (N + threadsPerBlock - 1) / threadsPerBlock; //ceil(n/threadsPerBlock)

    cudaEvent_t start, stop;

    //record start event
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

	vAdd<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, N);
    
    //record stop event
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    float elapsed;
    cudaEventElapsedTime(&elapsed, start, stop);
	
	//Copy output vector back to host
	cudaMemcpy(h_c, d_c, sizeof(int) * N, cudaMemcpyDeviceToHost);
	
	//Print the output vector
    for(int i = 0; i < N; ++i)
    {
        std::cout << h_c[i] << " ";

        if((i + 1) % 15 == 0)
            std::cout << std::endl;
    }

    std::cout << std::endl << "Compute time: " << elapsed << "ms" << std::endl;
}
