#include<iostream>
using namespace std;

const int Lmax=256;
int count=0;//��¼�ڼ���
int b[Lmax][Lmax]={0};
int breakpoint[Lmax]={0};

int bmax(int *p,int **b,int i,int j)//�÷ֶ����bitλ
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
	b[i][j]=b;//b[i][j]�÷ֶ���ֽ���ֵ
	return b;
}
Compress(int n,int *p,int **s,int **b)
{
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			s[i][j]=0;
			bmax(p,b,i,j);//��ʼ��b[][]
			
		}
	return space(1,n,p,s);
}
int l[Lmax]={0};
int bb[Lmax]={0};
//p[]Ϊԭͼ����Ҷ�ֵ���ϣ�s[][]��¼�����ֶεĴ洢��С��l[i]�Ǹ÷ֶεĳ���(����)��b[i][j]�÷ֶ���ֽ���ֵ
int space(int i,int j,int *p,int **s)//i��j��ֹ��,�Զ�����
{
	if(s[i][j]>0)return s[i][j];
	if(i==j)
		{ l[i]=1;s[i][i]=b[i][i]+11;return ( s[i][i] );}
	//b[i]=bmax(p,i,j);
	l[i]=j-i;
	u=space(i,i,p,s)+(j-i)*b[i+1][j]+11;
	
	//l[i+1]=j-i;
	//b[i+1]=bit1;
	for(int k=i+1;k<j&&(j-k)<Lmax;k++)  //�����ж϶ε�
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
void record(int *l,int *point,int n)//point[]��¼���еĵ�
{
	for(int i=1,k=1;i<=n;)
	{
		if(l[i])point[k++]=i++;
	}
	count=k;
}


void Output(int n,int **s,int*point)//������Ž�
{
	cout<<"����ֵ"<<s[1][n]<<endl;
	cout<<"�ֶΣ�"<<endl;
	cout<<"["<<"1"<<"---";
	for(int i=1;i<=count;i++)
	{
		cout<<point[i]<<"]"<<"����ֽ���:"<<bb[point[i]]<<endl;
		cout<<"["<<point+1;

	}
	//cout<<l<<b
}