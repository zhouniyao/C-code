#include<iostream>
using namespace std;
template <typename T>
void Combine(T *a,int n,int m,int *b,const int M);
const int M=7;//彩票打印数，通常固定为7位，注M<=N
const int N=9;//购买时，选择的预中奖号码
int count=0;//记录彩票打印的数量，方便计算购买票数与金额

template <typename T>
void Combine(T *a,int n,int m,int *b,const int M){
	for(int i=n;i>m-1;i--)
	{
		b[m-1]=i-1;//记录下选择的数据位
		if(m>1)
		{
			Combine(a,i-1,m-1,b,M);//Combine(N,M)选定好后半段，再递归查找Combine(N-1,M-1)
		}
		else  //m==1,保存数据位的数组已满，打印出来
		{
			for(int j=M-1;j>=0;j--)
			{
				cout<<a[b[j]]<<" ";
			}
			count++;
			cout<<endl;
		}
	}
}
int main()
{
	int a[]={7,8,9,12,18,22,23,32,16};
	int b[M];
	Combine<int>(a,N,M,b,M);
	cout<<endl;
	cout<<count;
	return 0;
}