#include <iostream>
using namespace std;
//归并排序
template <typename Type>
void Merge(Type L[],int low,int mid,int high){//假设L[]前半部分L[low]---L[mid]有序，L[]后半部分L[mid+1]---L[high]有序，现在将L[]数组排序，默认序列为【升序】，为了使空间复杂度最小，我采用插入法。
	Type temp;int i;
	while(mid>=low&&high>mid){					//将前半段的每个数据，从后往前，逐个地插入到后半段的相应位置。【此条件如何缺少其中之一或不是并逻辑将出错！】
		if(L[mid]<=L[high])high--;
		else{
			temp=L[mid];
			for(i=mid;i<high;i++){			//后半段的数据前移动一位，腾出1个位置，给L[mid]
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
											//L[high]放大数据
		if(L[high]>=L[flag])mini=L[flag];	//mini存两个比较中较小的数据
		else
		{
			mini=L[high];					//mini存两个比较中较小的数据
			L[high]=L[flag];
		}
		high--;								//L[]后半段中次大的数据
		
		if(mini>L[high]){					//因为mini肯定大于等于前半段所有的数据，所以比较mini与L[high]
			L[flag]=L[high];				//利用L[flag]交换mini与L[high]
			L[high]=mini;					//把大数据始终放在L[high]位置
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
	//待排列数组分段
	while(i+2*len<=n){					//条件是i+2*len-1<n-1，
		Merge(L,i,i+len-1,i+2*len-1);
		i+=2*len;
	}
	if(i+len-1<n-1){					//最后一段，中间点小于n-1，但是后半段长度又小于len
		Merge(L,i,i+len-1,n-1);
	}
	else{
		Merge(L,0,i-1,n-1);
	}
	
	/*
	else
	{
		同一数组内，最后小于len的部分无需复制到数组中【此说法错误】
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
//分而治之——递归合并算法
void myMergeSort(int L[], int left, int right)
{
	if(left >= right)return;
	//分治
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