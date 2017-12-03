
#include "E:\VisualStudio\CUDA\common\book.h"

#define  N  128



__global__ void kernel(int *A, int *C)
{
	int i = blockIdx.x;
	int j = blockIdx.y;
	if (A[i]>A[j])
		atomicAdd(&C[i], 1);
	if ((A[i] == A[j])&&(i>j))
		atomicAdd(&C[i], 1);
}
int main(void)
{
	int  A[128] = { 637, 84, 96, 2, 67, 91, 68, 355, 91, 96, 19, 56, 90, 48, 657, 99, 94, 89, 93, 76, 102, 784, 11, 12, 98, 106, 42, 112, 999, 114, 87, 21, 22, 64, 91, 632, 60, 25, 97, 74, 42, 40, 281, 37, 30, 45, 69, 67, 41, 924, 42, 40, 85, 108, 12, 22, 465, 66, 99, 118, 50, 5, 15, 49, 8, 66, 71, 38, 27, 50, 70, 77, 108, 44, 54, 26, 49, 61, 110, 16, 85, 54, 15, 129, 110, 50, 100, 27, 56, 47, 62, 2, 107, 19, 29, 20, 7, 64, 69, 26, 38, 18, 81, 67, 20, 78, 51, 40, 76, 120, 32, 128, 36, 34, 63, 128, 6, 88, 65, 108, 102, 105, 13, 33, 92, 21, 102, 20 };
	int   *B, *C;

	int *dev_A, *dev_C;
	// allocate the memory on the CPU
	B = (int*)malloc(N * sizeof(int));
	C = (int*)malloc(N * sizeof(int));
	for (int i = 0; i<N; i++)
	{
		 
		B[i] = 0;
		C[i] = 0;
	}
	// allocate the memory on the GPU
	HANDLE_ERROR(cudaMalloc((void**)&dev_A, N * sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_C, N * sizeof(int)));


	// copy the arrays 'A' and 'C' to the GPU
	HANDLE_ERROR(cudaMemcpy(dev_A, A, N * sizeof(int),
		cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_C, C, N * sizeof(int),
		cudaMemcpyHostToDevice));
	
	dim3   blocks(N,N);
	// capture the start time
	cudaEvent_t     start, stop;
	HANDLE_ERROR(cudaEventCreate(&start));
	HANDLE_ERROR(cudaEventCreate(&stop));
	HANDLE_ERROR(cudaEventRecord(start, 0));

	kernel <<< blocks, 1 >>>(dev_A, dev_C);

	HANDLE_ERROR(cudaEventRecord(stop, 0));
	HANDLE_ERROR(cudaEventSynchronize(stop));
	float   elapsedTime;
	HANDLE_ERROR(cudaEventElapsedTime(&elapsedTime,
		start, stop));
	printf("Time to generate:  %3.1f ms\n", elapsedTime);
	HANDLE_ERROR(cudaEventDestroy(start));
	HANDLE_ERROR(cudaEventDestroy(stop));
	
	// copy the array 'C' back from the GPU to the CPU
	HANDLE_ERROR(cudaMemcpy(C, dev_C, N * sizeof(int),
		cudaMemcpyDeviceToHost));
	printf("Have sorted:\n");
	for (int i = 0; i<N; i++)
	{
		B[C[i]] = A[i];
		printf("%d,", B[i]);

	}

	// free the memory we allocated on the GPU
	HANDLE_ERROR(cudaFree(dev_A));
	HANDLE_ERROR(cudaFree(dev_C));

	// free the memory we allocated on the CPU

	free(B);
	free(C);

	return 0;

}
