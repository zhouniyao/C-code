#if 1
#include "E:\VisualStudio\CUDA\common\book.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

#define MAXSIZE 100
//�Ϸ����жϡ�����rowĳ������֮ǰ�����бȽϣ�Q[]�洢֮ǰ�кϷ���λ��
__device__ int isLegal(int L[], int row, int pos )
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
			if(row == N-1)//�����ж��������
			{
				(*count)++;
				//myCount++;
				L[row] = -1;//�������Ҹ���i���Ժ��λ��
				//copyQueen
			}
			findQueen(L, row+1, count);
		}
	}
}
__global__ void kernel(int* part_sum, int* L)//*sumÿ��Ԫ��Ϊ���ֽ����
{
	int x = threadIdx.x;//�߳�����
	//__shared__ int cache[N];//�����ڴ�
	int temp = 0;
	if(x < N)
	{
		if(isLegal(L, 1, x))
		{
			L[1] = x;		
			findQueen(L, 2, &temp);	//��1-10
		}
		printf("partJie = %d\n",temp);
	}
	part_sum[x] = temp;
	__syncthreads();
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
	int i=0,sum=0;
	int count[N] = {0};
	int* L = new int[N];
	for(i=0; i<N; i++)
		L[i] = 0;
	int* dev_cnt;
	int* dev_L;
	cudaMalloc((void**)&dev_cnt,N*sizeof(int)); 
	cudaMalloc((void**)&dev_L,N*sizeof(int)); 
	cudaMemcpy(dev_cnt, count,
                N*sizeof(int),
                cudaMemcpyHostToDevice);

	//HANDLE_ERROR( cudaMemcpy(dev_L, L,
 //                             N*sizeof(int),
 //                             cudaMemcpyHostToDevice) );
			/*ʱ���ʱ����*/
	LARGE_INTEGER t1,t2,tc;//����ʱ�����
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//
//	for(i=0; i<N; i++)
	{
		L[0] = 5;
		cudaMemcpy(dev_L, L,
                N*sizeof(int),
                cudaMemcpyHostToDevice);
		kernel<<<1,N>>>(dev_cnt, dev_L);
	
		cudaMemcpy(count, dev_cnt, N*sizeof(int),cudaMemcpyDeviceToHost);
		for(i=0; i<N; i++)
			sum += count[i];
	}
	QueryPerformanceCounter(&t2);//����ʱ��


	printf("\n�ܹ�%d����\n", sum);

	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ��ʱ
	cudaFree(dev_cnt);
	delete []L;
	return 0;
}
#endif