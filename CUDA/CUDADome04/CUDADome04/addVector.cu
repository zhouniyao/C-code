#if 0
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include"E:\研究生-2016年3月\CUDA\CUDA by Example.An Introduction to General-Purpose GPU Programming\cuda_by_example1\common\book.h"
#define N (32*32+133)  //每个block中最大的thread数目——max threads per block
//【如果分配的线程数大于机器内部规定数，会发生什么？】
//终止核函数运行，因为GPU有完善的内存管理机制，它会强行结束所有违反内存访问规则的进程。
__global__ void add(int* dev_a, int* dev_b, int* dev_c)
{
	int index = blockIdx.x*blockDim.x + threadIdx.x;//blockDim.x保存的是线程块中每一维的线程数量,gridDim保存【线程格】中每一维的线程块的数量；gridDim是二维的，而blockDim是三维的
	//int index = blockIdx.x;//分配N个block，每个block分配一个thread
	//int index = threadIdx.x;//单个块分配N个thread
	//if换成while，可处理任意大小的适量相加
	while(index < N)
	{
		dev_c[index] = dev_a[index] + dev_b[index];
		index += gridDim.x*blockDim.x;//步长：每个线程块中的线程数量乘以线程格中线程块的数量
	}
}

int main()
{
	int i;
	int* a = (int*)malloc(N*sizeof(int));
	int* b = (int*)malloc(N*sizeof(int));
	int* c = (int*)malloc(N*sizeof(int));
	int* dev_a;
	int* dev_b;
	int* dev_c;
	HANDLE_ERROR( cudaMalloc( (void**)&dev_a,
                             N*sizeof(int) ) );
    HANDLE_ERROR( cudaMalloc( (void**)&dev_b,
                             N*sizeof(int) ) );
	HANDLE_ERROR( cudaMalloc( (void**)&dev_c,
                             N*sizeof(int) ) );
	for(i=0; i<N; i++)
	{
		a[i] = i;
		b[i] = i*i;
		printf("%d   %d\n",a[i],b[i]);
	}
	HANDLE_ERROR( cudaMemcpy( dev_a, a, N*sizeof(int),
                            cudaMemcpyHostToDevice ) ); 
	HANDLE_ERROR( cudaMemcpy( dev_b, b, N*sizeof(int),
                            cudaMemcpyHostToDevice ) ); 
	//add<<<N,1>>>(dev_a, dev_b, dev_c);
	//add<<<1,N>>>(dev_a, dev_b, dev_c);
	add<<<(N+1023)/1024,1024>>>(dev_a, dev_b, dev_c);

	HANDLE_ERROR( cudaMemcpy( c, dev_c, N*sizeof(int),
							 cudaMemcpyDeviceToHost ) ); 
	--i;
	while(i>=0)
	{
		printf("%d\t",c[i]);
		i--;
	}
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);
	return 0;
}
#endif