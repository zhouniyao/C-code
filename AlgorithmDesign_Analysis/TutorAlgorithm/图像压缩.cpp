#include<iostream>
using namespace std;
/*
�ҵ�ÿһ�εĳ���l[],ÿ�����bitλb[],�ó���͵Ĵ洢�ռ�s[]��
*/
void Compress(int n,int p[],int s[],int l[],int b[])
{
	int Lmax=256,header=11;
	s[0]=0;
	for(int i=1;i<=n;i++)
	{
		b[i]=length(p[i]);//����p[i]��bitλ
		int bmax=b[i];
		s[i]=s[i-1]+bmax;    
		l[i]=1;
		for(int j=2;j<=i&&j<=Lmax;j++)//�ҵ�һ�������϶�,ʹ��s[i]��С��
		{
			if(bmax<b[i-j+1])bmax=b[i-j+1];//ÿ��ѭ������ǰһ��b[i-1]�Ƚϴ�С����ȡ����һ��Ϊ�öε�b[i]ֵ��
			if(s[i]>s[i-j]+j*bmax)
			{
				s[i]=s[i-j]+j*bmax;//(i-j)+j=i,����Ϊi�������εĴ洢�ռ��С��
				l[i]=j;
			}
			s[i]+=header;
		}
	}
}

int length(int i)//�ó�iΪ����bitλ
{
	int k=1;i=i/2;
	while(i>0){k++;i=i/2;}//while(i>0){k++;i=i>>2;}//����һ��bitλ
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