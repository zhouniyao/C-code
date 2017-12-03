#include <stdio.H>
#include <math.h>
#define N 14
int x[N+1];
int count;

void output()
{
	int i,j ;
	
	printf("%d:\n",++count);
	for(i=1; i<=N; i++)
	{
		for(j=1; j<x[i]; j++)
			printf(".");
		printf("Q\n");
	}
	
}
bool conflect(int i,int j)
{
	int p,q;

	for(p=1; p<i; p++)
	{
		q=x[p];
		if(j==q || abs(q-j)==abs(p-i))
			return true;
	}
	x[i]=j;
	return false;
}

void backtrack(int i)
{
	int j;

	if(i>N)
	{
		output();
		return;
	}

	for(j=1; j<=N; j++)
		if( ! conflect(i,j) )
			backtrack(i+1);
}
void main()
{
	count=0;
	backtrack(1);
	printf("\nSum=%d\n",count);
}

