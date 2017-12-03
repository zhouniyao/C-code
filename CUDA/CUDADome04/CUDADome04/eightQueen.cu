#if 0
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include"E:\�о���-2016��3��\CUDA\CUDA by Example.An Introduction to General-Purpose GPU Programming\cuda_by_example1\common\book.h"

#define N 4
#define M 100
//int (*QueenS)[N*M][N] = new int[N][N*M][N];
//�Ϸ����жϡ�����rowĳ������֮ǰ�����бȽϣ�Q[]�洢֮ǰ�кϷ���λ��
__device__ int isLegal(int* L, int row, int pos)
{
	int i;

	for(i=0; i<row; i++)
	{
		if(L[i] == -1)return 0;
		if(pos == L[i])	{return 0;}
		if(L[i] - pos == i - row)return 0;//���Խ���
		if(L[i] - pos == row - i)return 0;//б�Խ���
	}
	return 1;
}
//��������_������н�����ά����ĳ��
//void saveQueen(int Queen[][N], int cnt, int* dev_L)
//{	
//	int tmp[N] ={0};
//	int cnt1;
//	cudaMemcpy(tmp, dev_L, N*sizeof(int), cudaMemcpyDeviceToHost );
//	cudaMemcpy(&cnt1, &cnt, sizeof(int), cudaMemcpyDeviceToHost );
//	for(int i=0; i<N; i++)
//		Queen[cnt1][i] = tmp[i];	
//}
//��ӡ�ʺ�
void showQueen(int Queen[][N], int count)
{
	for(int i=0; i<=count; i++)
	{
		printf("��%d���⣺ ",i+1);
		for(int j=0; j<N; j++)
			printf("(%d,%d)",j,Queen[i][j]);
		printf("\n");
	}
}
__global__ void kernel(int* L, int* count)
{
	//int x = blockIdx.x;
	int x = threadIdx.x;
	L[0] = x;
	int i1, i2, i3;
	for(i1=0; i1<N; i1++ )
	{
		if(isLegal(L, 1, i1))
		{
			L[1] = i1;
			for(i2=0; i2<N; i2++)
			{
				if(isLegal(L, 2, i2))
				{
					L[2] = i2;
					for(i3=0; i3<N; i3++)
					{
						if(isLegal(L, 3, i3))
						{
							L[3] = i3;
							count[x]++;
							//saveQueen(QueenS[x], count[x], L);
						}
					}
				}
			}
		}
	}
}
int main(void)
{
	int* dev_L;
	int* dev_CNT;
	int myCount[N] = {0};
	int i,sum = 0;
	cudaMalloc((void**)&dev_CNT, M*sizeof(int));
	cudaMalloc((void**)&dev_L, N*sizeof(int));	
	//kernel<<<N, 1>>>(dev_L, dev_CNT);
	kernel<<<1, N>>>(dev_L, dev_CNT);
	cudaMemcpy(myCount, dev_CNT, N*sizeof(int), cudaMemcpyDeviceToHost );
	for(i=0; i<N; i++)
		sum += myCount[i];
	printf("sum= %d\n",sum);
}

#endif