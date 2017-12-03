#define N 8
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int Q[N+1],count;
void aQueen()
{
	for(int i=1;i<=N;i++)
		Q[i]=(int)(double)((rand()/RAND_MAX)*(N))+1;
}
bool LV()//¼ì²éÊÇ·ñ³åÍ»
{
	aQueen();
	for(int i=1;i<=N-1;i++)
		for(int j=i+1;j<=N;j++)
		{
			if(Q[i]==Q[j]||abs(Q[i]-i)==abs(Q[j]-j))return true;
		}
	return false;
}
void print()
{
	printf("\n");
	for(int i=1;i<=N;i++)
	{
		for(int k=1;k<Q[i];k++)
			printf(".");
		printf("Q");
		for(k=k+1;k<=N;k++)
			printf(".");
		printf("\n");
	}
}
void haha()
{
	while(LV())printf("%d\t",++count);
	print();
}
void main()
{
	srand((unsigned)time(NULL));
	haha();
}