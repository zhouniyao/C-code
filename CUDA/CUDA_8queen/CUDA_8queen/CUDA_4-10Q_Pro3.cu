#if 1
/*
*N皇后，利用CUDA将传统的串行算法——递归回溯，并行化，规划最初3层
*
*
*/
#include "E:\VisualStudio\CUDA\common\book.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

#define MAXSIZE 100 
//合法性判断——该row某列与其之前所有行比较，Q[]存储之前行合法列位置
__device__ int isLegal(int* L, int row, int pos )
{
	for(int i=0; i<row; i++)
	{
		if(L[i] == -1)return 0;
		if(pos == L[i])return 0;
		if(L[i] - pos == i - row)return 0;//正对角线
		if(L[i] - pos == row - i)return 0;//斜对角线
	}
	
	return 1;
}
//__device__ static int myCount = 0;//统计解个数
__device__ void findQueen(int* L, int row, int* count)
{
	int i;
	if(row == N)
	{
		return;
	}
	for(i=0; i<N; i++)
	{
		if(isLegal(L, row, i))
		{
			L[row] = i;//该行找到合法位置
			if(row == N-1)//递归到最后一行
			{
				(*count)++;
				//myCount++;
				L[row] = -1;//继续查找该行i列以后的位置
				//copyQueen
			}
			findQueen(L, row+1, count);//递归下一行
		}
	}
}
__device__ void Allocate(int* pa, int* pb, int* pc, int* count)
{
	int L[N] = {0};
	L[0] = *pa;
	L[1] = *pb;
	L[2] = *pc;
	findQueen(L, 3, count);
	
}

__global__ void kernel(int* part_sum, int* L)//*sum每个元素为部分解个数
{
	int z = threadIdx.z;
	int y = threadIdx.y;//块索引号
	int x = threadIdx.x;//线程索引号
	
	int a = y;
	int b = x;
	int c = z;
	
	//__shared__ int cache[N];//共享内存
	int tid = x + y*blockDim.x + z*blockDim.x*blockDim.x;
	//printf("(%d,%d,%d)\t",x,y,z);
	//printf("a,b,c = (%d, %d, %d)\n",a,b,c);
	int temp = 0;
	//if(tid < N*N)
	{		
		//if(a != b && a-b != 1 && b-a != 1)
		{	
			if((a != b && a-b != 1 && b-a != 1)&&(c != b && c-b != 1 && b-c != 1)&&(a != c && a-c != 2 && c-a != 2))
				Allocate(&a, &b, &c, &temp);
		}
		//printf("Temp = %d\n",temp);
		part_sum[tid] = temp;
	}
	//printf("PartSUM = %d\n",part_sum[tid]);
	//printf("Tid = %d\t",tid);
	//__syncthreads();
	//归约运算
	// i = (N)/2;
	//while(i != 0)
	//{
	//	if(x <= i)
	//		cache[x] += cache[x + i];
	//	__syncthreads();
	//	i /= 2;
	//}	
}

int main()
{
	LARGE_INTEGER t1,t2,tc,t3,t4,tq;//定义时间变量
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);//总执行时间start
	int j,i = 0;
	int sum = 0;//记录所有问题解个数
	int* partial_cnt = new int[N*N*N];//记录部分解
	int* L = new int[N];
	for(i=0; i<N; i++)
	{		
		L[i] = 0;
	}
	for(j=0; j<N*N*N; j++)		
			partial_cnt[j] = 0;//初始化
	int* dev_cnt;
	int* dev_L;
	cudaMalloc((void**)&dev_cnt,N*N*N*sizeof(int)); 
	cudaMalloc((void**)&dev_L,N*sizeof(int)); 
	cudaMemcpy(dev_cnt, partial_cnt,
                N*N*N*sizeof(int),
                cudaMemcpyHostToDevice);

	HANDLE_ERROR( cudaMemcpy(dev_L, L,
						N*sizeof(int),
						cudaMemcpyHostToDevice) );

	QueryPerformanceFrequency(&tq);//
	QueryPerformanceCounter(&t3);//核函数开始时间
	dim3 num_threads(N,N,N);
	kernel<<<1,num_threads>>>(dev_cnt,  dev_L);//执行核函数
	QueryPerformanceCounter(&t4);//核函数结束时间

	cudaMemcpy(partial_cnt, dev_cnt, N*N*N*sizeof(int),cudaMemcpyDeviceToHost);
	for(int k=0; k<N*N*N; k++)
	{
		//printf("Part = %d\n",partial_cnt[k]);
		sum += partial_cnt[k];	
	}
	printf("\n总共%d个解\n", sum);

	QueryPerformanceCounter(&t2);//总执行时间end
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时
	printf("Kernel Use Time:%f\n",(t4.QuadPart-t3.QuadPart)*1.0/tq.QuadPart);//打印核函数耗时
	delete[]partial_cnt;
	delete[]L;
	cudaFree(dev_cnt);
	cudaFree(dev_L);
	return 0;
}

#endif