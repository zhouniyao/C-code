#if 0
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
#define N 100

void	add(int (*a)[N],int (*b)[N],int (*c)[N]);
//void	add(int (&a)[N][N],int (&b)[N][N],int (&c)[N][N]);//��ά��������

int main()
{
	int a[N][N],b[N][N],c[N][N];
	
	//
	//int (*a)[N]=new int[N][N];
	//int (*b)[N]=new int[N][N];
	//int (*c)[N]=new int[N][N];
	
	//
	//int a[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);//����,Ϊʲô��a��ָ�볣������������ֵ
	//int b[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);
	//int c[N][N]=(int(*)[N])malloc(sizeof(int)*N*N);
	//
	
	//int (*a)[N]=(int(*)[N])malloc(sizeof(int)*N*N);//���������ָ�룬��ȷ
	//int (*b)[N]=(int(*)[N])malloc(sizeof(int)*N*N);
	//int (*c)[N]=(int(*)[N])malloc(sizeof(int)*N*N);
	
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			a[i][j]=i+j,b[i][j]=i*j;
			printf("a[%d][%d]=%4d\t b[%d][%d]=%4d  \t",i,j,a[i][j],i,j,b[i][j]);
			
		}
		if(i%1==0)printf("\n\n");
	}
	/*ʱ���ʱ����*/
	LARGE_INTEGER t1,t2,tc;//����ʱ�����
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//
	
	add(a,b,c);
	
	
	printf("=========================================================================================\n");
	printf("result:\n");
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
}

//void	add(int (&a)[N][N],int (&b)[N][N],int (&c)[N][N])//��ά���������
//{
//		for(int i=0;i<N;i++)
//			for(int j=0;j<N;j++)
//				c[i][j]=a[i][j]+b[i][j];
//}
void	add(int (*a)[N],int (*b)[N],int (*c)[N])  //��ά����ָ��
{
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)//һ�����ߵȼ�
				c[i][j]=a[i][j]+b[i][j]; 
				//*(c[i]+j) = *(a[i]+j) + *(b[i]+j);
				//*(*(c+i)+j) = *(*(a+i)+j) + *(*(b+i)+j);
}

#endif