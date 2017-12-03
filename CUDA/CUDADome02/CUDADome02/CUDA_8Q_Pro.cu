#if 0
#include "E:\VisualStudio\CUDA\common\book.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

#define MAXSIZE 100
//合法性判断——该row某列与其之前所有行比较，Q[]存储之前行合法列位置
__device__ int isLegal(int L[], int row, int pos )
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
			if(row == N-1)//所有行都查找完毕
			{
				(*count)++;
				//myCount++;
				L[row] = -1;//继续查找该行i列以后的位置
				//copyQueen
			}
			findQueen(L, row+1, count);
		}
	}
}
__global__ void kernel(int* part_sum)//*sum每个元素为部分解个数
{
	int L[N];
	int x = threadIdx.x;//线程索引
	//__shared__ int cache[N];//共享内存
	int temp = 0;
	if(x < N)
	{
		L[0] = x;
		findQueen(L, 1, &temp);	//从1-10
		printf("partJie = %d\n",temp);
	}
	part_sum[x] = temp;
	__syncthreads();
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
	int i=0,sum=0;
	int count[N] = {0};
	int* dev_cnt;


	cudaMalloc((void**)&dev_cnt,N*sizeof(int)); 
	cudaMemcpy(dev_cnt, count,
                              N*sizeof(int),
                              cudaMemcpyHostToDevice);
	//HANDLE_ERROR( cudaMemcpy(dev_L, L,
 //                             N*sizeof(int),
 //                             cudaMemcpyHostToDevice) );
			/*时间计时函数*/
	LARGE_INTEGER t1,t2,tc;//定义时间变量
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//

	kernel<<<1,N>>>(dev_cnt);
	cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
	
	QueryPerformanceCounter(&t2);//结束时间
	for(int i=0; i<N; i++)
		sum += count[i];

	printf("\n总共%d个解\n", sum);

	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时
	cudaFree(dev_cnt);
	return 0;
}
#endif