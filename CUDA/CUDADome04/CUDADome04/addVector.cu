#if 0
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include"E:\�о���-2016��3��\CUDA\CUDA by Example.An Introduction to General-Purpose GPU Programming\cuda_by_example1\common\book.h"
#define N (32*32+133)  //ÿ��block������thread��Ŀ����max threads per block
//�����������߳������ڻ����ڲ��涨�����ᷢ��ʲô����
//��ֹ�˺������У���ΪGPU�����Ƶ��ڴ������ƣ�����ǿ�н�������Υ���ڴ���ʹ���Ľ��̡�
__global__ void add(int* dev_a, int* dev_b, int* dev_c)
{
	int index = blockIdx.x*blockDim.x + threadIdx.x;//blockDim.x��������߳̿���ÿһά���߳�����,gridDim���桾�̸߳���ÿһά���߳̿��������gridDim�Ƕ�ά�ģ���blockDim����ά��
	//int index = blockIdx.x;//����N��block��ÿ��block����һ��thread
	//int index = threadIdx.x;//���������N��thread
	//if����while���ɴ��������С���������
	while(index < N)
	{
		dev_c[index] = dev_a[index] + dev_b[index];
		index += gridDim.x*blockDim.x;//������ÿ���߳̿��е��߳����������̸߳����߳̿������
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