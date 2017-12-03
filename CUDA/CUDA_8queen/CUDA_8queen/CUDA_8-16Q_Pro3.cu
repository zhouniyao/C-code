#if 0
#include "E:\VisualStudio\CUDA\common\book.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10

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
__device__ void Allocate(int* pa, int* pb, int* pc, int* count)
{
	int L[N] = {0};
	L[0] = *pa;
	L[1] = *pb;
	L[2] = *pc;
	findQueen(L, 3, count);
	
}

__global__ void kernel(int* part_sum, int* L)//*sumÿ��Ԫ��Ϊ���ֽ����
{
	int z = threadIdx.z +  blockIdx.z * blockDim.z;
	int y = threadIdx.y +  blockIdx.y * blockDim.y;//��������
	int x = threadIdx.x +  blockIdx.x * blockDim.x;//�߳�������
	
	int a = y;
	int b = x;
	int c = z;
	
	//__shared__ int cache[N];//�����ڴ�
	int tid = x + y*blockDim.x + z*blockDim.x*blockDim.x;
	//printf("(%d,%d,%d)\t",x,y,z);
	//printf("a,b,c = (%d, %d, %d)\n",a,b,c);
	int temp = 0;
	if(tid < N*N*N)
	{		
		//if(a != b && a-b != 1 && b-a != 1)
		{	
			if((a != b && a-b != 1 && b-a != 1)&&(c != b && c-b != 1 && b-c != 1)&&(a != c && a-c != 2 && c-a != 2))
				Allocate(&a, &b, &c, &temp);
		}
		//printf("Temp = %d\n",temp);
		
	}
	part_sum[tid] = temp;
	//printf("PartSUM = %d\n",part_sum[tid]);
	//printf("Tid = %d\t",tid);
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
	int j,i = 0;
	int sum = 0;//��¼������������
	int* partial_cnt = new int[N*N*N];//��¼���ֽ�
	int* L = new int[N];
	for(i=0; i<N; i++)
	{		
		L[i] = 0;
	}
	for(j=0; j<N*N*N; j++)		
			partial_cnt[j] = 0;//��ʼ��
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
	//dim3 num_threads(N,N,N);
	//kernel<<<1,num_threads>>>(dev_cnt,  dev_L);//ִ�к˺���
	dim3 num_blocks((N+7)/8);
	dim3 num_threads(8,8,8);
	kernel<<<num_blocks,num_threads>>>(dev_cnt,  dev_L);//ִ�к˺���
	cudaMemcpy(partial_cnt, dev_cnt, N*N*N*sizeof(int),cudaMemcpyDeviceToHost);
	for(int k=0; k<N*N*N; k++)
	{
		//printf("Part = %d\n",partial_cnt[k]);
		sum += partial_cnt[k];	
	}
	printf("\n�ܹ�%d����\n", sum);
	delete[]partial_cnt;
	delete[]L;
	cudaFree(dev_cnt);
	cudaFree(dev_L);
	return 0;
}

#endif