#if 0
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"../common/book.h"
using namespace std;
#define N 32        //每个块  最大只能取32个线程，由本机硬件配置限制

//void	add(int (*a)[N],int (*b)[N],int (*c)[N]);
__global__ void add(int (*a)[N],int (*b)[N],int (*c)[N])
{
	/*既然GPU将运行核函数的N个副本，那么如何在代码中知道
	*当前正在运行的是哪个线程块？
	*无需定义blockIdx，它是一个内置变量，包含的值就是当前执行设备代码的线程块的索引。
	*
	*/
	//int j=blockIdx.x;  //计算位于这个索引处的数据，从0开始
	//int i=blockIdx.y;

	int j=threadIdx.x;
	int i=threadIdx.y;
	if(i<N&&j<N)c[i][j]=a[i][j]+b[i][j];//only "if" no "while"
	/*
	for(int i=0;i<N;i++)
	for(int j=0;j<N;j++)
	c[i][j]=a[i][j]+b[i][j];
	*/
}
int main()
{
	int a[N][N],b[N][N],c[N][N];
	int (*dev_a)[N],(*dev_b)[N],(*dev_c)[N];
	//allocate the memory on the GPU
	HANDLE_ERROR(cudaMalloc((void**)&dev_a,N*N*sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_b,N*N*sizeof(int)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_c,N*N*sizeof(int)));

	/*
	int (*a)[N]=new int[N][N];
	int (*b)[N]=new int[N][N];
	int (*c)[N]=new int[N][N];


	int a[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);//错误,为什么？a是指针常量，不能做左值
	int b[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);
	int c[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);
	*/
	/*
	int (*a)[N]=(int(*)[N])malloc(sizeof(int)*N*N);//分配数组指针
	int (*b)[N]=(int(*)[N])malloc(sizeof(int)*N*N);
	int (*c)[N]=(int(*)[N])malloc(sizeof(int)*N*N);
	*/
	//在cpu上为数组a[]，b[]赋初始值
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			a[i][j]=i+j,b[i][j]=i*j+1;
			printf("a[%d][%d]=%4d\t b[%d][%d]=%4d  \t",i,j,a[i][j],i,j,b[i][j]);

		}
		if(i%1==0)printf("\n\n");
	}
	/*主机向设备内存传值（将a[]、b[]数组复制到GPU上）*/
	HANDLE_ERROR(cudaMemcpy(dev_a,a,N*N*sizeof(int),cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b,b,N*N*sizeof(int),cudaMemcpyHostToDevice));


	/*时间计时函数*/
	LARGE_INTEGER t1,t2,tc;//定义时间变量
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//


	/*此处两个参数，第一个参数表示设备在执行核函数是使用的并行线程块的数量。
	*例如kernel<<<256,1>>>表示将有256个线程块在GPU上运行。
	*/
	dim3 thread(N,N);//thread 仅是定义某个块内线程总数，最大为32,32*32 = 1024,正好是本机线程块包含最大线程数。

	//add<<<grid,1>>>(dev_a,dev_b,dev_c);
	add<<<1,thread>>>(dev_a,dev_b,dev_c);	//在GPU上将两数相加，返回
	//将数组c[]从GPU赋值到CPU
	HANDLE_ERROR(cudaMemcpy(c,dev_c,N*N*sizeof(int),cudaMemcpyDeviceToHost));


	printf("=========================================================================================");
	printf("result:\n");//显示 结果
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			printf(" c[%d][%d]=%4d\t",i,j,c[i][j]);

		}
		if(i%1==0)printf("\n\n");
	}

	QueryPerformanceCounter(&t2);//
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时

	/*
	free a;
	free b;
	free c;
	*/
	//释放GPU上分配的内存
	HANDLE_ERROR( cudaFree( dev_a ) );
	HANDLE_ERROR( cudaFree( dev_b ) );
	HANDLE_ERROR( cudaFree( dev_c ) );
	return 0;
}

#endif

//
//#include <stdio.h> 
//
//#include <stdlib.h> 
//
//#include <cuda_runtime.h> 
//
//
//
//#define ROWS 32 
//
//#define COLS 16 
//
//#define CHECK(res) if(res!=cudaSuccess){exit(-1);} 
//
//__global__ void Kerneltest(int **da, unsigned int rows, unsigned int cols) 
//
//{ 
//
//	unsigned int row = blockDim.y*blockIdx.y + threadIdx.y; 
//
//	unsigned int col = blockDim.x*blockIdx.x + threadIdx.x; 
//
//	if (row < rows && col < cols) 
//
//	{ 
//
//		da[row][col] = row*cols + col; 
//
//	} 
//
//} 
//
//
//
//int main(int argc, char **argv) 
//
//{ 
//
//	int **da = NULL; 
//
//	int **ha = NULL; 
//
//	int *dc = NULL; 
//
//	int *hc = NULL; 
//
//	cudaError_t res; 
//
//	int r, c; 
//
//	bool is_right=true; 
//
//
//
//	res = cudaMalloc((void**)(&da), ROWS*sizeof(int*));CHECK(res) 
//
//		res = cudaMalloc((void**)(&dc), ROWS*COLS*sizeof(int));CHECK(res) 
//
//		ha = (int**)malloc(ROWS*sizeof(int*)); 
//
//	hc = (int*)malloc(ROWS*COLS*sizeof(int)); 
//
//
//
//	for (r = 0; r < ROWS; r++) 
//
//	{ 
//
//		ha[r] = dc + r*COLS; 
//
//	} 
//
//	res = cudaMemcpy((void*)(da), (void*)(ha), ROWS*sizeof(int*), cudaMemcpyHostToDevice);CHECK(res) 
//
//		dim3 dimBlock(16,16); 
//
//	dim3 dimGrid((COLS+dimBlock.x-1)/(dimBlock.x), (ROWS+dimBlock.y-1)/(dimBlock.y)); 
//
//	Kerneltest<<<dimGrid, dimBlock>>>(da, ROWS, COLS); 
//
//	res = cudaMemcpy((void*)(hc), (void*)(dc), ROWS*COLS*sizeof(int), cudaMemcpyDeviceToHost);CHECK(res) 
//
//
//
//		for (r = 0; r < ROWS; r++) 
//
//		{ 
//
//			for (c = 0; c < COLS; c++) 
//
//			{ 
//
//				printf("%4d ", hc[r*COLS+c]); 
//
//				if (hc[r*COLS+c] != (r*COLS+c)) 
//
//				{ 
//
//					is_right = false; 
//
//				} 
//
//			} 
//
//			printf("\n"); 
//
//		} 
//
//		printf("the result is %s!\n", is_right? "right":"false"); 
//
//		cudaFree((void*)da); 
//
//		cudaFree((void*)dc); 
//
//		free(ha); 
//
//		free(hc); 
//
//		getchar(); 
//
//		return 0; 
//
//} 