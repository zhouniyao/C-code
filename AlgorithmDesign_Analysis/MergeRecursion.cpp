#include<iostream>
using namespace std;

template <typename T>
void Combine(T a[],int n,int m,int b[],const int M){
	for(int i=n;i>=m;i--)
	{
		b[m-1]=i-1;//ѡȡ��ѡ��a[]��������������b[]��¼�����±�
		if(m>1)Combine(a,i-1,m-1,b,M);//��n-1����ѡm-1��Ԫ��
		else{    //m==1ʱ��û��Ԫ�ؿ�ѡ��һ������Ѿ���ɣ������
			for(int j=M-1;j>=0;j--)cout<<a[b[j]];count++;
			cout<<endl;
		}
	}
}





*********************************************************************


#include<iostream>
using namespace std;
template <typename T>
void Combine(T *a,int n,int m,int *b,const int M);
const int M=7;//��Ʊ��ӡ����ͨ���̶�Ϊ7λ��עM<=N
const int N=9;//����ʱ��ѡ���Ԥ�н�����
int count=0;//��¼��Ʊ��ӡ��������������㹺��Ʊ������

int main()
{
	int a[]={7,8,9,12,18,22,23,32,16};
	int b[M];
	Combine<int>(a,N,M,b,M);
	cout<<endl;
	cout<<count;
	return 0;
}

template <typename T>
void Combine(T *a,int n,int m,int *b,const int M){
	for(int i=n;i>m-1;i--)
	{
		b[m-1]=i-1;//��¼��ѡ�������λ
		if(m>1)
		{
			Combine(a,i-1,m-1,b,M);//Combine(N,M)ѡ���ú��Σ��ٵݹ����Combine(N-1,M-1)
		}
		else  //m==1,��������λ��������������ӡ����
		{
			for(int j=M-1;j>=0;j--)
			{
				cout<<a[b[j]]<<" ";
			}
			cout<<endl;count++;
		}
	}
}
