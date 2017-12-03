#if 0
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "E:\VisualStudio\CUDA\common\book.h"
#define imin(a,b)  ((a)<(b)?(a):(b))
#define sum_squares(x) (x*(x+1)*(2*x+1)/6)
const int N = 3 * 1024;
const int threadsPerBlock = 256;
const int blocksPerGrid = imin(32, (N+threadsPerBlock-1)/threadsPerBlock);

__global__ void doc(float* a, float* b, float* c)//点积运算
{
	int x = threadIdx.x + blockIdx.x*blockDim.x;
	__shared__ float cache[threadsPerBlock];
	int cacheId = threadIdx.x;
	float temp = 0;
	while(x < N)
	{
		temp += a[x] * b[x];//正确，防止分配的线程不够
		//temp = a[x] * b[x];
		x += blockDim.x * gridDim.x;
	}
	cache[cacheId] = temp;
	//对线程块中的线程进行同步
	__syncthreads();

	//归约
	int i = blockDim.x/2;
	while(i != 0)
	{
		if(cacheId < i)
			cache[cacheId] += cache[cacheId + i];
		__syncthreads();
		i /= 2;
	}
	if(cacheId == 0)
	{c[blockIdx.x] = cache[0];}

}


int main(void)
{
	float *a, *b, c, *partial_c;
	float *dev_a, *dev_b, *dev_partial_c;
	a = new float[N];
	b = new float[N];
	partial_c = new float[blocksPerGrid];
	HANDLE_ERROR(cudaMalloc((void**)&dev_a,
							N*sizeof(float)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_b,
							N*sizeof(float)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_partial_c,
							blocksPerGrid*sizeof(float)));
	for(int i=0; i<N; i++)
	{
		a[i] = i;
		b[i] = 2*i;
	}
	HANDLE_ERROR(cudaMemcpy(dev_a, a, N*sizeof(float), cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b, b, N*sizeof(float), cudaMemcpyHostToDevice));
	doc<<<blocksPerGrid,threadsPerBlock>>>(dev_a, dev_b, dev_partial_c);

	    HANDLE_ERROR( cudaMemcpy( partial_c, dev_partial_c,
                              blocksPerGrid*sizeof(float),
                              cudaMemcpyDeviceToHost ) );
	c = 0;
	for(int i=0; i<blocksPerGrid; i++)
		c += partial_c[i];
	printf("Does  GPU value %.6g =  %.6g\n",c,
			2*sum_squares((float)(N-1)));
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_partial_c);
	delete []a;
	delete []b;
	delete []partial_c;
	return 0;
}
#endif