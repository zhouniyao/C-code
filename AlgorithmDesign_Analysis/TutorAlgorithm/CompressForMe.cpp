#include<iostream>
using namespace std;

const int Lmax=256;
int count=0;//记录第几段
int b[Lmax][Lmax]={0};
int breakpoint[Lmax]={0};

int bmax(int *p,int **b,int i,int j)//该分段最大bit位
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
	b[i][j]=b;//b[i][j]该分段最长字节码值
	return b;
}
Compress(int n,int *p,int **s,int **b)
{
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			s[i][j]=0;
			bmax(p,b,i,j);//初始化b[][]
			
		}
	return space(1,n,p,s);
}
int l[Lmax]={0};
int bb[Lmax]={0};
//p[]为原图像个灰度值集合，s[][]记录各个分段的存储大小，l[i]是该分段的长度(数量)、b[i][j]该分段最长字节码值
int space(int i,int j,int *p,int **s)//i、j起止点,自顶向下
{
	if(s[i][j]>0)return s[i][j];
	if(i==j)
		{ l[i]=1;s[i][i]=b[i][i]+11;return ( s[i][i] );}
	//b[i]=bmax(p,i,j);
	l[i]=j-i;
	u=space(i,i,p,s)+(j-i)*b[i+1][j]+11;
	
	//l[i+1]=j-i;
	//b[i+1]=bit1;
	for(int k=i+1;k<j&&(j-k)<Lmax;k++)  //查找中断段点
	{
		//int b[k+1]=bmax(p,k+1,j);
		t=space(i,k,p,s)+(j-k)*b[k+1][j]+11;
		if(t<u)
		{u=t;l[k+1]=j-k;bb[k+1]=b[k+1][j]}
	}
	s[i][j]=u;
	return u;
}

//int count=0;
void record(int *l,int *point,int n)//point[]记录所有的点
{
	for(int i=1,k=1;i<=n;)
	{
		if(l[i])point[k++]=i++;
	}
	count=k;
}


void Output(int n,int **s,int*point)//输出最优解
{
	cout<<"最优值"<<s[1][n]<<endl;
	cout<<"分段："<<endl;
	cout<<"["<<"1"<<"---";
	for(int i=1;i<=count;i++)
	{
		cout<<point[i]<<"]"<<"最大字节码:"<<bb[point[i]]<<endl;
		cout<<"["<<point+1;

	}
	//cout<<l<<b
}