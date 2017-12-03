#if 0
/*
*N�ʺ�����CUDA����ͳ�Ĵ����㷨�����ݹ���ݣ����л����滮���2��
*
*
*/
#include "E:\VisualStudio\CUDA\common\book.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8
#define MAXSIZE 100 
//�Ϸ����жϡ�����rowĳ������֮ǰ�����бȽϣ�Q[]�洢֮ǰ�кϷ���λ��
__device__ int isLegal(int* L, int row, int pos )
{
	for(int i=0; i<row; i++)
	{
		if(L[i] == -1)return 0;
		if(pos == L[i])return 0;
		if(L[i] - pos == i - row)return 0;//���Խ���
		if(L[i] - pos == row - i)return 0;//б�Խ���
	}
	
	return 1;
}
//__device__ static int myCount = 0;//ͳ�ƽ����
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
			L[row] = i;//�����ҵ��Ϸ�λ��
			if(row == N-1)//�ݹ鵽���һ��
			{
				(*count)++;
				//myCount++;
				L[row] = -1;//�������Ҹ���i���Ժ��λ��
				//copyQueen
			}
			findQueen(L, row+1, count);//�ݹ���һ��
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

__global__ void kernel(int* part_sum, int* L)//*sumÿ��Ԫ��Ϊ���ֽ����
{
	int y = blockIdx.x;//��������
	int x = threadIdx.x;//�߳�������
	
	int a = y;
	int b = x;
	//__shared__ int cache[N];//�����ڴ�
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
	//��Լ����
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
	LARGE_INTEGER t1,t2,tc,t3,t4,tq;//����ʱ�����
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);//��ִ��ʱ��start
	int j,i = 0;
	int sum = 0;//��¼������������
	int* partial_cnt = new int[N*N];//��¼���ֽ�
	int* L = new int[N];
	for(i=0; i<N; i++)
	{		
		L[i] = 0;
	}
	for(j=0; j<N*N; j++)		
			partial_cnt[j] = 0;//��ʼ��
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
	//			kernel<<<1,1>>>(dev_cnt,  dev_L);//ִ�к˺���
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
	QueryPerformanceCounter(&t3);//�˺�����ʼʱ��
	kernel<<<N,N>>>(dev_cnt,  dev_L);//ִ�к˺���
	QueryPerformanceCounter(&t4);//�˺�������ʱ��

	cudaMemcpy(partial_cnt, dev_cnt, N*N*sizeof(int),cudaMemcpyDeviceToHost);
	for(int k=0; k<N*N; k++)
	{
		//printf("Part = %d\n",partial_cnt[k]);
		sum += partial_cnt[k];	
	}
	printf("\n�ܹ�%d����\n", sum);
	QueryPerformanceCounter(&t2);//��ִ��ʱ��end
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ��ʱ
	printf("Kernel Use Time:%f\n",(t4.QuadPart-t3.QuadPart)*1.0/tq.QuadPart);//��ӡ�˺�����ʱ
	return 0;
}

//�״θĽ���������
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
//			/*ʱ���ʱ����*/
//	LARGE_INTEGER t1,t2,tc;//����ʱ�����
//	QueryPerformanceFrequency(&tc);//
//	QueryPerformanceCounter(&t1);//
//	i = 0;
//
//	switch(N)
//	{
////===================4�ʺ�========================
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
////=================5�ʺ�==========================
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
//	//=================6�ʺ�==========================
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
//	//=================7�ʺ�==========================
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
//	//=================8�ʺ�==========================
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
//	//=================9�ʺ�==========================
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
//	//=================10�ʺ�==========================
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
//	//=================11�ʺ�==========================
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
//	//=================12�ʺ�==========================
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
//	//=================13�ʺ�==========================
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
//	//=================14�ʺ�==========================
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
//	//=================15�ʺ�==========================
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
//	//=================16�ʺ�==========================
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
//	QueryPerformanceCounter(&t2);//����ʱ��
//	printf("\n�ܹ�%d����\n", sum);
//
//	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ��ʱ
//	cudaFree(dev_cnt);
//	delete []L;
//	return 0;
//}
#endif