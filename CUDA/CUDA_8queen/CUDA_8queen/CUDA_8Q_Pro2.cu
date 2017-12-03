#if 0
/*
*N皇后，利用CUDA将传统的串行算法——递归回溯，并行化，规划最初2层
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
__device__ void Allocate(int* pa, int* pb, int* count)
{
	int L[N] = {0};
	L[0] = *pa;
	L[1] = *pb;
	findQueen(L, 2, count);
	
}

__global__ void kernel(int* part_sum, int* L)//*sum每个元素为部分解个数
{
	int y = blockIdx.x;//块索引号
	int x = threadIdx.x;//线程索引号
	
	int a = y;
	int b = x;
	//__shared__ int cache[N];//共享内存
	int tid = x+y*blockDim.x;
	int temp = 0;
	//if(tid < N*N)
	{		
		if(a != b && a-b != 1 && b-a != 1)
		{			
			Allocate(&a, &b, &temp);
		}
		//printf("Temp = %d\n",temp);
		part_sum[tid] = temp;
	}
	//printf("PartSUM = %d\n",part_sum[tid]);
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
	int* partial_cnt = new int[N*N];//记录部分解
	int* L = new int[N];
	for(i=0; i<N; i++)
	{		
		L[i] = 0;
	}
	for(j=0; j<N*N; j++)		
			partial_cnt[j] = 0;//初始化
	int* dev_cnt;
	int* dev_L;
	cudaMalloc((void**)&dev_cnt,N*N*sizeof(int)); 
	cudaMalloc((void**)&dev_L,N*sizeof(int)); 
	cudaMemcpy(dev_cnt, partial_cnt,
                N*sizeof(int),
                cudaMemcpyHostToDevice);


	//for(i=0; i<N; i++)
	//{
	//	L[0] = i;
	//	for(j=0; j<N; j++)
	//	{
	//		if(j != L[0] && L[0]-j != 1 && j-L[0] != 1)
	//		{
	//			L[1] = j;
	//			HANDLE_ERROR( cudaMemcpy(dev_L, L,
	//								N*sizeof(int),
	//								cudaMemcpyHostToDevice) );
	//			kernel<<<1,1>>>(dev_cnt,  dev_L);//执行核函数
	//			cudaMemcpy(partial_cnt, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
	//			for(int k=0; k<N; k++)
	//				sum += partial_cnt[k];	
	//		}
	//	}
	//}

	HANDLE_ERROR( cudaMemcpy(dev_L, L,
						N*sizeof(int),
						cudaMemcpyHostToDevice) );
	QueryPerformanceFrequency(&tq);//
	QueryPerformanceCounter(&t3);//核函数开始时间
	kernel<<<N,N>>>(dev_cnt,  dev_L);//执行核函数
	QueryPerformanceCounter(&t4);//核函数结束时间

	cudaMemcpy(partial_cnt, dev_cnt, N*N*sizeof(int),cudaMemcpyDeviceToHost);
	for(int k=0; k<N*N; k++)
	{
		//printf("Part = %d\n",partial_cnt[k]);
		sum += partial_cnt[k];	
	}
	printf("\n总共%d个解\n", sum);
	QueryPerformanceCounter(&t2);//总执行时间end
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时
	printf("Kernel Use Time:%f\n",(t4.QuadPart-t3.QuadPart)*1.0/tq.QuadPart);//打印核函数耗时
	return 0;
}

//首次改进——有误
//int main()
//{
//	int i=0,sum=0;
//	int count[N] = {0};
//	int* L = new int[N];
//	for(i=0; i<N; i++)
//		L[i] = 0;
//	int* dev_cnt;
//	int* dev_L;
//	cudaMalloc((void**)&dev_cnt,N*sizeof(int)); 
//	cudaMalloc((void**)&dev_L,N*sizeof(int)); 
//	cudaMemcpy(dev_cnt, count,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//
//	//HANDLE_ERROR( cudaMemcpy(dev_L, L,
// //                             N*sizeof(int),
// //                             cudaMemcpyHostToDevice) );
//			/*时间计时函数*/
//	LARGE_INTEGER t1,t2,tc;//定义时间变量
//	QueryPerformanceFrequency(&tc);//
//	QueryPerformanceCounter(&t1);//
//	i = 0;
//
//	switch(N)
//	{
////===================4皇后========================
//	case 4:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//
////=================5皇后==========================
//		case 5:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//	//=================6皇后==========================
//		case 6:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//	//=================7皇后==========================
//		case 7:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//	break;
//	//=================8皇后==========================
//		case 8:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//	//=================9皇后==========================
//		case 9:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 8;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//	break;
//	//=================10皇后==========================
//		case 10:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 8;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 9;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//	//=================11皇后==========================
//		case 11:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 8;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 9;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 10;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//	break;
//	//=================12皇后==========================
//		case 12:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 8;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 9;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 10;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//								L[0] = 11;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//	//=================13皇后==========================
//		case 13:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 8;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 9;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 10;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 11;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 12;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//	//=================14皇后==========================
//		case 14:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 8;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 9;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 10;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 11;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 12;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 13;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//	//=================15皇后==========================
//		case 15:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 8;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 9;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 10;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 11;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 12;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 13;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 14;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//	//=================16皇后==========================
//		case 16:
//		L[0] = 0;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 1;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//		
//				L[0] = 2;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//				L[0] = 3;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 4;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 5;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 6;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 7;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 8;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 9;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//						L[0] = 10;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//		
//								L[0] = 11;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 12;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 13;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//								L[0] = 14;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//										L[0] = 15;
//		cudaMemcpy(dev_L, L,
//                N*sizeof(int),
//                cudaMemcpyHostToDevice);
//		kernel<<<1,N>>>(dev_cnt, dev_L);
//		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
//		for(i=0; i<N; i++)
//			sum += count[i];
//
//	break;
//
//	}
//	QueryPerformanceCounter(&t2);//结束时间
//	printf("\n总共%d个解\n", sum);
//
//	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时
//	cudaFree(dev_cnt);
//	delete []L;
//	return 0;
//}
#endif