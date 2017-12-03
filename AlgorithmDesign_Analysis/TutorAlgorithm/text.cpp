#include<iostream>
using namespace std;

const int Lmax=256;
int count=0;//记录第几段
const int header=11;//头标记占bit位
int b[Lmax][Lmax]={0};

int bmax(int *p,int i,int j)//该分段最大bit位
{
	int max=p[i],b;
	while(++i<=j)
	{
		if(p[i]>max)max=p[i];
	}
	do
	{
		b++;
	}while(max>>=2);
	return b;
}



int Compress(int *p,int n,int**s,int **k)
{	
	
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			s[i][j]=0;  //所有段最小存储空间初始化为0
			
			k[i][j]=0;
			
		}
	return space(1,n,p,s);//计算最优值，最小存储空间

}
//p[]为原图像个灰度值集合，s[][]记录各个分段的存储大小，k[][]记录断点位置
int space(int i,int j,int *p,int**s,int **k)//i、j起止点,自顶向下
{
	if(s[i][j]>0)return s[i][j];
	if(i==j)
	{
	 s[i][i]=header+bmax(p,i,i);
	 
	 return s[i][i];
	}
	u=space(i,i,p,s)+(j-i)*bmax(p,i+1,j)+header;
	k[i][j]=i;//断点在i身后断开
	for(int k=i+1;k<j&&(j-k)<256;k++)//查找最佳中断段点中···
	{
		t=space(i,k,p,s)+(j-k)*bmax(p,k+1,j)+header;
		if(u>t)
		{u=t;k[i][j]=k;} //记录断点位置，并记录最小空间
	}
	s[i][j]=u;
	return u;
}