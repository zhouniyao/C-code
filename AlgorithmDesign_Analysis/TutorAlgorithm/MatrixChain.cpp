#include <iostream>
using namespace std;

void MatrixChain(int *p,int n,int **m,int **s)//m记录最优值，s记录断点
{
	for(int i=1;i<=n;i++)m[i][i]=0;
	for(int r=2;r<=n;r++)
		for(int i=1;i<=n-r+1;i++){
			int j=i+r-1;
			m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];//m[i][j]=m[i][i]+m[i+1][j]+p[i-1]*p[i]*p[j];   m[i][i]=0
			s[i][j]=i;
			for(int k=i+1;k<j;k++){   //找出最佳断点
				int t=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(t<m[i][j])
				{
					m[i][j]=t;s[i][j]=k;
				}
			}
		}
}
void Traceback(int i,int j,int **s)
{
	if(i==j)return;
	Traceback(i,s[i][j],s);
	Traceback(s[i][j]+1,j,s);
	cout<<"Multiply A"<<i<<","<<s[i][j];
	cout<<"and A"<<(s[i][j]+1)<<","<<j<<endl;
}