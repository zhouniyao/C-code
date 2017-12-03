#include <iostream>
using namespace std;
//�鲢����
template <typename Type>
void Merge(Type L[],int low,int mid,int high){//����L[]ǰ�벿��L[low]---L[mid]����L[]��벿��L[mid+1]---L[high]�������ڽ�L[]��������Ĭ������Ϊ�����򡿣�Ϊ��ʹ�ռ临�Ӷ���С���Ҳ��ò��뷨��
	Type temp;int i;
	while(mid>=low&&high>mid){					//��ǰ��ε�ÿ�����ݣ��Ӻ���ǰ������ز��뵽���ε���Ӧλ�á������������ȱ������֮һ���ǲ��߼���������
		if(L[mid]<=L[high])high--;
		else{
			temp=L[mid];
			for(i=mid;i<high;i++){			//���ε�����ǰ�ƶ�һλ���ڳ�1��λ�ã���L[mid]
				L[i]=L[i+1];
			}
			L[high]=temp;
			mid--;
			high--;
		}
	}
}


	/*
	int flag=mid;
	Type mini;
	while(){
											//L[high]�Ŵ�����
		if(L[high]>=L[flag])mini=L[flag];	//mini�������Ƚ��н�С������
		else
		{
			mini=L[high];					//mini�������Ƚ��н�С������
			L[high]=L[flag];
		}
		high--;								//L[]�����дδ������
		
		if(mini>L[high]){					//��Ϊmini�϶����ڵ���ǰ������е����ݣ����ԱȽ�mini��L[high]
			L[flag]=L[high];				//����L[flag]����mini��L[high]
			L[high]=mini;					//�Ѵ�����ʼ�շ���L[high]λ��
			mini=L[flag];
		}
		flag--;
	}
	*/
/*
template <typename Type>
void Merge(Type L[],int low,int mid,int high){
	
}
*/
template <typename Type>
void MergePass(Type L[],int n,int len){
	int i=0;
	//����������ֶ�
	while(i+2*len<=n){					//������i+2*len-1<n-1��
		Merge(L,i,i+len-1,i+2*len-1);
		i+=2*len;
	}
	if(i+len-1<n-1){					//���һ�Σ��м��С��n-1�����Ǻ��γ�����С��len
		Merge(L,i,i+len-1,n-1);
	}
	else{
		Merge(L,0,i-1,n-1);
	}
	
	/*
	else
	{
		ͬһ�����ڣ����С��len�Ĳ������踴�Ƶ������С���˵������
	}
	*/
}

template <typename Type>
void MergeSort(Type L[],int n){
	int len=1;
	while(len<n/2+1){
		MergePass(L,n,len);
		len*=2;
	}
}

void show(int a[],int n){
	for(int i=0;i<n;i++){
		cout<<a[i]<<"  ";
	}
	cout<<endl;
}
//�ֶ���֮�����ݹ�ϲ��㷨
void myMergeSort(int L[], int left, int right)
{
	if(left >= right)return;
	//����
	int mid = (left + right)/2;
	myMergeSort(L, left, mid);
	myMergeSort(L, mid+1, right);
	Merge<int>(L, left, mid, right);
}


int main(){

	//int a[]={2,4,6,8,10,1,3,5,7,9};
	int a[]={12,4,36,28,10,18,31};
	show(a,7);	
//	MergePass(a,10,1);
	myMergeSort(a,0,6);
	show(a,7);	
	
	return 0;
}