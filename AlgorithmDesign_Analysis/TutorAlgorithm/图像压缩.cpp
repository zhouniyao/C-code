#include<iostream>
using namespace std;
/*
找到每一段的长度l[],每段最长的bit位b[],得出最低的存储空间s[]。
*/
void Compress(int n,int p[],int s[],int l[],int b[])
{
	int Lmax=256,header=11;
	s[0]=0;
	for(int i=1;i<=n;i++)
	{
		b[i]=length(p[i]);//计算p[i]的bit位
		int bmax=b[i];
		s[i]=s[i-1]+bmax;    
		l[i]=1;
		for(int j=2;j<=i&&j<=Lmax;j++)//找到一个最佳组合段,使得s[i]最小。
		{
			if(bmax<b[i-j+1])bmax=b[i-j+1];//每次循环后与前一个b[i-1]比较大小，并取最大的一个为该段的b[i]值。
			if(s[i]>s[i-j]+j*bmax)
			{
				s[i]=s[i-j]+j*bmax;//(i-j)+j=i,总数为i的整个段的存储空间大小。
				l[i]=j;
			}
			s[i]+=header;
		}
	}
}

int length(int i)//得出i为多少bit位
{
	int k=1;i=i/2;
	while(i>0){k++;i=i/2;}//while(i>0){k++;i=i>>2;}//右移一个bit位
	return k;
}

void Traceback(int n,int & i,int s[],int l[])
{
	if(n==0)return;
	Traceback(n-l[n],i,s,l);
	s[i++]=n-l[n];
}
 void Output(int s[],int l[],int b[],int n)
 {
	cout<<"the optimal value is"<<s[n]<<endl;
	int m=0;
	Traceback(n,m,s,l);
	s[m]=n;
	cout<<"Decompose into"<<m<<"segments"<<endl;
	for(int j=1;j<=m;j++){l[j]=l[s[j]];b[j]=b[[s[j]];}
	for(int j=1;j<=m;j++)
		cout<<l[j]<<" "<<b[j]<<endl;
 }