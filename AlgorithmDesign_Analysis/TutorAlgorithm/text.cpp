#include<iostream>
using namespace std;

const int Lmax=256;
int count=0;//��¼�ڼ���
const int header=11;//ͷ���ռbitλ
int b[Lmax][Lmax]={0};

int bmax(int *p,int i,int j)//�÷ֶ����bitλ
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
			s[i][j]=0;  //���ж���С�洢�ռ��ʼ��Ϊ0
			
			k[i][j]=0;
			
		}
	return space(1,n,p,s);//��������ֵ����С�洢�ռ�

}
//p[]Ϊԭͼ����Ҷ�ֵ���ϣ�s[][]��¼�����ֶεĴ洢��С��k[][]��¼�ϵ�λ��
int space(int i,int j,int *p,int**s,int **k)//i��j��ֹ��,�Զ�����
{
	if(s[i][j]>0)return s[i][j];
	if(i==j)
	{
	 s[i][i]=header+bmax(p,i,i);
	 
	 return s[i][i];
	}
	u=space(i,i,p,s)+(j-i)*bmax(p,i+1,j)+header;
	k[i][j]=i;//�ϵ���i���Ͽ�
	for(int k=i+1;k<j&&(j-k)<256;k++)//��������ж϶ε��С�����
	{
		t=space(i,k,p,s)+(j-k)*bmax(p,k+1,j)+header;
		if(u>t)
		{u=t;k[i][j]=k;} //��¼�ϵ�λ�ã�����¼��С�ռ�
	}
	s[i][j]=u;
	return u;
}