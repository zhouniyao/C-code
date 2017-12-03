#if 0
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"../common/book.h"
using namespace std;
#define N 32        //ÿ����  ���ֻ��ȡ32���̣߳��ɱ���Ӳ����������

//void	add(int (*a)[N],int (*b)[N],int (*c)[N]);
__global__ void add(int (*a)[N],int (*b)[N],int (*c)[N])
{
	/*��ȻGPU�����к˺�����N����������ô����ڴ�����֪��
	*��ǰ�������е����ĸ��߳̿飿
	*���趨��blockIdx������һ�����ñ�����������ֵ���ǵ�ǰִ���豸������߳̿��������
	*
	*/
	//int j=blockIdx.x;  //����λ����������������ݣ���0��ʼ
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


	int a[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);//����,Ϊʲô��a��ָ�볣������������ֵ
	int b[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);
	int c[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);
	*/
	/*
	int (*a)[N]=(int(*)[N])malloc(sizeof(int)*N*N);//��������ָ��
	int (*b)[N]=(int(*)[N])malloc(sizeof(int)*N*N);
	int (*c)[N]=(int(*)[N])malloc(sizeof(int)*N*N);
	*/
	//��cpu��Ϊ����a[]��b[]����ʼֵ
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			a[i][j]=i+j,b[i][j]=i*j+1;
			printf("a[%d][%d]=%4d\t b[%d][%d]=%4d  \t",i,j,a[i][j],i,j,b[i][j]);

		}
		if(i%1==0)printf("\n\n");
	}
	/*�������豸�ڴ洫ֵ����a[]��b[]���鸴�Ƶ�GPU�ϣ�*/
	HANDLE_ERROR(cudaMemcpy(dev_a,a,N*N*sizeof(int),cudaMemcpyHostToDevice));
	HANDLE_ERROR(cudaMemcpy(dev_b,b,N*N*sizeof(int),cudaMemcpyHostToDevice));


	/*ʱ���ʱ����*/
	LARGE_INTEGER t1,t2,tc;//����ʱ�����
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//


	/*�˴�������������һ��������ʾ�豸��ִ�к˺�����ʹ�õĲ����߳̿��������
	*����kernel<<<256,1>>>��ʾ����256���߳̿���GPU�����С�
	*/
	dim3 thread(N,N);//thread ���Ƕ���ĳ�������߳����������Ϊ32,32*32 = 1024,�����Ǳ����߳̿��������߳�����

	//add<<<grid,1>>>(dev_a,dev_b,dev_c);
	add<<<1,thread>>>(dev_a,dev_b,dev_c);	//��GPU�Ͻ�������ӣ�����
	//������c[]��GPU��ֵ��CPU
	HANDLE_ERROR(cudaMemcpy(c,dev_c,N*N*sizeof(int),cudaMemcpyDeviceToHost));


	printf("=========================================================================================");
	printf("result:\n");//��ʾ ���
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			printf(" c[%d][%d]=%4d\t",i,j,c[i][j]);

		}
		if(i%1==0)printf("\n\n");
	}

	QueryPerformanceCounter(&t2);//
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ��ʱ

	/*
	free a;
	free b;
	free c;
	*/
	//�ͷ�GPU�Ϸ�����ڴ�
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