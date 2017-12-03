#include<iostream>
using namespace std;
const int L=10;//Ĭ�����鳤��

int *b=new int[L];


//template <typename T>
//T *b=new T[L];//��ʱ����

template <typename T>
void Mergesort(T a[],int left,int right)//�鲢����,Asc
{
	if(left<right)
	{
		int mid=(left+right)/2;
		Mergesort(a,left,mid);
		Mergesort(a,mid+1,right);
		Merge(a,b,left,mid,right);
		copy(a,b,left,right);
	}
}
template <typename T>
void copy(T a[],T *b,int left,int right)//���鿽��
{
	//for(int i=left;i<right+1;i++)a[i]=b[i];
	for(int i=left;i<right+1;a[i]=b[i],i++);
}

template <typename T>
void Merge(T a[],T *b,int left,int mid,int right)//��a����ǰ�󲿷��ź��򣬴���b����
{
	//int step=right-mid;
	int k,i,j;
	j=mid+1;
	k=i=left;
	while(i<mid+1&&j<right+1)
	{
		/*��ȷ
		while(a[i]<a[j]&&(i<mid+1&&j<right+1))
		{
			b[k]=a[i];
			k++;i++;
		}
		while(a[i]>a[j]&&(i<mid+1&&j<right+1))
		{
			b[k]=a[j];
			k++;j++;
		}
		*/
		//while(a[j]>a[i]&&(i<mid+1&&j<right+1))b[k++]=a[i++];
		//while(a[j]<a[i]&&(i<mid+1&&j<right+1))b[k++]=a[j++];
		//��ȷ
		if(a[i]<a[j])b[k]=a[i],i++;
		else
			b[k]=a[j],j++;
		k++;
		
	}
	while(i<mid+1)b[k++]=a[i++];
	while(j<right+1)b[k++]=a[j++];
}


template<class T>
void printaa(T a[],int n)//��ӡ����
{
	for(int i=0;i<n;i++)printf("%4d",a[i]);
}

int main()
{
	int a[]={8,7,9,5,4,2,3,1};
	
	printaa(a,8);
	cout<<endl;
	Mergesort(a,0,7);
	cout<<"���������к�����飺"<<endl;
	printaa(a,8);
	cout<<endl;
	return 0;
}